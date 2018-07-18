/*******************************************/
/* 		    tictactoe.c                    */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "tictactoe.h"

tNodo *NodoInicial()
{
   return crearNodo(tablero_inicial);
}

tNodo *crearNodo(int celdas[N])
{
   tNodo *Nodo = (tNodo *) malloc(sizeof(tNodo));
   int i, c;
   Nodo->vacias=0;
   for (i=0;i<N;i++){
         c=celdas[i];
         Nodo->celdas[i]=c;
         if (c==0)
	      Nodo->vacias=Nodo->vacias+1;
      }
   return Nodo;
}


tNodo *aplicaJugada(tNodo *actual, int jugador, int jugada){
    tNodo *nuevo = (tNodo *) malloc(sizeof(tNodo));
    memcpy(nuevo,actual,sizeof(tNodo));
    nuevo->celdas[jugada]=jugador;
    nuevo->vacias--;  // marca la posicion que indica pone la marca del jugador
    return nuevo;
}
int esValida(tNodo *actual, int jugada){
    return (jugada>=0 && jugada<9 && actual->celdas[jugada]==0) ;  // si esta vacia la posicion, la jugada es valido
}
int opuesto( int jugador){
    return (jugador * -1);//Jugador 1 y Jugador -1
}

int lleno(tNodo *s){
    return (s->vacias != 0);
}

int terminal(tNodo *Nodo, int jugador)
{
    unsigned opciones[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i=0,res=0;
    while (res==0 && i<8) {
      if(Nodo->celdas[opciones[i][0]] != 0 &&
         Nodo->celdas[opciones[i][0]] == Nodo->celdas[opciones[i][1]] &&
         Nodo->celdas[opciones[i][0]] == Nodo->celdas[opciones[i][2]])
           res=Nodo->celdas[opciones[i][2]];  //indica que jugador ocupa las casillas ganadoras
      i++;
    }
    return res*100;
}

int heuristica(tNodo *actual, int jugador)
{
  unsigned opciones[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
  int i, jug1, jug2, res;

  jug1 = 0;

  for(i = 0; i < OPERADOR; ++i)
  {
    if(((actual -> celdas[opciones[i][0]] == jugador) ||
      (actual -> celdas[opciones[i][0]] == BLANCA)) &&
      ((actual -> celdas[opciones[i][1]] == jugador) ||
      (actual -> celdas[opciones[i][0]] == BLANCA)) &&
      ((actual -> celdas[opciones[i][2]] == jugador) ||
      (actual -> celdas[opciones[i][0]] == BLANCA)))
        jug1++;
  }

  jugador = opuesto(jugador);
  jug2 = 0;

  for(i = 0; i < OPERADOR; ++i)
  {
    if(actual -> celdas[opciones[i][0]] == (jugador || BLANCA) &&
      actual -> celdas[opciones[i][1]] == (jugador || BLANCA) &&
      actual -> celdas[opciones[i][2]] == (jugador || BLANCA) )
        jug2++;
  }

  res = jug1 - jug2;

  return res;
}

////////////////////////////////////////
//  VISUALIZACI�N DE NodoS
////////////////////////////////////////

char marca(int i) {
   switch(i) {
     case 1:
          return 'X';
     case 0:
           return ' ';
     case -1:
          return 'O';
     default: return ' ';}
}

void dispNodo(tNodo *s) {
     printf("---+---+---\n");
     printf(" %c | %c | %c\n",marca(s->celdas[0]),marca(s->celdas[1]),marca(s->celdas[2]));
     printf("---+---+---\n");
     printf(" %c | %c | %c\n",marca(s->celdas[3]),marca(s->celdas[4]),marca(s->celdas[5]));
     printf("---+---+---\n");
     printf(" %c | %c | %c\n",marca(s->celdas[6]),marca(s->celdas[7]),marca(s->celdas[8]));
     printf("---+---+---\n\n");
}
