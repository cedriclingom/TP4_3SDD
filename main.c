#include "./hachage.h"





int main(int argc, char ** argv)
{

  enum bool CodeLecture;

  table_t TableHashage;

  if(argc == 2)
    {

      LectureFichier(argv[1], TableHashage, &CodeLecture);

      if(CodeLecture)                              /*si la lecture c'est bien passée*/
	{

	  printf("La longueur moyenne des sous-tables est: %f\n", LongeurMoyenne(TableHashage));
	  
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
