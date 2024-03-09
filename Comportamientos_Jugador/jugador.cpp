#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

Action ComportamientoJugador::think(Sensores sensores)
{

	switch (ult_accion)
	{
	case actWALK:
		switch (brujula)
		{
		case 0:
			fil--;
			break; // Norte
		case 1:
			col++;
			fil--;
			break; // Noreste
		case 2:
			col++;
			break; // Este
		case 3:
			col++;
			fil++;
			break; // Sureste
		case 4:
			fil++;
			break; // Sur
		case 5:
			fil++;
			col--;
			break; // Suroeste
		case 6:
			col--;
			break; // Oeste
		case 7:
			col--;
			fil--;
			break; // Noroeste
		}
		break;

	case actTURN_L:
		brujula = (brujula + 6) % 8;
		break;

	case actTURN_SR:
		brujula = (brujula + 1) % 8;
		break;
	}

	Action accion = actIDLE;

	// Casillas especiales
	switch (sensores.terreno[0])
	{
	case 'K':
		bikini = true;
		break;
	case 'D':
		zapatillas = true;
		break;
	case 'X':
		recargando = true;
		break;
	}

	if (sensores.reset)
	{
		bikini = zapatillas = false;
	}

	// Completar precipicios: Sabemos que los ult 3 filas y columnas son precipicios.
	Precipicios();

	// Número de pasos dependiendo del mapa
	int pasos = 0;

	if (mapaResultado.size() == 30) {
		pasos = 10;
	}
	else if (mapaResultado.size() == 50) {
		pasos = 20;
	}
	else if (mapaResultado.size() == 75) {
		pasos = 30;
	}
	else {
		pasos = 40;
	}

	if (recargando)
	{
		accion = actIDLE;

		if (sensores.bateria >= 4900 || sensores.vida < 1500)
		{
			recargando = false;
			accion = actWALK;
		}
	}
	else
	{
		if (sensores.terreno[2] == 'P' || sensores.terreno[2] == 'M' || sensores.terreno[1] == 'P' || sensores.terreno[1] == 'M' && contador < pasos)
		{
			accion = actTURN_L;
			contador++;
		}
		else if (sensores.terreno[3] == 'P' || sensores.terreno[3] == 'M' && contador < pasos)
		{
			accion = actTURN_SR;
			contador++;
		}
		else if (contador > pasos)
		{
			if (ult_accion == actTURN_L)
			{
				accion = actTURN_SR;
			}
			else
			{
				accion = actTURN_L;
			}
			contador = 0;
		}
		else
		{
			accion = actWALK;
			contador++;
		}
	}

	// Ver el mapa
	fil = sensores.posF;
	col = sensores.posC;
	Ver(sensores);

	ult_accion = accion;

	return accion;
}

void ComportamientoJugador::Ver(Sensores sensores)
{
	fil = sensores.posF;
	col = sensores.posC;

	mapaResultado[fil][col] = sensores.terreno[0];
	switch (sensores.sentido)
	{
	case 0:
		mapaResultado[fil - 1][col - 1] = sensores.terreno[1];
		mapaResultado[fil - 1][col] = sensores.terreno[2];
		mapaResultado[fil - 1][col + 1] = sensores.terreno[3];
		mapaResultado[fil - 2][col - 2] = sensores.terreno[4];
		mapaResultado[fil - 2][col - 1] = sensores.terreno[5];
		mapaResultado[fil - 2][col] = sensores.terreno[6];
		mapaResultado[fil - 2][col + 1] = sensores.terreno[7];
		mapaResultado[fil - 2][col + 2] = sensores.terreno[8];
		mapaResultado[fil - 3][col - 3] = sensores.terreno[9];
		mapaResultado[fil - 3][col - 2] = sensores.terreno[10];
		mapaResultado[fil - 3][col - 1] = sensores.terreno[11];
		mapaResultado[fil - 3][col] = sensores.terreno[12];
		mapaResultado[fil - 3][col + 1] = sensores.terreno[13];
		mapaResultado[fil - 3][col + 2] = sensores.terreno[14];
		mapaResultado[fil - 3][col + 3] = sensores.terreno[15];
		break;
	case 1:
		mapaResultado[fil - 1][col] = sensores.terreno[1];
		mapaResultado[fil - 1][col + 1] = sensores.terreno[2];
		mapaResultado[fil][col + 1] = sensores.terreno[3];
		mapaResultado[fil - 2][col] = sensores.terreno[4];
		mapaResultado[fil - 2][col + 1] = sensores.terreno[5];
		mapaResultado[fil - 2][col + 2] = sensores.terreno[6];
		mapaResultado[fil - 1][col + 2] = sensores.terreno[7];
		mapaResultado[fil][col + 2] = sensores.terreno[8];
		mapaResultado[fil - 3][col] = sensores.terreno[9];
		mapaResultado[fil - 3][col + 1] = sensores.terreno[10];
		mapaResultado[fil - 3][col + 2] = sensores.terreno[11];
		mapaResultado[fil - 3][col + 3] = sensores.terreno[12];
		mapaResultado[fil - 2][col + 3] = sensores.terreno[13];
		mapaResultado[fil - 1][col + 3] = sensores.terreno[14];
		mapaResultado[fil][col + 3] = sensores.terreno[15];
		break;
	case 2:
		mapaResultado[fil - 1][col + 1] = sensores.terreno[1];
		mapaResultado[fil][col + 1] = sensores.terreno[2];
		mapaResultado[fil + 1][col + 1] = sensores.terreno[3];
		mapaResultado[fil - 2][col + 2] = sensores.terreno[4];
		mapaResultado[fil - 1][col + 2] = sensores.terreno[5];
		mapaResultado[fil][col + 2] = sensores.terreno[6];
		mapaResultado[fil + 1][col + 2] = sensores.terreno[7];
		mapaResultado[fil + 2][col + 2] = sensores.terreno[8];
		mapaResultado[fil - 3][col + 3] = sensores.terreno[9];
		mapaResultado[fil - 2][col + 3] = sensores.terreno[10];
		mapaResultado[fil - 1][col + 3] = sensores.terreno[11];
		mapaResultado[fil][col + 3] = sensores.terreno[12];
		mapaResultado[fil + 1][col + 3] = sensores.terreno[13];
		mapaResultado[fil + 2][col + 3] = sensores.terreno[14];
		mapaResultado[fil + 3][col + 3] = sensores.terreno[15];
		break;
	case 3:
		mapaResultado[fil][col + 1] = sensores.terreno[1];
		mapaResultado[fil + 1][col + 1] = sensores.terreno[2];
		mapaResultado[fil + 1][col] = sensores.terreno[3];
		mapaResultado[fil][col + 2] = sensores.terreno[4];
		mapaResultado[fil + 1][col + 2] = sensores.terreno[5];
		mapaResultado[fil + 2][col + 2] = sensores.terreno[6];
		mapaResultado[fil + 2][col + 1] = sensores.terreno[7];
		mapaResultado[fil + 2][col] = sensores.terreno[8];
		mapaResultado[fil][col + 3] = sensores.terreno[9];
		mapaResultado[fil + 1][col + 3] = sensores.terreno[10];
		mapaResultado[fil + 2][col + 3] = sensores.terreno[11];
		mapaResultado[fil + 3][col + 3] = sensores.terreno[12];
		mapaResultado[fil + 3][col + 2] = sensores.terreno[13];
		mapaResultado[fil + 3][col + 1] = sensores.terreno[14];
		mapaResultado[fil + 3][col] = sensores.terreno[15];
		break;
	case 4:
		mapaResultado[fil + 1][col + 1] = sensores.terreno[1];
		mapaResultado[fil + 1][col] = sensores.terreno[2];
		mapaResultado[fil + 1][col - 1] = sensores.terreno[3];
		mapaResultado[fil + 2][col + 2] = sensores.terreno[4];
		mapaResultado[fil + 2][col + 1] = sensores.terreno[5];
		mapaResultado[fil + 2][col] = sensores.terreno[6];
		mapaResultado[fil + 2][col - 1] = sensores.terreno[7];
		mapaResultado[fil + 2][col - 2] = sensores.terreno[8];
		mapaResultado[fil + 3][col + 3] = sensores.terreno[9];
		mapaResultado[fil + 3][col + 2] = sensores.terreno[10];
		mapaResultado[fil + 3][col + 1] = sensores.terreno[11];
		mapaResultado[fil + 3][col] = sensores.terreno[12];
		mapaResultado[fil + 3][col - 1] = sensores.terreno[13];
		mapaResultado[fil + 3][col - 2] = sensores.terreno[14];
		mapaResultado[fil + 3][col - 3] = sensores.terreno[15];
		break;
	case 5:
		mapaResultado[fil + 1][col] = sensores.terreno[1];
		mapaResultado[fil + 1][col - 1] = sensores.terreno[2];
		mapaResultado[fil][col - 1] = sensores.terreno[3];
		mapaResultado[fil + 2][col] = sensores.terreno[4];
		mapaResultado[fil + 2][col - 1] = sensores.terreno[5];
		mapaResultado[fil + 2][col - 2] = sensores.terreno[6];
		mapaResultado[fil + 1][col - 2] = sensores.terreno[7];
		mapaResultado[fil][col - 2] = sensores.terreno[8];
		mapaResultado[fil + 3][col] = sensores.terreno[9];
		mapaResultado[fil + 3][col - 1] = sensores.terreno[10];
		mapaResultado[fil + 3][col - 2] = sensores.terreno[11];
		mapaResultado[fil + 3][col - 3] = sensores.terreno[12];
		mapaResultado[fil + 2][col - 3] = sensores.terreno[13];
		mapaResultado[fil + 1][col - 3] = sensores.terreno[14];
		mapaResultado[fil][col - 3] = sensores.terreno[15];
		break;
	case 6:
		mapaResultado[fil + 1][col - 1] = sensores.terreno[1];
		mapaResultado[fil][col - 1] = sensores.terreno[2];
		mapaResultado[fil - 1][col - 1] = sensores.terreno[3];
		mapaResultado[fil + 2][col - 2] = sensores.terreno[4];
		mapaResultado[fil + 1][col - 2] = sensores.terreno[5];
		mapaResultado[fil][col - 2] = sensores.terreno[6];
		mapaResultado[fil - 1][col - 2] = sensores.terreno[7];
		mapaResultado[fil - 2][col - 2] = sensores.terreno[8];
		mapaResultado[fil + 3][col - 3] = sensores.terreno[9];
		mapaResultado[fil + 2][col - 3] = sensores.terreno[10];
		mapaResultado[fil + 1][col - 3] = sensores.terreno[11];
		mapaResultado[fil][col - 3] = sensores.terreno[12];
		mapaResultado[fil - 1][col - 3] = sensores.terreno[13];
		mapaResultado[fil - 2][col - 3] = sensores.terreno[14];
		mapaResultado[fil - 3][col - 3] = sensores.terreno[15];
		break;
	case 7:
		mapaResultado[fil][col - 1] = sensores.terreno[1];
		mapaResultado[fil - 1][col - 1] = sensores.terreno[2];
		mapaResultado[fil - 1][col] = sensores.terreno[3];
		mapaResultado[fil][col - 2] = sensores.terreno[4];
		mapaResultado[fil - 1][col - 2] = sensores.terreno[5];
		mapaResultado[fil - 2][col - 2] = sensores.terreno[6];
		mapaResultado[fil - 2][col - 1] = sensores.terreno[7];
		mapaResultado[fil - 2][col] = sensores.terreno[8];
		mapaResultado[fil][col - 3] = sensores.terreno[9];
		mapaResultado[fil - 1][col - 3] = sensores.terreno[10];
		mapaResultado[fil - 2][col - 3] = sensores.terreno[11];
		mapaResultado[fil - 3][col - 3] = sensores.terreno[12];
		mapaResultado[fil - 3][col - 2] = sensores.terreno[13];
		mapaResultado[fil - 3][col - 1] = sensores.terreno[14];
		mapaResultado[fil - 3][col] = sensores.terreno[15];
		break;
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

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}