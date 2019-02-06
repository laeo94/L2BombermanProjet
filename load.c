#include "load.h"
#define BUFFSIZE 2048


//Creation du joueur
joueur* add_player(char rep, position p){
  joueur* j = malloc(sizeof(joueur));
  j->rep_j = rep;
  j->pos_j = p;
  j->nb_bombe = 1;
  j->portee = 3;
  j->vie = 3;
  j->vitesse = 2.5;
  j->poser = 0;
  j->b = (bombes*)malloc(sizeof(bombes)*j->nb_bombe);
  j->b[0].tps_pose = 0;
  j->b[0].duree = 2.5;
  j->p.type = aucun;
  j->p.tps = 0;
  j->p.duree = 6;
  j->p.actif = false;
  return j;
}

//Supprime le niveau
void delete_niveau(niveau* niv){
     int i;
     for(i=0; i < (niv->h); i++ ){
        free(niv->carte[i]);
     }
     free(niv->carte);
     for(i=0; i < (niv->h); i++ ){
        free(niv->bonus[i]);
     }
     free(niv->bonus);
     for(i=0; i < 2; i++ ){
        free(niv->j[i]->b);
        free(niv->j[i]);
     }
     free(niv);
}

int myopen(char* filename){
  int fd = open(filename,O_RDONLY);
  if ( fd == -1) {
    perror (filename);
    exit(1);
  }
  return fd;
}

//Création du niveau
niveau* create_niveau(char* filename){
  niveau* niv = (niveau*)malloc(sizeof(niveau));
  int i; int j; int k = 0;
  int n;
  char h[2];
  char l[2];
  int fd = myopen(filename);
  read(fd,h,2);
  lseek(fd,1,SEEK_CUR);
  read(fd,l,2);
  lseek(fd,1,SEEK_CUR);
  niv->h = atoi(h);
  niv->l =atoi(l);
  position p1 ;
  p1.x =2; //initialisé a (2,2) pr j1
  p1.y =2;
  position p2;
  p2.x =niv->h-1;
  p2.y =niv->l-1;
  niv->j[0]=add_player('A',p1);
  niv->j[1]=add_player('B',p2);
  niv->carte = (char**)malloc(niv->h*sizeof(char*));
  for(i=0; i<niv->h; i++){
    niv->carte[i] = (char*)malloc(niv->l*sizeof(char));
  }
  niv->bonus = (char**)malloc(niv->h*sizeof(char*));
  for(i=0; i<niv->h; i++){
    niv->bonus[i] = (char*)malloc(niv->l*sizeof(char));
  }
  //Création des cartes du niveau
  char buffer[BUFFSIZE];
  while((n=read(fd,buffer,BUFFSIZE))>0){
    i=0; j=0; k=0;
    //Carte sans bonus
    while(k<niv->l*niv->h+niv->h){
      if(buffer[k]=='\n'){
        i++;
        j=0;
      }else{
        niv->carte[i][j]=buffer[k];
        j++;
      }
      k++;
    }
      
  //Creation carte des bonus
  i=0;j=0;
  while(k<n){
    if(buffer[k]=='\n'){
      i++;
      j=0;
    }else{
      niv->bonus[i][j]=buffer[k];
      j++;
    }
    k++;
    }
  }
  close(fd);
  return niv;
}


//Affichage d'un joueur
void print_player(joueur *j, char rep){
  char b[10];
  int taille = sprintf(b,"\x1b[33m\x1b[%d;%dH%c", j->pos_j.x+2, j->pos_j.y+2, rep);
  write(1,b,taille);
  taille = sprintf(b,"\x1b[37m");
  write(1,b,taille);
} 

//Test si le jeu est fini
bool game_over(niveau* n){
      if(n->j[0]->vie <=0 || n->j[1]->vie <= 0){ 
         return true;
      }
     return false;
}

//Place les bonus sur la carte quand il y a un vide
void placement_bonus(niveau* n){
    int i; int j;
    for(i=0; i<n->h; i++){
       for(j=0; j<n->l; j++){
          if(n->bonus[i][j] != ' ' && n->carte[i][j] == ' ')
             n->carte[i][j] = n->bonus[i][j];
       }
    }
}

//affiche le niveau
void print_niveau(niveau* niv){
  system("clear");
  //Teste si le jeu est fini
  if(game_over(niv)){
    if(niv->j[1]->vie == 0 && niv->j[0]->vie != 0){
        char* buf1 = "\n\n                    Le joueur A a gagné la partie                \n\n";
            write(1, buf1, strlen(buf1));
     }else if(niv->j[0]->vie == 0 && niv->j[1]->vie != 0){
        char* buf2 = "\n\n                    Le joueur B a gagné la partie                \n\n";
        write(1, buf2, strlen(buf2));
     }else if(niv->j[0]->vie == 0 && niv->j[1]->vie == 0){
        char* buf3 = "\n\n                    La partie se termine sur un match nul                \n\n";
        write(1, buf3, strlen(buf3));
     }        
    char* buf = "******************************GAME OVER****************************\n\n";
    write(1, buf, strlen(buf));
  }else{
    //representation carte
    int i,j;
    //placement des bonus sur la carte
    placement_bonus(niv);
    //Affichage de la carte
    for(i=0; i< niv->h ;i++){
      for(j=0;j<niv->l;j++){
        char c =niv->carte[i][j];
        char aff[1];
        int taille;
        if(c=='@'){ //Affiche en rouge la bombe
          taille=sprintf(aff,"\x1b[91m\x1b[%d;%dH%c",i+3,j+3,c);
          write(1,aff,taille);
          taille = sprintf(aff,"\x1b[37m");
          write(1,aff,taille);
        }else{
          taille=sprintf(aff,"\x1b[%d;%dH%c",i+3,j+3,c);
          write(1,aff,taille);
        }
      }
    }
    write(1,"\n\n",2);
    char* buf = "   A: QZSD et espace  ||  B :fleches et * pour poser la bombe\n";
    write(1, buf, strlen(buf));
    char b [60];
    int taille =sprintf(b,"\x1b[%d;%dH [Vie A : %d] [Vie B : %d]",niv->h+7,22,niv->j[0]->vie,niv->j[1]->vie);
    write(1,b,taille);
    //affiche les joueurs
    print_players(niv);
  }
}
//affiche les joueurs sur la carte
void print_players (niveau* niv){
    print_player(niv->j[0],niv->j[0]->rep_j);
    print_player(niv->j[1],niv->j[1]->rep_j);
    char b [2];
    int taille =sprintf(b,"\x1b[%d;%dH",niv->h+7,0);
    write(1,b,taille);
}

