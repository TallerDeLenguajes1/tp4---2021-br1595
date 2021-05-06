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

int CantidadTareas();
void CargarTarea(Tarea **, int);
void TestTareaCompletada(Tarea **, Tarea **, int);
void MostrarTareas(Tarea *);
Tarea *BuscarPorPalabra(tarea **, int);
Tarea * BusquedaPorId(Tarea **, int);



int main()
{
    srand(time(0));
	Tarea ** TareasPendientes, ** TareasRealizadas, * TareaEncontrada;
    int cantidad/*, cantidad2*/;


	cantidad = CantidadTareas();
	TareasPendientes = (Tarea**) malloc(sizeof(Tarea*) * cantidad);
	TareasRealizadas = (Tarea**) malloc(sizeof(Tarea*) * cantidad);
	TareaEncontrada = (Tarea*) malloc(sizeof(Tarea*));

	CargarTarea(TareasPendientes, cantidad);

	TareaEncontrada = BuscarPorPalabra(TareasPendientes, cantidad);
	MostrarTareas(TareaEncontrada);
	
	TareaEncontrada = BusquedaPorId(TareasPendientes, cantidad);
	MostrarTareas(TareaEncontrada);

	/*cantidad2 = */TestTareaCompletada(TareasPendientes, TareasRealizadas, cantidad);
	
	printf("\nTareas pendientes:\n\n");
	for(int i=0; i < cantidad; i++)
	{	
		if(*(TareasPendientes + i) != NULL)
		{	
			MostrarTareas(*(TareasPendientes + i));
		}
	}
	
	printf("\nTareas realizadas:\n\n");	
	for(int i=0; i < cantidad; i++)
	{	
		if(*(TareasRealizadas + i) != NULL)
		{			
			MostrarTareas(*(TareasRealizadas + i));
		}
	}

    return 0;
}

int CantidadTareas()
{
	int cantidad;

    printf("Ingrese cantidad de tareas a cargar: ");
    scanf("%d", &cantidad);
    getchar();

	return cantidad;
}

Tarea *CargarTarea(int posicion)
{
	char aux[100];
	Tarea * auxiliar = (Tarea*) malloc(sizeof(Tarea));
	printf("\nIngrese el nombre de la tarea a realizar: ");
    fflush(stdin);
	gets(aux);
    fflush(stdin);
	auxiliar->Descripcion = (char*) malloc(strlen(aux) * sizeof(char));
	auxiliar->TareaID = posicion + 1;
	strcpy(auxiliar->Descripcion, aux);	
	auxiliar->Duracion = rand() % 91 + 10;

	return auxiliar;
}

void CargarTarea(Tarea ** lista, int cantidad)
{
	for(int i=0; i < cantidad; i++)
	{
		lista[i] = CargarTarea(i);
	}	
}

/*int*/
void TestTareaCompletada(Tarea ** lista, Tarea ** completo, int cantidad)
{
	int j, h = 0, tamano2 = 0;
	char c;

	for(int i=0; i < cantidad; i++)
	{
		j = 0;
		
		//Creo un bucle que solo terminará si la opción ingresada es una de las solicitadas
		while(j == 0)
		{
			printf("\nLa tarea %s", lista[i]->Descripcion);
			printf(" se completó? S/N\n");
			fflush(stdin);
			scanf("%c", &c);
			fflush(stdin);
			if('s' == tolower(c) || 'n' == tolower(c))
			{
				if('s' == tolower(c))
				{
					completo[i] = lista[i];
					lista[i] = NULL;
					/*
					completo[tamano2] = lista[i];
					lista[i] = NULL;
					tamano2 += 1;
					*/
				}else{					
            		completo[i] = NULL;
				}
				j += 1;
			}
			else
			{
				printf("\nError al ingresar dato, reintente.\n");
			}
		}
	}
	/*return tamano2;*/
}

void MostrarTareas(Tarea * lista)
{
	printf("Tarea %d", lista->TareaID);		
	printf("\nDescripción: %s", lista->Descripcion);
	printf("\nDuración: %d\n\n", lista->Duracion);
}

Tarea *BusquedaPorId(tarea ** lista, int cantidad)
{
    char PalabraABuscar[30];
    char *Palabra;
    int Resultado = 0;

    printf("\nIngrese una palabra para buscar en tarea: ");
    fflush(stdin);
	gets(PalabraABuscar);
	fflush(stdin);

    printf("\nBuscando tarea..\n");
    for (int i = 0; i < cantidad; i ++)
	{
       
        Palabra = strstr((*(lista + i))->Descripcion, PalabraABuscar);

        if(Palabra != NULL)
		{
            //MostrarTareas((*(lista + i)));
			return *(lista + i);
        }
    }
    printf("No se encontraron resultados.\n");
	return NULL;
}

Tarea * BuscarPorPalabra(Tarea ** lista, int cantidad)
{
    int id;
    printf("\nIngrese el ID de la tarea que desea buscar (entre 1 y %d): ", cantidad);
    scanf("%d", &id);

    if(id > cantidad || id < 0)
	{
        printf("El ID ingresado no pertenece a ninguna tarea");
        BuscarPorPalabra(lista, cantidad);
    }
	else
	{
		printf("\nTarea encontrada: \n");
		//MostrarTareas(*(lista + id));
    }
	return *(lista + (id - 1));
}