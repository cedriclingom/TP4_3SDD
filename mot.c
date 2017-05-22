/*---------------------------------------------------------------------------------------------*/
/*                                                                                             */
/*                                           mot.c                                             */
/*                                                                                             */
/* Role : Définition des fonctions et procédures permettant la manipulation des mots.          */
/*                                                                                             */
/*---------------------------------------------------------------------------------------------*/ 






#include "./mot.h"




/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* AlloactionMot            Alloue le bloc devant contenir la valeur du mot et sa traduction et  */
/*                          un pointeur sur le suivant.                                          */
/*                                                                                               */
/* En entrée             :        Rien en entrée                                                 */
/*                                                                                               */
/* En sortie             : pmot - R'envoie l'adresse du bloc alloué.                             */
/*                                                                                               */
/* Variable(s) locale(s) : pmot - Pointeur sur le bloc mot alloué.                               */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


mot_t * AllocationMot()
{

  mot_t * pmot = (mot_t *)malloc(sizeof(mot_t));

  pmot->valeur = NULL;

  pmot->traduction = NULL;

  pmot->suivant = NULL;

  return pmot;

}


/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* LectureLigneFichier          Lit une ligne du fichier texte.                                  */
/*                                                                                               */
/* En entrée             : f            - Pointeur sur un fichier.                               */
/*                         PcodeLecture - Pointeur sur une case contenant vrai si la lecture est */
/*                                        c'est bien passé et faux si on est en fin de lecture.  */
/*                                                                                               */
/* En sortie             : PcodeLecture - Pointeur sur une case contenant vrai si la lecture est */
/*                                        c'est bien passé et faux si on est en fin de lecture.  */
/*                                                                                               */
/* Variable(s) locale(s) : chaine - Une chaine de caractères qui est la ligne lu.                */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


void LectureLigneFichier(FILE * f, char * chaine, enum bool * PcodeLecture)
{

  *PcodeLecture = vrai;

  if(!fgets(chaine, TAILLECHAINE, f))  /*si on est pas à la fin de la lecture*/
    {

      *PcodeLecture = faux;

    }
  
}


/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* CreationMot             Créer un cellule devant contenir un mot et sa traduction.             */
/*                                                                                               */
/* En entrée             : chaine        - Pointeur sur une chaine de caractères.                */
/*                         PcodeCreation - Pointeur sur une case mémoire contenant vrai si la    */
/*                                         création c'est passé et faux sinon.                   */
/*                                                                                               */
/* En sortie             : PcodeCreation - Pointeur sur une case mémoire contenant vrai si la    */
/*                                         création c'est passé et faux sinon.                   */
/*                         pmot          - Retourne l'adresse de la cellule contenant devant     */
/*                                         contenir le mot et ça traduction.                     */
/*                                                                                               */
/* Variable(s) locale(s) : long          - Longeur d'une chaine de caractères.                   */
/*                         pmot          - pointeur sur la cellule contenant devant contenir le  */
/*                                         le mot et ça traduction.                              */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


mot_t * CreationMot(char * chaine, enum bool * PcodeCreation)
{

  int longeur;

  char * copie = (char *)malloc(TAILLECHAINE * sizeof(char));

  mot_t * pmot = AllocationMot();

  *PcodeCreation = faux;            /*on suppose que la création pourrai mal se passer*/

  if(pmot && copie)                          /*si alloué*/
    {

      strcpy(copie, chaine);

      pmot->valeur = strtok(copie, ";");

      copie = NULL;

      if(pmot->valeur)                                   /*si l'extraction du mot à été effectué*/
	{

	  longeur = strlen(pmot->valeur);

	  pmot->traduction = strtok((chaine + longeur + 1), "\n");

	  if(pmot->traduction)                           /*si l'extraction de la traduction a été effectué*/
	    {

	      *PcodeCreation = vrai;

	    }
	  else
	    {

	      printf("Erreur de création!\n");

	      free(pmot->valeur);

	      free(pmot);

	    }

	}
      else
	{
	  
	  printf("Erreur de création!\n");

	  free(pmot);

	}

    }

  return pmot;

}





/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/**/
/**/
/* En entrée:*/
/**/
/* En sortie:*/
/**/
/* Variable(s) locale(s):*/
/**/
/*-----------------------------------------------------------------------------------------------*/
