
/*
* Inizio modulo inizializzazione oggetti. Il seguente modulo si occupa di inizializzare ogni nuovo oggetto che viene
* istanziato all'interno del gioco
*/

/**
* @file
* Modulo di inizializzazione di tutti gli oggetti del gioco
*/


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


#include "define.h"
#include "data_structure.h"
#include "init_object.h"

extern Snake s;
extern Apple a;
ALLEGRO_SAMPLE *effect;

/**iniziallizzazione della testa*/
void init_snake(Snake &s){
  s.snake=new Snake_node[MAX_SNAKE];
  s.snake[0].x=40;
  s.snake[0].y=40;
  s.nodi=1;
}



/**iniziallizzazione della apple*/
void init_apple(Apple &a){
  a.x=(rand()%750);
  a.y=(rand()%550);
}
