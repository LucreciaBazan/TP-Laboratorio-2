///Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
///Funciones
NodoReg * InicListaRegistro(){
    return NULL;
}

NodoReg * CrearNodoRegistro (Registro r){
    NodoReg * aux = (NodoReg*)malloc(sizeof(NodoReg));
    aux->r=r;
    aux->siguiente=NULL;
    return aux;
}

NodoReg * AgregarRegistroAlFinal(NodoReg * NuevoRegistro, NodoReg * lista){
    if(lista==NULL){
        lista=NuevoRegistro;
    }
    else{
        NodoReg * ultimo = BuscarUltimoRegistro(lista);
        ultimo->siguiente=NuevoRegistro;
    }
    return lista;
}

NodoReg * BuscarUltimoRegistro (NodoReg * lista){
    NodoReg * sig=lista;
    while (sig->siguiente!=NULL){
        sig=sig->siguiente;
    }
    return sig;
}

NodoReg * Transaccion0 (NodoReg * listaReg, NodoCli ** listaCli, NodoDiv * listaDiv){
    NodoCli * auxCli=NULL;
    NodoDiv * auxDiv=NULL;
    NodoReg * NuevoRegistro;
    Registro r;
    r.Opcion=0;
    char control='s';
    do{
        printf("Ingrese divisa de cambio\n");
        fflush(stdin);
        gets(r.d.nombre);
        auxDiv=BuscarDivisa(listaDiv,r.d.nombre);
        if (auxDiv==NULL){
            printf("Error: Divisa no encontrada ''%s''",r.d.nombre);
            printf("Desea volver a intentar? s/n (n cancelara la transaccion)\n");
            fflush(stdin);
            scanf("%c", &control);
            while(control!='s' && control!='n'){
                printf("Error: elija s/n \n");
                fflush(stdin);
                scanf("%c", &control);
            }
        system("cls");
        }
    }while(auxDiv==NULL && control=='s');
    if (control=='s'){
        r.d=auxDiv->d;
        printf("Ingrese la cantidad de pesos que desea convertir a ''%s''\n",r.d.nombre);
        fflush(stdin);
        scanf("%f", &r.montonEntrante);
        r.montoSaliente=(float)r.montonEntrante/r.d.valorVenta;
        printf("Usted recibira %.2f ''%s'' ",r.montoSaliente,r.d.nombre);
        ///A LO ULTIMO EL CLIENTE.
        printf("Ingrese su DNI o pasaporte\n");
        fflush(stdin);
        scanf("%i", &r.c.DNIoPasaporte);
        auxCli=BuscarCliente(*listaCli,r.c.DNIoPasaporte);
        if (auxCli!=NULL){
            r.c=auxCli->c;
        }else{
            printf("su/s nombre/s\n");
            fflush(stdin);
            gets(r.c.nombre);
            printf("su/s apellido/s\n");
            fflush(stdin);
            gets(r.c.apellido);
            printf("Ingrese su nacionalidad\n");
            fflush(stdin);
            gets(r.c.nacionalidad);
            printf("Ingrese su telefono\n");
            fflush(stdin);
            gets(r.c.telefono);
            printf("Ingrese su direccion\n");
            fflush(stdin);
            gets(r.c.direccion);
            auxCli=CrearNodoCliente(r.c);
            (*listaCli)=AgregarAListaClientesPorDNI(*listaCli,auxCli);
        }
        NuevoRegistro=CrearNodoRegistro(r);
        listaReg=AgregarRegistroAlFinal(NuevoRegistro,listaReg);
    }
    return listaReg;
}

NodoReg * Transaccion1 (NodoReg * listaReg, NodoCli ** listaCli, NodoDiv * listaDiv){
    NodoCli * auxCli=NULL;
    NodoDiv * auxDiv=NULL;
    NodoReg * NuevoRegistro;
    Registro r;
    r.Opcion=1;
    char control='s';
    do{
        printf("Ingrese divisa a cambiar\n");
        fflush(stdin);
        gets(r.d.nombre);
        auxDiv=BuscarDivisa(listaDiv,r.d.nombre);
        if (auxDiv==NULL){
            printf("Error: Divisa no encontrada ''%s''",r.d.nombre);
            printf("Desea volver a intentar? s/n (n cancelara la transaccion)\n");
            fflush(stdin);
            scanf("%c", &control);
            while(control!='s' && control!='n'){
                printf("Error: elija s/n \n");
                fflush(stdin);
                scanf("%c", &control);
            }
        system("cls");
        }
    }while(auxDiv==NULL && control=='s');
    if (control=='s'){
        r.d=auxDiv->d;
        printf("Ingrese la cantidad de ''%s'' que desea convertir a pesos\n",r.d.nombre);
        fflush(stdin);
        scanf("%f", &r.montonEntrante);
        r.montoSaliente=(float)r.montonEntrante*r.d.valorCompra;
        printf("Usted recibira %.2f pesos ",r.montoSaliente);
        ///A LO ULTIMO EL CLIENTE.
        printf("Ingrese su DNI o pasaporte\n");
        fflush(stdin);
        scanf("%i", &r.c.DNIoPasaporte);
        auxCli=BuscarCliente(*listaCli,r.c.DNIoPasaporte);
        if (auxCli!=NULL){
            r.c=auxCli->c;
        }else{
            printf("su/s nombre/s\n");
            fflush(stdin);
            gets(r.c.nombre);
            printf("su/s apellido/s\n");
            fflush(stdin);
            gets(r.c.apellido);
            printf("Ingrese su nacionalidad\n");
            fflush(stdin);
            gets(r.c.nacionalidad);
            printf("Ingrese su telefono\n");
            fflush(stdin);
            gets(r.c.telefono);
            printf("Ingrese su direccion\n");
            fflush(stdin);
            gets(r.c.direccion);
            auxCli=CrearNodoCliente(r.c);
            (*listaCli)=AgregarAListaClientesPorDNI(*listaCli,auxCli);
        }
        NuevoRegistro=CrearNodoRegistro(r);
        listaReg=AgregarRegistroAlFinal(NuevoRegistro,listaReg);
    }
    return listaReg;
}
