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

int valorMin(tNodo *t, int jugador, int lim);

//Devuelve el valor maximo de una jugada

int valorMax(tNodo *t, int jugador, int lim);

//Devuelve el entero más bajo pasado como parametro

int minimo(int vMin, int vMax);

//Devuelve el entero más alto pasado como parametro

int maximo(int vMax, int vMin);

//Realiza la busqueda heuristica con Poda alfa-beta

tNodo *podaAB(tNodo *actual, int jugador);

//Devuelve el valor minimo del arbol

int valorMinAB(tNodo *actual, int jugador, int prof, int alfa, int beta, int lim);

//Devuelve el valor maximo del arbol

int valorMaxAB(tNodo *actual, int jugador, int prof, int alfa, int beta, int lim);
