#include "calcul.h"

void affichage_thread_disponnible()
{
	int nombre_thread;
	int id_thread;

	#pragma omp parallel private(id_thread)           // id_thread est privé pour chaque thread (chaque thread a son id)
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
}

void calcul_nombre_premier(int nombre_min, int nombre_max)
{

	int nombre_thread = 0;
  	int id_thread = 0;

  	int nombre = 0;
  	int diviseur = 0;
  	int est_premier = 0;
  	int nombre_de_premier = 0;

	/******* EXPLICATION omp parallel for private() shedule() reduction() *********/

	/* private -> variables prive a chaque thread, chaque thread aura SA variable
	 * innaccessible par les autres thread, on la qualifie donc de prive
	 */

	// shedule -> odre d'execution des thread (ici dynamic car l'odre n'a pas d'importance)

	/* reduction -> nombre_de_premier est prive a chaque thread donc on les
	 * additione ( reduction(+:) ) pour avoir le total du nombre de premier
	 * nombre_de_premier(thread 0) + nombre_de_premier(thread 1) +
	 * nombre_de_premier(thread 2)+ nombre_de_premier(thread 3)  = nombre_de_premier(total)
	 */
  	
	#pragma omp parallel for private(diviseur,est_premier,id_thread) schedule(static) reduction(+:nombre_de_premier)
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

	    // on recupere le numero du thread pour savoir que c'est lui qui est trouve le resultat
	    id_thread = omp_get_thread_num();
	    if(est_premier) // si on a trover un nombre premier
	    {
	        #pragma omp critical   // afficher resultat chacun son tour
	        {
	            printf("Thread N° %d a trouve: %d\n",id_thread,nombre); // affiche le resultat
	        }
	        nombre_de_premier++; // on augmente de 1 le nombre de nombre premier trouve
	    }
	}

}