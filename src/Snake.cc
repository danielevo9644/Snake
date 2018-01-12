

/**
* @mainpage Snake
*
* Gioco classico Snake creato con allegro5.
*
*  Vedere la documentazione della funzione ::main per maggiori dettagli
* sulle funzionalità e sulla loro implementazione.
*
* @author Daniele Mennella
*/

/**
* @file
* Funzione principale (main) del gioco
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

#include <assert.h>

using namespace std;

#include "define.h"
#include "data_structure.h"
#include "init_object.h"
#include "collision.h"



unsigned int MASK = 3; //livello di debug
#define DBG(A, B) {if ((A) & MASK) {B; } }
#define D1(a) DBG(1, a)
#define D2(a) DBG(2, a)



/**variabile score*/
int score = 0;
/**variabile  per il tempo*/
int tempo=0;

extern ALLEGRO_SAMPLE *effect;

/**allocamento apple nel main*/
Apple a;
/**allocamento snake nel main*/
Snake s;


/**Enum for the direction of the player**/
enum Direction {UP, LEFT, DOWN, RIGHT};

/**direction of snake**/
int dir = DOWN;


int main(int argc, char **argv){
  init_snake(s);
  init_apple(a);
   ALLEGRO_DISPLAY *display = NULL;

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
   if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }

   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }
   bool work = true, draw = true, menu = true;

   /** init and install components */
   al_init_primitives_addon();
   al_install_keyboard();
   al_install_mouse();
   al_init_image_addon();
   al_install_audio();
   al_init_acodec_addon();

   /** riservo lo spazio per i samples */
   al_reserve_samples(50); //più è grande il numero, più ram occupo
   al_set_new_display_flags(ALLEGRO_WINDOWED);
   display = al_create_display(Swidth,Sheight);

   al_set_window_position(display, 100, 0);
   al_set_window_title(display, "Snakee");
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }

   ALLEGRO_KEYBOARD_STATE keyState;

   /** set the font */
   al_init_font_addon();
   al_init_ttf_addon();
/**carico texture font*/
  ALLEGRO_FONT *mcfont = al_load_font("../media/fonts/Roboto-Bold.ttf", 75, 0);
  ALLEGRO_FONT *mcfont2 = al_load_font("../media/fonts/Roboto-Black.ttf", 30, 0);
/**carico texture image*/
  ALLEGRO_BITMAP *headup = al_load_bitmap("../media/head_up.bmp");
  ALLEGRO_BITMAP *headdown = al_load_bitmap("../media/head_down.bmp");
  ALLEGRO_BITMAP *headleft = al_load_bitmap("../media/head_left.bmp");
  ALLEGRO_BITMAP *headright = al_load_bitmap("../media/head_right.bmp");
  ALLEGRO_BITMAP *body = al_load_bitmap("../media/body.bmp");
  ALLEGRO_BITMAP *apple = al_load_bitmap("../media/apple.bmp");
/*carico audio*/
  effect=al_load_sample("../media/lifeUp.wav");

  ALLEGRO_COLOR color = al_map_rgb(255, 0, 0);

   ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
   /** INV: il timer deve essere definito, altrimenti bisogna abortire il programma */
   assert(timer);
   ALLEGRO_TIMER *VERME = al_create_timer(1.0);/**INV:timer per il tempo deve essere corretto*/
   assert(VERME);

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(VERME));
    al_register_event_source(event_queue, al_get_display_event_source(display));
   /** INV: la coda eventi deve essere creata correttamente */
   assert(event_queue);


   al_draw_text(mcfont, color, 70, 150, 0,
    "Press Enter to Start");
   al_draw_text(mcfont, color, 100, 250, 0,
    "Press Esc to Exit");
    al_draw_text(mcfont2,color,280,500,0,"Daniele Mennella");
     al_flip_display();

     while(menu){

       ALLEGRO_EVENT events;
       al_wait_for_event(event_queue, &events);

       if(events.type == ALLEGRO_EVENT_KEY_DOWN){
         switch (events.keyboard.keycode) {
           case ALLEGRO_KEY_ENTER:
           menu = false;

           break;

           case ALLEGRO_KEY_ESCAPE:
           menu = false;
           work = false;

           break;
         }


       }
       al_flip_display();


     }

     al_show_native_message_box(display, "Istruzioni","Comandi: Frecce direzionali", "\nEnter per avviare. \nEsc per uscire.",  NULL, ALLEGRO_MESSAGEBOX_WARN);
     al_start_timer(timer);
     al_start_timer(VERME);

  // -------------------------------------------------ciclo infinito ---------------------------------------------- //


    while(work){
      ALLEGRO_EVENT events;
      al_wait_for_event(event_queue, &events);
      //il gioco finisce quando si toccano i bordi o quando la testa tocca il corpo
       for(int i=1;i<s.nodi;i++){
              if(s.snake[0].x==s.snake[i].x && s.snake[0].y==s.snake[i].y && menu==false)
                    {work=false;
                    al_show_native_message_box(display, "Sconfitta","Hai perso","Vuoi riprovare?", NULL, ALLEGRO_MESSAGEBOX_WARN);}
              }
       if(s.snake[0].x<=0 || s.snake[0].x>=790 || s.snake[0].y<=0 || (s.snake[0].y>=590 && menu==false)) {
        work=false;
        al_show_native_message_box(display, "Sconfitta","Hai perso","Vuoi riprovare?", NULL, ALLEGRO_MESSAGEBOX_WARN);//ALLEGRO_MESSAGEBOX_YES_NO);
        //if (ALLEGRO_MESSAGEBOX_YES_NO = true ) {menu=true; work=true;}
        }


      if(events.type == ALLEGRO_EVENT_TIMER){
      if(events.timer.source == VERME) tempo++;
      if(events.timer.source == timer)
        {

          for(int i = s.nodi;i>0;i--)
          {
            s.snake[i].x=s.snake[i-1].x;
            s.snake[i].y=s.snake[i-1].y;
          }


          al_get_keyboard_state(&keyState);
          if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && dir!=LEFT)
          dir=RIGHT;
         else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT) && dir!=RIGHT)
          dir=LEFT;
         else if(al_key_down(&keyState, ALLEGRO_KEY_UP) && dir!=DOWN)
          dir=UP;
         else if(al_key_down(&keyState, ALLEGRO_KEY_DOWN) && dir!=UP)
          dir=DOWN;



          switch(dir){
                      case RIGHT: s.snake[0].x += movespeed;
                      break;
                      case LEFT: s.snake[0].x -= movespeed;
                      break;
                      case UP: s.snake[0].y -= movespeed;
                      break;
                      case DOWN: s.snake[0].y += movespeed;
                      break;
                      }

}

}
/**collisione tra apple e testa snake*/
if (collision_check(s.snake[0].x, s.snake[0].y, a.x, a.y, 20, 20, 20, 20))
{
  collision(s,a,score);

}

        if(draw){

           switch (dir) {
             case UP:
             al_draw_bitmap(headup, s.snake[0].x, s.snake[0].y, 0);
             break;
             case DOWN:
             al_draw_bitmap(headdown, s.snake[0].x, s.snake[0].y, 0);
             break;
             case LEFT:
             al_draw_bitmap(headleft, s.snake[0].x, s.snake[0].y, 0);
             break;
             case RIGHT:
             al_draw_bitmap(headright, s.snake[0].x, s.snake[0].y, 0);
             break;
           }
             al_draw_bitmap(apple, a.x, a.y, 0);

             for (int i = 1;i<s.nodi;i++){
               al_draw_bitmap(body, s.snake[i].x,s.snake[i].y,0);}



           al_draw_textf(mcfont2, color, 600, 5, 0, "Score : %i",score);
           //al_draw_text(mcfont2, color, 700, 5, 0, score_text);
           al_draw_textf(mcfont2, color, 50, 5, 0, "Tempo: %i",tempo);


           al_flip_display();
           al_clear_to_color(al_map_rgb(0,0,0));}
}





  /** dallocamento snake */
   delete [] s.snake;
  /** dallocamento risorse */
   al_destroy_bitmap(headup);
   al_destroy_bitmap(headdown);
   al_destroy_bitmap(headleft);
   al_destroy_bitmap(headright);
   al_destroy_bitmap(body);
   al_destroy_bitmap(apple);
   al_destroy_font(mcfont);
   al_destroy_font(mcfont2);
   al_destroy_sample(effect);
   al_destroy_timer(timer);
   al_destroy_timer(VERME);
   al_destroy_event_queue(event_queue);
   al_destroy_display(display);


   return 0;



}
