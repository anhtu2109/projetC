#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 50
#define NB_PREDATEURS 50
#define T_WAIT 40000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.3;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-9;


int main(void) {
    srand(time(NULL));

 
  /* A completer. Part 2:
   * exercice 4, questions 2 et 4 
   * exercice 6, question 2
   * exercice 7, question 3
   * exercice 8, question 1
  */
  //rafrarchirmonde
  int monde[SIZE_X][SIZE_Y];
  // Initialisation à 0 
  for (int i = 0; i < SIZE_X; ++i) {
    for (int j = 0; j < SIZE_Y; ++j) {
        monde[i][j] = 0; 
    }
  }
  Animal *liste_predateur =NULL;
  Animal *liste_proie= NULL;
  unsigned int nbproie =0;
  unsigned int nbpred = 0;
  int energie =20;

  //cree 20 proies 
  for(int i=0 ; i <NB_PROIES; i++){
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);
  }
  for(int j = 0; j <NB_PREDATEURS;j++){
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
  }
  nbproie =compte_animal_it(liste_proie);
  nbpred =compte_animal_it(liste_predateur);

  afficher_ecosys(liste_proie,liste_predateur);
  FILE *f = fopen("Evol_Pop.txt","w");
  //cree20poire 
  int boucle = 0;
  while(boucle < 200 ){
    fprintf(f,"%d %d %d\n",boucle,nbproie,nbpred);
    if(nbproie ==0){
      printf("il n'y a plus proies");
      break ;
    }

    rafraichir_monde(monde);
    rafraichir_proies(&liste_proie,monde);
    rafraichir_predateurs(&liste_predateur,&liste_proie);
    nbproie =compte_animal_it(liste_proie);
    nbpred = compte_animal_it(liste_predateur);
    boucle+=1;
    
    usleep(T_WAIT);
    printf("apres la boucle.......\n");
    afficher_ecosys(liste_proie,liste_predateur);
  }
  
  fclose(f);



  return 0;
}

