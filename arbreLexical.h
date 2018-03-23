/*@uthor : CRUVEILLIER Marie & YIP Michel*/
#ifndef __ARBRE_LEXICAL__
#define __ARBRE_LEXICAL__

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 50

typedef struct noeud{
	unsigned char lettre;
	struct noeud * filsg, *frered;
} Noeud, * Arbre;

/* Initialise un arbre lexical tree avec la valeur c en paramètre */
void initTree(Arbre * tree, unsigned char c);

/* Ajoute dans l'arbre lexical tree la branche word correspondant au mot à ajouter */
void addBranch(Arbre * tree, unsigned char * word);

/* Ajoute dans l'arbre lexical tree le mot word en paramètre */
void addWord(Arbre * tree, unsigned char * word);

/* Affiche tout les mots de l'arbre lexical tree en paramètre */
void printDictionnary(Arbre tree);

/* 
Affiche le résultat de recherche du mot word dans l'arbre tree en paramètre,
la fonction renvoie :
- 1 Si le mot est présent dans l'arbre
- 0 Sinon
*/
int search(Arbre tree, unsigned char * word);



/* TODO : */
/* Libère la mémoire allouée par l'arbre tree en paramètre */
void freeTree(Arbre * tree);

#endif