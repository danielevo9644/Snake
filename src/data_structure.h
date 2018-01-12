/*
*Modulo per la gestione di oggetti-player
*/
/**
* @file
* Header delle strutture dati
*/


/**struct per ogni nodo*/

  struct Snake_node{
  /**coordinate x attuali*/
  int x;
  /**coordinate y attuali*/
  int y;

};
/**struct per tutto lo snake*/

struct Snake{
  /**array di struct per il corpo*/
  Snake_node *snake;
  /**numero di nodi*/
  int nodi; 
};
/**struct della apple*/

struct Apple {
  /**coordinare x della apple*/
  int x;
  /**coordinate y della apple*/
  int y;
};
/*Fine modulo*/
