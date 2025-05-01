
typedef struct{
char* NOM;
char* ESPECE;
int ANNEE;
char* COMMENTAIRE;
int NUM;
int poids;
}Animal;

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




