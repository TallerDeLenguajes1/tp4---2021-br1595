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
void MostrarTareas(Tarea **, int);



int main()
{
    srand(time(0));
	Tarea ** TareasPendientes, ** TareasRealizadas;
    int cantidad, cantidad2;


	cantidad = CantidadTareas();
	TareasPendientes = (Tarea**) malloc(sizeof(Tarea*) * cantidad);
	TareasRealizadas = (Tarea**) malloc(sizeof(Tarea*) * cantidad);

	CargarTarea(TareasPendientes, cantidad);
	/*cantidad2 = */TestTareaCompletada(TareasPendientes, TareasRealizadas, cantidad);
	
	printf("\nTareas pendientes:\n");
	MostrarTareas(TareasPendientes, cantidad);
	printf("\nTareas realizadas:\n");
	MostrarTareas(TareasRealizadas, /*cantidad2*/ cantidad);

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

void MostrarTareas(Tarea ** lista, int cantidad)
{
	for(int i=0; i < cantidad; i++)
	{	
		if(lista[i] != NULL)
		{
			printf("Tarea %d", lista[i]->TareaID);		
			printf("\nDescripción: %s", lista[i]->Descripcion);
			printf("\nDuración: %d\n\n", lista[i]->Duracion);
		}
	}
}

