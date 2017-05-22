#include "./hachage.h"





int main(int argc, char ** argv)
{

  enum bool CodeLecture;

  if(argc == 2)
    {

      LectureFichier(argv[1], &CodeLecture);

    }
  else
    {

      printf("Erreur vous n'avez pas entrer le bon nombre d'arguments!\n");

    }

  return 0;

}
