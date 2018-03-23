/*@uthor : CRUVEILLIER Marie & YIP Michel*/
#include "Lexique.h"

int main(int argc, char ** argv){
	Arbre dict = NULL, dico = NULL;

	/* TODO :*/
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
			printf("This file exist !\n");
		} else {
			/* ---- file does not exist ---- */
			fprintf(stderr,"This file does not exist, cannot do any operation on it\n");
			
			/* - Simple test - Begin */
			/*
				printf("Traitement de dict ...\n");
				addWord(&dict, (unsigned char *)"chat");
				addWord(&dict, (unsigned char *)"tournesol");
				addWord(&dict, (unsigned char *)"tournefeuille");
				addWord(&dict, (unsigned char *)"soleil");
				addWord(&dict, (unsigned char *)"sol");
				addWord(&dict, (unsigned char *)"hiver");
				addWord(&dict, (unsigned char *)"tous");
				addWord(&dict, (unsigned char *)"chien");
				addWord(&dict, (unsigned char *)"les");
				addWord(&dict, (unsigned char *)"le");
				addWord(&dict, (unsigned char *)"l");
				addWord(&dict, (unsigned char *)"chateau");
				addWord(&dict, (unsigned char *)"maisons");

				printDictionnary(dict);
			*/
			/*
				printf("%d\n",search(dict,(unsigned char *)"sol"));
				printf("%d\n",search(dict,(unsigned char *)"de"));
			
			
				createFileFromTree(dict,"test",0);
				createFileFromTree(dict,"test",1);

				printf("Traitement de dico ...\n");
				createTreeFromDICO(&dico, "test.DICO");
				printDictionnary(dico);
				createFileFromTree(dict,"test2",1);				
			*/

			/* - Simple test - End */
			
			exit(EXIT_FAILURE);
		}
	}
	else if (argc <= 4){
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







