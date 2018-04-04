#include <stdio.h>
#include <stdlib.h>
#include "reversi.h"




  cellule **grille;
  fleche *rose;

int main()
{

  rose = initrose();
  grille=initGrille(7);
  affichage(grille);
  terminateGrille(grille, rose);
  pose(grille,rose, vert);
  affichage(grille);

  return 0;
}
