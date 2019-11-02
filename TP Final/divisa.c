///Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "divisa.h"
///Funciones
NodoDiv * InicListaDivisa (){
    return NULL;
}

NodoDiv * CrearNodoDivisa (Divisa d){
    NodoDiv * aux = (NodoDiv*)malloc(sizeof(NodoDiv));
    aux->d=d;
    aux->siguiente=NULL;
    return aux;
}

NodoDiv * LeerDivisa (NodoDiv * lista){
    NodoDiv * flag=NULL, * divisa =NULL;
    char control='s';
    Divisa d;
    do{
        printf("Ingrese el nombre de la divisa:\n");
        fflush(stdin);
        gets(d.nombre);
        flag=BuscarDivisa(lista,d.nombre);
        if (flag!=NULL){
            printf("ERROR:La divisa ''%s'' ya existe.\n",d.nombre);
            printf("Desea voler a intentarlo (de lo contrario se cancelara la carga)? s/n\n");
            fflush(stdin);
            scanf("%c", &control);
            while(control!='s' && control!='n'){
                printf("Error: elija s/n \n");
                fflush(stdin);
                scanf("%c", &control);
            }
            if (control=='n'){
                flag==NULL;
            }
        }
        system("cls");
    }while(flag!=NULL && control=='s');
    if(control=='s'){
        printf("Ingrese el valor de compra de la divisa %s:\n",d.nombre);
        fflush(stdin);
        scanf("%f", &d.valorCompra);
        printf("Ingrese el valor de venta de la divisa %s:\n",d.nombre);
        fflush(stdin);
        scanf("%f", &d.valorVenta);
        divisa=CrearNodoDivisa(d);
        lista=AgregarDivisaAlFinal(divisa,lista);
    }
    return lista;
}

NodoDiv * BuscarDivisa(NodoDiv * lista, char nombre[]){
    NodoDiv * sig;
    sig = lista;
    while ((sig !=NULL)&& (strcmpi(nombre,sig->d.nombre)!=0)){
        sig=sig->siguiente;
    }
    return sig;
}

NodoDiv * AgregarDivisaAlFinal(NodoDiv * divisa, NodoDiv * lista){
    if(lista==NULL){
        lista=divisa;
    }
    else{
        NodoDiv * ultimo = BuscarUltimaDivisa(lista);
        ultimo->siguiente=divisa;
    }
    return lista;
}

NodoDiv * BuscarUltimaDivisa (NodoDiv * lista){
    NodoDiv * sig=lista;
    while (sig->siguiente!=NULL){
        sig=sig->siguiente;
    }
    return sig;
}

NodoDiv * EditarDivisa (NodoDiv * lista){
    NodoDiv * editando=NULL;
    int control;
    char nombre[25];
    printf("Ingrese el nombre de la divisa que desea buscar");
    fflush(stdin);
    scanf("%s", &nombre);
    editando=BuscarDivisa(lista,nombre);
    Divisa d;
    if (editando!=NULL){
        do{
            printf("Datos actuales:\n");
            printf("\tDivisa: %s\n",editando->d.nombre);
            printf("1.\tValor Compra: %.2f\n",editando->d.valorCompra);
            printf("2.\tValor Compra: %.2f\n\n\n",editando->d.valorVenta);
            printf("Que desea editar 1. o 2. y 3. para salir?\n");
            fflush(stdin);
            scanf("%i",&control);
            switch (control){
            case 1:
                printf("Ingrese el nuevo Valor de compra\n");
                fflush(stdin);
                scanf("%f", &d.valorCompra);
                editando->d.valorCompra=d.valorCompra;
                break;
            case 2:
                printf("Ingrese el nuevo Valor de venta\n");
                fflush(stdin);
                scanf("%f", &d.valorVenta);
                editando->d.valorVenta=d.valorVenta;
                break;
            case 3:
                printf("Los cambios fueron aceptados\n");
                break;
            default:
                printf("ERROR: opcion incorrecta\n");
            }
        system("cls");
        }while (control!=3);
    }else{
        printf("No se encuentra la divisa\n");
    }
    return lista;
}

NodoDiv * BorraDivisa (NodoDiv * lista){
    char nombre[25],control;
    NodoDiv * aux=NULL;
    printf("Ingrese la divisa que desea borrar:\n");
    fflush(stdin);
    scanf("%s", &nombre);
    aux=BuscarDivisa(lista,nombre);
    if (aux!=NULL){
        printf("Esta seguro de eliminar la divisa %s s/n de lo contrario se cancelara esta accion\n",nombre);
        fflush(stdin);
        scanf("%s", &control);
        if (control=='s'){
            lista=BorrarNodoDivisa(nombre,lista);
        }
        else{
            printf("Operacion cancelada\n");
        }
    }
    else{
        printf("La divisa no existe o aun no se han cargado\n");
    }
}

NodoDiv * BorrarNodoDivisa (char nombre[], NodoDiv * lista){
    NodoDiv * sig;
    NodoDiv * ante;

    if((lista!=NULL) && (strcmpi(nombre,lista->d.nombre)==0)){
        NodoDiv * aux= lista;
        lista =lista->siguiente;
        free(aux);
    }
    else{
        sig=lista;
        while((sig!=NULL)&&(strcmpi(nombre,sig->d.nombre)!=0)){
            ante= sig;
            sig= sig->siguiente;
        }
        if (sig!=NULL)
        {
            ante->siguiente=sig->siguiente;
            free(sig);
        }
    }
    return lista;
}

void MostrarNodoDiv(NodoDiv * nodo){
    printf("Divisa: %s \n", nodo->d.nombre);
    printf("Valor compra: %.2f\n",nodo->d.valorCompra);
    printf("Valor venta: %.2f\n",nodo->d.valorVenta);

}

void MostrarDivisas (NodoDiv * lista){
    char control='s';
    NodoDiv * sig = lista;
    while (sig != NULL && control=='s')
    {
        MostrarNodoDiv(sig);
        sig= sig->siguiente;
        if (sig!=NULL){
            printf("\nDesea continuar? s/n\n");
            fflush(stdin);
            scanf("%c",&control);
        }
    }
}

void LFRDivisa(NodoDiv * lista){
    NodoDiv * aux;
    char nombre[25];
    printf("Ingrese el nombre de la divisa que desea buscar\n");
    fflush(stdin);
    gets(nombre);
    aux=BuscarDivisa(lista,nombre);
    if (aux!=NULL){
        MostrarNodoDiv(aux);
    }else{
        printf("No se encontro la divisa\n");
    }
}

NodoDiv * RecargarDivisas (NodoDiv * lista){
    FILE * archi;
    Divisa d;
    NodoDiv * nodo;
    archi = fopen("Divisas.dat","rb");
    if (archi!=NULL){
        while(fread(&d,sizeof(Divisa),1,archi)>0){
            nodo=CrearNodoDivisa(d);
            lista=AgregarDivisaAlFinal(nodo,lista);
        }
    }else{
        lista=InicListaDivisa();
    }
    fclose(archi);
    return lista;
}

void GuardarDivisas (NodoDiv * lista){
    FILE *archi;
    archi = fopen("Divisas.dat","wb");
    if (archi!=NULL){
        NodoDiv * sig=lista;
        Divisa d;
        while (sig!=NULL){
            d=sig->d;
            fwrite(&d,sizeof(Divisa),1,archi);
            sig=sig->siguiente;
        }
    }
    fclose(archi);
}
