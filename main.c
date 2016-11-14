#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "calcul.h"

int main()
{
	int nombre_min = 0;
	int nombre_max = 0;
	int c = 0;
  
  affichage_thread_disponnible();

  do
  {
  	printf("Entrez le nombre minimum ( >= 2): ");
  	scanf("%d",&nombre_min);
  } while (nombre_min < 2);

  do
  {
  	printf("Entrez le nombre maximum ( > nombre minimum): ");
  	scanf("%d",&nombre_max);
  } while (nombre_max <= 2);
  
  printf("\n###### RECHERCHE NOMBRE PREMIER ######\n\n");

  calcul_nombre_premier(nombre_min,nombre_max);
  
  return 0;
}
