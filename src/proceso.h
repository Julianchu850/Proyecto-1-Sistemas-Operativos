#ifndef PROCESO_H
#define PROCESO_H

#include <string>
#include <vector>

enum Estado {
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

struct Proceso {
    int pid;
    int pc = 0; // Program counter
    int ax = 0, bx = 0, cx = 0; // Registros
    int quantum = 0; // Tiempo de CPU asignado
    int repeticionesPC = 0; // Contador de repeticiones del PC
    int ultimoPC = -1; // Último valor del PC
    Estado estado = READY; // Estado del proceso
    std::vector<std::string> instrucciones; // Instrucciones del proceso
};

std::string estadoToString(Estado estado);

#endif