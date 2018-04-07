#include <stdio.h>
#include <stdlib.h>
#include "reversi.h"
#include "initreversi.h"

  cellule **plateau=NULL;
  int **age=NULL;
  fleche *rose=NULL;
  carte *Vcartes,*Rcartes;
  int cpt=0,res,tour=0,N=0;
  joueur *tabjoueurs;

int main()
{
  rose = initrose();
  plateau=initplateau(&N,Vcartes,Rcartes);
  age=initage(&N);
  tabjoueurs=initJoueurs();
  //ne rien changer avant

  while(cpt!=-1){
    tour++;
    affichage(plateau,tour,&N);
    res=pose(plateau,rose,tabjoueurs[cpt],age,tour,&N);
    cpt=(cpt+1)%2;
    if(res==0){
      cpt=checkfin(plateau,rose,tabjoueurs,cpt,&N);
    }
  }
  scores(plateau,tabjoueurs,&N);

  //ne rien changer apres
  terminate(plateau,rose,age,&N,Rcartes,Vcartes);
  return (0);
}
