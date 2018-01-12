/*
* Inzio modulo principale gestione delle collisioni.
* Il modulo si occupa di gestire tutte le collisioni .
*/
/**
* @file
* Modulo per la gestione delle collisioni
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
#include "collision.h"


extern int MASK; // livello di debug
#define DBG(A, B) {if ((A) & MASK) {B; } }
#define D1(a) DBG(1, a)
#define D2(a) DBG(2, a)

extern Snake s;
extern Apple a;
extern ALLEGRO_SAMPLE *effect;

bool collision_check(int x, int y, int fx, int fy, int width, int height, int fwidth, int fheight)
{
  if (x+width<=fx || y+height<=fy || fx+fwidth<=x || fy+fheight<=y)
    return false;
    /**non c'è collisione*/
    else
      return true;
      /**c'è collisione*/
}

void collision (Snake &s, Apple &a , int &score){

  D1(cout<<"collisione"<<endl);
  score++;
  al_play_sample(effect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
  a.x=(rand()%700);
  a.y=(rand()%500);
  D2(cout<<a.x<<endl);
  D2(cout<<a.y<<endl);
  s.nodi++;
  D1(cout<<"Incremento snake."<<endl);

}


/* Fine modulo gestione delle collisioni */
