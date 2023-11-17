#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "ecosys.h"
#define NB_PROIES 20
#define NB_PREDATEURS 20
float p_ch_dir=0.01;
float p_reproduce_proie=0.2;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-9;

int main(void){

    Animal *liste_predateur20 = NULL;
    Animal *liste_proie20 = NULL;
    int energie = 10;
    unsigned int count =0;
    Animal *pre = creer_animal(10,20,energie);
    liste_predateur20 = pre;
    liste_predateur20->suivant=NULL;

    srand(time(NULL));
    for(int i =0; i < NB_PREDATEURS;i++){
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur20);
    }
    for(int j=0; j < NB_PROIES; j++){
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie20);
    }

    afficher_ecosys(liste_proie20,liste_predateur20);

    enlever_animal(&liste_predateur20,pre);
    printf("apres elenver .....\n");
    afficher_ecosys(liste_proie20,liste_predateur20);

    ecrire_ecosys("position_tests_ecosys2",liste_proie20,liste_predateur20);
    //lire_ecosys("position_tests_ecosys2",&lis)


    liberer_liste_animaux(liste_predateur20);
    liberer_liste_animaux(liste_proie20);

    return 0;
    
}