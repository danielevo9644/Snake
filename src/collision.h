/*Modulo per la gestione della collisione
*/
/**
* @file
* Header del modulo collisioni collision.cc
*/

/** funzione per il check delle collisioni tra due box,
* prende in input: x dello snake, y dello snake, x dell'apple, y dell'apple, larghezza e altezza dello snake e larghezza e altezza della apple.
*/
bool collision_check (int x, int y, int fx, int fy, int width, int height, int fwidth, int fheight);
/**funzione per la gestione della collisione
*/
void collision (Snake &s , Apple &a , int &score);


//fine modulo
