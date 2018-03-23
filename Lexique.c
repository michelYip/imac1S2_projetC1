/*@uthor : CRUVEILLIER Marie & YIP Michel*/
#include "Lexique.h"

int main(int argc, char ** argv){
	Arbre dict = NULL;

	if (argc > 4 || argc < 2){
		/*
		Erreur : nombre de paramètre invalide
		*/
		fprintf(stderr, "Invalid number of argument ...\n");
		exit(EXIT_FAILURE);
	}
	else if (argc == 2){
		/*
		Vérifier si le fichier argv[1] existe :
			- le fichier existe, afficher le menu + traitement
			- le fichier n'existe pas, quitter le programme
		*/
		if (access(argv[1], F_OK) != -1){
			/* ---- file exist ---- */
			
			/* Verification si le dico existe, construit l'arbre en fonction : à mettre dans une fonction */
				char * token, * ext, * DICOFile = NULL, * filename;
				
				if((filename = malloc(sizeof(char)*strlen(argv[1]))) == NULL){
					fprintf(stderr, "Could not allocate memory in searchForDICOFile : abort...\n");
					exit(EXIT_FAILURE);
				}
				strcpy(filename, argv[1]);
				token = strtok(argv[1],".");
				while (token != NULL){
					ext = token;
					token = strtok(NULL, ".");
				}
				if (strcmp(ext, "DICO") == 0){
					printf("The dico exist !\nCreating tree from dico : %s\n", filename);
					createTreeFromDICO(&dict, filename);
				} else {
					if ((DICOFile = malloc(sizeof(char)*(strlen(argv[1])+5))) == NULL){
						fprintf(stderr, "Could not allocate memory in searchForDICOFile : abort...\n");
						exit(EXIT_FAILURE);
					}
					sprintf(DICOFile, "%s.DICO", filename);
					if (access(DICOFile, F_OK) != -1){
						printf("The dico exist !\nCreating tree from dico : %s\n", DICOFile);
						createTreeFromDICO(&dict, DICOFile);
					} else {
						printf("The dico does not exist !\nCreating tree from file : %s\n",filename);
						createTreeFromText(&dict, filename);
					}
				}
			/* Fin vérification */

			Menu();

		} else {
			/* ---- file does not exist ---- */
			fprintf(stderr,"File doesn't exist, cannot do any operation : abort program...\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (argc <= 4){
		/*
		Vérification de l'option :
			si -S : 
				reconstruction d'un arbre depuis argv[2] 
				puis d'un fichier .DICO vers argv[2].DICO
			sinon
				si -r : 
					reconstitution d'un arbre depuis argv[3].DICO s'il existe, argv[3] sinon 
					traitement de recherche de argv[2] dans l'arbre
				sinon : 
					reconstitution d'un arbre depuis argv[2].DICO s'il existe, argv[2] sinon 
					traitement 
						si -l : affichage du lexique
						si -s : sauvegarde du lexique vers argv[2].L
		*/
	}

	return 1;
} 

/* Fais afficher un menu */
void Menu(){
	int i;
	printf("  ");
	for(i=0;i<13;i++)
		printf("_ _");
	printf("\n\n | Voir la liste triée..........Taper 1 |");
	printf("\n\n | Sauvegarder liste triée......Taper 2 |");
	printf("\n\n | Rechercher un mot............Taper 3 |");
	printf("\n\n | Sauvegarder l'arbre..........Taper 4 |\n");
	printf("  ");
	for(i=0;i<13;i++)
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







