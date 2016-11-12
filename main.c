#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
  int nombre_thread;
  int id_thread;

  int nombre = 0;
  int diviseur = 0;
  int est_premier = 0;
  int nombre_de_premier = 0;

  const int nombre_max = 30;
  const int nombre_min = 2;



  #pragma omp parallel private(id_thread)             // id_thread est privé pour chaque thread (chaque thread a son id)
  {
      #pragma omp master                              // seul le thread principal execute cette partie
      {
          nombre_thread = omp_get_num_threads();      // recupère le nombre de thread disponnible
          printf("Nombre de thread disponnible: %d\n",nombre_thread);
      }

      #pragma omp barrier                             // attendre que tout les thread soit au meme niveau

      id_thread = omp_get_thread_num();               // chaque thread remplis ça variables (id_thread) par son id
      #pragma omp critical                            // chaque thread execute cette partie chacun son tour
      {
          printf("Thread N° %d pret\n",id_thread);
      }
  }

  printf("\n###### RECHERCHE NOMBRE PREMIER ######\n\n");

  #pragma omp parallel for private(diviseur,est_premier,id_thread) schedule(dynamic) reduction(+:nombre_de_premier)
  for(nombre = nombre_min; nombre <= nombre_max ; nombre++)
  {
      est_premier = 1; // est premier
      diviseur = nombre_min; // diviseur = 2

      while(diviseur < nombre && est_premier) // si diviseur < nombre et est premier
      {
          if(nombre % diviseur == 0) // si le reste du nombre / diviseur = 0
              est_premier = 0; // il n'est pas premier

          diviseur++; // on augmente le diviseur de 1 et on recommence
      }

      // Add n to the list
      id_thread = omp_get_thread_num();
      if(est_premier)
      {
          #pragma omp critical   // afficher resultat chacun son tour
          {
              printf("Thread N° %d a trouve: %d\n",id_thread,nombre);
          }
          nombre_de_premier++;
      }
  }
  return 0;
}
