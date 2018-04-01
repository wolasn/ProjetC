#ifndef __REVERSI__
#define __REVERSI__

  typedef enum{vide=0,bombe,vert,rouge}cellule;


  cellule **initGrille(int M);
  int terminateGrille();
  char getSymbole(cellule c);
  int affichage();

#endif
