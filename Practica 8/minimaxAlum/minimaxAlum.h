/*******************************************/
/* 		    minimaxAlum.h                  */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#define N 9

tNodo *jugadaAdversario(tNodo *t);
tNodo *PSEUDOminimax(tNodo *Nodo);

//Realiza la busqueda heuristica MiniMax

tNodo *MiniMax(tNodo *t, int jugador);

//Devuelve el valor minimo de una jugada

int valorMin(tNodo *t, int jugador);

//Devuelve el valor maximo de una jugada

int valorMax(tNodo *t, int jugador);

//Devuelve el entero más bajo pasado como parametro

int minimo(int vMin, int vMax);

//Devuelve el entero más alto pasado como parametro

int maximo(int vMax, int vMin);

/*
  if(!terminal)
    tal cual
  else if (limite < LIMITE)
    heuristica
    else
      tal cual con limite.
*/
