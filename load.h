#ifndef __load_h_LEBLANC_ONG__
#define __load_h_LEBLANC_ONG__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <time.h>

//struct position
typedef struct {
	int x;
	int y;
}position;

//type de bonus
typedef enum{
	vitesse,
	portee,
	bombe,
        aucun,
}type_b;

//struct power ups
typedef struct {
    type_b type; // vit:*, portee:+, bombe:@	
    time_t tps;
    int duree;
    bool actif;
}powerup;

//struct bombes
typedef struct{
   time_t tps_pose; //temps de la pose de la bombe
   position p; //position de la bombe dans la carte
   int duree; //duree avant explosion
}bombes;

//struct joueur
typedef struct{
	char rep_j; // 1er joueur : A ; 2ème joueur : B
	position pos_j;
	int nb_bombe; //nombre de bombe qu'un joueur peut poser soit 1
	int portee; //portee de la bombe
	int vitesse; //vitesse du joueur
	int vie;
        int poser; //nb de bombes poser sur la carte
        bombes* b; //tableau de bombes
        powerup p;
}joueur;

//struct d'un niveau
typedef struct {
	int h;
	int l;
	joueur* j[2];
	char** carte; //Représentation (x,y) de la carte sans les bonus
	char** bonus; //Représentation (x,y) de la carte des bonus
}niveau;

joueur* add_player(char rep, position p);
void delete_niveau(niveau* niv);
int myopen(char* filename);
niveau* create_niveau(char* filename);
void print_player(joueur *j, char rep);
bool game_over(niveau* n);
void print_niveau(niveau* niv);
void print_players (niveau* niv);

#endif
