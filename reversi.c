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
static cellule **grille;

//tableau de directions prédéfinies
const direction nord={0,-1},sud={0,1},est={1,0},ouest={-1,0},nordest={1,-1},nordouest={-1,-1},sudest={1,1},sudouest={-1,1};
//à mettre en constante
direction *rose;

//initialisation du tableau de directions
void initrose()
{
  rose=malloc(sizeof(direction)*8);
  rose[0]=nord;
  rose[1]=sud;
  rose[2]=est;
  rose[3]=ouest;
  rose[4]=nordest;
  rose[5]=nordouest;
  rose[6]=sudest;
  rose[7]=sudouest;
}

//initialisation de la grille de jeu
cellule **initGrille(int M)
{
  cellule **grille;
  int randomX,randomY,milieu=(N/2)-1;
  srand(time(NULL));

  initrose();

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

//désallouages
int terminate()
{
  for(int i=N-1;i>=0;i--){
    free(grille[i]);
  }
  free(grille);
  free(rose);
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
void affichage()
{
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      printf("[%c]",getSymbole(grille[i][j]));
    }
    printf("\n");
  }
}

int checkbords(int i, int j, direction dir)
{
  if
  ((dir.dirhori==1 && dir.dirverti==1 && (i==N-1 || j==N-1))  //sudest
  ||(dir.dirhori==1 && dir.dirverti==-1 && (i==N-1 || j==0))  //nordest
  ||(dir.dirhori==-1 && dir.dirverti==1 && (i==0 || j==N-1)) //sudouest
  ||(dir.dirhori==-1 && dir.dirverti==-1 && (i==0 || j==0))  //nordouest
  ||(dir.dirhori==1 && dir.dirverti==0 && i==N-1)                //est
  ||(dir.dirhori==-1 && dir.dirverti==0 && i==0)                //ouest
  ||(dir.dirhori==0 && dir.dirverti==1 && j==N-1)                //sud
  ||(dir.dirhori==0 && dir.dirverti==-1 && j==0)){               //nord
    return(0);
  }
  return(1);
}

int checkligne(int x, int y, direction dir, cellule c)
{
  int i=x,j=y;
  cellule suivante;

  if(!checkbords(i,j,dir))
  {
    return(0);
  }else{
    suivante=(grille[i+dir.dirhori][y+dir.dirverti]);
    if(suivante==vide || suivante==bombe || suivante==c){
      return(0);
    }
  }
  while(suivante!=c){
    i+=dir.dirhori;j+=dir.dirverti;
    if(!checkbords(i,j,dir))
    {
      return(0);
    }else{
      suivante=(grille[i+dir.dirhori][y+dir.dirverti]);
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

//explosion d'une bombe, met la case ainsi que celles autour à vide
void explosion(int x, int y)
{
  if(x>0 && y>0){
    grille[x-1][y-1]=grille[x-1][y]=grille[x][y-1]=vide;
  }
  if(x<N-1 && y<N-1){
    grille[x+1][y+1]=grille[x+1][y]=grille[x][y+1]=vide;
  }
  if(x<N+1 && y>0){
    grille[x+1][y-1]=vide;
  }
  if(x>0 && y<N-1){
    grille[x-1][y+1]=vide;
  }
  grille[x][y]=vide;
}

void capture(int *tab, int x, int y, cellule c)
{int dir1,dir2;
  for(int i=0;i<8;i++){
    dir1=(rose[i].dirhori);
    dir2=(rose[i].dirverti);
    for(int j=1;j<tab[i];j++){
      grille[x+dir1*j][y+dir2*j]=c;
    }
  }
}

//pose d'un pion
void pose(cellule c)
{
  int x,y,tab[8];

  do{
    printf("Entrez la case où vous souhaitez jouer au format x,y\n");
    scanf("%d,%d",&x,&y);

    tab[0]=checkligne(x,y,nord,c);
    tab[1]=checkligne(x,y,sud,c);
    tab[2]=checkligne(x,y,est,c);
    tab[3]=checkligne(x,y,ouest,c);
    tab[4]=checkligne(x,y,nordest,c);
    tab[5]=checkligne(x,y,nordouest,c);
    tab[6]=checkligne(x,y,sudest,c);
    tab[7]=checkligne(x,y,sudouest,c);

  }while
  (!(tab[0] || tab[1] || tab[2] || tab[3] || tab[4] || tab[5] || tab[6] || tab[7]));

  if(grille[x][y]==bombe){
    explosion(x,y);
  }else{
    capture(tab,x,y,c);
  }
}
