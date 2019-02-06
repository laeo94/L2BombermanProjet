#include <termios.h>
#include "menu.h"
#include "game.h"

//Passe le terminal en mode non canonique
int not_canonical(struct termios* old_t){
  struct termios new_t;

  /*Recupère param de l'entree standard stdin
  et stocke dans termios pointés par old_t sinon error*/
  if(tcgetattr(STDIN_FILENO,old_t)==-1){
    perror("Error : not_canonical mode");
    return EXIT_FAILURE;
  }
  new_t.c_iflag = old_t->c_iflag;
  new_t.c_oflag = old_t->c_oflag;
  new_t.c_cflag = old_t->c_cflag;
  new_t.c_lflag = 0;
  new_t.c_cc[VMIN] = 1;
  new_t.c_cc[VTIME] = 0;

  /*Fixe les parametres du term ci dessus en lisant la struct de new_t
  pointée par old_t ; les modif sont effectuées immédiatement avec TCSANOW*/

  if(tcsetattr(STDIN_FILENO, TCSANOW, &new_t) == -1){
    perror("Error: not_canonical mode");
    return EXIT_FAILURE;  
  }
  return 1;
}

//Passe le terminal en mode canonique
int canonical(struct termios* term){
  if(tcsetattr(STDIN_FILENO, TCSANOW, term) == -1){
    perror("Error: canonical mode");
    return EXIT_FAILURE;  
  }
  return 1;
}

void niveau1(){
    niveau* n = create_niveau("mods/mod1/niveaux/1");
    print_niveau(n);
    game_players(n);
    delete_niveau(n);
}

void niveau2(){
  niveau* n = create_niveau("mods/mod1/niveaux/2");
  print_niveau(n);
  game_players(n);
  delete_niveau(n);
}

void info(){
  printf("**********************Commandes du jeu**************************\n\n");
  printf("      Joueur 1(A) :  |       Joueur 2(B):\n");
  printf("           QZSD      |  Fleches directionnelles  -  se déplacer\n");
  printf("          ESPACE     |       Touche '*'          -  placer une bombe\n");
  printf("CTRL+C pour quitter la partie\n");
}

bool cont = true;

void quit() {
  printf("\n\n              Merci d'avoir joué à ce jeu !\n\n");
  printf("***********************AU REVOIR************************\n");
  cont = false;
}

int main (int argc, char* argv []){
  struct termios term;
  if(not_canonical(&term) == -1) return EXIT_FAILURE;
  //curseur cacher 
  write(1,"\x1b[?25l",9);

  //execution du jeu
        menu_t* m;
        menu_t* sm;
 
       //Menu
        m = createMenu("| BOMBERMAN | -- Menu Principal");

       //1st submenu "MOD1" 
        sm= createMenu("MOD1");
        addSubMenu(m,sm);
        addMenuAction(sm,"NIVEAU 1", niveau1);
        addMenuAction(sm,"NIVEAU 2", niveau2);
        
        //Affichage des commandes du jeu
        addMenuAction(m,"Commandes du jeu", info);

       //Fonction quit
        addMenuAction(m,"Quitter",quit);
 
        while(cont) launchMenu(m);
        deleteMenu(m);


  //reaffiche le curseur et le mode canonique
  write(1,"\x1b[?25h",8);
  if(canonical(&term) == -1) return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
