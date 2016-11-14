#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "calcul.h"

int main()
{
  
  affichage_thread_disponnible();
  
  printf("\n###### RECHERCHE NOMBRE PREMIER ######\n\n");

  calcul_nombre_premier();
  
  return 0;
}
