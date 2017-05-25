/*---------------------------------------------------------------------------------------------*/
/*                                                                                             */
/*                                        hachage.h                                            */
/*                                                                                             */
/* Role : Déclarations des directives de préprocésseur, des constantes, des types personnels   */
/*        et des prototypes.                                                                   */
/*                                                                                             */
/*---------------------------------------------------------------------------------------------*/ 

#ifndef _GESTIONNAIRE_APPLICATION_MULTILINGUE_HACHAGE_H
#define _GESTIONNAIRE_APPLICATION_MULTILINGUE_HACHAGE_H






#include <ctype.h>
#include "./mot.h"





#define HASH_MAX 29






typedef mot_t * table_t[HASH_MAX];





void LectureFichier(char *, enum bool *);

void InsertionChainee (mot_t **, mot_t *);

unsigned int hash_string(const char *);

mot_t ** RechercheEntree(char *, enum bool *, table_t);

void CreationTable(FILE *, table_t, enum bool *, enum bool *);









#endif
