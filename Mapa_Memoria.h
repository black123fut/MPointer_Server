#ifndef MPOINTER_SERVER_MAPA_MEMORIA_H
#define MPOINTER_SERVER_MAPA_MEMORIA_H

#include "MPointer.h"
#include "MPointerGC.h"
#include <iostream>

using namespace std;

template <typename T>

class Mapa_Memoria{

private:

    MPointer<T> *heap; //puntero al heap de memoria
    LinkedList< MPointer<T> *>  *lista_memoria; //lista enlazada que almacenara todos los MPointer que apuntan al heap

public:
    Mapa_Memoria(int size_heap); //Constructor
    int reservar_memoria(int ID,int contador_direcciones);/*metodo para reservar memoria en heap para un MPointer,devuelve el tamano
                                                                del MPointer que acaba de almacenar en el heap para llevar el control de la
                                                                proxima direccion de memoria en la cual se almacenara el otro MPointer*/
    void asignar_dato(int ID,int dato);//asignar dato a un MPointer en el heap
    T obtener_dato(int ID);//obtener el dato de un MPointer almacenado en el heap
    MPointer<T>* buscar_Mpointer(int ID);//Buscar un MPointer en el heap


};

#endif //MPOINTER_SERVER_MAPA_MEMORIA_H
