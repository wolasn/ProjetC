#include <stdio.h>
#include <stdlib.h>
#include "reversi.h"

  cellule **grille=NULL;
  fleche *rose=NULL;
  int cpt=0,res;
  joueur *tabjoueurs;

int main()
{
  rose = initrose();
<<<<<<< HEAD
  grille=initGrille(0);
=======
  grille=initGrille(13);
>>>>>>> c3a4ce8efa94c42c94ab19db657469a0327d4e5e
  tabjoueurs=initJoueurs();
  //ne rien changer avant

  while(cpt!=-1){
    affichage(grille);
    res=pose(grille,rose,tabjoueurs[cpt]);
    cpt=(cpt+1)%2;
<<<<<<< HEAD
    printf("CPT : %d\n",cpt);
    if(res==0){
      printf("AH?\n");
=======
    if(res==0){
>>>>>>> c3a4ce8efa94c42c94ab19db657469a0327d4e5e
      cpt=checkfin(grille,rose,tabjoueurs,cpt);
    }
  }

  //ne rien changer après
  terminateGrille(grille,rose);
  return (0);
}
