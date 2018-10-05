#include "Server.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "../Mapa_Memoria.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

#define PORT 8080

using namespace rapidjson;

Server::Server(int reserved_memory) {
    size_heap = reserved_memory;
    contador_direcciones = 0;
    IDs = 100;
}

void Server::run() {
    Mapa_Memoria<int> memory(size_heap);
    char *buffer = new char[1024];


    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while (true) {

        valread = read(new_socket, buffer, 1024);
        bool poo = true;

        if (valread <= 0) {
            perror("Error server quitting");
            break;
        }
        else {
            // Lee el mensaje del cliente.

            string recieved = string(buffer, buffer + valread);
            strcpy(buffer, recieved.c_str());

            rapidjson::Document doc;

            doc.Parse(buffer);

            rapidjson::Value& val = doc["opcode"];

            if (strcmp(val.GetString(), "00") == 0) {
                contador_direcciones += memory.reservar_memoria(IDs, contador_direcciones);

                // Escribe la respuesta al cliente.

                Document response;

                response.SetObject();
                rapidjson::Document::AllocatorType& allocator = response.GetAllocator();

                response.AddMember("opcode", "01", allocator);
                response.AddMember("id", IDs, allocator);

                rapidjson::StringBuffer sbuffer;
                rapidjson::Writer<StringBuffer> writer(sbuffer);
                response.Accept(writer);


                cout << memory.buscar_Mpointer(IDs)->getID() << "      " << memory.buscar_Mpointer(IDs)->get_dato() <<
                "         " << memory.buscar_Mpointer(IDs);

                send(new_socket, sbuffer.GetString(), strlen(sbuffer.GetString()), 0);
                IDs += 1;
            }
            else if (strcmp(val.GetString(), "02") == 0) {
                Value& clientID = doc["serverID"];
                Value& data = doc["data"];

                memory.asignar_dato(clientID.GetInt(), data.GetInt());

                Document response;

                response.SetObject();
                rapidjson::Document::AllocatorType& allocator = response.GetAllocator();

                response.AddMember("opcode", "03", allocator);

                rapidjson::StringBuffer sbuffer;
                rapidjson::Writer<StringBuffer> writer(sbuffer);
                response.Accept(writer);

                cout << memory.buscar_Mpointer(clientID.GetInt())->getID() << "      " << memory.buscar_Mpointer(clientID.GetInt())->get_dato() <<
                "         " << memory.buscar_Mpointer(clientID.GetInt());

                send(new_socket, sbuffer.GetString(), strlen(sbuffer.GetString()), 0);
            }

            else if (strcmp(val.GetString(), "04") == 0) {
                rapidjson::Value& clientID = doc["serverID"];

                poo = memory.estaEnLista(clientID.GetInt());
                if (memory.estaEnLista(clientID.GetInt())){
                    cout << memory.buscar_Mpointer(clientID.GetInt())->getID() << "      " << memory.buscar_Mpointer(clientID.GetInt())->get_dato() <<
                         "         " << memory.buscar_Mpointer(clientID.GetInt());

                    memory.remover_MPointer(clientID.GetInt());
                }


                Document response;

                response.SetObject();
                rapidjson::Document::AllocatorType& allocator = response.GetAllocator();

                response.AddMember("opcode", "03", allocator);
                int tab = 0;
                if (!poo)
                    tab = 1;
                response.AddMember("message", tab, allocator);

                rapidjson::StringBuffer sbuffer;
                rapidjson::Writer<StringBuffer> writer(sbuffer);
                response.Accept(writer);

                send(new_socket, sbuffer.GetString(), strlen(sbuffer.GetString()), 0);
            }
            if (poo)
                printf("               Mensaje: %s\n", buffer);

        }
    }

}