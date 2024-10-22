#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento
{

public:
  ComportamientoJugador(unsigned int size) : Comportamiento(size)
  {
    fil = col = 99;
    brujula = 0; // Norte
    ult_accion = actIDLE;
    bikini = zapatillas = recargando = false;
    posicionado = false;

    contador = 0;
    atasco = 0;
  }

  ComportamientoJugador(const ComportamientoJugador &comport) : Comportamiento(comport) {}
  ~ComportamientoJugador() {}

  Action think(Sensores sensores);
  int interact(Action accion, int valor);
  void Ver(Sensores sensores);
  void Precipicios();

private:
  // Declarar aquí las variables de estado
  Action ult_accion;
  int fil, col, brujula;
  bool bikini, zapatillas, recargando;
  bool posicionado;

  int contador, atasco;
};
#endif
