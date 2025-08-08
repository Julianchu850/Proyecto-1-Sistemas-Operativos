#include "simulador.h"
#include "instrucciones.h"
#include <iostream>

void ejecutarSimulacion(std::vector<Proceso>& procesos) {
    bool todosTerminados = false;

    while (!todosTerminados) {
        todosTerminados = true;

        for (auto& p : procesos) {
            if (p.estado == TERMINATED) 
                continue;

             //Hay al menos un proceso que no ha terminado
             todosTerminados = false;

             std::cout << "\n[Cambio de contexto]" << std::endl;
             std::cout << "Ejecutando Proceso " << p.pid << " (Quantum = " << p.quantum << ")" << std::endl;
             p.estado = RUNNING;
             int instruccionesEjecutadas = 0;
             

             
             while (instruccionesEjecutadas < p.quantum && p.pc < p.instrucciones.size()) {
                int pcAntes = p.pc; // Guardar el valor del PC antes de ejecutar la instrucción
                 std::string instruccion = p.instrucciones[p.pc];

                 std::cout << "PC=" << p.pc << " | " << instruccion << std::endl;
                    
                 ejecutarInstruccion(p, instruccion);

                 //Si no hubo JMP, avanzar PC normalmente
                 if (instruccion.substr(0, 3) != "JMP"){
                     p.pc++;
                 }
                    
                 instruccionesEjecutadas++;

                 
                //Detectar procesos atorados en el mismo PC (bucle infinito)
                 if (p.pc == pcAntes) {
                     p.repeticionesPC++;
                     if (p.repeticionesPC > 10) {
                         std::cerr << "[ERROR] Proceso " << p.pid
                                   << " se ha quedado en un bucle infinito. Proceso Terminado" << std::endl;
                            p.estado = TERMINATED; // Termina el proceso si se detecta un bucle infinito
                            break;
                        }
                    } else {
                        p.repeticionesPC = 0; // Reiniciar el contador si el PC ha cambiado
                    }
                 

                 if (p.estado == TERMINATED) {
                    if (p.pc >= p.instrucciones.size()) {
                        p.estado = TERMINATED;
                        std::cout << "Proceso " << p.pid << " ha terminado." << std::endl;
                    } else {
                        p.estado = READY;
                        std::cout << "Proceso " << p.pid << " pausa en PC=" << p.pc << std::endl;
                    }
             }

            

            }

        }

        std::cout << "\nTodos los procesos han terminado." << std::endl;

    }
}
