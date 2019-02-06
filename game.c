#include "game.h"

//Met à jour le tableau des bombes du joueurs
/*void maj_bombe(joueur* j){
    j->b = realloc(j->b, sizeof(bombes)*j->nb_bombe);
    int i;
    for(i=0; i<j->nb_bombe; i++){
       j->b[i].tps_pose = 0;
       j->b[i].duree = 4;
    }
}*/

//Modifie les bonus du joueur
void modif_powerup(joueur* j, char c){
    switch(c){
        case '*' : j->portee++; j->p.type = portee; j->p.tps = time(NULL); j->p.actif = true; break;
        case '@' : /*j->nb_bombe++; j->p.type = bombe; j->p.tps = time(NULL); j->p.actif = true; maj_bombe(j);*/ break;
        case '+': /*j->vitesse++; j->p.type = vitesse; j->p.tps = time(NULL); j->p.actif = true;*/ break;
    }
}


//test si bonus, si oui modifie les bonus du joueur puis enleve le bonus de la carte
bool bonus (niveau* n,joueur* j,char c){
    if(c=='d' || c=='C'){
        if(n->carte[j->pos_j.x-1][j->pos_j.y] == '*'){
            modif_powerup(j,'*');
            n->carte[j->pos_j.x-1][j->pos_j.y]=' ';
            n->bonus[j->pos_j.x-1][j->pos_j.y]=' ';
            return true;
        }else if(n->carte[j->pos_j.x-1][j->pos_j.y]=='+'){
            modif_powerup(j,'+');
            n->carte[j->pos_j.x-1][j->pos_j.y]=' ';
            n->bonus[j->pos_j.x-1][j->pos_j.y]=' ';
            return true;
        }else if(n->carte[j->pos_j.x-1][j->pos_j.y]=='@'){
            modif_powerup(j,'@');
            n->carte[j->pos_j.x-1][j->pos_j.y]=' ';
            n->bonus[j->pos_j.x-1][j->pos_j.y]=' ';
            return true;
        }
    }else if(c=='q' || c=='D'){
        if(n->carte[j->pos_j.x-1][j->pos_j.y-2] == '*'){
            modif_powerup(j,'*');
            n->carte[j->pos_j.x-1][j->pos_j.y-2]=' ';
            n->bonus[j->pos_j.x-1][j->pos_j.y-2]=' ';
            return true;
        }else if(n->carte[j->pos_j.x-1][j->pos_j.y-2]=='+'){
            modif_powerup(j,'+');
            n->carte[j->pos_j.x-1][j->pos_j.y-2]=' ';
            n->bonus[j->pos_j.x-1][j->pos_j.y-2]=' ';
            return true;
        }else if(n->carte[j->pos_j.x-1][j->pos_j.y-2]=='@'){
            modif_powerup(j,'@');
            n->carte[j->pos_j.x-1][j->pos_j.y-2]=' ';
             n->bonus[j->pos_j.x-1][j->pos_j.y-2]=' ';
            return true;
        }
    }else if(c=='z' || c=='A'){
        if(n->carte[j->pos_j.x-2][j->pos_j.y-1] == '*'){
            modif_powerup(j,'*');
            n->carte[j->pos_j.x-2][j->pos_j.y-1]=' ';
            n->bonus[j->pos_j.x-2][j->pos_j.y-1]=' ';
            return true;
        }else if(n->carte[j->pos_j.x-2][j->pos_j.y-1]=='+'){
            modif_powerup(j,'+');
            n->carte[j->pos_j.x-2][j->pos_j.y-1]=' ';
            n->bonus[j->pos_j.x-2][j->pos_j.y-1]=' ';
            return true;
        }else if(n->carte[j->pos_j.x-2][j->pos_j.y-1]=='@'){
            modif_powerup(j,'@');
            n->carte[j->pos_j.x-2][j->pos_j.y-1]=' ';
            n->bonus[j->pos_j.x-2][j->pos_j.y-1]=' ';
            return true;
        }
    }else if(c=='s' || c=='B'){
        if(n->carte[j->pos_j.x][j->pos_j.y-1] == '*'){
            modif_powerup(j,'*');
            n->carte[j->pos_j.x][j->pos_j.y-1]=' ';
            n->bonus[j->pos_j.x][j->pos_j.y-1]=' ';
            return true;
        }else if(n->carte[j->pos_j.x][j->pos_j.y-1]=='+'){
            modif_powerup(j,'+');
            n->carte[j->pos_j.x][j->pos_j.y-1]=' ';
            n->bonus[j->pos_j.x][j->pos_j.y-1]=' ';
            return true;
        }else if(n->carte[j->pos_j.x][j->pos_j.y-1]=='@'){
            modif_powerup(j,'@');
            n->carte[j->pos_j.x][j->pos_j.y-1]=' ';
            n->bonus[j->pos_j.x][j->pos_j.y-1]=' ';
            return true;
        }
    }
    return false;
}

//test la collision avec les murs et de l'autre joueur
bool collision(niveau* n, joueur* j, char c){
    switch (c) {
        case 'd': if(n->carte[j->pos_j.x-1][j->pos_j.y] != ' ' ||(n->j[1]->pos_j.x == j->pos_j.x && n->j[1]->pos_j.y == j->pos_j.y+1)){ return true ;} break;
        case 'C': if(n->carte[j->pos_j.x-1][j->pos_j.y] != ' ' ||(n->j[0]->pos_j.x == j->pos_j.x && n->j[0]->pos_j.y == j->pos_j.y+1)){ return true ;} break;
        case 'q': if(n->carte[j->pos_j.x-1][j->pos_j.y-2] != ' '||(n->j[1]->pos_j.x == j->pos_j.x && n->j[1]->pos_j.y == j->pos_j.y-1)){ return true ;} break;
        case 'D': if(n->carte[j->pos_j.x-1][j->pos_j.y-2] != ' '||(n->j[0]->pos_j.x == j->pos_j.x && n->j[0]->pos_j.y == j->pos_j.y-1)){ return true ;} break;
        case 'z': if(n->carte[j->pos_j.x-2][j->pos_j.y-1] != ' ' ||(n->j[1]->pos_j.x == j->pos_j.x-1 && n->j[1]->pos_j.y == j->pos_j.y)){ return true ;} break;
        case 'A': if(n->carte[j->pos_j.x-2][j->pos_j.y-1] != ' '||(n->j[0]->pos_j.x == j->pos_j.x-1 && n->j[0]->pos_j.y == j->pos_j.y)){ return true ;} break;
        case 's': if(n->carte[j->pos_j.x][j->pos_j.y-1] != ' '  ||(n->j[1]->pos_j.x == j->pos_j.x+1 && n->j[1]->pos_j.y == j->pos_j.y)){ return true ;} break;
        case 'B': if(n->carte[j->pos_j.x][j->pos_j.y-1] != ' ' ||(n->j[0]->pos_j.x == j->pos_j.x+1 && n->j[0]->pos_j.y == j->pos_j.y)){ return true ;} break;
    }
    return false;
}


void explosion(niveau* n){
   int i; int k;
   for(i=0; i<2; i++){
     for(k=0; k<n->j[i]->nb_bombe; k++){
         if(n->j[i]->poser > 0){
            if(difftime(time(NULL), n->j[i]->b[k].tps_pose) >= n->j[i]->b[k].duree){
               n->carte[n->j[i]->b[k].p.x][n->j[i]->b[k].p.y] = ' ';
              //TEST si le joueur est sur la bombe et lui enlève de la vie
              if((n->j[i]->b[k].p.x == n->j[i]->pos_j.x-1 && n->j[i]->b[k].p.y == n->j[i]->pos_j.y-1)) n->j[i]->vie--;
            //TEST pour savoir si il y a des murs indestructibles dans la zone d'explosion
               int j = 1;
               //HAUT
               while(j <= n->j[i]->portee && n->carte[n->j[i]->b[k].p.x-j][n->j[i]->b[k].p.y] != '0'){
                   //TEST décrémentation des murs destructibles
                   int e = n->carte[n->j[i]->b[k].p.x-j][n->j[i]->b[k].p.y] - 48;
                   if(e > 1 && e < 10){
                       e--;
                       n->carte[n->j[i]->b[k].p.x-j][n->j[i]->b[k].p.y] = e + 48;
                   }else{
                       n->carte[n->j[i]->b[k].p.x-j][n->j[i]->b[k].p.y] = ' ';
                   }
                   //TEST si l'ennemi ou le joueur est dans la zone d'eplosion et lui enlève de la vie
                   if((n->j[0]->b[k].p.x-j == n->j[1]->pos_j.x-1 && n->j[0]->b[k].p.y == n->j[1]->pos_j.y-1) || (n->j[1]->b[k].p.x-j == n->j[1]->pos_j.x-1 && n->j[1]->b[k].p.y == n->j[1]->pos_j.y-1)) n->j[1]->vie--;
                   if((n->j[1]->b[k].p.x-j == n->j[0]->pos_j.x-1 && n->j[1]->b[k].p.y == n->j[0]->pos_j.y-1) || (n->j[0]->b[k].p.x-j == n->j[0]->pos_j.x-1 && n->j[0]->b[k].p.y == n->j[0]->pos_j.y-1)) n->j[0]->vie--;
           
                   j++;
               }
               j = 1;
               //BAS
               while(j <= n->j[i]->portee && n->carte[n->j[i]->b[k].p.x+j][n->j[i]->b[k].p.y] != '0'){
                   //TEST décrémentation des murs destructibles
                   int e = n->carte[n->j[i]->b[k].p.x+j][n->j[i]->b[k].p.y] - 48;
                   if(e > 1 && e < 10){
                      e--;
                      n->carte[n->j[i]->b[k].p.x+j][n->j[i]->b[k].p.y] = e+48;
                   }else{
                      n->carte[n->j[i]->b[k].p.x+j][n->j[i]->b[k].p.y] = ' ';
                   }
                   //TEST si l'ennemi ou le joueur est dans la zone d'eplosion et lui enlève de la vie
                   if((n->j[0]->b[k].p.x+j == n->j[1]->pos_j.x-1 && n->j[0]->b[k].p.y == n->j[1]->pos_j.y-1) || (n->j[1]->b[k].p.x+j == n->j[1]->pos_j.x-1 && n->j[1]->b[k].p.y == n->j[1]->pos_j.y-1)) n->j[1]->vie--;
                   if((n->j[1]->b[k].p.x+j == n->j[0]->pos_j.x-1 && n->j[1]->b[k].p.y == n->j[0]->pos_j.y-1) || (n->j[0]->b[k].p.x+j == n->j[0]->pos_j.x-1 && n->j[0]->b[k].p.y == n->j[0]->pos_j.y-1)) n->j[0]->vie--;
                 
                   j++;
               }
               j = 1;
               //GAUCHE
               while(j <= n->j[i]->portee && n->carte[n->j[i]->b[k].p.x][n->j[i]->b[k].p.y-j] != '0'){
                   //TEST décrémentation des murs destructibles
                   int e = n->carte[n->j[i]->b[k].p.x][n->j[i]->b[k].p.y-j] - 48;
                   if(e > 1 && e < 10){
                       e--;
                       n->carte[n->j[i]->b[k].p.x][n->j[i]->b[k].p.y-j] = e+48;
                   }else{
                       n->carte[n->j[i]->b[k].p.x][n->j[i]->b[k].p.y-j] = ' ';
                   }
                   //TEST si l'ennemi ou le joueur est dans la zone d'eplosion et lui enlève de la vie
                   if((n->j[0]->b[k].p.x == n->j[1]->pos_j.x-1 && n->j[0]->b[k].p.y-j == n->j[1]->pos_j.y-1) || (n->j[1]->b[k].p.x == n->j[1]->pos_j.x-1 && n->j[1]->b[k].p.y-j == n->j[1]->pos_j.y-1)) n->j[1]->vie--;
                   if((n->j[1]->b[k].p.x == n->j[0]->pos_j.x-1 && n->j[1]->b[k].p.y-j == n->j[0]->pos_j.y-1) || (n->j[0]->b[k].p.x == n->j[0]->pos_j.x-1 && n->j[0]->b[k].p.y-j == n->j[0]->pos_j.y-1)) n->j[0]->vie--;
                 
                   j++;
               }
               j = 1;
               //DROITE
               while(j <= n->j[i]->portee && n->carte[n->j[i]->b[k].p.x][n->j[i]->b[k].p.y+j] != '0'){
                   //TEST décrémentation des murs destructibles
                   int e = n->carte[n->j[i]->b[k].p.x][n->j[i]->b[k].p.y+j] - 48;
                   if(e > 1 && e < 10){
                       e--;
                       n->carte[n->j[i]->b[k].p.x][n->j[i]->b[k].p.y+j] = e+48;
                   }else{
                       n->carte[n->j[i]->b[k].p.x][n->j[i]->b[k].p.y+j] = ' ';
                   }
                   //TEST si l'ennemi ou le joueur est dans la zone d'eplosion et lui enlève de la vie
                   if((n->j[0]->b[k].p.x == n->j[1]->pos_j.x-1 && n->j[0]->b[k].p.y+j == n->j[1]->pos_j.y-1) || (n->j[1]->b[k].p.x == n->j[1]->pos_j.x-1 && n->j[1]->b[k].p.y+j == n->j[1]->pos_j.y-1)) n->j[1]->vie--;
                   if((n->j[1]->b[k].p.x == n->j[0]->pos_j.x-1 && n->j[1]->b[k].p.y+j == n->j[0]->pos_j.y-1) || (n->j[0]->b[k].p.x == n->j[0]->pos_j.x-1 && n->j[0]->b[k].p.y+j == n->j[0]->pos_j.y-1)) n->j[0]->vie--;
                 
                   j++;
               }
               n->j[i]->b[k].tps_pose = 0;
               n->j[i]->poser--; //remet à -1 le nb de bombes posees
            }
         }
     }
   }
}

//Pose la bombe dans la map
void pose_bombe(niveau* n, joueur* j){
    if(j->poser < j->nb_bombe){ 
        n->carte[j->pos_j.x-1][j->pos_j.y-1]='@';
        int i;
        for(i=0; i<j->nb_bombe; i++){
           if(j->nb_bombe>1 && j->b[i].tps_pose == 0){
              j->b[i].tps_pose = time(NULL);
              j->b[i].p.x = j->pos_j.x-1;
              j->b[i].p.y = j->pos_j.y-1;
              j->poser++; //met à +1 le nb de bombes posees
           }else if(j->nb_bombe == 1){
              j->b[i].tps_pose = time(NULL);
              j->b[i].p.x = j->pos_j.x-1;
              j->b[i].p.y = j->pos_j.y-1;
              j->poser++; //met à +1 le nb de bombes posees
           }
        }
    }
}

//Remet à la normale si joueur nb déjà sous l'effet d'un bonus
void power_down(joueur* j){
   switch(j->p.type){
        case bombe : /*j->p.actif = false;
                     j->nb_bombe--; 
                     j->p.tps = 0;
                     j->p.type = aucun;*/ break;
        case portee : j->p.actif = false;
                      j->portee--; 
                      j->p.tps = 0;
                      j->p.type = aucun; break;
        case vitesse : /*j->p.actif = false;
                       j->vitesse--; 
                       j->p.tps = 0;
                       j->p.type = aucun;*/ break;
        default : break;
   }
}

//TEST si la duree du bonus est finie et remise à la normale
void test_bonus(niveau* n){
   int i;
   for(i=0; i<2; i++){
      if(n->j[i]->p.actif == true){
         if(difftime(time(NULL), n->j[i]->p.tps) >= n->j[i]->p.duree){
            power_down(n->j[i]);
         }
      }
   }
}

//Mise a jour du deplacement des joueurs
int game_players(niveau* n){
    struct pollfd fds[2];
    fds[0].fd = STDIN_FILENO;
    fds[0].events =POLLIN;
    fds[1].fd = STDIN_FILENO;
    fds[1].events =POLLIN;
    int timeout = 2500;
    char buf[10];
    bool pose_b1, pose_b2;
    while(game_over(n) == false){ // Tant que la partie n'est pas finis
        int p = poll(fds,1,timeout);
        if(p ==-1){
            perror ("poll");
            return -1;
        }
        pose_b1= false;
        pose_b2= false;
        //Test si le joueur est sous l'effet d'un bonus
        test_bonus(n);
        for(int i=0;i<2;i++){
          if(fds[i].revents & POLLIN){
            read(fds[i].fd, buf,5);
            switch (buf[0]){
                case 'd':if(bonus(n,n->j[0],'d')==true){n->j[0]->pos_j.y=n->j[0]->pos_j.y+1;}
                else if(collision(n, n->j[0],'d') == false) { n->j[0]->pos_j.y=n->j[0]->pos_j.y+1;} break;
                case 'q':if(bonus(n,n->j[0],'q')==true){n->j[0]->pos_j.y=n->j[0]->pos_j.y-1;}
                else if(collision(n, n->j[0],'q') == false) {n->j[0]->pos_j.y=n->j[0]->pos_j.y-1;} break;
                case 'z':if(bonus(n,n->j[0],'z')==true){n->j[0]->pos_j.x=n->j[0]->pos_j.x-1;}
                else if(collision(n, n->j[0],'z') == false) {n->j[0]->pos_j.x=n->j[0]->pos_j.x-1;} break;
                case 's':if(bonus(n,n->j[0],'s')==true){n->j[0]->pos_j.x=n->j[0]->pos_j.x+1;}
                else if(collision(n, n->j[0],'s') == false) {n->j[0]->pos_j.x=n->j[0]->pos_j.x+1; }break;
                case 32 :pose_b1 = true; break ; //espace pour poser bombe
                case 3: return 1; //CTRL+C pour quitter la partie
           }
          
          if(buf[0]=='*'){ pose_b2 = true;}//* pour poser bombe
          if(buf[0]==27 && buf[1]==91){
            switch (buf[2]){
                case 'C':if(bonus(n,n->j[1],'C')==true){n->j[1]->pos_j.y=n->j[1]->pos_j.y+1;}
                else if(collision(n, n->j[1],'C') == false){n->j[1]->pos_j.y=n->j[1]->pos_j.y+1;}break;
                case 'D':if(bonus(n,n->j[1],'D')==true){n->j[1]->pos_j.y=n->j[1]->pos_j.y-1;}
                else if(collision(n, n->j[1],'D') == false){n->j[1]->pos_j.y=n->j[1]->pos_j.y-1;} break;
                case 'A':if(bonus(n,n->j[1],'A')==true){n->j[1]->pos_j.x=n->j[1]->pos_j.x-1;}
                else if(collision(n, n->j[1],'A') == false){n->j[1]->pos_j.x=n->j[1]->pos_j.x-1;} break;
                case 'B':if(bonus(n,n->j[1],'B')==true){n->j[1]->pos_j.x=n->j[1]->pos_j.x+1;}
                else if(collision(n, n->j[1],'B') == false){n->j[1]->pos_j.x=n->j[1]->pos_j.x+1;} break;
                }
           }
        }
        if(pose_b1 == true){
           pose_bombe(n,n->j[0]);
        }
        if(pose_b2 == true){
           pose_bombe(n,n->j[1]);
        }
      }
      //Test si une bombe explose avant d'afficher
      explosion(n);
      print_niveau(n);
    }
    return 1;
}

