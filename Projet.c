#define SIZE 50

int affiche_animaux(Animal refuge){

  int i = 0, c = 0;
  int chien = 0, chat = 0, autruche = 0, hamster = 0;

  for(i; i <= 50; i++){
    if(strlen(refuge[i].nom) != 0){
      c++;
    }
  }
  printf("Il y a %d anilaux dans le refuge.\n", c);

  for(i = 0, i <= c; i++){

    if(refuge[i].nom == 'chien'){
      chien++;
    }

    if(refuge[i].nom == 'chat'){
      chat++;
    }

    if(refuge[i].nom == 'autruche'){
      autruche++;
    }

    if(refuge[i].nom == 'hamster'){
      hamster++;
    }

int main(){

  Animal refuge[SIZE];
    
    
