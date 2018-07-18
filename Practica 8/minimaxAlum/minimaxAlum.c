/*******************************************/
/* 		    minimaxAlum.c                  */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "tictactoe.h"
//#include "minimaxAlum.h"



tNodo *PSEUDOminimax(tNodo *t) {
     int mejorJugada = -1;
     int puntos = -2;
     int i, temp;
     tNodo *intento=malloc(sizeof(tNodo));
     printf("\n Mi turno: \n");
     for(i = 0; i < 9; ++i){
      if (esValida(t,i)) {
            intento=aplicaJugada(t,1,i); //Intenta jugada
            temp =terminal(intento,-1); // Calcula el valor minimax
            if(temp > puntos) {
              puntos = temp;
              mejorJugada = i;
            }
      }}//for
      t=aplicaJugada(t,1,mejorJugada);
      return t;
}

tNodo *MiniMax(tNodo *t, int jugador)
{
     int max, maxActual, jugada, mejorJugada, lim;
     tNodo *intento;

     mejorJugada = -1;
     intento = malloc(sizeof(tNodo));
     max = -100;

     for (jugada = 0; jugada < N; ++jugada)
     {
          if(esValida(t, jugada))
          {
               intento = aplicaJugada(t, jugador, jugada);
               maxActual = valorMin(intento, opuesto(jugador));

               if(maxActual > max)
               {
                    max = maxActual;
                    mejorJugada = jugada;
               }
          }
     }

     intento = aplicaJugada(t, jugador, mejorJugada);

     return intento;
}

int valorMin(tNodo *t, int jugador)
{
     int valorMin, jugada, lim;

     lim = 0;

     if(terminal(t, jugador) != 0)
          valorMin = terminal(t, jugador);
     else if(lim < LIMITE)
          {
               valorMin = heuristica(t, jugador);
               lim++;
          }
          else
          {
               valorMin += 100;

               for (jugada = 0; jugada < N; jugada++)
               {
                    if(esValida(t, jugada))
                    {
                         valorMin = minimo(valorMin,
                           valorMax(aplicaJugada(t, jugador, jugada),
                            opuesto(jugador)));
                    }
               }
          }

     return valorMin;
}

int minimo(int vMin, int vMax)
{
     int min;

     if(vMin < vMax)
          min = vMin;
     else
          min = vMax;

     return min;
}

int valorMax(tNodo *t, int jugador)
{
     int valorMax, jugada;

     if(!terminal(t, jugador))
          valorMax = terminal(t, jugador);
     else
     {
          valorMax -= 100;

          for(jugada = 0; jugada < N; ++jugada)
          {
               if(esValida(t, jugada))
               {
                    valorMax = maximo(valorMax, valorMin(aplicaJugada(t, jugador, jugada), opuesto(jugador)));
               }
          }
     }

     return valorMax;
}

int maximo(int vMax, int vMin)
{
     int max;

     if(vMax > vMin)
          max = vMax;
     else
          max = vMin;

     return max;
}

tNodo *jugadaAdversario(tNodo *t) {
     int jugada = 0;
     printf("\nJugada ([0..8])?: ");
     scanf("%d", &jugada);
     while (!esValida(t,jugada))
     {
        printf("\n Intenta otra posicion del tablero \n");
        printf("\n");
        printf("\nJugada ([0..8])?: ");
        scanf("%d", &jugada);
     }
     t=aplicaJugada(t,-1,jugada);
     return t;
}
