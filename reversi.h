#ifndef __REVERSI__
#define __REVERSI__

  typedef enum{vide=0,bombe,vert,rouge}cellule;

  cellule **initGrille(int M);
  int terminateGrille();
  char getSymbole(cellule c);
  int affichage();
  int checkbords(int i, int j, int dirhori, int dirverti);
  int checkligne(int x, int y, int dirhori, int dirverti, cellule c);
  int pose(cellule c);

#endif
