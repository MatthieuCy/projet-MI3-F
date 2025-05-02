#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAILLE_MAX 100

typedef struct{
char* NOM;
char* ESPECE;
int ANNEE;
char* COMMENTAIRE;
int NUM;
int poids;
}Animal;

int calculerAge(int annee_naissance) {
    int annee_courante = 2025; // peut être rendu dynamique
    return annee_courante - annee_naissance;
}


void MENU(Animal* a){
  int c,f;
  char* b,d;
  printf("donner le ESPECE de l'animal,sinon ecrire 0 \n");
  scanf("%s, b");
    switch(b){
      case'chat': // a faire quand je pourrais verifier une ligne de caractère
      break;
      case'chien':
      break;
      case'hamster':
      break;
      case'autruche':
      break;
      case'0':
      break;
      default:
      break;
    }
    printf("donner le nom de l'animal,sinon ecrire 0 \n");
    scanf("%s", d);
        if(d!='0'){
      // a faire quand je pourrais verifier une ligne de caractère 
    }
     
  printf("donner l'age de l'animal,sinon ecrire 0 \n");
  c=2025-a->ANNEE;
  scanf("%d", f);
  
}
int main(){
int a;
char mot[TAILLE_MAX],jeune[]="jeune",senior[]="senior",adulte[]="adulte";

 while(a!=4){
printf(" ========== MENU ========== \n ecrire le chiffre pour la recherche:\n 1 - Espece\n 2 - Nom\n3 - âge\n4 - finir la recherche\n");
scanf("%d", &a);    
switch(a){
  case 1:scanf("%c", &a); 
      break;
  case 2:scanf("%d", &a); 
      break;
  case 3:
    printf("ecrire:\n sénior- âge>10\n adulte- 2<âge<10\n jeune- âge<2);  
    scanf("%s", &demande);
    if(demande==jeune){
      
    }
    else if(demande==senior){}
    else if(demande==adulte){}
      break;
  case 4:
  default:
      break;}
  return 0;}
