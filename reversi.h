
#ifndef __REVERSI__
#define __REVERSI__

  typedef enum{vide=0,trou,bombe,vert,rouge}cellule;
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
  int **initage();
  cellule **initplateau();
  int terminate(cellule **plateau, fleche *rose, int **age);
  char getSymbole(cellule c);
  void affichage(cellule **plateau);
  int checkbords(int i, int j, direction dir);
  int checkcapture(cellule **plateau, int x, int y, direction dir, cellule c);
  void init3x3(cellule **plateau, fleche *rose, int x, int y, int **age);
  void explosion(cellule **plateau, cellule c, fleche *rose, int x, int y, int **age);
  void capture(cellule **plateau, fleche *rose, int x, int y, int **age, cellule c);
  int trahison(cellule **plateau, fleche *rose, int **age, int tour);
  int pose(cellule **plateau, fleche *rose, joueur j, int **age, int tour);
  int verifcouprestant(cellule **plateau, fleche *rose, joueur j);
  direction directioninverse(fleche *rose, direction dir);
  int checkfin(cellule **plateau, fleche *rose, joueur *tabjoueurs, int cpt);
  void scores(cellule **plateau, joueur *tabjoueurs);

#endif
