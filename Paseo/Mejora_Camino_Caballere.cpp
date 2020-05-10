// Mejora_Camino_Caballere.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

// Mejora con ayuda de la heuristica de Warndorff ordenando y encapsulando todo en una clase Board.

#include "pch.h"
#include <iostream>
#include <iomanip>												//Operaciones para el output (imprimir)
#include <array>												//Estructura para almacenar los resultados
#include <string>												//Entrada
#include <tuple>												//Estructuras para almacenar los resultados
#include <algorithm>											//Operaciones del Sort
using namespace std;

template<int N = 8>
class Board
{
public:
	array<pair<int, int>, 8> moves;								//Array de pares de tamaño 8 de los posibles movimientos del caballero.
	array<array<int, N>, N> tablero;							//Tablero: Matriz de tamaño N*N

	Board()
	{
		moves[0] = make_pair(2, 1);								//Ordena cada movimiento es pairs
		moves[1] = make_pair(1, 2);
		moves[2] = make_pair(-1, 2);
		moves[3] = make_pair(-2, 1);
		moves[4] = make_pair(-2, -1);
		moves[5] = make_pair(-1, -2);
		moves[6] = make_pair(1, -2);
		moves[7] = make_pair(2, -1);
	}

	array<int, 8> ordenaMoves(int x, int y) const	{				//Función que ordenará el resultado del movimiento de 2 en 2 retornando un array de 8 enteros de los movimientos(indices) de menor a mayor según cuantos caminos factibles tiene.
		array<tuple<int, int>, 8> counts;						//Array de tuplas de posiciones.
		for (int i = 0; i < 8; ++i)						
		{
			int dx = get<0>(moves[i]);							//Primer Movimiento
			int dy = get<1>(moves[i]);

			int c = 0;
			for (int j = 0; j < 8; ++j)
			{
				int x2 = x + dx + get<0>(moves[j]);				//Segundo Movimiento
				int y2 = y + dy + get<1>(moves[j]);

				if (x2 < 0 || x2 >= N || y2 < 0 || y2 >= N)		//Comprueba si aún está en el tablero
					continue;
				if (tablero[y2][x2] != 0)						//Comprueba de que la casilla no esté ocupada
					continue;

				c++;
			}

			counts[i] = make_tuple(c, i);						//se guarda c con su respectivo i, c es la cantidad de posibles caminos para cada  
		}														//uno de los caminos iniciales.

		sort(counts.begin(), counts.end());						//Se ordena lexicograficamente de menor a mayor según la cantidad de caminos posibles que tiene.

		array<int, 8> indices;									//Array que va a retornar con los indices de los caminos.
		for (int i = 0; i < 8; ++i)
			indices[i] = get<1>(counts[i]);
		return indices;
	}

	void recorridoCaballero(string start)
	{
		for (int v = 0; v < N; ++v)								//Rellena el tablero de 0's
			for (int u = 0; u < N; ++u)
				tablero[v][u] = 0;

		int x0 = start[0] - 'a';								//Recupera la posición inicial de x
		int y0 = N - (start[1] - '0');							//Recupera la posición inicial de y	
		tablero[y0][x0] = 1;									//Setea la primera casilla del tablero con 1

		array<tuple<int, int, array<int, 8>>, N* N> order;		//Array de tuplas de los movimientos de tamaño N*N
		order[0] = make_tuple(x0, y0, ordenaMoves(x0, y0));		//Selea la primera tupla con las posiciones y los posibles caminos

		int n = 0;												//Cantidad de movimientos que ha realizado
		while (n < N * N - 1)
		{
			int x = get<0>(order[n]);
			int y = get<1>(order[n]);

			bool ok = false;									//boolean que comprobará si falló el camino.
			for (int i = 0; i < 8; ++i)
			{
				int dx = moves[get<2>(order[n])[i]].first;		//Avance que tendra que realizar en x
				int dy = moves[get<2>(order[n])[i]].second;		//Avance que tendra que realizar en y

				if (x + dx < 0 || x + dx >= N || y + dy < 0 || y + dy >= N)			//Comprueba si aún está en el tablero
					continue;
				if (tablero[y + dy][x + dx] != 0)									//Comprueba de que la casilla no esté ocupada
					continue;

				++n;
				tablero[y + dy][x + dx] = n + 1;				//Setea en el tablero el movimiento que realizó
				order[n] = make_tuple(x + dx, y + dy, ordenaMoves(x + dx, y + dy));	//Crea una nueva tupla con los siguiente movimientos.
				ok = true;
				break;
			}

			if (!ok)											//En caso que falle hace un backtracking
			{
				tablero[y][x] = 0;
				--n;
			}
		}
	}

	template<int N>
	friend ostream& operator<<(ostream& out, const Board<N>& b);					//Operador para imprimir
};

template<int N>
ostream& operator<<(ostream& out, const Board<N>& b)								//Sobrecarga del operador para imprimir		
{
	for (int v = 0; v < N; ++v)
	{
		for (int u = 0; u < N; ++u)
		{
			if (u != 0) out << ",";
			out << setw(3) << b.tablero[v][u];
		}
		out << endl;
	}
	return out;
}

int main()
{
	Board<5> b1;
	b1.recorridoCaballero("a5");
	cout << b1 << endl;

	return 0;
}
