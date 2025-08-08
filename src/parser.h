#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "proceso.h"

std::vector<Proceso> cargarProcesos(const std::string& rutaProcesos, const std::string& rutaInstrucciones);

#endif