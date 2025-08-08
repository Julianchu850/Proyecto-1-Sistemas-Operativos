#ifndef SIMULADOR_H
#define SIMULADOR_H
#include "instrucciones.h"
#include <vector>
#include "proceso.h"

void ejecutarSimulacion(std::vector<Proceso>& procesos);

#endif