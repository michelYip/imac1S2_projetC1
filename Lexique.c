/*@uthor : CRUVEILLIER Marie & YIP Michel*/
#include "Lexique.h"

int main(int argc, char ** argv){
	Arbre dict;
/*
	printf("Creating dictionnary...\n");

	createTreeFromText(&dict, "test.txt");
	printf("Printing dictionnary...\n");
	printDictionnary(dict);

	printf("Creating Dictionnary from dict...\n");
	createFileFromTree(dict, "dico", 1);
	createFileFromTree(dict, "lexique", 0);

	printf("End of program...\n");

	return 1;
*/
/*
	printf("Affichage de l'arbre lexicographique ... \n");
	addWord(&dict, (unsigned char *)"ce");
	addWord(&dict, (unsigned char *)"ces");
	addWord(&dict, (unsigned char *)"des");
	addWord(&dict, (unsigned char *)"le"); 
	addWord(&dict, (unsigned char *)"les");
	addWord(&dict, (unsigned char *)"lettre");
	addWord(&dict, (unsigned char *)"mes");
	addWord(&dict, (unsigned char *)"mettre");
	printDictionnary(dict);	

	printf("Creating Dictionnary from dict...\n");
	createFileFromTree(dict, "dico", 1);
	return 1;
*/
	/* TODO :*/
	if (argc > 3 || argc < 2){
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
			printf("This file exist !\n");
		} else {
			printf("This file does not exist ! \n");
			/* ---- file does not exist ---- */
		}
	}
	else if (argc <= 3){
		/*
		Vérification de l'option :
			si -S : 
				reconstruction d'un arbre depuis argv[1] 
				puis d'un fichier .DICO vers argv[1].DICO
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


/* TODO : */
/* Construit un fichier .L à partir de l'arbre en paramètre */
void createLexique(FILE * f, Arbre tree){
	return;
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