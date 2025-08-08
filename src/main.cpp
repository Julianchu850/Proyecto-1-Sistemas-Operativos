#include <iostream>
#include "proceso.h"
#include "parser.h"
#include "simulador.h"

int main() {
    std::string rutaProcesos = "procesos.txt";
    std::string rutaInstrucciones = "instrucciones";

    // Cargar procesos desde el archivo
    std::vector<Proceso> procesos = cargarProcesos(rutaProcesos, rutaInstrucciones);

    std::cout << "Se cargaron " << procesos.size() << " procesos." << std::endl;

    for (const Proceso& p : procesos) {
        std::cout << "PID: " << p.pid
                  << ", Quantum: " << p.quantum
                  << ", AX: " << p.ax
                  << ", BX: " << p.bx
                  << ", CX: " << p.cx
                  << ", Instrucciones: " << p.instrucciones.size()
                  << std::endl;
    }

    ejecutarSimulacion(procesos);
    
    return 0;

}

