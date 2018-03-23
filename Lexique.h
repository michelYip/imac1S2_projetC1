/*@uthor : CRUVEILLIER Marie & YIP Michel*/
#ifndef __LEXIQUE__
#define __LEXIQUE__

#include <string.h>
#include <unistd.h>
#include "arbreLexical.h"

/* Construit un arbre lexical depuis un fichier d'entrée */
void createTreeFromText(Arbre * tree, char * in);

/* Construit un arbre lexical depuis un fichier .DICO */
void createTreeFromDICO(Arbre * tree, char * in);

/* Construit un fichier .L à partir de l'arbre en paramètre */
void createLexique(FILE * f, Arbre tree);

/* Construit un fichier .DICO à partir de l'arbre en paramètre */
void createDict(FILE * f, Arbre tree);

/* Construit un fichier .L ou .DICO à partir d'un arbre lexical en entrée */
void createFileFromTree(Arbre tree, char * out, int flag);

#endif