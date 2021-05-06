#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct tarea Tarea;
struct tarea
{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
};

typedef struct Nodo Tnodo;
struct Nodo{
	Tarea T;
	Tnodo *Siguiente;
};

int CantidadTareas();
Tnodo * CrearListaVacia();
void CargarTareasEnLista(Tnodo **, int);
void InsertarNodoEnLista(Tnodo **, Tnodo *);
void CargarTareaEnNodo(Tnodo *, int, char *, int);

void TestTareaCompletada(Tnodo **, Tnodo **);
void MostrarTareas(Tnodo *);
void BuscarPorPalabra(Tnodo **);
void BuscarPorID(Tnodo **, int);



int main()
{
    srand(time(0));
	Tnodo * TareasPendientes, * TareasRealizadas, * auxiliar;
    int cantidad;


	cantidad = CantidadTareas();
    TareasPendientes = CrearListaVacia();
    TareasRealizadas = CrearListaVacia();

	CargarTareasEnLista(&TareasPendientes, cantidad);

	BuscarPorPalabra(&TareasPendientes);
	
	BuscarPorID(&TareasPendientes, cantidad);

	TestTareaCompletada(&TareasPendientes, &TareasRealizadas);
	
	printf("\nTareas pendientes:\n\n");
	auxiliar = TareasPendientes;
	while(auxiliar  != NULL)
	{	
		MostrarTareas(auxiliar);
		auxiliar = auxiliar->Siguiente;
	}
	
	printf("\nTareas realizadas:\n\n");	
	auxiliar = TareasRealizadas;
	while(auxiliar  != NULL)
	{	
		MostrarTareas(auxiliar);
		auxiliar = auxiliar->Siguiente;
	}

	
	auxiliar = TareasPendientes;
    while (auxiliar != NULL)
    {
        Tnodo * auxiliar2 = auxiliar;
        auxiliar = auxiliar->Siguiente;
        free(auxiliar2);
    }

    auxiliar = TareasRealizadas;
    while (auxiliar != NULL)
    {
        Tnodo * auxiliar2 = auxiliar;
        auxiliar = auxiliar->Siguiente;
        free(auxiliar2);
    }

    return 0;
}

int CantidadTareas()
{
	int cantidad;

	printf("/////////////////////////////////////\n");
    printf("Ingrese cantidad de tareas a cargar: ");
    scanf("%d", &cantidad);
    getchar();

	return cantidad;
}

Tnodo * CrearNodo()
{	
	Tnodo * NodoNuevo =	(Tnodo*) malloc(sizeof(Tnodo));	
	NodoNuevo->Siguiente = NULL;
	return NodoNuevo;
}

Tnodo * CrearListaVacia()
{
	return NULL;
}

void CargarTareaEnNodo(Tnodo * Nodo, int TareaID, char *Descripcion, int Duracion)
{
	Nodo->T.TareaID = TareaID;
	Nodo->T.Descripcion = Descripcion;
	Nodo->T.Duracion = Duracion;
}

void CargarTareasEnLista(Tnodo ** lista, int cantidad)
{
	for(int i=0; i < cantidad; i++)
	{
		Tnodo * NuevoNodo = CrearNodo();
		char aux[100];
		printf("\nIngrese el nombre de la tarea a realizar: ");
        fflush(stdin);
		gets(aux);
        fflush(stdin);
		char * Descripcion = (char*) malloc(strlen(aux) * sizeof(char));
		strcpy(Descripcion, aux);
        CargarTareaEnNodo(NuevoNodo, i + 1, Descripcion, rand() % 91 + 10);
		InsertarNodoEnLista(lista, NuevoNodo);
	}	
}

void InsertarNodoEnLista(Tnodo ** lista, Tnodo * Nodo)
{	
	Tnodo * aux = *lista;
	if(aux != NULL)
	{
		while (aux->Siguiente != NULL)
		{	
			aux = aux->Siguiente;
		}		
		aux->Siguiente = Nodo;
	}
	else *lista = Nodo;
}


void TestTareaCompletada(Tnodo ** lista, Tnodo ** completo)
{
	int j = 0;
	char c;	
    Tnodo * auxiliar = *lista;
    Tnodo * auxiliar2 = *completo;
    Tnodo * anterior = auxiliar;
		//Creo un bucle que solo terminará si la opción ingresada es una de las solicitadas
	while(auxiliar != NULL)
	{
		j = 0;
		while( j == 0)
		{
			printf("\nLa tarea %s", auxiliar->T.Descripcion);
			printf(" se completó? S/N\n");
			getchar();
			scanf("%c", &c);
			fflush(stdin);

			if('s' == tolower(c) || 'n' == tolower(c))
			{
				if('s' == tolower(c))
				{
					auxiliar2 = auxiliar;
					auxiliar = auxiliar->Siguiente;

					if(anterior->Siguiente == auxiliar)
					{
						*lista = auxiliar;
						anterior = auxiliar;
					}else
					{
						anterior->Siguiente = auxiliar;
					}
					auxiliar2->Siguiente = *completo;   
					*completo = auxiliar2;    				
				}else
        {
            anterior = auxiliar;
            auxiliar = auxiliar->Siguiente;
        } 
				j += 1;
			}
			else
			{
				printf("\nError al ingresar dato, reintente.\n");
			}
		}
	}
}

void MostrarTareas(Tnodo * lista)
{
	printf("Tarea %d", lista->T.TareaID);		
	printf("\nDescripción: %s", lista->T.Descripcion);
	printf("\nDuración: %d\n\n", lista->T.Duracion);
}

void BuscarPorPalabra(Tnodo ** lista)
{
    char PalabraABuscar[30];
    char *Palabra;
    int Resultado = 0;
	Tnodo * posicion = *lista;

    printf("\nIngrese una palabra para buscar en tarea: ");
    fflush(stdin);
	gets(PalabraABuscar);
	fflush(stdin);

    printf("\nBuscando tarea..\n");
    while(posicion != NULL)
	  {		
      Palabra = strstr(posicion->T.Descripcion, PalabraABuscar);
		
      if(Palabra != NULL)
      {
          MostrarTareas(posicion);
			    Resultado = 1;
      }
      posicion = posicion->Siguiente;
	}
	if(Resultado != 1)
	{
    	printf("No se encontraron resultados.\n");
	}
}

void BuscarPorID(Tnodo ** lista, int cantidad)
{
    int id;
	Tnodo * posicion = *lista;
	
    printf("\nIngrese el ID de la tarea que desea buscar (entre 1 y %d): ", cantidad);
    scanf("%d", &id);

    if(id > cantidad || id < 1)
	{
        printf("El ID ingresado no pertenece a ninguna tarea");
		printf("Intente nuevamente");
        BuscarPorID(lista, cantidad);
    }
	else
	{
		printf("\nTarea encontrada: \n");		
        while(posicion->T.TareaID != id){
            posicion = posicion->Siguiente;
        }
		MostrarTareas(posicion);
    }
}