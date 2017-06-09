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




typedef struct mineur
{
  
  mot_t * ptete;

  unsigned int NbElement;

}mineur_t;

typedef mineur_t * table_t[HASH_MAX];




void IntialiseTableMajeure(table_t *);

void LibererSousTable(mineur_t **);

void LibererTable(table_t *);

void LectureFichier(char *, table_t *, enum bool *);

void InsertionChainee (mot_t **, mot_t *);

void SuppressionChainee(mot_t **);

unsigned int hash_string(const char *);

mot_t ** RechercheEntree(char *, enum bool *, table_t *, unsigned int);

void CreationTable(FILE *, table_t *, enum bool *, enum bool *);

float LongeurMoyenne(table_t *);

void TraductionMot(char *, table_t *);

void TraductionExpression(char *, table_t *);










#endif
