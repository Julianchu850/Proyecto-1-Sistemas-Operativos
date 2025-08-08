#include "instrucciones.h"
#include <sstream>
#include <iostream>
#include <cctype>

int& obtenerRegistro(Proceso& p, const std::string& reg) {
    if (reg == "AX") return p.ax;
    if (reg == "BX") return p.bx;
    if (reg == "CX") return p.cx;

    //En caso de Error Grave
    throw std::invalid_argument("Registro invalido: " + reg);
}

void ejecutarInstruccion(Proceso& p, const std::string& instruccion) {
    std::istringstream ss(instruccion);
    std::string comando;
    ss >> comando;

    if (comando == "NOP") {
        //No hace nada
        return;
    }

    if (comando == "INC") {
        std::string reg;
        ss >> reg;
        try {
            obtenerRegistro(p, reg)++;
        } catch (...) {
            std::cerr << "[ERROR] Registro invalido en INC: " << reg << std::endl;
        }
        return;
    }

    if (comando == "JMP") {
        int destino;
        ss >> destino;
        if (destino >= 0 && destino < p.instrucciones.size()) {
            p.pc = destino; // Cambia el PC al destino
        } else {
            std::cerr << "[ERROR] Salto invalido en JMP: " << destino << " (Proceso " << p.pid << ")" << std::endl;
            p.estado = TERMINATED; // Termina el proceso si el salto es invalido
        }
        return;
    }

    //Comandos tipo ADD, SUB, MUL
    std::string arg1, arg2;
    ss >> arg1 >> arg2;
    if (arg1.back() == ',') arg1.pop_back(); // Eliminar la coma al final
    ss >> arg2;

    try {
        int& destino = obtenerRegistro(p, arg1);
        if (std::isalpha(arg2[0])) {
            int valor = obtenerRegistro(p, arg2);

            if (comando == "ADD") destino += valor;
            else if (comando == "SUB") destino -= valor;
            else if (comando == "MUL") destino *= valor;
        } else {
            int constante = std::stoi(arg2);
            if (comando == "ADD") destino += constante;
            else if (comando == "SUB") destino -= constante;
            else if (comando == "MUL") destino *= constante;
        }
    } catch (...) {
        std::cerr << "[ERROR] Error al ejecutar instruccion: " << instruccion << " (Proceso " << p.pid << ")" << std::endl;
       
    }
}