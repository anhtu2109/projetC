#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"
#include <string.h>

extern float p_ch_dir;
extern float p_reproduce_proie;
extern float p_reproduce_predateur;
extern int temps_repousse_herbe;
/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  /*A Completer*/
  assert(x >= 0 && x < SIZE_X);
  assert(y >= 0 && y < SIZE_Y);
  Animal *ani = creer_animal(x,y,energie);
  *liste_animal=ajouter_en_tete_animal(*liste_animal,ani);
}
/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  /*A Completer*/
  if(*liste==NULL || animal ==NULL){
    return;
  }
  Animal *nouvel =*liste;
  Animal *tmp = NULL;

  if(*liste == animal){
    *liste =(*liste)->suivant;
    free(nouvel);
    return ;
  
  }
  while(nouvel && nouvel ->suivant != animal){
    nouvel = nouvel ->suivant;
  }
  tmp = nouvel->suivant;
  nouvel->suivant=tmp->suivant;
  free(tmp);

}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
   /*A Completer*/
  if(!liste){
    return NULL;
  }
  Animal *sup = NULL;
  while(liste){
    sup = liste;
    liste =liste-> suivant;
    free(sup);
  }  

  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
    while(la){
      if((float)rand()/RAND_MAX < p_ch_dir){
        la->dir[0]=(rand()%3)-1;//so du lon nhat = so bi chia -1
        la->dir[1]=(rand()%3)-1;
      }
      la->x =(la->x + la->dir[0]+SIZE_X)%SIZE_X;
      la->y =(la->y + la ->dir[1]+SIZE_Y)%SIZE_Y;

      la=la->suivant;//animal suivant

    }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   /*A Completer*/
   Animal *ani = *liste_animal;
   while(ani){
    if((float)rand()/RAND_MAX < p_reproduce){
      ajouter_animal(ani->x,ani->y,(ani->energie)/2,liste_animal);
      ani->energie/=2;

    }
    ani=ani->suivant;
   }

}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*A Completer*/

    bouger_animaux(*liste_proie);
    Animal *ani =*liste_proie;
    Animal *adress= NULL;
    while(ani){
      if(monde[ani->x][ani->y]>0){
        ani->energie += monde[ani->x][ani->y];
        monde[ani->x][ani->y]= temps_repousse_herbe;
      }
      ani->energie-=1;
      adress=ani->suivant;

      if(ani->energie <0){
        enlever_animal(liste_proie,ani);
      }
      ani = adress;
    }

    reproduce(liste_proie,p_reproduce_proie);


}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/
    Animal*ani = l;
    while(ani){
      if(x==ani->x && y==ani->y){
        return ani;
      }
      ani =ani->suivant;
    }

  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  /*A Completer*/
  bouger_animaux(*liste_predateur);
  Animal *proie =NULL;
  Animal *adress = NULL;
  Animal *preda =*liste_predateur;
  while (preda) {
    proie = animal_en_XY(*liste_proie, preda->x, preda->y);
    if(proie && proie ->energie > 0){
      preda->energie += proie->energie;
      enlever_animal(liste_proie, proie);
    } 
    preda->energie -= 1;
    adress = preda->suivant;
    if(preda->energie < 0){
      enlever_animal(liste_predateur,preda);
    }
    preda = adress;
  }
  

  reproduce(liste_predateur, p_reproduce_predateur);

}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){

  /*A Completer*/
  for(unsigned i=0;i <SIZE_X;i++){
    for(unsigned j =0; j< SIZE_Y;j++){
      monde[i][j]+=1;
    }
  }
}

void ecrire_ecosys(const char *nom_fichier,Animal *liste_predateur,Animal*liste_proie){
  FILE *f =fopen(nom_fichier,"w");

  if(f==NULL){
    printf("Erreur ouverture %s\n",nom_fichier);
    return ;
  }
  Animal*ani;
  fprintf(f,"<proies>\n"); //proies
  ani = liste_proie;
  while(ani){
    fprintf(f,"x=%d y=%d dir=[%d %d] e=%.2f\n",ani->x,ani->y,ani->dir[0],ani->dir[1],ani->energie);
    ani = ani->suivant;
  }
  fprintf(f,"</proies>\n");
  
  fprintf(f,"<predateurs>\n");//predateurs
  ani=liste_predateur;
  while(ani){
    fprintf(f,"x=%d y=%d dir=[%d %d] e=%.2f\n",ani->x,ani->y,ani->dir[0],ani->dir[1],ani->energie);
    ani=ani->suivant;
  }
  fprintf(f,"</predateurs>\n");

  fclose(f);
}

void lire_ecosys(const char *nom_ficher, Animal **liste_predateur, Animal **liste_proie){
  
  // Ouvrir un fichier et lire(read) dans le fichier
  FILE *f = fopen(nom_ficher,"r");
  
  if (f==NULL)
  {
    printf("Erreur ouverture %s\n",nom_ficher);
    return;
  }
  
  // D'abord lire les proies
  Animal *ani;
  char buffer[256];
  int x,y;
  int dir[2];
  float e;

  fgets(buffer,256,f); 
  assert(strncmp(buffer,"<proies>",8) == 0);

  fgets(buffer,256,f);
  while (strncmp(buffer,"</proies>",9) != 0)
  {
    sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f\n",&x,&y,&dir[0],&dir[1],&e);
    ani = creer_animal(x,y,e);
    ani->dir[0] = dir[0];
    ani->dir[1] = dir[1];
    *liste_proie = ajouter_en_tete_animal(*liste_proie,ani);
    fgets(buffer,256,f);
  }
  
  // Lire les prédateurs
  fgets(buffer,256,f);
  assert(strncmp(buffer,"<predateurs>",12) == 0);

  fgets(buffer,256,f);
  while (strncmp(buffer,"</predateurs>",13) != 0)
  {
    sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f\n",&x,&y,&dir[0],&dir[1],&e);
    ani = creer_animal(x,y,e);
    ani->dir[0] = dir[0];
    ani->dir[1] = dir[1];
    *liste_predateur = ajouter_en_tete_animal(*liste_predateur,ani);
    fgets(buffer,256,f);
  }

  fclose(f);
}