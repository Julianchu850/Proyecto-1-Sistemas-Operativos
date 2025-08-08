#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>//c++17
#include <algorithm>

namespace fs = std::filesystem;

std::vector<std::string> cargarInstrucciones(int pid, const std::string& rutaInstrucciones) {
    std::vector<std::string> instrucciones;
    std::string path = rutaInstrucciones + "/" + std::to_string(pid) + ".txt";

    std::ifstream archivo(path);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo de instrucciones para el PID " << pid << ": " << path << "\n";
        return instrucciones;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (!linea.empty()) 
            instrucciones.push_back(linea);
        
    }

    return instrucciones;
}

std::vector<Proceso> cargarProcesos(const std::string& rutaProcesos, const std::string& rutaInstrucciones) {
    std::vector<Proceso> procesos;
    std::ifstream archivo(rutaProcesos);

    if (!archivo.is_open()) {
        std::cerr << "[ERROR]No se pudo abrir el archivo de procesos: " << rutaProcesos << std::endl;
        return procesos;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        Proceso p;

        std::replace(linea.begin(), linea.end(), ',', ' ');
        std::istringstream ss(linea);
        std::string token;

        while (ss >> token) {
            if (token.find("PID:") == 0)
                p.pid = std::stoi(token.substr(4));
            else if (token.find("AX=") == 0)
                p.ax = std::stoi(token.substr(3));
            else if (token.find("BX=") == 0)
                p.bx = std::stoi(token.substr(3));
            else if (token.find("CX=") == 0)
                p.cx = std::stoi(token.substr(3));
            else if (token.find("Quantum=") == 0)
                p.quantum = std::stoi(token.substr(8));
        }

        //Validación Minima
        if (p.pid == 0 || p.quantum == 0) {
            std::cerr << "[ERROR] Proceso Invalido (PID o Quantum no definido): " << linea << std::endl;
            continue;
        }

        //Cargar instrucciones
        p.instrucciones = cargarInstrucciones(p.pid, rutaInstrucciones);
        procesos.push_back(p);
    }
    
    return procesos;
}