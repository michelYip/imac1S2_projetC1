/*@uthor : CRUVEILLIER Marie & YIP Michel*/
#include "../h/Lexique.h"

int main(int argc, char ** argv){
	Arbre dict = NULL;
	if (argc > 4 || argc < 2){
		/* Erreur : nombre de paramètre invalide */
		fprintf(stderr, "Invalid number of argument ...\n");
		exit(EXIT_FAILURE);
	}
	else if (argc == 2){
		/* Vérifie si le fichier argv[1] existe */
		if (access(argv[1], F_OK) == -1){
			/* ---- le fichier n'existe pas ---- */
			fprintf(stderr,"File doesn't exist, cannot do any operation : abort program...\n");
			exit(EXIT_FAILURE);
		} else {
			/* ---- Le fichier existe ---- */	
			searchForDICOFile(&dict, argv[1]);
			char input;
			unsigned char searchWord[MAXLENGTH];
			int loop = 1;
			while (loop){
				Menu();
				printf("Choisissez une option :\n");
				scanf("%c", &input);
				fflush(stdin);
				if (input == 'Q'){
					loop = 0;
				} else if (input == '1'){
					printDictionnary(dict);
				} else if (input == '2'){
					createFileFromTree(dict, argv[1], 0);
				} else if (input == '3'){
					printf("Entrez un mot à rechercher dans le lexique :\n");
					scanf("%51s", searchWord);
					printf("word = %s\n",searchWord);
					if (search(dict, searchWord))
						printf("Le mot \"%s\" est présent.\n", searchWord);
					else
						printf("Le mot \"%s\" est absent.\n", searchWord);
				} else if (input == '4'){
					createFileFromTree(dict, argv[1], 1);
				} else {
					printf("Option invalide...\n");
				}
			}
			printf("Fermeture du programme...\n");
			return EXIT_SUCCESS;
		}
	}
	else if (argc <= 4){
		if(strcmp(argv[1],"-S")==0){
			createTreeFromText(&dict,argv[2]);
			createFileFromTree(dict, argv[2],1);
			return EXIT_SUCCESS;
		}
		if(strcmp(argv[1],"-r")==0){
			searchForDICOFile(&dict,argv[3]);
			if (search(dict, (unsigned char *)argv[2]))
				printf("Le mot \"%s\" est présent.\n", argv[2]);
			else
				printf("Le mot \"%s\" est absent.\n", argv[2]);
			return EXIT_SUCCESS;

		}
		searchForDICOFile(&dict,argv[2]);
		if(strcmp(argv[1],"-s")==0){
			createFileFromTree(dict, argv[2],0);
		}
		else if(strcmp(argv[1],"-l")==0){
			printDictionnary(dict);
		}
		
	}

	return EXIT_SUCCESS;
} 

/* Fais afficher un menu */
void Menu(){
	int i;
	printf("  ");
	for(i=0;i<14;i++)
		printf("_ _");
	printf("\n\n | Voir le lexique des mots trié....Taper 1 |");
	printf("\n\n | Sauvegarder le lexique...........Taper 2 |");
	printf("\n\n | Rechercher un mot................Taper 3 |");
	printf("\n\n | Sauvegarder l'arbre..............Taper 4 |");
	printf("\n\n | Quitter le programme.............Taper Q |\n");
	printf("  ");
	for(i=0;i<14;i++)
		printf("_ _");
	printf("\n");
}


/* Construit un arbre lexical depuis un fichier d'entrée */
void createTreeFromText(Arbre * tree, char * in){
	FILE * f = fopen(in, "r");
	unsigned char str[MAXLENGTH];
	int i = 0, j;

	while ((str[i] = fgetc(f)) != (unsigned char)EOF){
		if (str[i] == ' '){
			str[i] = '\0';
			addWord(tree, str);
			i = 0;
			for (j = 0; str[j] != '\0'; j++)
				str[j] = '\0';
		}
		else
			i++;
	}

	fclose(f);
}

/* Construit un arbre lexical depuis un fichier .DICO */
void createTreeFromDICO(Arbre * tree, char * in){
	FILE * f = fopen(in,"r");
	unsigned char str[MAXLENGTH];
	int i = 0;
	while((str[i] = fgetc(f)) != (unsigned char)EOF){
		if (str[i] == ' '){
			str[i] = '\0';
			i--;
			addWord(tree, str);
		}
		if (str[i] == '\n'){
			i--;
		}
		else{
			i++;
		}
	}
	fclose(f);
}

/* Construit un fichier .L à partir de l'arbre en paramètre */
void createLexique(FILE * f, Arbre tree){
	static char buffer[MAXLENGTH];
	static int index = 0;	
	int i;
	if(tree != NULL){
		buffer[index++] = tree->lettre;
		if(tree->lettre == '\0'){
			for(i = 0; buffer[i] != '\0'; i++){
				fputc(buffer[i], f);
			}
			fputc('\n', f);
		}
		else 
			createLexique(f, tree->filsg);
		index--;
		if(tree->frered != NULL)
			createLexique(f, tree->frered);
	}
}	

/* Construit un fichier .DICO à partir de l'arbre en paramètre */
void createDict(FILE * f, Arbre tree){
	if(tree != NULL){
		if (tree->lettre == '\0'){
			fputc(' ', f);
			createDict(f, tree->frered);
		}
		else {
			fputc(tree->lettre, f);
			createDict(f, tree->filsg);
			createDict(f, tree->frered);
		}
	} else{
		fputc('\n', f);
	}
}

/* Construit un lexique à partir d'un arbre lexical en entrée */
void createFileFromTree(Arbre tree, char * out, int flag){
	char * filename;
	FILE * f;
	if ((filename = malloc(sizeof(char)*(strlen(out)+5))) == NULL){
		fprintf(stderr, "Could not allocate memory in createFileFromTree()\n");
		exit(EXIT_FAILURE);
	}

	if (flag)
		sprintf(filename, "%s.DICO", out);
	else
		sprintf(filename, "%s.L", out);

	f = fopen(filename, "w");

	if (flag)
		createDict(f, tree);
	else
		createLexique(f, tree);

	fclose(f);
}

/* 
 * Vérifie d'abord si le fichier file entré en paramètre est un fichier .DICO, si oui créer un arbre avec
 * Sinon vérifie si un fichier file.DICO existe, si oui créer l'arbre avec
 * Sinon créer un arbre avec le texte du fichier file
 */
 void searchForDICOFile(Arbre * tree, char * file){
 	char * token, * ext, * DICOFile = NULL, * filename;
 	if((filename = malloc(sizeof(char)*strlen(file))) == NULL){
 		fprintf(stderr, "Could not allocate memory in searchForDICOFile : abort...\n");
 		exit(EXIT_FAILURE);
 	}

 	strcpy(filename, file);

	/* Vérification de l'extension du fichier */
 	token = strtok(filename,".");
 	while (token != NULL){
 		ext = token;
 		token = strtok(NULL, ".");
 	}
 	if (strcmp(ext, "DICO") == 0){
 		createTreeFromDICO(tree, file);
 	} else {
		/* Vérification de l'existence d'un fichier .DICO */
 		if ((DICOFile = malloc(sizeof(char)*(strlen(file)+5))) == NULL){
 			fprintf(stderr, "Could not allocate memory in searchForDICOFile : abort...\n");
 			exit(EXIT_FAILURE);
 		}
 		sprintf(DICOFile, "%s.DICO", file);
 		if (access(DICOFile, F_OK) != -1)
 			createTreeFromDICO(tree, DICOFile);
 		else
 			createTreeFromText(tree, file);
 	}
 }
