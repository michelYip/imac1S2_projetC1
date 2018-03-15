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
	addWord(&dict, "Allo");
	addWord(&dict, "Buonjuorno");
	addWord(&dict, "Ni Hao"); 
	addWord(&dict, "Namaste");
	addWord(&dict, "Thank You");
	addWord(&dict, "Arigato");
	addWord(&dict, "Xie Xie");
	addWord(&dict, "Bo Bun");
	addWord(&dict, "Hello");
	addWord(&dict, "Gracias");
	addWord(&dict, "Kam sa");
	addWord(&dict, "Ah Niong");
	addWord(&dict, "Guten Tag");

	printDictionnary(dict);

	printf("\"Guten Tag\" est présent dans le dictionnaire : %d\n",search(dict,"Guten Tag"));
	printf("\"Bruh\" est présent dans le dictionnaire : %d\n",search(dict,"Bruh"));
	
	return 1;
*/
}

/* Construit un arbre lexical depuis un fichier d'entrée */
void createTreeFromFile(Arbre * tree, char * in){
	FILE * f = fopen(in, "r");
	char str[MAXLENGTH];
	while (fscanf(f, " %s ", str) == 1){
		addWord(tree, str);
	}
	fclose(f);
}
