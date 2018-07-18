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
     lim = 0;

     for (jugada = 0; jugada < N; ++jugada)
     {
          if(esValida(t, jugada))
          {
               intento = aplicaJugada(t, jugador, jugada);
               maxActual = valorMin(intento, opuesto(jugador), ++lim);

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

int valorMin(tNodo *t, int jugador, int lim)
{
     int valorMin, jugada;

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
                            opuesto(jugador), ++lim));
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

int valorMax(tNodo *t, int jugador, int lim)
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
                    valorMax = maximo(valorMax, valorMin(aplicaJugada(t, jugador, jugada), opuesto(jugador), ++lim));
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

tNodo *podaAB(tNodo *actual, int jugador)
{
     int alfa, beta, jugada, mejorJugada, prof, v, lim;
     tNodo *intento;

     intento = malloc(sizeof(tNodo));
     alfa = -10000;
     beta = +10000;
     mejorJugada = -1;
     prof = 0;
     lim = 0;

     for(jugada = 0; jugada <= N; ++jugada)
     {
          if(esValida(actual, jugada))
          {
            intento = aplicaJugada(actual, jugador, jugada);
            v = valorMinAB(intento, opuesto(jugador), prof++, alfa, beta, ++lim);


           if(v > alfa)
           {
                alfa = v;
                mejorJugada = jugada;
           }
      }

      ++jugada;

     }

     if(esValida(actual, mejorJugada))
          actual = aplicaJugada(actual, jugador, mejorJugada);

     return actual;
}

int valorMinAB(tNodo *actual, int jugador, int prof, int alfa, int beta, int lim)
{
     int vMin, jugada;
     tNodo *intento;

     intento = malloc(sizeof(tNodo));

     if(!terminal(actual, jugador))
     {
          vMin = terminal(actual, jugador);
     }
     else if (prof == LIMITE)
     {
          vMin = heuristica(actual, jugador);
     }
     else
     {
       jugada = 0;
        while(jugada <= N && alfa < beta)
        {
          if(esValida(actual, jugada))
          {
            intento = aplicaJugada(actual, jugador, jugada);
            beta = minimo(beta, valorMaxAB(intento, opuesto(jugador),
             ++prof, alfa, beta, ++lim));
          }

          ++jugada;
        }

        vMin = beta;
     }

     return vMin;
}

int valorMaxAB(tNodo *actual, int jugador, int prof, int alfa, int beta, int lim)
{
  int vMax, jugada;
  tNodo *intento;

  intento = malloc(sizeof(tNodo));

  if(!terminal(actual, jugador))
     vMax = terminal(actual, jugador);
  else if(prof == LIMITE)
     vMax = heuristica(actual, jugador);

     else
     {
          jugada = 0;

          while (jugada <= N && alfa < beta)
          {
               if (esValida(actual, jugada))
               {
                    intento = aplicaJugada(actual, jugador, jugada);
                    alfa = maximo(alfa, valorMinAB(intento, opuesto(jugador),
                    ++prof, alfa, beta, ++lim));
               }

               ++jugada;
          }

          vMax = alfa;
     }

  return vMax;
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
