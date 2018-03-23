/*@uthor : CRUVEILLIER Marie & YIP Michel*/
#include "Lexique.h"

int main(int argc, char ** argv){
	Arbre dict;


	printf("Creating dictionnary...\n");

	createTreeFromFile(&dict, "test.txt");
	printf("Printing dictionnary...\n");
	printDictionnary(dict);

	printf("End of program...\n");

	return 1;


/*
	printf("Affichage de l'arbre lexicographique ... \n");
	addWord(&dict, "Hola");
	addWord(&dict, "àllo");
	addWord(&dict, "Buonjuorno");
	addWord(&dict, "Ni Hao"); 
	addWord(&dict, "Namaste");
	addWord(&dict, "Thank You");
	addWord(&dict, "àrigato");
	addWord(&dict, "Xie Xie");
	addWord(&dict, "Bo Bun");
	addWord(&dict, "Hello");
	addWord(&dict, "Gracias");
	addWord(&dict, "Kam sa");
	addWord(&dict, "Ah Niong");
	addWord(&dict, "été");
	addWord(&dict, "à");
	addWord(&dict, "ôla");
	addWord(&dict, "è.é è.é");
	addWord(&dict, "'");

	printDictionnary(dict);

	printf("\"Guten Tag\" est présent dans le dictionnaire : %d\n",search(dict,"Guten Tag"));
	printf("\"Bruh\" est présent dans le dictionnaire : %d\n",search(dict,"Bruh"));
	
	return 1;
*/
} 

/* Construit un arbre lexical depuis un fichier d'entrée */
void createTreeFromFile(Arbre * tree, char * in){
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
/* Construit un lexique à partir d'un arbre lexical en entrée */
void createFileFromTree(Arbre tree, char * out, int flag);

/* Construit un fichier .L à partir de l'arbre en paramètre */
void createLexique(FILE * f, Arbre tree);

/* Construit un fichier .DICO à partir de l'arbre en paramètre */
void createDict(FILE * f, Arbre tree);



