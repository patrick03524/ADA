// ProyectoCaminoDelCaballero.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>
#define N 8

using namespace std;
int is_valid(int i, int j, int sol[N + 1][N + 1]) {
	if (i >= 1 && i <= N && j >= 1 && j <= N && sol[i][j] == -1) ///si la posicion esta dentro de la tabla y no ha sido ocupada
		return 1;                                                ///entonces es valido
	return 0;                                                    ///si no cumplio ninguna de las condiciones anteriores entonces no es valido
}

int knight_tour(int sol[N + 1][N + 1], int i, int j, int step_count, int x_move[], int y_move[]) {
	if (step_count == N * N)                                     ///si la cantidad de pasos es igual N*N, entonces ya todas las casillas estan llenas
		return 1;                                                ///y el algoritmo se ha completado

	int k;                                                       ///como son 8 las posibilidades que tiene el caballo para empezar, k es 8
	for (k = 0; k < 8; k++) {                                    ///es necesario iterar los arrays de posiciones
		int next_i = i + x_move[k];
		int next_j = j + y_move[k];

		if (is_valid(i + x_move[k], j + y_move[k], sol)) {       ///si la movida es valida, entonces en la matriz de solucion se muestra el numero
			sol[next_i][next_j] = step_count;                    ///del paso
			if (knight_tour(sol, next_i, next_j, step_count + 1, x_move, y_move))   ///luego es necesario ver si la nueva posicion (recursivo)
				return 1;                                                           ///nos esta llevando a la posicion, si es asi, retorna 1
			sol[i + x_move[k]][j + y_move[k]] = -1; /// backtracking                 //si no es así, se coloca -1 a la nueva posicion y regresando
		}
	}

	return 0;                                               ///si no es valido, retorna 0
}

int start_knight_tour() {
	int sol[N + 1][N + 1];                         /// se crea la matriz de soluciones
	int i, j;                                      /// las coordenadas x e y
	for (i = 1; i <= N; i++) {                     /// toda la matriz de soluciones se llena de -1
		for (j = 1; j <= N; j++) {
			sol[i][j] = -1;
		}
	}

	int x_move[] = { 2, 1, -1, -2, -2, -1, 1, 2 };              ///como son maximo 8 caminos que puede tomarse desde cualquier coordenada
	int y_move[] = { 1, 2, 2, 1, -1, -2, -2, -1 };              /// i,j, se crean dos arrays con los posibles caminos a tomar

	sol[1][1] = 0;                                              /// se coloca al caballo en la posicion x=1,  y=1

	if (knight_tour(sol, 1, 1, 1, x_move, y_move)) {            ///se colocan los parametros en la funcion knight_tour

		cout << "Si Hay Solucion:" << endl;
		for (i = 1; i <= N; i++) {                              ///se ejecuta, y si returna 1 se imprime la matriz de solucion
			for (j = 1; j <= N; j++) {
				cout << sol[i][j] << "	";
			}
			cout << " " << endl;
		}
		return 1;
	}
	else {
		cout << "No Hay Solucion" << endl;
	}
	return 0;
}

int main() {
	start_knight_tour();
	return 0;
}
