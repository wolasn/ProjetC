#ifndef __BOMBES__
#define __BOMBES__

  void init3x3(cellule **plateau, fleche *rose, int x, int y, int **age, int *N);
  void explosion(cellule **plateau, cellule c, fleche *rose, int x, int y, int **age, int *N);

#endif
