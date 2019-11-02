#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

///Estructuras
typedef struct{
    int DNIoPasaporte;
    char telefono[25];
    char nacionalidad[25];
    char direccion[50];
    char apellido[50];
    char nombre[50];
}Cliente;

typedef struct{
    Cliente c;
    struct NodoCli * siguiente;
}NodoCli;

///prototipados de funciones
NodoCli * InicListaCliente();
NodoCli * CrearNodoCliente (Cliente c);
NodoCli * AgregarAListaClientesPorDNI (NodoCli * lista, NodoCli * NuevoCliente);
NodoCli * BuscarCliente (NodoCli * lista, int DNI);
NodoCli * AgregarClienteAlFinal(NodoCli * nuevoNodo, NodoCli * lista);
NodoCli * BuscarUltimoCliente (NodoCli * lista);
void MostrarNodoCli(NodoCli * nodo);
void MostrarClientes (NodoCli * lista);
void LFRCliente(NodoCli * lista);
NodoCli * RecargarClientes (NodoCli * lista);
void GuardarClientes (NodoCli * lista);

#endif // CLIENTE_H_INCLUDED
