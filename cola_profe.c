#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct nodo{
    int data;
    struct nodo* sig;
}Nodo;

typedef struct cola{
    Nodo* cabecera, *final;
    int cursor;
}Cola;

Nodo* crearNodo(int data,int* error);
void crearCola(Cola* c, int* error);
void enQueue(int dato,Cola* cola, int* error);
void deQueue(Cola* cola, int* error);
void imprimir(Cola* cola,int* error);
void sort(Cola* arreglo, int tam,int* error);
void mezcla(Cola *arrIzq, int tamIzq, Cola *arrDer, int tamDer, Cola* arreglo,int* error);;

Nodo* crearNodo(int data, int* error){
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->data = data;
    nodo->sig = NULL;
    *error = 0;
    return nodo;
}

void crearCola(Cola* c, int* error){
    c->final = NULL;
    c->cabecera = NULL;
    c->cursor = 0;
    *error = 0;
}

void enQueue(int dato,Cola* cola, int* error){
    Nodo* nuevo = crearNodo(dato, error);
    if(cola->cabecera == NULL && cola->final == NULL){
        cola->cabecera = cola->final = nuevo;
        cola->cursor++;
    }
    else{
        cola->final->sig = nuevo;
        cola->final = nuevo;
        cola->cursor++;
    }
    *error = 0;
}
//elimiar elementos de la cola
void deQueue(Cola* cola, int* error){
    if(cola->cursor == 0) return;

    Nodo* cabecera = cola->cabecera;
    cola->cursor--;
    cola->cabecera = cabecera->sig;
    int dato = cabecera->data;
    free(cabecera);
    *error = 0;
}

void imprimir(Cola* cola,int* error){
    if(cola->cursor == 0 ) return;

    Nodo* temp = cola->cabecera;
    while (temp)
    {
        printf("%d \t",temp->data);
        temp = temp->sig;
    }
    printf("\n ----------------------------------------------------------------\n");
}

void sort(Cola* arreglo, int tam,int* error){
    if(tam>1){
        int i,j,k;
        int mitad=tam/2;
        Nodo* temp = arreglo->cabecera;
        Cola arrIzq; crearCola(&arrIzq,error);
        Cola arrDer; crearCola(&arrDer,error);
        for(i=0; i<mitad; i++){
            enQueue(temp->data,&arrIzq,error);
            temp = temp->sig;
        }
        for(j=0; j< (tam-mitad); j++){
            enQueue(temp->data,&arrDer,error);
            temp = temp->sig;
        }
        sort(&arrIzq,mitad,error);
        sort(&arrDer,tam-mitad,error);
        crearCola(arreglo,error);
        mezcla(&arrIzq,mitad, &arrDer,tam-mitad,arreglo,error);
    }
}

void mezcla(Cola* arrIzq, int tamIzq, Cola *arrDer, int tamDer, Cola* arreglo,int* error){
    int i=0,j=0;
    while(i<tamIzq && j<tamDer){
        if(arrIzq->cabecera->data < arrDer->cabecera->data){
            enQueue(arrIzq->cabecera->data,arreglo,error);
            deQueue(arrIzq,error);
            i++;
        } else{
            enQueue(arrDer->cabecera->data,arreglo,error);
            deQueue(arrDer,error);
            j++;
        }
    }
    while(j<tamDer){
        enQueue(arrDer->cabecera->data,arreglo,error);
            deQueue(arrDer,error);
            j++;
    }
    while(i<tamIzq){
        enQueue(arrIzq->cabecera->data,arreglo,error);
            deQueue(arrIzq,error);
            i++;
    }
}

void main(int argc, char** argv){
    int error;
    Cola c; 
    
    crearCola(&c,&error);

    enQueue(6, &c, &error);
    enQueue(-32, &c, &error);
    enQueue(-2, &c, &error);
    enQueue(53, &c, &error);
    enQueue(-3, &c, &error);
    enQueue(10, &c, &error);
    enQueue(1, &c, &error);

    imprimir(&c, &error);

    sort(&c, c.cursor, &error);

    imprimir(&c, &error);

    while(c.cabecera){
        printf(" elimado el primer numero\n");
        deQueue(&c, &error);
        imprimir(&c, &error);
    }
}