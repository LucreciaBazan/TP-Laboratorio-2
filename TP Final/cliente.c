///Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
///Funciones
NodoCli * InicListaCliente(){
    return NULL;
}

NodoCli * CrearNodoCliente (Cliente c){
    NodoCli * aux = (NodoCli*)malloc(sizeof(NodoCli));
    aux->c=c;
    aux->siguiente=NULL;
    return aux;
}

NodoCli * AgregarAListaClientesPorDNI (NodoCli * lista, NodoCli * NuevoCliente){
    if (lista==NULL){
        lista=NuevoCliente;
    }else{
        if (NuevoCliente->c.DNIoPasaporte<lista->c.DNIoPasaporte){
            NuevoCliente->siguiente=lista;
            lista=NuevoCliente;
        }else{
            NodoCli * ante = lista;
            NodoCli * sig = lista->siguiente;
            while ((sig!=NULL)&&(NuevoCliente->c.DNIoPasaporte>sig->c.DNIoPasaporte)){
                ante = sig;
                sig = sig->siguiente;
            }
            NuevoCliente->siguiente=sig;
            ante->siguiente=NuevoCliente;
        }
    }
    return lista;
}

NodoCli * BuscarCliente (NodoCli * lista, int DNI){
    NodoCli * aux=NULL;
    if (lista!=NULL){
        aux=lista;
        while ((aux!=NULL)&&(aux->c.DNIoPasaporte!=DNI)){
            aux=aux->siguiente;
        }
    }
    return aux;
}

NodoCli * AgregarClienteAlFinal(NodoCli * nuevoNodo, NodoCli * lista){
    if(lista==NULL){
        lista=nuevoNodo;
    }
    else{
        NodoCli * ultimo = BuscarUltimoCliente(lista);
        ultimo->siguiente=nuevoNodo;
    }
    return lista;
}

NodoCli * BuscarUltimoCliente (NodoCli * lista){
    NodoCli * sig=lista;
    while (sig->siguiente!=NULL){
        sig=sig->siguiente;
    }
    return sig;
}

void MostrarNodoCli(NodoCli * nodo){
    printf("DNI o pasaporte: %i\n",nodo->c.DNIoPasaporte);
    printf("Apellido: %s \n", nodo->c.apellido);
    printf("Nombre: %s \n", nodo->c.nombre);
    printf("Nacionalidad: %s \n", nodo->c.nacionalidad);
    printf("direccion: %s \n", nodo->c.direccion);
    printf("Telefono: %s \n", nodo->c.telefono);
}

void MostrarClientes (NodoCli * lista){
    char control='s';
    NodoCli * sig = lista;
    while (sig != NULL && control=='s')
    {
        MostrarNodoCli(sig);
        sig= sig->siguiente;
        if (sig!=NULL){
            printf("\nDesea continuar? s/n\n");
            fflush(stdin);
            scanf("%c",&control);
        }
    }
}

void LFRCliente(NodoCli * lista){
    NodoCli * aux;
    int id;
    printf("Ingrese el DNI del cliente que desea buscar\n");
    fflush(stdin);
    scanf("%i", &id);
    aux=BuscarCliente(lista,id);
    if (aux!=NULL){
        MostrarNodoCli(aux);
    }else{
        printf("No se encontro al cliente\n");
    }
}

NodoCli * RecargarClientes (NodoCli * lista){
    Cliente c;
    NodoCli * nodo;
    FILE * archi;
    archi = fopen("Clientes.dat","rb");
    if (archi!=NULL){
        while(fread(&c,sizeof(Cliente),1,archi)>0){
            nodo=CrearNodoCliente(c);
            lista=AgregarClienteAlFinal(nodo,lista);
        }
    }else{
        lista=InicListaCliente();
    }
    fclose(archi);
    return lista;
}

void GuardarClientes (NodoCli * lista){
    FILE *archi;
    archi = fopen("Clientes.dat","wb");
    Cliente c;
    if (archi!=NULL){
        NodoCli * sig=lista;
        while (sig!=NULL){
            c=sig->c;
            fwrite(&c,sizeof(Cliente),1,archi);
            sig=sig->siguiente;
        }
    }
    fclose(archi);
}
