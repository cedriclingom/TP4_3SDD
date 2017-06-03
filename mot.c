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
/* LongeurMot              Calcule la longueur d'un possédant un délimiteur.                     */
/*                                                                                               */
/* En entrée             : chaine     - Pointeur sur une chaine de caractères.                   */
/*                         delimiteur - Le délimiteur qui est un caractère.                      */
/*                                                                                               */
/* En sortie             : longeur    - Retourne la longueur de ce mot délimiter.                */
/*                                                                                               */
/* Variable(s) locale(s) : i          - Variable de boucle.                                      */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


int LongeurMot(char * chaine, char delimiteur)
{

  static int i, longeur;

  i = 0;
  
  while(chaine[i] != delimiteur)                  /*tantque l'on a pas atteint le délimiteur*/
    {

      ++i;
    }

  longeur = i;

  return longeur;

}


/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* CopieMot                Copie un mot délimiter d'une source vers une destination.             */
/*                                                                                               */
/* En entrée             : src        - Source du mot à copier.                                  */
/*                         dest       - Destination du mot à copier.                             */
/*                         delimiteur - Délimiteur qui est un caractère.                         */
/*                                                                                               */
/* En sortie             : dest       - Destination du mot à copier.                             */
/*                                                                                               */
/* Variable(s) locale(s) : i          - Variable de boucle.                                      */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


void CopieMot(char * dest, char * src, char delimiteur)
{

  static int i;
  
  i = 0;

  while(src[i] != delimiteur)       /*tantque l'on a pas atteint le délimiteur*/
    {

      dest[i] = src[i];

      ++i;

    }

  dest[i] = '\0';

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
  
 static int longeur1, longeur2;
 
 mot_t * pmot = AllocationMot();
 
  longeur1 = 0;
  
  longeur2 = 0;
  
  *PcodeCreation = faux;            /*on suppose que la création pourrai mal se passer*/
  
  if(pmot)                          /*si alloué*/
    {

      longeur1 = LongeurMot(chaine, ';');

      pmot->valeur = (char *)malloc((longeur1 + 1) * sizeof(char));

      if(pmot->valeur)                                   /*si l'alloctaion à marcher*/
	{

	  CopieMot(pmot->valeur, chaine, ';');           /*je copie le mot*/

	  longeur2 = strlen(&chaine[longeur1 + 1]);

	  pmot->traduction = (char *)malloc((longeur2 +1) * sizeof(char));

	  if(pmot->traduction)                           /*si l'allocation à marcher*/
	    {

	      strcpy(pmot->traduction, &chaine[longeur1 + 1]); 

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

  /*printf("%s;%s\n", pmot->valeur, pmot->traduction);*/

  return pmot;

}


/*-------------------------------------------------------------------------------------------------------------------------*/
/* RechercheMot        Recherche un mot dans la liste chainée des mots.                                                    */
/*                                                                                                                         */
/* En entrée:     PpteteListe - Pointeur de pointeur de tête de la liste chainée des mots.                                 */
/*                    pvaleur - Pointeur sur le mot à rechercher (qui est une chaine de caractères).                       */
/*                   ptrouver - booleen 1 si le mot est trouvé 0 sinon                                                     */
/*                                                                                                                         */
/* En sortie:            prec - Retourne l'adresse du pointeur de tete de liste chainée des mot ou l'adresse de la         */
/*                              case pointeur de l'élément précédent dans la liste chainée de mots.                        */
/*                   ptrouver - booleen 1 si le mot est trouvé 0 sinon                                                     */
/*                                                                                                                         */
/* Variable(s) locale(s):   pcour - Pointeur sur le mot courante.                                                          */
/*                          prec  - Pointeur de pointeur de tete de liste chainée des mot ou pointeur sur la case          */
/*                                  pointeur de l'élément précédent de la liste chainée des mot.                           */
/*-------------------------------------------------------------------------------------------------------------------------*/


mot_t **  RecherchePrec (mot_t ** PpteteListe, char * pvaleur, enum bool * ptrouver)
{

  static mot_t * pcour, ** prec; 

  pcour = *PpteteListe;

  prec = PpteteListe;

  *ptrouver = faux;

  while   ((pcour != NULL) && (strcmp(pvaleur, pcour->valeur) > 0)) /*Tantque je suis dans la liste et que ma chaine est plus grande*/
    {
      
      prec = &(pcour->suivant);                                    /*On récupère l'adresse de la case pointeur de l'élément courant*/
      
      pcour = *prec;                                                 /*Passe au suivant*/
      
    }

  if ((pcour != NULL) && (!strcmp(pvaleur, pcour->valeur)))         /*Si on trouve la chaine*/
    {

      *ptrouver = vrai;

    }

  return prec;

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
