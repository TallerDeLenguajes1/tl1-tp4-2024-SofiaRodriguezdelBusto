#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

struct Tarea
{
    int TareaID;
    char *Descripcion;
    int duracion;
}typedef Tarea;


struct Nodo
{
   Tarea T;
   struct Nodo *siguiente;
}typedef Nodo;

int numAleatorios(int min, int max);
Nodo *crearListaVacia();
Nodo *crearTarea(int id);
void agregarNodo(Nodo **listaPendientes, int *id);
void mostrarLista(Nodo **lista);
void eliminarPrimerNodo(Nodo **lista);
Nodo *quitarNodoporId(Nodo **listaPendientes, int id);
void agregarCompletados(Nodo **listaPendientes, Nodo **listaRealizados);
void consultarTareas(Nodo **listaPendientes, Nodo **listaRealizados);

int main()
{
   int id = 1000;
   Nodo *listaTareasPendientes = crearListaVacia();
   Nodo *listaTareasRealizadas = crearListaVacia();
   agregarNodo(&listaTareasPendientes,&id);
   printf("\nTareas pendientes");
   mostrarLista(&listaTareasPendientes);
   printf("\nTareas realizadas");
   mostrarLista(&listaTareasRealizadas);
   mostrarLista(&listaTareasPendientes);
   agregarCompletados(&listaTareasPendientes, &listaTareasRealizadas);
   printf("\nTareas pendientes");
   mostrarLista(&listaTareasPendientes);
   printf("\nTareas realizadas");
   mostrarLista(&listaTareasRealizadas);
   return 0;
}
int numAleatorios(int min, int max)
{
    int num;
    num = min + rand()%(max-min+1);
    return num;
}
Nodo *crearListaVacia()
{
    return NULL;
}
Nodo *crearTarea(int id)
{
    char *buff = (char *)malloc(sizeof(char)*100);
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->T.TareaID = id;
    nuevoNodo->T.duracion = numAleatorios(10,100);
    printf("\nIngrese la descripción de la tarea: ");
    fflush(stdin);
    gets(buff);
    nuevoNodo->T.Descripcion = (char *)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(nuevoNodo->T.Descripcion, buff);
    free(buff);
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void agregarNodo(Nodo **listaPendientes, int *id)
{
    int control;
    do{
        Nodo *tarea = crearTarea(*id);
        tarea->siguiente = *listaPendientes;
        *listaPendientes = tarea;
        (*id)++;
        printf("\nDesea agregar otra tarea(Ingrese 1 si lo desea. Caso contrario ingrese 0): ");
        scanf("%d", &control);
    }while(control != 0);
}

void mostrarLista(Nodo **lista)
{
    int cont = 0;
    Nodo *aux = *lista;
    while(aux != NULL)
    {
        printf("\nTarea %d", cont + 1);
        printf("\nId de la tarea: %d", aux->T.TareaID);
        printf("\nDescripción: %s", aux->T.Descripcion);
        printf("\nDuracion: %d", aux->T.duracion);
        aux = aux->siguiente;
        cont++;
    }
}


void eliminarPrimerNodo(Nodo **lista)
{
    Nodo *aux = *lista;
    if(aux != NULL)
    {
      *lista = aux->siguiente;
       free(aux);
    }
}

Nodo *quitarNodoporId(Nodo **listaPendientes, int id)
{
    Nodo *aux = *listaPendientes; 
    Nodo *anterior = *listaPendientes;
    while (aux != NULL && aux ->T.TareaID != id) {
        anterior = aux;
        aux = aux->siguiente;
    }
    if(aux != NULL)
    {
       anterior->siguiente = aux->siguiente;
       aux->siguiente = NULL;
    }
    return aux;
}
void agregarCompletados(Nodo **listaPendientes, Nodo **listaRealizados)
{
    int id;
    printf("\nIngrese el id del nodo que desea eliminar: ");
    scanf("%d", &id);
    Nodo *nodoQuitado = quitarNodoporId(listaPendientes,id);
    nodoQuitado->siguiente = *listaRealizados;
    *listaRealizados = nodoQuitado;
}

void consultarTareasporID(Nodo **listaPendientes, Nodo **listaRealizados, int id)
{
    Nodo *aux1 = *listaPendientes; 
    Nodo *aux2 = *listaRealizados;
    while (aux1 != NULL && aux2->T.TareaID != id) 
    {
        aux1 = aux1->siguiente;
    }
    while (aux2 != NULL && aux2->T.TareaID != id) 
    {
        aux2 = aux2->siguiente;
    }
    if(aux1 != NULL)
    {
        printf("La tarea se encuentra en pendientes: ");
        printf("\nId de la tarea: %d", aux1->T.TareaID);
        printf("\nDescripción: %s", aux1->T.Descripcion);
        printf("\nDuracion: %d", aux1->T.duracion);
    }else if(aux2 != NULL){
        printf("La tarea se encuentra en realizados: ");
        printf("\nId de la tarea: %d", aux2->T.TareaID);
        printf("\nDescripción: %s", aux2->T.Descripcion);
        printf("\nDuracion: %d", aux2->T.duracion);
    }else{
        printf("\nLa tarea no se encuentra en ninguna lista");
    }
}

void consultarTareasporPalabraClave(Nodo **listaPendientes, Nodo **listaRealizados,char *clave)
{
    Nodo *aux1 = *listaPendientes; 
    Nodo *aux2 = *listaRealizados;
    while (aux1 != NULL && strstr(aux1->T.Descripcion,clave) == NULL) 
    {
        aux1 = aux1->siguiente;
    }
    while (aux2 != NULL && strstr(aux1->T.Descripcion,clave) != NULL) 
    {
        aux2 = aux2->siguiente;
    }
    if(aux1 != NULL)
    {
        printf("La tarea se encuentra en pendientes: ");
        printf("\nId de la tarea: %d", aux1->T.TareaID);
        printf("\nDescripción: %s", aux1->T.Descripcion);
        printf("\nDuracion: %d", aux1->T.duracion);
    }else if(aux2 != NULL){
        printf("La tarea se encuentra en realizados: ");
        printf("\nId de la tarea: %d", aux2->T.TareaID);
        printf("\nDescripción: %s", aux2->T.Descripcion);
        printf("\nDuracion: %d", aux2->T.duracion);
    }else{
        printf("\nLa tarea no se encuentra en ninguna lista");
    }
}