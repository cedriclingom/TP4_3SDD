/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/*                                           main.c                                              */
/*                                                                                               */
/* Role :  Contient notre fonction principale main qui fait à d'autres fonctions et procédurés   */
/*         tels que: LectureFichier, Traduction et LongeurMoyenne permettant des traiments.      */
/*         sur des mots.                                                                         */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/






#include "./hachage.h"





/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* main                    Fonction principale faisant à des fonctions et procédures qui         */
/*                         permettent de lire des mots fichier ainsi que leur traduction et      */
/*                         de stocker dans des tables qui seront ensuite utiliser pour faire des */
/*                         traductions.                                                          */
/*                                                                                               */
/*                                                                                               */
/* En entrée             : argc         - Compte de le nombre d'arguments passés en ligne de     */
/*                                        commande.                                              */
/*                         argv         - Pointeur de pointeur de  chaines caractères qui sont   */
/*                                        rien d'autres que les arguments passés en ligne de     */
/*                                        commande.                                              */
/*                                                                                               */
/* En sortie             :               Rien en sortie.                                         */
/*                                                                                               */
/* Variable(s) locale(s) : CodeLecture  - Variable contenant vrai si la lecture à partir du      */
/*                                        fichier c'est passé et faux sinon.                     */
/*                         TableHashage - Un tableau de pointeur si des tables mineurs.          */ 
/*                         phrase       - Un tableau de caractères qui constitue la phrase à     */
/*                                        traduire.                                              */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/



int main(int argc, char ** argv)
{

  enum bool CodeLecture;

  table_t TableHashage;

  char phrase[80];
  
  if(argc == 2)
    {
      
      LectureFichier(argv[1], TableHashage, &CodeLecture);
      
      if(CodeLecture)                              /*si la lecture c'est bien passée*/
	{
	  
	  printf("La longueur moyenne des sous-tables est: %f\n", LongeurMoyenne(TableHashage));

	  strcpy(phrase, "We often play football on the pitch just behind our school");
	  
	  printf("La trauction de la phrase:\n%s\n", phrase);
	  
	  TraductionExpression(phrase, TableHashage);
	  
	  LibererTable(TableHashage);

	}
      else
	{
	  
	  printf("Erreur dans la lecture du fichier");
	  
	}
      
    }
  else
    {
      
      printf("Erreur vous n'avez pas entrer le bon nombre d'arguments!\n");
      
    }
  
  return 0;
  
}
