/*******************************************/
/* 		    main.c                         */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

/*
  IMPORTANTE!!!

  para compilar en un ide, hay que restablecer los archivos .h como cabeceras y
  borrar los .c del main

*/


#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"
#include "minimaxAlum.h"
#include "minimaxAlum.c"
#include "tictactoe.c"

int main()
{
    int jugador;  //+1 o -1
    int primero,ganador;
    tNodo *juego=NodoInicial();
    dispNodo(juego);

    printf("El Agente Inteligente juega con X \n El Jugador Humano con O \n Elige el turno 1:Primero o 2:Segundo ");
    scanf("%d",&primero); printf("\n");
    if (primero==1)
       jugador=-1; // Turno de Min
    else
        jugador=1; // Turno de Max

    ganador=terminal(juego,jugador);
    while(juego->vacias>0 && ganador==0){
       if (jugador==1)
          juego=(tNodo *) podaAB(juego, jugador);
       else
          juego=(tNodo *)jugadaAdversario(juego);

       dispNodo(juego);
       ganador=terminal(juego,jugador);
       jugador=opuesto(jugador);// turno del adversario
    }
    switch(ganador){
     case 100:
          printf("\n HE GANADOOOO\n"); break;
     case 0:
           printf("\n EMPATE\n"); break;
     case -100:
          printf("\n Increible pero has ganado tu :(( \n\n"); break;
     default: printf("\n algo ha salido mal en el juego ..\n");
     }


    system("pause");
    return 0;
}
