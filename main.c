#include <stdio.h>
#include <stdlib.h>
#include "reversi.h"

  cellule **plateau=NULL;
  fleche *rose=NULL;
  int cpt=0,res;
  joueur *tabjoueurs;

int main()
{
  rose = initrose();
  plateau=initplateau();
  tabjoueurs=initJoueurs();
  //ne rien changer avant

  while(cpt!=-1){
    affichage(plateau);
    res=pose(plateau,rose,tabjoueurs[cpt]);
    cpt=(cpt+1)%2;
    if(res==0){
      cpt=checkfin(plateau,rose,tabjoueurs,cpt);
    }
  }
  scores(plateau,tabjoueurs);

  //ne rien changer après
  terminate(plateau,rose);
  return (0);
}
