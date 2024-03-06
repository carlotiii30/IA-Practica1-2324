#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

Action ComportamientoJugador::think(Sensores sensores)
{

	Action accion = actIDLE;

	// Completar precipicios: Sabemos que los ult 3 filas y columnas son precipicios.
	Precipicios();

	// Ver el mapa
	fil = sensores.posF;
	col = sensores.posC;
	Ver(sensores);

	// Mostrar el valor de los sensores
	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC;
	switch (sensores.sentido)
	{
	case norte:
		cout << " Norte\n";
		break;
	case noreste:
		cout << " Noreste\n";
		break;
	case este:
		cout << " Este\n";
		break;
	case sureste:
		cout << " Sureste\n";
		break;
	case sur:
		cout << " Sur\n";
		break;
	case suroeste:
		cout << " Suroeste\n";
		break;
	case oeste:
		cout << " Oeste\n";
		break;
	case noroeste:
		cout << " Noroeste\n";
		break;
	}
	cout << "Terreno: ";
	for (int i = 0; i < sensores.terreno.size(); i++)
		cout << sensores.terreno[i];

	cout << "  Agentes: ";
	for (int i = 0; i < sensores.agentes.size(); i++)
		cout << sensores.agentes[i];

	cout << "\nColision: " << sensores.colision;
	cout << "  Reset: " << sensores.reset;
	cout << "  Vida: " << sensores.vida << endl
		 << endl;

	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}

int ComportamientoJugador::Ver(Sensores sensores)
{
	fil = sensores.posF;
	col = sensores.posC;

	int sensorIndex = 0;
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			mapaResultado[fil + i][col + j] = sensores.terreno[sensorIndex++];
		}
	}
}

void ComportamientoJugador::Precipicios()
{
	int size = mapaResultado.size();
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (i < 3 || i >= size - 3 || j < 3 || j >= size - 3)
			{
				mapaResultado[i][j] = 'P';
			}
		}
	}
}