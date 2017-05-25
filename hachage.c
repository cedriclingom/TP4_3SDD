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
/*	                   pmot - Pointeur sur le élément à insérer.                             */
/*                                                              				  */
/* En sortie             : adpt - Pointeur de pointeur de tete de liste chainée ou pointeur sur la*/
/*                                case pointeur de l'élément précédent.                           */
/*                                                                                                */
/* Variable(s) locale(s) :        Rien en variable locale                                         */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/

   
void InsertionChainee (mot_t ** adpt, mot_t * pmot)
{

  pmot->suivant = *adpt;

  *adpt = pmot;

}


/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* hash_string             Fonction de hachage qui étant donnée une chaine considérer comme la   */
/*                         clé calcule et nous retourne l'indice de la case au niveau de la table*/
/*                         majeur devant pointer sur la bonne table mineur aproprié.             */
/*                                                                                               */
/* En entrée             : str  - Pointeur sur une chaine de caractères.                         */
/*                                                                                               */
/* En sortie             : hash - L'indice de la table majeur associé à la clé.                  */
/*                                                                                               */
/* Variable(s) locale(s) : hash - Retourne L'indice de la table majeur associé à la clé.         */
/*                         s    - Pointeur sur une chaine de caractères.                         */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


unsigned int hash_string(const char *str)
{ 
  unsigned int hash = 5381;                /*  fonction de hachage de D.J. Bernstein*/
  
  const char *s;
  
  for (s = str; *s; s++)
  
 	 hash = ((hash << 5) + hash) + tolower(*s);
 	 
  return (hash & 0x7FFFFFFF)% HASH_MAX;
  
}





/*-------------------------------------------------------------------------------------------------------------------------*/
/* RechercheEntree              Recherche un mot dans le dictionnaire.                                                     */
/*                                                                                                                         */
/* En entrée:     TableHachage- L'adresse de la premiere case dans notre table majeur                                      */
/*                   pmot     - Pointeur sur le mot à rechercher (qui est une chaine de caractères).                       */
/*                   ptrouver - booleen 1 si le mot est trouvé 0 sinon                                                     */
/*                                                                                                                         */
/* En sortie:            prec - Retourne l'adresse du pointeur de tete de liste chainée des mot ou l'adresse de la         */
/*                              case pointeur de l'élément précédent dans la liste chainée de mots.                        */
/*                   ptrouver - booleen 1 si le mot est trouvé 0 sinon                                                     */
/*                                                                                                                         */
/* Variable(s) locale(s) :   IndiceHach - l'indice du mot à chercher dans table majeur donné par la fonction hash_string.  */
/*                          Ppteteliste  - Pointeur de pointeur de tete de liste chainée des mot                           */
/*-------------------------------------------------------------------------------------------------------------------------*/



mot_t ** RechercheEntree(char * pmot, enum bool * ptrouver, table_t TableHachage)
{
  unsigned int IndiceHach = hash_string(pmot);
  
  mot_t ** Ppteteliste = &(TableHachage[IndiceHach]);
  
  mot_t ** prec = RecherchePrec(Ppteteliste, pmot, ptrouver);
  
  return prec;
}







void CreationTable(FILE * f, table_t hash, enum bool * PcodeLecture, enum bool * PcodeCreation)
{

  enum bool trouver;

  char * chaine = (char *)malloc(TAILLECHAINE * sizeof(char));

  mot_t ** prec = NULL, * pmot = NULL;

  *PcodeLecture = vrai;

  *PcodeCreation = vrai;

  if(chaine)                                                                    /*si allocation de la chaine*/
    {

      do
	{
	  
	  LectureLigneFichier(f, chaine, PcodeLecture);
	  
	  if(*PcodeLecture)
	    {
	      
	      pmot = CreationMot(chaine, PcodeCreation);
	      
	      if(*PcodeCreation)                            /* si la création à reussi*/
		{
		  
		  prec = RechercheEntree(pmot->valeur, &trouver, hash);
		  
		  if(!trouver)
		    {
		      
		      InsertionChainee(prec, pmot);
		      
		    }
		  
		}
	      
	    }      	  
	  
	}while(*PcodeLecture && *PcodeCreation);                                   /*tantque je ne suis pas à la fin de la lecture*/ 

    }
  else
    {

      *PcodeCreation = faux;

    }

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
/* Variable(s) locale(s) : CodeCreation - Pointeur sur une case mémoire contenant vrai si la     */
/*                                        création de la table c'est bien passée et faux sinon.  */
/*                         f            - Pointeur sur un fichier.                               */
/*                         hash         - Pointeur sur la table majeur (liste contigue de        */
/*                                        pointeur de tete de liste chainée de mot.              */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


void LectureFichier(char * NomFichier, enum bool * PcodeLecture)
{  

  FILE * f = fopen(NomFichier, "r");

  enum bool CodeCreation;

  table_t hash;

  if(f)                                                      /*si l'ouverture du fichier à réussi*/
    {
      
      CreationTable(f, hash, PcodeLecture, &CodeCreation);

      if(!CodeCreation)                                      /*si erreur dans la création de table*/
	{

	  /*Liberer la table*/

	  *PcodeLecture = CodeCreation;

	}
      else
	{

	  *PcodeLecture = vrai;                               /*la lecture c'est bien passé*/

	}

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
