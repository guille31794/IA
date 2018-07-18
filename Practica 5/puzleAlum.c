/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "puzle.h"



tEstado *crearEstado(int celdas[N][N])
{
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, ficha;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
      {
         ficha=celdas[i][j];
         estado->celdas[i][j]=ficha;
         estado->fila[ficha]=i;
         estado->col[ficha]=j;
      }
   return estado;
}


tEstado *estadoInicial()
{
   return crearEstado(puzle_inicial);
}


tEstado *estadoObjetivo()
{
   return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado *estado)
{
   return 1;
}

/* VISUALIZACI�N DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado)
{
   int i,j;

   for (i=0; i<N; i++)
   {
      for (j=0; j<N; j++)
         printf("%d",estado->celdas[i][j]);
      printf("\n");
   }
   printf("\n");
}


void dispOperador(unsigned op)
{
   switch(op)
   {
      case ARRIBA:    printf("Movimiento ARRIBA:\n"); break;
      case ABAJO:     printf("Movimiento ABAJO:\n"); break;
      case IZQUIERDA: printf("Movimiento IZQUIERDA:\n"); break;
      case DERECHA:   printf("Movimiento DERECHA:\n"); break;
   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

// Funcion auxiliar para comprobar si dos
//puzles tienen las fichas colocadas en el
// mismo orden en el tablero

int iguales(tEstado *s, tEstado *t)
{
  int i = 0, j = 0, iguales = 0;
  while  (i < N && iguales)
  {
    while (j < N && iguales)
    {
      iguales= s->celdas[i][j] == t->celdas[i][j];
      j++;
    }
  i++;
}
  return iguales;
}

int heuristica(tEstado *s)
{
  int cont, i, j;
  tEstado *final;

  final = estadoObjetivo();
  cont = 0;

  //Mal colocadas
  for(i = 0; i < N; ++i)
  {
    for(j = 0; j < N; ++j)
    {
      if((s -> fila[i][j] != final -> fila[i][j])
      || (s -> col[i][j] != final -> col[i][j]))
      {
        ++cont;
      }
    }
  }
  return cont;
}

int manhattan(tEstado *s)
{
  int cont, i, j;
  tEstado *final;

  final = estadoObjetivo();
  cont = 0;

  for(i = 0; i < N; ++i)
    for(j = 0; j < N; ++j)
    {
      cont += abs(s -> fila[i][j] - final -> fila[i][j])
              + abs(s -> col[i][j] - final -> col[i][j]);
    }

  return cont;
}

int testObjetivo(tEstado *estado)
{
  tEstado *estadoFinal;
  estadoFinal = estadoObjetivo();
  return iguales(estado, estadoFinal);
}


int esValido(unsigned op, tEstado *estado)
{
  int valido = 0, i, j;
  i =  estado->fila[0]; //filaDelHueco(*estado);
  j =  estado->col[0]; //columnaDelHueco(*estado);
  switch (op) {
    case ARRIBA:  if(i < 0) {
      valido = ARRIBA;   break; }
    case ABAJO:  if(i > (N-1)){
      valido = ABAJO;    break; }
    case IZQUIERDA: if(j > 0){
      valido =  IZQUIERDA;    break;  }
    case DERECHA: if(j < (N-1)) {
      valido = DERECHA;   break;  }
    default: valido = 0; break;
  }
  return valido;
}


tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
    int i, j, auxiliar, filaNueva, columnaNueva;
    i = estado->fila[0];
    j = estado->col[0];
    tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
    memcpy(nuevo, estado,sizeof(tEstado));  // Hace una copia del estado
    switch (op) {
      case ARRIBA: nuevo->fila[0] = i - 1; break;
      case ABAJO: nuevo->fila[0] = i + 1; break;
      case IZQUIERDA: nuevo->col[0] = j - 1; break;
      case DERECHA: nuevo->col[0] = j + 1; break;
    }
    filaNueva = nuevo->fila[0];
    columnaNueva = nuevo->col[0];
    auxiliar = nuevo->celdas[filaNueva][columnaNueva];
    nuevo->celdas[filaNueva][columnaNueva] = nuevo->celdas[i][j];
    nuevo->celdas[i][j] = auxiliar;
    return nuevo;
}

/*  int main()
{
  tEstado *estado1;
  tEstado *estado2;
  int i;

  estado1 = estadoInicial();
  estado2 = estadoObjetivo();

  //i = iguales(estado1, estado2);
    if(!iguales(estado1, estado2))
        printf("Son distintos\n" );

  dispEstado(estado1);

  return 0;
}
*/
