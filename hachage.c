/*---------------------------------------------------------------------------------------------*/
/*                                                                                             */
/*                                        hachage.c                                            */
/*                                                                                             */
/* Role : Définition des fonctions et procédures permettant gestion de la table de hachage.    */
/*                                                                                             */
/*---------------------------------------------------------------------------------------------*/ 



#include "./hachage.h"






/*------------------------------------------------------------------------------------------------*/
/* InsertionChainee         Insère une nouvelle une cellule dans la liste chainée.                */ 
/*									                          */ 
/* En entrée             : adpt - Pointeur de pointeur de tete de liste chainée ou pointeur sur la*/
/*                                case pointeur de l'élément précédent.                           */ 
/*	                   pcour - Pointeur sur le élément à insérer.                             */
/*                                                              				  */
/* En sortie             : adpt - Pointeur de pointeur de tete de liste chainée ou pointeur sur la*/
/*                                case pointeur de l'élément précédent.                           */
/*                                                                                                */
/* Variable(s) locale(s) :        Rien en variable locale                                         */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/

   
void InsertionChainee (mot_t ** adpt, mot_t * pcour)
{

  paction->paction_suiv = *ppaction;

  *ppaction = paction;

}




/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* LectureFichier          Permet d'ouvrir un fichier, créer la table de hachage indirect et     */
/*                         d'insérer chaque ligne du fichier dans la sous table apropriée.       */
/*                                                                                               */
/* En entrée             : NomFichier   - Pointeur sur chaine de caractères.                     */
/*                         PcodeLecture - Pointeur sur une case mémoire contenant vrai si la     */
/*                                        lecture c'est bien passée et faux sinon.               */
/*                                                                                               */
/* En sortie             : PcodeLecture - Pointeur sur une case mémoire contenant vrai si la     */
/*                                        lecture c'est bien passée et faux sinon.               */
/*                                                                                               */
/* Variable(s) locale(s) : chaine       - Pointeur sur une chaine de caractères.                 */
/*                         f            - Pointeur sur un fichier.                               */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


void LectureFichier(char * NomFichier, enum bool * PcodeLecture)
{

  char * chaine = (char *)malloc(TAILLECHAINE * sizeof(char));

  FILE * f = fopen(NomFichier, "r");

  enum bool CodeCreation;

  mot_t * pmot = NULL;

  *PcodeLecture = vrai;                                      /*on suppose que la lecture va bien se passé*/

  if(f && chaine)                                                /*si l'ouverture du fichier à réussi*/
    {

      do
	{

	  LectureLigneFichier(f, chaine, PcodeLecture);

	  pmot = CreationMot(chaine, &CodeCreation);

	  /*calculer le hachage*/

	  /*inserer dans la table de hachage*/

	  

	}while(*PcodeLecture && CodeCreation);                                   /*tantque je ne suis pas à la fin de la lecture*/

    }

}
      



/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/**/
/*                                                                                               */
/* En entrée             :*/
/*                                                                                               */
/* En sortie             :*/
/*                                                                                               */
/* Variable(s) locale(s) :*/
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/
