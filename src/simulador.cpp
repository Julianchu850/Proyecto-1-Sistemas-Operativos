#include "simulador.h"
#include "instrucciones.h"
#include "proceso.h"   // Aquí está la definición de Proceso
#include <iostream>
#include <vector>      // Aquí está la definición de std::vector

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
                 std::string instruccion = p.instrucciones[p.pc];

                    
                 int resultado_inst = ejecutarInstruccion(p, instruccion);
                 if (resultado_inst != 0){
                std::cout << "PC=" << p.pc << " | " << instruccion << " | RESULTADO = "<< resultado_inst <<std::endl;
                    } else {
                        std::cout << "PC=" << p.pc << " | " << instruccion << " | No hay resultado relevante" << std::endl;
                 }


                 //Si no hubo JMP, avanzar PC normalmente
                 if (instruccion.substr(0, 3) != "JMP"){
                     p.pc++;
                 }else{
                    if (p.repeticionesPC > 10) {
                        std::cerr << "[ERROR] Proceso " << p.pid
                                  << " se ha quedado en un bucle infinito. Proceso Terminado" << std::endl;
                        p.estado = TERMINATED; // Termina el proceso si se detecta un bucle infinito
                        break;
                    }
                 }

                    
                 instruccionesEjecutadas++;
           }

                    // Verificar si terminó después de su quantum
        if (p.estado != TERMINATED) {
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
