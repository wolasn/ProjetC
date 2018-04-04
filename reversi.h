#ifndef __REVERSI__
#define __REVERSI__

  typedef enum{vide=0,bombe,vert,rouge}cellule;
  typedef struct{
    int dirhori;
    int dirverti;
  }direction;
  typedef struct{
    direction dir;
    int nbcases;
  }fleche;

  void initrose();
  void initGrille(int M);
  int terminate();
  char getSymbole(cellule c);
  void affichage();
  int checkbords(int i, int j, direction dir);
  int checkcapture(int x, int y, direction dir, cellule c);
  void explosion(int x, int y);
  void capture(int x, int y, cellule c);
  void pose(cellule c);

#endif
