#ifndef DIVISA_H_INCLUDED
#define DIVISA_H_INCLUDED

///Estructuras
typedef struct{
    float valorCompra;
    float valorVenta;
    char nombre[25];
}Divisa;

typedef struct{
    Divisa d;
    struct NodoDiv * siguiente;
}NodoDiv;

///prototipados de funciones
NodoDiv * InicListaDivisa ();
NodoDiv * CrearNodoDivisa (Divisa d);
NodoDiv * LeerDivisa (NodoDiv * lista);
NodoDiv * BuscarDivisa(NodoDiv * lista, char nombre[]);
NodoDiv * AgregarDivisaAlFinal(NodoDiv * divisa, NodoDiv * lista);
NodoDiv * BuscarUltimaDivisa (NodoDiv * lista);
NodoDiv * EditarDivisa (NodoDiv * lista);
NodoDiv * BorraDivisa (NodoDiv * lista);
NodoDiv * BorrarNodoDivisa (char nombre[], NodoDiv * lista);
void MostrarNodoDiv(NodoDiv * nodo);
void MostrarDivisas (NodoDiv * lista);
void LFRDivisa(NodoDiv * lista);
NodoDiv * RecargarDivisas (NodoDiv * lista);
void GuardarDivisas (NodoDiv * lista);


#endif // DIVISA_H_INCLUDED
