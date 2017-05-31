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


/*-------------------------------------------------------------------------------------------------------*/
/*                                                                                                       */
/* SuppressionChainee          Supprime un bloc(Dans notre cas contenant un mot et ça traduction.        */ 
/*										     			 */ 
/* En entrée             : adpt  - Pointeur de pointeur de tete de liste chainée ou pointeur sur la case */
/*                                 pointeur de l'élément précédent de la liste chainée.                  */                  
/*                                                                                                       */
/* En sortie             : adpt  - Pointeur de pointeur de tete de liste chainée ou pointeur sur la case */
/*                                 pointeur de l'élément précédent de la liste chainée.                  */
/* Variable(s) locale(s) : pcour - Pointeur sur élément à supprimer.                                     */
/*                                                                                                       */
/*-------------------------------------------------------------------------------------------------------*/


void SuppressionChainee(mot_t ** adpt)
{

  mot_t * pcour = *adpt;     /*recupère l'adresse de l'élément à supprimer*/

  *adpt = pcour->suivant;    /*pointe sur l'élément après l'élément à supprimer*/

  free(pcour);               /*supprime l'élément*/

  pcour = NULL;

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

  static unsigned int hash;                /*  fonction de hachage de D.J. Bernstein*/
  
  const char *s;

  hash = 5381;
  
  for (s = str; *s; s++)
  
 	 hash = ((hash << 5) + hash) + tolower(*s);
 	 
  return (hash & 0x7FFFFFFF)% HASH_MAX;
  
}





/*-------------------------------------------------------------------------------------------------------------------------*/
/* RechercheEntree              Recherche un mot dans le dictionnaire.                                                     */
/*                                                                                                                         */
/* En entrée             : hash       - Tableau de pointeurs de tetes de liste chainées.                                   */
/*                         pvaleur    - Pointeur sur le mot à rechercher (chaine de caractères).                           */
/*                         ptrouver   - Booleen valant vrai si le mot est trouvé faux sinon.                               */
/*                         IndiceHash - L'indice de la table majeur dont le contenu de la case est un pointeur sur une     */
/*                                      liste chainée censé contenir le bloc du mot rechercher.                            */
/*                                                                                                                         */
/* En sortie             : prec       - Retourne l'adresse du pointeur de tete de liste chainée des mot ou l'adresse de la */
/*                                      case pointeur de l'élément précédent dans la liste chainée de mots.                */
/*                         ptrouver   - Booleen valant vrai si le mot est trouvé faux sinon.                               */
/*                                                                                                                         */
/* Variable(s) locale(s) : Ppteteliste - Pointeur de pointeur de tete de liste chainée des mots.                           */
/*-------------------------------------------------------------------------------------------------------------------------*/



mot_t ** RechercheEntree(char * pvaleur, enum bool * ptrouver, table_t hash, unsigned int IndiceHash)
{
  
  static mot_t ** Ppteteliste, ** prec;

  if(!hash[IndiceHash])                        /*si la structure représentant la table mineur n'existe pas*/
    {

      hash[IndiceHash] = (mineur_t *)malloc(sizeof(mineur_t));

      if(hash[IndiceHash])                    /*si l'allocation de la structure à marcher*/
	{

	  hash[IndiceHash]->ptete = NULL;
	  
	  hash[IndiceHash]->NbElement = 0;

	}

    }

  Ppteteliste = &(hash[IndiceHash]->ptete);

  prec = RecherchePrec(Ppteteliste, pvaleur, ptrouver);
  
  return prec;

}







void CreationTable(FILE * f, table_t hash, enum bool * PcodeLecture, enum bool * PcodeCreation)
{

  unsigned int IndiceHash;

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
		  
		  IndiceHash = hash_string(pmot->valeur);

		  prec = RechercheEntree(pmot->valeur, &trouver, hash, IndiceHash);
		  
		  if(!trouver)
		    {
		      
		      InsertionChainee(prec, pmot);

		      (hash[IndiceHash])->NbElement++;
		      
		    }
		  else
		    {
		      
		      SuppressionChainee(&pmot);
		  
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
/* InitialiseTableMajeure  Initialise les cases du tableau à NULL.                               */
/*                                                                                               */
/* En entrée             : hash - Tableau de pointeur sur des structures servant de table mineurs*/
/*                                                                                               */
/* En sortie             :        Rien en sortie.                                                */
/*                                                                                               */
/* Variable(s) locale(s) : i    - Variable de boucle.                                            */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


void IntialiseTableMajeure(table_t hash)
{

  int i;
  
  for(i = 0; i < HASH_MAX; ++i)
    {

      hash[i] = NULL;

    }

}



void LibererTable(table_t hash)
{

  int i = 0;

  for(i = 0; i < HASH_MAX; ++i)
    {
      
      LibererSousTable(&hash[i]);
      
    }
  
}


/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* */
/*                                                                                               */
/* En entrée             :*/
/*                                                                                               */
/* En sortie             :*/
/*                                                                                               */
/* Variable(s) locale(s) :*/
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


void LibererSousTable(mineur_t ** SousTable)
{

  while(((*SousTable) != NULL) && ((*SousTable)->ptete != NULL))  /*tanqu'il existe une sous table et qu'elle n'est pas libérer*/
	{

	  SuppressionChainee(&((*SousTable)->ptete));  /*supprime l'élément en tete de la liste chainée courante*/

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
/*                         hash         - C'est un tableau (table majeure) de pointeur sur des   */
/*                                        tables mineurs.                                        */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


void LectureFichier(char * NomFichier, table_t hash, enum bool * PcodeLecture)
{  

  FILE * f = fopen(NomFichier, "r");

  enum bool CodeCreation;

  IntialiseTableMajeure(hash);

  if(f)                                                      /*si l'ouverture du fichier à réussi*/
    {
      
      CreationTable(f, hash, PcodeLecture, &CodeCreation);

      if(!CodeCreation)                                      /*si erreur dans la création de table*/
	{

	  LibererTable(hash);

	  *PcodeLecture = CodeCreation;

	}
      else
	{

	  *PcodeLecture = vrai;                               /*la lecture c'est bien passé*/

	}
      
      fclose(f);

    }

}
      

/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* LongeurMoyenne          Calcule la longueur moyenne des sous-tables.                          */
/*                                                                                               */
/* En entrée             : hash - C'est un tableau (table majeure) de pointeur sur des           */
/*                                tables mineurs.                                                */
/*                                                                                               */
/* En sortie             : moy  - Retourne la longueur moyenne des sous-tables.                  */
/*                                                                                               */
/* Variable(s) locale(s) : i    - Variable de boucle.                                            */
/*                         longeur - La somme des toutes les longueurs.                          */
/*                         moy  - La longueur moyenne des sous-tables.                           */ 
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/


float LongeurMoyenne(table_t hash)
{

  int i, longeur = 0;

  float moy = 0;

  for(i = 0; i < HASH_MAX; ++i)
    {

      if(hash[i])                   /*si la table mineur existe*/
	{

	  longeur += hash[i]->NbElement;

	}

    }

  moy = (longeur * 1.0)/HASH_MAX;

  return moy;

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
