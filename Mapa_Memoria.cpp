#include "Mapa_Memoria.h"

#include <iostream>
#include "MPointer.h"
#include "MPointerGC.h"
#include "DataStructures/LinkedList.cpp"

using namespace std;

template <typename T>
Mapa_Memoria<T>::Mapa_Memoria(int size_heap) {
    lista_memoria = new LinkedList<MPointer<int>*>;
    cout<<"Lista memoria:"<<endl;
    cout<<lista_memoria<<endl;
    heap = (MPointer<int>*) malloc(size_heap);
    cout<<"heap:"<<endl;
    cout<<heap<< "\n" << "------------------------------------" <<endl;

    cout << "ID" << "       " << "Valor" << "       " << "Direccion" << endl;
}

template <typename T>
int Mapa_Memoria<T>::reservar_memoria(int IDs, int contador_direcciones) {
    MPointer<int> *x = new MPointer<int>();
    x=heap+contador_direcciones;
    x->setID(IDs);
   // cout << "puntero: " << x << endl;
    lista_memoria->add(x);
    return sizeof(x);
}


template <typename T>
void Mapa_Memoria<T>::asignar_dato(int ID, int dato) {
    for (int i=0;i<(lista_memoria->length());i++) {
        if (lista_memoria->get(i)->getID()==ID){
            (lista_memoria->get(i))->set_dato(dato);

        }
    }
//    cout << "Lista: \n" ;
//    for (int j = 0; j < lista_memoria->length(); ++j) {
//        cout << lista_memoria->get(j) ->get_dato() << ", ";
//    }
}

template <typename T>
T Mapa_Memoria<T>::obtener_dato(int ID) {
    for (int i=0;i<lista_memoria->length();i++){
        if (lista_memoria->get(i)->getID()==ID){
            return lista_memoria->get(i)->get_dato();
        }
    }
}

template <typename T>
MPointer<T>* Mapa_Memoria<T>::buscar_Mpointer(int ID) {
    for (int i=0;i<lista_memoria->length();i++){
        if (lista_memoria->get(i)->getID()==ID){
            return lista_memoria->get(i);
        }
    }
}

template <typename T>
void Mapa_Memoria<T>::remover_MPointer(int ID){
    for (int i = 0; i < lista_memoria->length(); i++) {
        if(lista_memoria->get(i)->getID()==ID){
            lista_memoria->remove(i);
        }
    }
}

template <typename T>
bool Mapa_Memoria<T>::estaEnLista(int id){
    for (int i = 0; i < lista_memoria->length(); i++) {
        if (lista_memoria->get(i)->getID() == id){
            return true;
        }
    }
    return false;
}

template class Mapa_Memoria<int>;
