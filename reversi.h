
#ifndef __REVERSI__
#define __REVERSI__

  typedef enum{vide=0,bombe,vert,rouge}cellule;
  typedef struct{
    int dirhori;
    int dirverti;
  }direction;
  //permet d'associer un nombre de cases à une direction
  typedef struct{
    direction dir;
    int nbcases;
  }fleche;
  //un joueur a une couleur et un nombre de coups possibles
  typedef struct{
    cellule couleur;
    int nbcoups;
  }joueur;

  joueur *initJoueurs();
  fleche *initrose();
  cellule **initGrille();
  int terminateGrille(cellule **grille, fleche *rose);
  char getSymbole(cellule c);
  void affichage(cellule **grille);
  int checkbords(int i, int j, direction dir);
  int checkcapture(cellule **grille, int x, int y, direction dir, cellule c);
  void explosion(cellule **grille, fleche *rose, int x, int y);
  void capture(cellule **grille, fleche *rose, int x, int y, cellule c);
  int pose(cellule **grille, fleche *rose, joueur j);
  int verifcouprestant(cellule **grille, fleche *rose, joueur j);
  direction directioninverse(fleche *rose, direction dir);
  int checkfin(cellule **grille, fleche *rose, joueur *tabjoueurs, int cpt);
  void scores(cellule **grille, joueur *tabjoueurs);

#endif
