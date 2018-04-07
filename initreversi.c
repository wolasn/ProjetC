
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "reversi.h"
#include "initreversi.h"

#define ERREUR_ALLOCATION_MEMOIRE 1

//renvoie le tableau de joueurs
joueur *initJoueurs()
{
  joueur *tabjoueurs=malloc(sizeof(joueur)*2);
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  //XXXCOULEURS NON GENERIQUESXXX
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  tabjoueurs[0].couleur=vert;
  tabjoueurs[1].couleur=rouge;
  return(tabjoueurs);
}

//initialisation du tableau de directions
fleche *initrose()
{
  fleche *rose;

  //tableau de directions predefinies
  const direction
  nord={0,-1},
  sud={0,1},
  est={1,0},
  ouest={-1,0},
  nordest={1,-1},
  nordouest={-1,-1},
  sudest={1,1},
  sudouest={-1,1};

  rose=malloc(sizeof(fleche)*8);
  rose[0].dir=nord;
  rose[1].dir=sud;
  rose[2].dir=est;
  rose[3].dir=ouest;
  rose[4].dir=nordest;
  rose[5].dir=sudouest;
  rose[6].dir=nordouest;
  rose[7].dir=sudest;
  return rose;
}

//initialise le tableau d'age des pions
int **initage(int *N)
{
  int **age,i,j;

  age=malloc(*N*sizeof(int*));
  if(age==NULL){
    exit(ERREUR_ALLOCATION_MEMOIRE);
  }

  for(i=0;i<*N;i++){
    age[i]=malloc(*N*sizeof(int));
    if(age[i]==NULL){
      for(j=i-1;j>=0;j--){
        free(age[j]);
      }
      free(age);
      exit(ERREUR_ALLOCATION_MEMOIRE);
    }
    for(j=0;j<*N;j++){
      age[i][j]=0;
    }
  }
  return(age);
}

//initialisation du age de jeu
cellule **initplateau(int *N)
{
  int randomX,randomY,nbbombes,i,j,milieu;
  cellule **plateau;
  srand(time(NULL));

  system("clear");

  while(*N<1 || *N>3){
    printf("Duree de la partie\n");
    printf("1 : courte\n");
    printf("2 : moyenne\n");
    printf("3 : longue\n\n");
    scanf("%d",N);
  }
  switch(*N){
    case 1 : *N=6;break;
    case 2 : *N=8;break;
    case 3 : *N=10;break;
  }

  plateau=malloc(*N*sizeof(cellule*));
  if(plateau==NULL){
    exit(ERREUR_ALLOCATION_MEMOIRE);
  }

  for(i=0;i<*N;i++){
    plateau[i]=malloc(*N*sizeof(cellule));
    if(plateau[i]==NULL){
      for(j=i-1;j>=0;j--){
        free(plateau[j]);
      }
      free(plateau);
      exit(ERREUR_ALLOCATION_MEMOIRE);
    }
    for(j=0;j<*N;j++){
      plateau[i][j]=vide;
    }
  }

  milieu=(*N/2)-1;
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  //XXXCOULEURS NON GENERIQUESXXX
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  plateau[milieu][milieu]=plateau[milieu+1][milieu+1]=vert;
  plateau[milieu+1][milieu]=plateau[milieu][milieu+1]=rouge;

  do{
    printf("Combien de bombes voulez-vous ? (maximum %d)\n",(*N**N)-16);
    scanf("%d",&nbbombes);
  }while(nbbombes>(*N**N)-16);
  for(int i=1;i<=nbbombes;i++){
    do{
      randomX=rand()%*N;
      randomY=rand()%*N;
    }while((((randomX >= milieu-1) && (randomX <= milieu+2)) && ((randomY >= milieu-1) && (randomY <= milieu+2))) || (plateau[randomX][randomY]==bombe));
    plateau[randomX][randomY]=bombe;
  }
  return(plateau);
}

//desallouage d'un plateau
int terminate(cellule **plateau, fleche *rose, int **age, int *N)
{
  for(int i=*N-1;i>=0;i--){
    free(plateau[i]);
    free(age[i]);
  }
  free(plateau);
  free(age);
  free(rose);
  return(0);
}
