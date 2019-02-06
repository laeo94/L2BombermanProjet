#include "menu.h"

//Creation d'un nouveau menu avec le descriptif text
menu_t* createMenu(const char* text){
	menu_t* m =(menu_t*)malloc(sizeof(menu_t));
	m->parentmenu= NULL;
	m->namemenu=(char*)malloc((strlen(text)+1)*sizeof(char));
	strcpy(m->namemenu,text);
	m->nb=0;
	return m;
}

//Ajoute action au menu 
void addMenuAction (menu_t* m, const char* text,void(*f)()){
	if(m->nb==9){
		printf("Filled items no more place\n");
	}else {	
		m->tab[m->nb].type=action;
		m->tab[m->nb].choice.itemact.nameaction=(char*)malloc((strlen(text)+1)*sizeof(char));
		strcpy(m->tab[m->nb].choice.itemact.nameaction,text);
		m->tab[m->nb].choice.itemact.p=f;
		m->nb++;
	}
}

//Ajout sousmenu sm au menu 
void addSubMenu(menu_t* m, menu_t* sm){
	if(m->nb==9){
		printf("Filled items no more place\n");
	}else {
		if(sm->parentmenu== NULL){
			sm->parentmenu=m;
			m->tab[m->nb].type=submenu;
			m->tab[m->nb].choice.itemsubmenu=sm;
			m->nb++;
		}else printf("Impossible to add submenu\n");
	}
}

//Libere memoire au menu et sous menu
void deleteMenu(menu_t* m){
	if(m->parentmenu==NULL){
		free(m);
		m=NULL;
	}
}

//Lancement du menu

void freebuffer(){
	int a=0;
	while(a!='\n'&& a!=EOF) a=getchar();
}


void launchMenu(menu_t* m){
	//Affiche le descritif du menu
	printf("             %s\n",m->namemenu);
	printf("------------------------------------------------------------------\n");
	//Affiche les choix/items du menu avec numero
	int i;
	for(i=0;i<m->nb;i++){
		switch(m->tab[i].type){
			case action:printf("                    %d - %s\n",i+1,m->tab[i].choice.itemact.nameaction); break;
			case submenu:printf("                    %d - %s\n",i+1,m->tab[i].choice.itemsubmenu->namemenu);break;

		}
	}
        printf("      ( Appuyez sur la touche 'p' pour retourner au menu précédent )\n");

	//Attends la reponse de l'utilisateur
	char c = getchar();
	freebuffer();
	int ch;

	//Si menu parmis numero lance menu sinon la fonction
	if(c>=49 && c<=57){
		ch=c-49;
		switch(m->tab[ch].type){
			case action: system("clear"); m->tab[ch].choice.itemact.p(); break;
			case submenu: system("clear"); launchMenu(m->tab[ch].choice.itemsubmenu); break;
		}
	}

	//Choix 'p' (precedent)
	if(c=='p'){
		system("clear");
		if(m->parentmenu==NULL) {
			printf("Impossible no menu parent\n");
		}else {
			
			launchMenu(m->parentmenu);
		}
	}

}


 