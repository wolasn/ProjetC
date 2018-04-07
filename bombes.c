#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "reversi.h"
#include "bombes.h"


//vide les cases situés autour de celel passée en paramètre
void init3x3(cellule **plateau, fleche *rose, int x, int y, int **age, int *N)
{
  direction dir;
  for(int i=0;i<8;i++){
    dir=rose[i].dir;
    if(checkbords(x,y,dir,N)){
      plateau[x+dir.hori][y+dir.verti]=vide;
      age[x+dir.hori][y+dir.verti]=0;
    }
  }
}

//explosion d'une bombe a effet aleatoire
void explosion(cellule **plateau, cellule couleur, fleche *rose, int x, int y, int **age, int *N)
{
  direction dir;
  cellule c;
  srand(time(NULL));

  printf("Bombe : ");
  switch(rand()%5){
    case 0 :
            //laser ultra puissant
            dir=rose[rand()%8].dir;
            int i=x,j=y;
            while(checkbords(i,j,dir,N)){
              i+=dir.hori;
              j+=dir.verti;
              c=plateau[i][j];
              if(c!=vide && c!=bombe && c!=trou){
                plateau[i][j]=vide;
                age[i][j]=0;
              }
            }
            plateau[x][y]=couleur;
            age[x][y]=1;
            printf("Laser!");
            break;
    case 1 :
            //change la couleur du pion qui vient d'etre pose
            //REGLE OPTIONNELLE : on capture apres ça
            //XXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            //XXXCOULEURS NON GENERIQUESXXX
            //XXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            if(couleur==vert){
              plateau[x][y]=rouge;
            }else{
              plateau[x][y]=vert;
            }
            age[x][y]=1;
            printf("Changement de couleur!");
            break;
    case 2 :
            //seul reste le pion joue
            init3x3(plateau,rose,x,y,age,N);
            plateau[x][y]=couleur;
            age[x][y]=1;
            printf("Survivant!");
            break;
    case 3 :
            //explosion normale + case inutilisable
            init3x3(plateau,rose,x,y,age,N);
            plateau[x][y]=trou;
            age[x][y]=0;
            printf("Mayhem!");
            break;
    case 4 :
            //explosion normale
            init3x3(plateau,rose,x,y,age,N);
            plateau[x][y]=vide;
            age[x][y]=0;
            printf("Classique!");
            break;
    default :
            printf("explosion() : valeur aleatoire incorrecte");
            exit(0);
  }
  printf("\n");
}
