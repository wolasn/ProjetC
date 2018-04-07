#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include "reversi.h"

//renvoie une main de cartes tirees aleatoirements
carte *pioche(int nbcartes)
{
  srand(time(NULL));
  carte *main;

  main=malloc(nbcartes*sizeof(carte));

  for(int i=0;i<nbcartes;i++){
    main[i]=rand()%7;
  }
  return(main);
}
