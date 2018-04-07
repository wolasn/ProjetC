#ifndef __INIT__
#define __INIT__

  joueur *initJoueurs();
  fleche *initrose();
  int **initage(int *N);
  cellule **initplateau(int *N, carte *Vcartes, carte *Rcartes);
  int terminate(cellule **plateau, fleche *rose, int **age, int *N, carte *Rcartes, carte*Vcartes);

#endif
