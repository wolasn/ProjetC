
#ifndef __REVERSI__
#define __REVERSI__

  typedef enum{vide=0,trou,bombe,vert,rouge}cellule;
  typedef struct{
    int hori;
    int verti;
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
  int **initage(int *N);
  cellule **initplateau(int *N);
  int terminate(cellule **plateau, fleche *rose, int **age, int *N);
  char getSymbole(cellule c);
  void affichage(cellule **plateau, int tour, int *N);
  int checkbords(int i, int j, direction dir, int *N);
  int checkcapture(cellule **plateau, int x, int y, direction dir, cellule c, int *N);
  void init3x3(cellule **plateau, fleche *rose, int x, int y, int **age, int *N);
  void explosion(cellule **plateau, cellule c, fleche *rose, int x, int y, int **age, int *N);
  void capture(cellule **plateau, fleche *rose, int x, int y, int **age, cellule c);
  int trahison(cellule **plateau, fleche *rose, int **age, int tour, int *N);
  int pose(cellule **plateau, fleche *rose, joueur j, int **age, int tour, int *N);
  int verifcouprestant(cellule **plateau, fleche *rose, joueur j, int *N);
  direction directioninverse(fleche *rose, direction dir);
  int checkfin(cellule **plateau, fleche *rose, joueur *tabjoueurs, int cpt, int *N);
  void scores(cellule **plateau, joueur *tabjoueurs, int *N);

#endif
