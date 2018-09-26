//
// Created by isaac on 24/09/18.
//

#ifndef MPOINTER_SERVER_MPOINTER_H
#define MPOINTER_SERVER_MPOINTER_H


#include <iostream>
#include "MPointerGC.h"

using namespace std;


template <class T>
class MPointer{
public:
    MPointer();
    MPointer<T> static New();

    //Metodos agregados por Gabriel (set_dato y get_dato)
    void set_dato(T);
    int get_dato();

    int getID() const;
    void setID(int);
    T * getData() const;
    void setData(T *);
    int getServerID();
    void setServerID(int);
    bool isOn();

    T &(operator *());
    T operator &();
    MPointer<T> & operator =(const MPointer<T> &);
    MPointer<T> & operator =(T);
    ~MPointer();

private:
    T *data;
    MPointerGC static *pointerGC;
    int id;
    int Dato;//Este atributo fue agregado por Gabriel
    bool on;
};


#endif //MPOINTER_SERVER_MPOINTER_H
