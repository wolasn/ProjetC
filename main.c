#include <stdio.h>
#include <stdlib.h>
#include "reversi.h"

  cellule **grille=NULL;
  fleche *rose=NULL;

int main()
{

  rose = initrose();
  grille=initGrille(7);
  affichage(grille);
  pose(grille,rose,vert);
  affichage(grille);
  terminate(grille,rose);
  return (0);
}
