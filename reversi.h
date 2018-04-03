#ifndef __REVERSI__
#define __REVERSI__

  typedef enum{vide=0,bombe,vert,rouge}cellule;


  cellule **initGrille(int M);
  int terminateGrille(cellule **grille);
  char getSymbole(cellule c);
  int affichage(cellule **grille);

#endif
