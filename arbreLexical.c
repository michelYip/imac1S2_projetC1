/*@uthor : CRUVEILLIER Marie & YIP Michel*/
#include "arbreLexical.h"


/* Initialise un Arbre tree avec la valeur c en paramètre */
void initTree(Arbre * tree, unsigned char c){
	Arbre tmp;
	if ((tmp = malloc(sizeof(Noeud))) == NULL){
		fprintf(stderr,"Error : could not malloc node, abort program...\n");
		exit(EXIT_FAILURE);
	}
	tmp -> lettre = c;
	tmp -> filsg  = NULL;
	tmp -> frered = NULL;
	*tree = tmp;
}

/* Ajoute dans l'arbre lexical tree la branche word correspondant au mot à ajouter */
void addBranch(Arbre * tree, unsigned char * word){
	initTree(tree, *word);
	if (tree != NULL){
		if (*word != '\0')
			addBranch(&(*tree)->filsg, word+1);
	}
}

/* Ajoute dans l'arbre lexical tree le mot word en paramètre */
void addWord(Arbre * tree, unsigned char * word){
	if (*tree == NULL)
		addBranch(tree, word);
	else {
		if ((*tree)->lettre < *word)
			addWord(&(*tree)->frered, word);
		else{
			if (((*tree)->lettre == *word) && (*word != '\0'))
				addWord(&(*tree)->filsg, word+1);
			else{
				Arbre tmp = NULL;
				addBranch(&tmp, word);
				tmp->frered = (*tree);
				(*tree) = tmp;
			}
		}
	}
}

/* Affiche tout les mots de l'arbre lexical tree en paramètre */
void printDictionnary(Arbre tree){
	static unsigned char buffer[MAXLENGTH];
	static int index = 0;
	if (tree != NULL){
		buffer[index++] = tree->lettre;
		if (tree->lettre == '\0')
			printf("%s\n", buffer);
		else
			printDictionnary(tree->filsg);
		index--;
		if (tree->frered != NULL)
			printDictionnary(tree->frered);
	}
}

/* 
Affiche le résultat de recherche du mot word dans l'arbre tree en paramètre,
la fonction renvoie :
- 1 Si le mot est présent dans l'arbre
- 0 Sinon
*/
int search(Arbre tree, unsigned char * word){
	if (tree == NULL || *word < tree->lettre)
		return 0;
	if (*word == tree->lettre){
		if (*word == '\0')
			return 1;
		return search(tree->filsg, word +1);
	}
	return search(tree->frered, word);

}

