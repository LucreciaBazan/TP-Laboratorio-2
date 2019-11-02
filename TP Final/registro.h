#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED

///Librerias
#include "divisa.h"
#include "cliente.h"

///Estructuras
typedef struct{
    int Opcion; //0 Pesos(ARG) a divisa y 1 divisa a peso(ARG)
    float montonEntrante, montoSaliente;
    Divisa d;
    Cliente c;
}Registro;

typedef struct{
    Registro r;
    struct NodoReg * siguiente;
}NodoReg;

///prototipados de funciones

NodoReg * inicListaRegistro();
NodoReg * CrearNodoRegistro (Registro r);
NodoReg * AgregarRegistroAlFinal(NodoReg * NuevoRegistro, NodoReg * lista);
NodoReg * BuscarUltimoRegistro (NodoReg * lista);
NodoReg * Transaccion0 (NodoReg * listareg, NodoCli ** listaCli, NodoDiv * listaDiv);
NodoReg * Transaccion1 (NodoReg * listareg, NodoCli ** listaCli, NodoDiv * listaDiv);
void MostrarNodoReg(NodoReg * nodo);
void MostrarRegistro (NodoReg * lista);
NodoReg * RecargarRegistros (NodoReg * lista);
void GuardarRegistros (NodoReg * lista);
#endif // REGISTRO_H_INCLUDED
