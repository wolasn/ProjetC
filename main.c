#include <stdio.h>
#include <stdlib.h>
#include "reversi.h"

  cellule **plateau=NULL;
  int **age=NULL;
  fleche *rose=NULL;
  int cpt=0,res,tour=0;
  joueur *tabjoueurs;

int main()
{
  rose = initrose();
  plateau=initplateau();
  age=initage();
  tabjoueurs=initJoueurs();
  //ne rien changer avant

  while(cpt!=-1){
    tour++;
    affichage(plateau,tour);
    res=pose(plateau,rose,tabjoueurs[cpt],age,tour);
    cpt=(cpt+1)%2;
    if(res==0){
      cpt=checkfin(plateau,rose,tabjoueurs,cpt);
    }
  }
  scores(plateau,tabjoueurs);

  //ne rien changer apres
  terminate(plateau,rose,age);
  return (0);
}
