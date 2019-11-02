#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"

///Estructuras de main.c
typedef struct{ /// Arreglo De Listas de Registros por clientes
    Cliente c;
    NodoReg * lista;
}Celda;

typedef struct{ ///Arbol de clientes
    Cliente c;
    struct nodoArbol * izq;
    struct nodoArbol * der;
}nodoArbol;

///prototipados de funciones
///Titulo
void Rep(char c, int j);
void Titulo();
void MenuPrincipal(NodoCli ** listaCli, NodoDiv ** listaDiv, NodoReg ** listaReg);
void transacciones(NodoCli ** listaCli, NodoDiv ** listaDiv, NodoReg ** listaReg);
NodoDiv * divisas(NodoDiv * listaDiv);
void clientes(NodoCli * listaCli);
void registros(NodoCli * listaCli, NodoDiv * listaDiv, NodoReg * listaReg);
///Arboles
nodoArbol * inicArbol ();
nodoArbol  * crearNodoArbol (Cliente c);
nodoArbol * CargandoArbol (nodoArbol * arbol, NodoCli * listaCli);
nodoArbol * cargarArbolOrdenado (nodoArbol * arbol, Cliente c);
void inorden (nodoArbol * arbol);
nodoArbol * buscarClienteEnArbol (nodoArbol * arbol, char apellido[]);
void MostrarPorApellido(nodoArbol * arbol);
///Arreglo de listas
int ValidasCliente (NodoCli * listaCli);
void CargarArregloDeListas (Celda arregloDeListas[],NodoReg * listaReg,NodoCli * listaCli);
void MostrarTransaccionesDelCliente(Celda arregloDeListas[], int validas);

///Funciones de main.c
void MostrarNodoReg(NodoReg * nodo){
    if (nodo->r.Opcion=0){
        printf("Cliente:\n");
        printf("\tDNI o pasaporte: %i\n", nodo->r.c.DNIoPasaporte);
        printf("\tApellido: %s \n", nodo->r.c.apellido);
        printf("\tNombre: %s \n", nodo->r.c.nombre);
        printf("\tNacionalidad: %s \n", nodo->r.c.nacionalidad);
        printf("\tdireccion: %s \n", nodo->r.c.direccion);
        printf("\tTelefono: %s \n", nodo->r.c.telefono);
        printf("\nTransaccion Peso a %s:\n",nodo->r.d.nombre);
        printf("\tMonto entrante: %.2f\n",nodo->r.montonEntrante);
        printf("\tMonto saliente: %.2f\n",nodo->r.montoSaliente);
    }else{
        printf("Cliente:\n");
        printf("\tDNI o pasaporte: %i\n", nodo->r.c.DNIoPasaporte);
        printf("\tApellido: %s \n", nodo->r.c.apellido);
        printf("\tNombre: %s \n", nodo->r.c.nombre);
        printf("\tNacionalidad: %s \n", nodo->r.c.nacionalidad);
        printf("\tdireccion: %s \n", nodo->r.c.direccion);
        printf("\tTelefono: %s \n", nodo->r.c.telefono);
        printf("\nTransaccion %s a Peso:\n",nodo->r.d.nombre);
        printf("\tMonto entrante: %.2f\n",nodo->r.montonEntrante);
        printf("\tMonto saliente: %.2f\n",nodo->r.montoSaliente);
    }
}

void MostrarRegistro (NodoReg * lista){
    char control='s';
    NodoReg * sig = lista;
    while (sig != NULL && control=='s')
    {
        MostrarNodoReg(sig);
        sig= sig->siguiente;
        if (sig!=NULL){
            printf("\nDesea continuar? s/n\n");
            fflush(stdin);
            scanf("%c",&control);
        }
    }
}

NodoReg * RecargarRegistros (NodoReg * lista){
    FILE * archi;
    Registro r;
    NodoReg * nodo;
    archi = fopen("Registros.dat","rb");
    if (archi!=NULL){
        while(fread(&r,sizeof(Registro),1,archi)>0){
            nodo=CrearNodoRegistro(r);
            lista=AgregarRegistroAlFinal(nodo,lista);
        }
    }else{
        lista=InicListaRegistro();
    }
    fclose(archi);
    return lista;
}

void GuardarRegistros (NodoReg * lista){
    FILE *archi;
    archi = fopen("Registros.dat","wb");
    Registro r;
    if (archi!=NULL){
        NodoReg * sig=lista;
        while (sig!=NULL){
            r=sig->r;
            fwrite(&r,sizeof(Registro),1,archi);
            sig=sig->siguiente;
        }
    }
    fclose(archi);
}

void Rep(char c, int j){
    int i;
    for (i=0;i<j;i++)
    {
        printf("%c",c);
    }
}

void Titulo(){
    printf("\n\t\t %c",201);
    Rep(205,46);
    printf("%c\n",187);
    printf("\t\t %c                                              %c\n",186,186);
	printf("\t\t %c                  BIENVENIDO                  %c\n",186,186);
	printf("\t\t %c                                              %c\n",186,186);
    printf("\t\t %c",204);
    Rep(205,46);
    printf("%c\n",185);
}

void MenuPrincipal(NodoCli ** listaCli, NodoDiv ** listaDiv, NodoReg ** listaReg){
  char salir = 1;
  int opcion = -1;
  do {
  	Titulo();

  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\tMENU PRINCIPAL                  %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\t[1]. Transacciones              %c\n",186,186);
  	printf("\t\t %c\t\t[2]. Divisas                    %c\n",186,186);
  	printf("\t\t %c\t\t[3]. Clientes                   %c\n",186,186);
  	printf("\t\t %c\t\t[4]. Registros                  %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\t[0]. Salir                      %c",186,186);
  	printf("\n\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c",200);
    Rep(205,46);
    printf("%c\n",188);
    printf("\n\t\t\t\tIngrese su opci%cn:", 162);
  	scanf("\t\t\t\t %i",&opcion );


  	switch (opcion) {

  		case 1:
  			transacciones(listaCli,listaDiv,listaReg);
  			break;

  		case 2:
            (*listaDiv)=divisas(*listaDiv);
            break;

  		case 3:
            clientes(*listaCli);
            break;

        case 4:
            registros(*listaCli, *listaDiv,*listaReg);
            break;

  		case 0:
  			salir = 0;
  			break;

        default:
            printf("Ingreso una opci%cn invalida, por favor intente nuevamente:\n",162);
            system("pause");
            system("cls");
            break;
  		}

  } while (salir);
}

void transacciones(NodoCli ** listaCli, NodoDiv ** listaDiv, NodoReg ** listaReg){
  char salir = 1;
  int opcion = -1;
  system("cls");

  do {
  	Titulo();

  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\tTRANSACCIONES:                  %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\t[1]. Peso a divisas             %c\n",186,186);
  	printf("\t\t %c\t\t[2]. Divisa a Peso              %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\t[0]. Salir                      %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c",200);
    Rep(205,46);
    printf("%c\n",188);
  	printf("\n\t\t\t\tIngrese su opci%cn: ",162);
    scanf(" %i",&opcion );

  	switch (opcion) {

  		case 1:
  		    system("cls");
  		    (*listaReg)=Transaccion0(*listaReg, listaCli, *listaDiv);
  		    system("pause");
            system("cls");
  			break;

  		case 2:
            system("cls");
            (*listaReg)= Transaccion1(*listaReg, listaCli, *listaDiv);
  		    system("pause");
            system("cls");
  			break;

  		case 0:
            system("cls");
  			salir = 0;
  			break;

        default:
            printf("Ingreso una opci%cn invalida, por favor intente nuevamente:\n",162);
            system("pause");
            system("cls");
            break;
  		}

  } while (salir);
}

NodoDiv * divisas(NodoDiv * listaDiv){
  char salir = 1;
  int opcion = -1;
  system("cls");
  do {

  	Titulo();

  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\tDIVISAS:                        %c",186,186);
  	printf("\n\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c \t\t[1]. Cargar divisa              %c\n",186,186);
  	printf("\t\t %c\t\t[2]. Editar divisa              %c\n",186,186);
    printf("\t\t %c\t\t[3]. Mostrar divisas            %c\n",186,186);
    printf("\t\t %c\t\t[4]. Buscar divisa              %c\n",186,186);
    printf("\t\t %c\t\t[5]. Borrar divisa              %c\n",186,186);
    printf("\t\t %c                                              %c",186,186);
    printf("\n\t\t %c\t\t[0]. Salir                      %c\n",186,186);
    printf("\t\t %c                                              %c",186,186);
    printf("\n\t\t %c",200);
    Rep(205,46);
    printf("%c\n",188);
  	printf("\n\t\t\t\tIngrese su opci%cn: ",162);
    scanf(" %i",&opcion );

  	switch (opcion) {

  		case 1:
            system("cls");
            listaDiv=LeerDivisa (listaDiv);
            fflush(stdin);
  		    system("pause");
            system("cls");
  			break;

  		case 2:
            system("cls");
            listaDiv=EditarDivisa (listaDiv);
  		    system("pause");
            system("cls");
  			break;

        case 3:
            system("cls");
            MostrarDivisas (listaDiv);
  		    system("pause");
            system("cls");
    		break;

        case 4:
            system("cls");
            LFRDivisa (listaDiv);
  		    system("pause");
            system("cls");
    		break;

        case 5:
            system("cls");
            listaDiv=BorraDivisa(listaDiv);
  		    system("pause");
            system("cls");
    		break;

        case 0:
            system("cls");
  			salir = 0;
  			break;

        default:
            printf("Ingreso una opci%cn invalida, por favor intente nuevamente\n",162);
            system("pause");
            system("cls");
            break;
  		}

  } while (salir);
  return listaDiv;
}

void clientes(NodoCli * listaCli){
    char salir = 1;
    int opcion = -1;
    system("cls");
    nodoArbol * arbol = inicArbol();
    arbol=CargandoArbol(arbol,listaCli);
    do {
  	Titulo();

  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\tCLIENTES:                       %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c \t\t[1]. Clientes por DNI           %c",186,186);
  	printf("\n\t\t %c \t\t[2]. Buscar un cliente por dni  %c\n",186,186);
  	printf("\t\t %c \t\t[3]. Buscar por apellido        %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\t[0]. Salir                      %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c",200);
    Rep(205,46);
    printf("%c\n",188);
  	printf("\n\t\t\t\tIngrese su opci%cn: ",162);
    scanf(" %i",&opcion );

  	switch (opcion) {

  		case 1:
  		    system("cls");
  		    MostrarClientes(listaCli);
  		    system("pause");
            system("cls");
  			break;

  		case 2:
            system("cls");
            LFRCliente(listaCli);
  		    system("pause");
            system("cls");
  			break;

        case 3:
            system("cls");
            MostrarPorApellido(arbol);
  		    system("pause");
            system("cls");
  			break;

  		case 0:
            system("cls");
  			salir = 0;
  			break;

        default:
            printf("Ingreso una opci%cn invalida, por favor intente nuevamente\n",162);
            system("pause");
            system("cls");
            break;
  		}

  } while (salir);
}

void registros(NodoCli * listaCli, NodoDiv * listaDiv, NodoReg * listaReg){
  char salir = 1;
  int opcion = -1;
  system("cls");

  do {
  	Titulo();

  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\tREGISTROS:                      %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c \t\t[1]. Ver registros              %c",186,186);
  	printf("\n\t\t %c \t\t[2]. Ver registro por cliente   %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c\t\t[0]. Salir                      %c\n",186,186);
  	printf("\t\t %c                                              %c",186,186);
  	printf("\n\t\t %c",200);
    Rep(205,46);
    printf("%c\n",188);
  	printf("\n\t\t\t\tIngrese su opci%cn: ",162);
    scanf(" %i",&opcion );

  	switch (opcion) {

  		case 1:
  		    system("cls");
  		    MostrarRegistro (listaReg);
  		    system("pause");
            system("cls");
  			break;

  		case 2:
            system("cls");
            int validas=ValidasCliente(listaCli);
            Celda * arregloDeListas=(Celda*)malloc(validas*sizeof(Celda));
            CargarArregloDeListas(arregloDeListas,listaReg,listaCli);
            MostrarTransaccionesDelCliente(arregloDeListas,validas);
  		    system("pause");
            system("cls");
  			break;

  		case 0:
            system("cls");
  			salir = 0;
  			break;

        default:
            printf("Ingreso una opci%cn invalida, por favor intente nuevamente\n",162);
            system("pause");
            system("cls");
            break;
  		}

  } while (salir);
}

///

nodoArbol * inicArbol (){
    return NULL;
}

nodoArbol  * crearNodoArbol (Cliente c){
    nodoArbol * aux= malloc(sizeof(nodoArbol));
    aux->c=c;
    aux->izq=NULL;
    aux->der= NULL;
    return aux;
}

nodoArbol * CargandoArbol (nodoArbol * arbol, NodoCli * listaCli){
    NodoCli * aux=listaCli;
    while (aux!=NULL){
        arbol=cargarArbolOrdenado(arbol,aux->c);
        aux=aux->siguiente;
    }
    return arbol;
}

nodoArbol * cargarArbolOrdenado (nodoArbol * arbol, Cliente c){
    if (arbol==NULL)
    {
        arbol= crearNodoArbol(c);
    }
    else
    {
        if (strcmpi(arbol->c.apellido,c.apellido)<0)
        {
            arbol->izq= cargarArbolOrdenado(arbol->izq,c);
        }
        else
        {
            arbol->der= cargarArbolOrdenado(arbol->der,c);
        }
    }
    return arbol;
}

nodoArbol * buscarClienteEnArbol (nodoArbol * arbol, char apellido[]){
    nodoArbol * rta = NULL;
    if (arbol!=NULL)
    {
        if (strcmpi(apellido, arbol->c.apellido)==0)
        {
            rta= arbol;
        }
        else
        {
            if (strcmpi(apellido, arbol->c.apellido)>0)
            {
                rta= buscarClienteEnArbol(arbol->izq, apellido);
            }
            else
            {
                rta= buscarClienteEnArbol(arbol->der, apellido);
            }
        }
    }
    return rta;
}

void MostrarPorApellido(nodoArbol * arbol){
    nodoArbol * aux=NULL;
    char apellido[50];
    printf("\nIngrese el apellido que desea buscar\n");
    fflush(stdin);
    gets(apellido);
    aux=buscarClienteEnArbol(arbol,apellido);
    if (aux!=NULL){
        printf("DNI o pasaporte: %i\n",aux->c.DNIoPasaporte);
        printf("Apellido: %s \n", aux->c.apellido);
        printf("Nombre: %s \n", aux->c.nombre);
        printf("Nacionalidad: %s \n", aux->c.nacionalidad);
        printf("direccion: %s \n", aux->c.direccion);
        printf("Telefono: %s \n", aux->c.telefono);
    }else{
        printf("\nNo se ha encontrado dicho apellido\n");
    }
}

///

int ValidasCliente (NodoCli * listaCli){
    NodoCli * aux=listaCli;
    int i=0;
    while (aux!=NULL){
        i++;
        aux=aux->siguiente;
    }
    return i;
}

void CargarArregloDeListas (Celda arregloDeListas[],NodoReg * listaReg,NodoCli * listaCli){
    NodoCli * auxCli=listaCli;
    NodoReg * auxReg;
    NodoReg * nuevoNodo;
    int i=0;
    while (auxCli!=NULL){
        arregloDeListas[i].c=auxCli->c;
        arregloDeListas[i].lista=InicListaRegistro();
        auxReg=listaReg;
        while(auxReg!=NULL){
            if(arregloDeListas[i].c.DNIoPasaporte==auxReg->r.c.DNIoPasaporte){
                nuevoNodo=CrearNodoRegistro(auxReg->r);
                arregloDeListas[i].lista=AgregarRegistroAlFinal(nuevoNodo,arregloDeListas[i].lista);
            }
            auxReg=auxReg->siguiente;
        }
        auxCli=auxCli->siguiente;
        i++;
    }
}

void MostrarTransaccionesDelCliente(Celda arregloDeListas[], int validas){
    int DNIoPasaporte,i=0;
    NodoReg * aux=NULL;
    printf("ingrese el DNI del cliente que desea buscar:\n");
    fflush(stdin);
    scanf("%i",&DNIoPasaporte);
    while (i<validas && aux==NULL){
        if (DNIoPasaporte==arregloDeListas[i].c.DNIoPasaporte){
            aux=arregloDeListas[i].lista;
            MostrarRegistro(aux);
        }
        i++;
    }
    if (aux==NULL){
        printf("Cliente No encontrado\n");
    }
}

int main(){
    NodoCli * listaCli=InicListaCliente(listaCli);
    NodoDiv * listaDiv=InicListaDivisa(listaDiv);
    NodoReg * listaReg=InicListaRegistro(listaReg);
    listaCli=RecargarClientes(listaCli);
    listaDiv=RecargarDivisas(listaDiv);
    listaReg=RecargarRegistros(listaReg);
    MenuPrincipal(&listaCli,&listaDiv,&listaReg);
    if (listaCli!=NULL){
        GuardarClientes(listaCli);
    }
    if (listaDiv!=NULL){
        GuardarDivisas(listaDiv);
    }
    if (listaReg!=NULL){
        GuardarRegistros(listaReg);
    }
    return 0;
}
