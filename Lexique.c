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
	FILE * fp = fopen(in, "r");
	char * word;
	if ((word = malloc(sizeof(char)*MAXLENGHT)) == NULL){
		fprintf(stderr,"Error : could not malloc node, abort program...\n");
		exit(EXIT_FAILURE);
	}
	/* Boucle infinie oups */
	while(fp){
		fscanf(fp, " %s ", word);
		printf("Adding %s :\n", word);
		addWord(tree, word);
	}
	fclose(fp);
}
