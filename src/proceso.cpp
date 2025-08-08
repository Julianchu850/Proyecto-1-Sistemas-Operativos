#include "proceso.h"

std::string estadoToString(Estado e) {
    switch (e) {
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";
        case TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}