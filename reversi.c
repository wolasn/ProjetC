#include "reversi.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define ERREUR_ALLOCATION_MEMOIRE 1
#define ERREUR_getSymbole 2
#define mode 'D'
//note : N pair et >= 6
#define N 14
//notre plateau
cellule **grille;

//initialisation de la grille de jeu
cellule **initGrille(int M)
{
  cellule **grille;
  int randomX,randomY,milieu=(N/2)-1;
  srand(time(NULL));

  grille=malloc(N*sizeof(cellule*));
  if(grille==NULL){
    exit(ERREUR_ALLOCATION_MEMOIRE);
  }

  for(int i=0;i<N;i++){
    grille[i]=malloc(N*sizeof(cellule));
    if(grille[i]==NULL){
      for(int j=i-1;j>=0;j--){
        free(grille[j]);
      }
      free(grille);
      exit(ERREUR_ALLOCATION_MEMOIRE);
    }
  }

  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      grille[i][j]=vide;
    }
  }

  grille[milieu][milieu]=grille[milieu+1][milieu+1]=vert;
  grille[milieu+1][milieu]=grille[milieu][milieu+1]=rouge;

  for(int i=1;i<=M;i++){
    do{
      randomX=rand()%N;
      randomY=rand()%N;
    }while((((randomX >= milieu-1) && (randomX <= milieu+2)) && ((randomY >= milieu-1) && (randomY <= milieu+2))) || (grille[randomX][randomY]==bombe));
    grille[randomX][randomY]=bombe;
  }
  return(grille);
}

//désallouage d'une grille
int terminateGrille()
{
  for(int i=N-1;i>=0;i--){
    free(grille[i]);
  }
  free(grille);
  return(0);
}

//traduction du type case en caractère
char getSymbole(cellule c)
{
  switch (c) {
    case vide : return(' ');
    case bombe :
    if(mode=='J'){
      return(' ');
    }else if(mode=='D'){
      return('o');
    }
    case vert : return('V');
    case rouge : return('R');
    default : exit(ERREUR_getSymbole);
  }
}

//affichage d'une grille sur la sortie standard
int affichage()
{
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      printf("[%c]",getSymbole(grille[i][j]));
    }
    printf("\n");
  }
  return(0);
}

int checkbords(int i, int j, int dirhori, int dirverti)
{
  if
  (((dirhori==1 && dirverti==1) && (i==N-1 || j==N-1))    //sudest
  ||((dirhori==1 && dirverti==-1) && (i==N-1 || j==0))    //nordest
  ||((dirhori==-1 && dirverti==1) && (i==0 || j==N-1))    //sudouest
  ||((dirhori==-1 && dirverti==-1) && (i==0 || j==0))     //nordouest
  ||((dirhori==1 && dirverti==0) && (i==N-1))             //est
  ||((dirhori==-1 && dirverti==0) && (i==0))              //ouest
  ||((dirhori==0 && dirverti==1) && (j==N-1))             //sud
  ||((dirhori==0 && dirverti==-1) && (j==0))){            //nord
    return(0);
  }else{
  return(1);
  }
}

int checkligne(int x, int y, int dirhori, int dirverti, cellule c)
{
  int i=x,j=y;
  cellule suivante;

  if(!checkbords(i,j,dirhori,dirverti))
  {
    return(0);
  }else{
    suivante=(grille[i+dirhori][y+dirverti]);
    if(suivante==vide || suivante==bombe || suivante==c){
      return(0);
    }
  }

  while(suivante!=c){
    i+=dirhori;j+=dirverti;
    if(!checkbords(i,j,dirhori,dirverti))
    {
      return(0);
    }else{
      suivante=(grille[i+dirhori][y+dirverti]);
      if(suivante==vide || suivante==bombe){
        return(0);
      }
    }
  }

  if(i!=0){
    return(abs(x-i));
  }else{
    return(abs(y-j));
  }
}

//pose d'un pion
int pose(cellule c)
{
  int x,y,nord,sud,ouest,est,nordouest,nordest,sudouest,sudest;
  do{
    printf("Entrez la case où vous souhaitez jouer au format x,y\n");
    scanf("%d,%d",&x,&y);
  }while
  (nord=checkligne(x,y,0,-1,c)
  || sud=checkligne(x,y,0,1,c)
  || ouest=checkligne(x,y,-1,0,c)
  || est=checkligne(x,y,1,0,c)
  || nordouest=checkligne(x,y,-1,-1,c)
  || nordest=checkligne(x,y,1,-1,c)
  || sudouest=checkligne(x,y,-1,1,c)
  || sudest=checkligne(x,y,1,1,c));
}
