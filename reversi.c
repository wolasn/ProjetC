#include "reversi.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ERREUR_ALLOCATION_MEMOIRE 1
#define ERREUR_getSymbole 2
#define mode 'D'
//note : N pair et >= 6
#define N 6

//renvoie le tableau de joueurs
joueur *initJoueurs()
{
  joueur *tabjoueurs=malloc(sizeof(joueur)*2);
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXX
  //XXXCOULEURS NON GENERIQUEXXX
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXX
  tabjoueurs[0].couleur=vert;
  tabjoueurs[1].couleur=rouge;
  return(tabjoueurs);
}

//initialisation du tableau de directions
fleche *initrose()
{
  fleche *rose;

  //tableau de directions pr�d�finies
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

//initialisation de la grille de jeu
cellule **initGrille()
{
  cellule **grille;
  int randomX,randomY,nbbombes,milieu=(N/2)-1;
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

  //XXXXXXXXXXXXXXXXXXXXXXXXXXXX
  //XXXCOULEURS NON GENERIQUEXXX
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXX
  grille[milieu][milieu]=grille[milieu+1][milieu+1]=vert;
  grille[milieu+1][milieu]=grille[milieu][milieu+1]=rouge;

  do{
    printf("Combien voulez-vous de bombes ? (maximum %d)\n",(N*N)-16);
    scanf("%d",&nbbombes);
  }while(nbbombes>(N*N)-16);
  for(int i=1;i<=nbbombes;i++){
    do{
      randomX=rand()%N;
      randomY=rand()%N;
    }while((((randomX >= milieu-1) && (randomX <= milieu+2)) && ((randomY >= milieu-1) && (randomY <= milieu+2))) || (grille[randomX][randomY]==bombe));
    grille[randomX][randomY]=bombe;
  }
  return(grille);
}

//d�sallouage d'une grille
int terminate(cellule **grille, fleche *rose)
{
  for(int i=N-1;i>=0;i--){
    free(grille[i]);
  }
  free(grille);
  free(rose);
  return(0);
}

//traduction du type case en caract�re
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
    case trou : return('X');
    case vert : return('V');
    case rouge : return('R');
    default : exit(ERREUR_getSymbole);
  }
}

//affichage d'une grille sur la sortie standard
void affichage(cellule **grille)
{
  //system("clear");
  printf("\n   ");
  for(int k=0;k<N;k++){
    printf(" %d ",k);
  }
  printf(" y\n");
  for(int i=0;i<N;i++){
    printf(" %d ",i);
    for(int j=0;j<N;j++){
      printf("[%c]",getSymbole(grille[i][j]));
    }
    printf("\n");
  }
  printf(" x\n\n");
}

//pour v�rifier si l'on va sur un bord
//renvoie 0 si c'est le cas
int checkbords(int i, int j, direction dir)
{
  if
  ((dir.dirhori==1 && dir.dirverti==1 && (i==N-1 || j==N-1))  //sudest
  ||(dir.dirhori==1 && dir.dirverti==-1 && (i==N-1 || j==0))  //nordest
  ||(dir.dirhori==-1 && dir.dirverti==1 && (i==0 || j==N-1))  //sudouest
  ||(dir.dirhori==-1 && dir.dirverti==-1 && (i==0 || j==0))   //nordouest
  ||(dir.dirhori==1 && dir.dirverti==0 && i==N-1)             //est
  ||(dir.dirhori==-1 && dir.dirverti==0 && i==0)              //ouest
  ||(dir.dirhori==0 && dir.dirverti==1 && j==N-1)             //sud
  ||(dir.dirhori==0 && dir.dirverti==-1 && j==0)){            //nord
    return(0);
  }
  return(1);
}

//renvoie le nombre de pion captur�s avec une pose dans une direction donn�e
int checkcapture(cellule **grille, int x, int y, direction dir, cellule c)
{
  int i=x,j=y;
  cellule suivante;

  if(!checkbords(i,j,dir))
  {
    return(0);
  }else{
    suivante=(grille[i+dir.dirhori][j+dir.dirverti]);
    if(suivante==vide || suivante==bombe || suivante==c || suivante==trou){
      return(0);
    }
  }
  while(suivante!=c){
    i+=dir.dirhori;j+=dir.dirverti;
    if(!checkbords(i,j,dir))
    {
      return(0);
    }else{
      suivante=(grille[i+dir.dirhori][j+dir.dirverti]);
      if(suivante==vide || suivante==bombe || suivante==trou){
        return(0);
      }
    }
  }
  if((i-x)!=0){
    return(abs(x-i));
  }else{
    return(abs(y-j));
  }
}

void init3x3(cellule **grille, fleche *rose, int x, int y)
{
  direction dir;
  for(int i=0;i<8;i++){
    dir=rose[i].dir;
    if(checkbords(x,y,dir)){
      grille[x+dir.dirhori][y+dir.dirverti]=vide;
    }
  }
}

//explosion d'une bombe à effet aléatoire
void explosion(cellule **grille, cellule couleur, fleche *rose, int x, int y)
{
  direction dir;
  cellule c;
  srand(time(NULL));

  switch(0){
    case 0 :
            //laser ultra puissant
            dir=rose[rand()%8].dir;
            int i=x,j=y;
            while(checkbords(i,j,dir)){
              i+=dir.dirhori;j+=dir.dirverti;
              c=grille[i][j];
              if(c!=vide && c!=bombe && c!=trou){
                grille[i][j]=vide;
              }
            }
            grille[x][y]=couleur;
            break;
    case 1 :
            //change la couleur du pion qui vient d'être posé
            //REGLE OPTIONNELLE : on capture après ça
            //XXXXXXXXXXXXXXXXXXXXXXXXXXXX
            //XXXCOULEURS NON GENERIQUEXXX
            //XXXXXXXXXXXXXXXXXXXXXXXXXXXX
            if(couleur==vert){
              grille[x][y]=rouge;
            }else{
              grille[x][y]=vert;
            }
            break;
    case 2 :
            //seul reste le pion joué
            init3x3(grille,rose,x,y);
            grille[x][y]=couleur;
            break;
    case 3 :
            //explosion normale + case inutilisable
            init3x3(grille,rose,x,y);
            grille[x][y]=trou;
            break;
    case 4 :
            //explosion normale
            init3x3(grille,rose,x,y);
            grille[x][y]=vide;
            break;
    default :
            printf("explosion() : valeur aléatoire incorrecte");
            exit(0);
  }
  printf("Il y avait une bombe!\n");
}

//capture de pions enemies
void capture(cellule **grille, fleche *rose, int x, int y, cellule c)
{
  int dir1,dir2;
  for(int i=0;i<8;i++){
    dir1=(rose[i].dir.dirhori);
    dir2=(rose[i].dir.dirverti);
    for(int j=0;j<=rose[i].nbcases;j++){
      grille[x+dir1*j][y+dir2*j]=c;
    }
  }
}

//pose d'un pion
//renvoie 0 si le joueur n'a pas pu jouer
int pose(cellule **grille, fleche *rose, joueur j)
{
  int x,y,s=0;

  printf("C'est à %c de jouer\n",getSymbole(j.couleur));

  if(verifcouprestant(grille,rose,j)==0){
    return(0);
  }

  while(s==0){
    printf("Entrez la case où vous souhaitez jouer %c (au format x,y)\n",getSymbole(j.couleur));
    scanf("%d,%d",&x,&y);
    for(int i=0;i<8;i++){
      rose[i].nbcases=checkcapture(grille,x,y,rose[i].dir,j.couleur);
      s+=rose[i].nbcases;
    }
  }
  if(grille[x][y]==bombe){
    explosion(grille,j.couleur,rose,x,y);
  }else{
    capture(grille,rose,x,y,j.couleur);
  }
  return(1);
}

//renvoie 1 si le joueur a au moins un coup jouable
int verifcouprestant(cellule **grille, fleche *rose, joueur j)
{
  direction dir,dirinverse;
  cellule couleur=j.couleur,c;
  int x,y;

  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      c=grille[i][j];
      if((c!=couleur) && (c!=bombe) && (c!=vide) && (c!=trou)){
        printf("J'ai trouvé un enemie en %d,%d\n",i,j);
        for(int k=0;k<8;k++){
          dir=rose[k].dir;
          if(checkbords(i,j,dir)){
            c=grille[i+dir.dirhori][j+dir.dirverti];
            x=i+dir.dirhori;
            y=j+dir.dirverti;
            dirinverse=directioninverse(rose,dir);
            if(((c==vide) || (c==bombe)) && (checkcapture(grille,x,y,dirinverse,couleur)>0)){
              printf("De %d,%d je peux l'avoir\n",x,y);
              return(1);
            }
            printf("De %d,%d c'est niet\n",x,y);
          }
        }
      }
    }
  }
  return(0);
}

//renvoie la direction inverse
direction directioninverse(fleche *rose, direction dir)
{
  direction dirinverse;

  dirinverse.dirhori=-(dir.dirhori);
  dirinverse.dirverti=-(dir.dirverti);

  return(dirinverse);
}

//renvoie le prochain l'indice du prochain joueur pouvant joueur
//renvoie -1 s'il n'y en a aucun
int checkfin(cellule **grille, fleche *rose, joueur *tabjoueurs, int cpt)
{
  int nbjoueurs=2;

  for(int k=cpt;k<nbjoueurs;k++,(cpt++)%2){
    if(verifcouprestant(grille,rose,tabjoueurs[k])!=0){
      return(k);
    };
  }
  return(-1);
}

void scores(cellule **grille, joueur *tabjoueurs)
{
  int nbjoueurs=2,score;
  cellule couleur;

  for(int k=0;k<nbjoueurs;k++){
    couleur=tabjoueurs[k].couleur;
    score=0;
    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
        if(couleur==grille[i][j])
          score++;
      }
    }
    printf("Le joueur %c a un score de %d\n",getSymbole(couleur),score);
  }
}
