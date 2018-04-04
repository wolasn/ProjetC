#include <stdio.h>
#include <stdlib.h>
#include "reversi.h"

  cellule **grille=NULL;
  fleche *rose=NULL;
  int fini=0;

int main()
{
  rose = initrose();
  grille=initGrille(13);
  //ne rien changer avant

  while(!fini){
    affichage(grille);
    pose(grille,rose,vert);
    affichage(grille);
    pose(grille,rose,rouge);
  }

  //ne rien changer après
  terminateGrille(grille,rose);
  return (0);
}
