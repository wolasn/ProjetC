
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


  fleche *initrose();
  cellule **initGrille(int M);
  int terminateGrille(cellule **grille, fleche *rose);
  char getSymbole(cellule c);
  void affichage(cellule **grille);

  int checkbords(int i, int j, direction dir);
  int checkcapture(cellule **grille, int x, int y, direction dir, cellule c);
  void explosion(cellule **grille, fleche *rose, int x, int y);
  void capture(cellule **grille, fleche *rose, int x, int y, cellule c);
  void pose(cellule **grille, fleche *rose, cellule c);

#endif
