//Implementación del problema del vino

#include "stdio.h"

const LlenarJ4 = 1;   const LlenarJ3 = 2;
const VaciarJ4 = 3;   const VaciarJ3 = 4;
const LlenarJ4conJ3 = 5;    const LlenarJ3conJ4 = 6;
const VaciarJ4enJ3 = 7;   const VaciarJ3enJ4 = 8;
const NUM_OPERADORES = 8;

typedef struct tEstado {
  int x, y;
}

int testObjetivo(tEstado estado){
  return estado.x = 2;
}

//Interpretemos una salida a 0 como falso y distinta como 1
int esValido(int op, tEstado: estado){
  int valido;
  switch (op) {
    case LlenarJ4: valido = estado.x < 4;   break;
    case LlenarJ3: valido = estado.y < 3;   break;
    case VaciarJ4: valido = estado.x > 0;   break;
    case VaciarJ3: valido = estado.y > 0;   break;
    case LlenarJ4conJ3: valido = (estado.x + estado.y) >= 4 && (estado.x < 4) && (estado.y > 0);
      break;
    case LlenarJ3conJ4: valido = (estado.x + estado.y) >= 3 && (estado.x > 0) && (estado.y < 3);
      break;
    case VaciarJ4enJ3: valido = (estado.x + estado.y) <= 3 && (estado.x > 0) && (estado.y < 3);
      break;
    case VaciarJ3enJ4: valido = (estado.x + estado.y <= 4) && (estado.y > 0) && (estado.x < 4);
      break;
    default: valido = 0; break;
  }
  return valido;
}

tEstado aplicaOperador(int op, tEstado estado){
  tEstado = nuevo;
  nuevo = estado;
  switch (op) {
    case LlenarJ4: nuevo.x = 4;   break;
    case LlenarJ3: nuevo.y = 3;   break;
    case VaciarJ4: nuevo.x = 0;   break;
    case VaciarJ3: nuevo.y = 0;   break;
    case LlenarJ4conJ3: nuevo.x = 4;    nuevo.y = (estado.x + estado.y) - 4;
      break;
    case LlenarJ3conJ4: nuevo.x = (estado.x + estado.y) - 3;    nuevo.y = 3;
      break;
    case VaciarJ4enJ3: nuevo.x = 0;   nuevo.y = estado.y + estado.x;
      break;
    case VaciarJ3enJ4: nuevo.x = estado.x + estado.y;   nuevo.y = 0;
      break;
  }
  return nuevo;
}

tEstado inicializa(tEstado estado){
  estado.x = 0;   estado.y = 0;   return estado;
}

int main() {

tEstado estadoInicial, estado;
estadoInicial = inicializa(estadoInicial);
/*
if (esValido(LlenarJ3, estadoInicial) < 3 )
  estado = aplicaOperador(LlenarJ3, estadoInicial);
if (esValido(VaciarJ3enJ4, estado) == VaciarJ3enJ4) {
  estado = aplicaOperador(VaciarJ3enJ4, estado);
if (esValido(LlenarJ3, estado) == LlenarJ3)
  estado = aplicaOperador(LlenarJ3, estado);
if (esValido(VaciarJ3enJ4, estado) == VaciarJ3enJ4)
  estado = aplicaOperador(VaciarJ3enJ4, estado);
if (esValido(VaciarJ4, estado) == VaciarJ4) {
  estado = aplicaOperador(VaciarJ4, estado);
if (esValido(VaciarJ3enJ4)) {
*/
}
}
}


}
