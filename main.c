#include "reversi.h"


int main()
{
  cellule **grille;
  
  grille=initGrille(7);
  affichage(grille);
  terminateGrille(grille);
}
