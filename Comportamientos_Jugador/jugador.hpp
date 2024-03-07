#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento
{

public:
  ComportamientoJugador(unsigned int size) : Comportamiento(size)
  {
    // Constructor de la clase
    // Dar el valor inicial a las variables de estado
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
  int fil, col;
  bool bikini, zapatillas, recargando;
};
#endif
