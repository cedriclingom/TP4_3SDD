/*---------------------------------------------------------------------------------------------*/
/*                                                                                             */
/*                                           mot.h                                             */
/*                                                                                             */
/* Role : Déclarations des directives de préprocésseur, des constantes, des types personnels   */
/*        et des prototypes.                                                                   */
/*                                                                                             */
/*---------------------------------------------------------------------------------------------*/ 

#ifndef _GESTIONNAIRE_APPLICATION_MULTILINGUE_MOT_H
#define _GESTIONNAIRE_APPLICATION_MULTILINGUE_MOT_H







#include <stdio.h>
#include <stdlib.h>
#include <string.h>






#define TAILLECHAINE 40







enum bool{faux, vrai};



typedef struct mot
{

  char * valeur;
  
  char * traduction;

  struct mot * suivant;

}mot_t;








mot_t * AllocationMot();

void LectureLigneFichier(FILE *, char *, enum bool *);

int LongeurMot(char *, char);

void CopieMot(char *, char *, char);

mot_t * CreationMot(char *, enum bool *);

mot_t **  RecherchePrec (mot_t **, char *, enum bool *);






#endif
