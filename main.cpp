#include <iostream>
#include "Mapa_Memoria.cpp"
#include "Server/Server.h"

int main() {
    Server server(1000);
    server.run();
    return 0;
}