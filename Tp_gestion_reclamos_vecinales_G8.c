#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =============================================
// Estructuras y constantes
// =============================================

typedef struct {
	char nombre[50];
	char direccion[100];
	char tipo[50];
	char fecha[15];
	char estado[20]; // "Pendiente", "En proceso", "Resuelto"
} Reclamo;

typedef struct Nodo {
	Reclamo dato;
	struct Nodo* siguiente;
} Nodo;

const char* ARCHIVO_RECLAMOS = "C:\\TP_Reclamos\\reclamos.txt";

// Prototipos
void menuPrincipal();
Nodo* cargarDesdeArchivo(const char* nombreArchivo);
void guardarEnArchivo(const char* nombreArchivo, Nodo* lista);
void agregarReclamo(Nodo** lista);
void mostrarReclamos(Nodo* lista);
void buscarReclamo(Nodo* lista);
void ordenarPorFecha(Nodo** lista);
void cambiarEstado(Nodo* lista);
void liberarLista(Nodo* lista);
void aMinusculas(char* str);

// =============================================
// FUNCIONES PRINCIPALES
// =============================================

void menuPrincipal() {
	Nodo* lista = cargarDesdeArchivo(ARCHIVO_RECLAMOS);
	int opcion;
	do {
		printf("\n--- Gestion de Reclamos Vecinales ---\n");
		printf("\n1. Agregar Reclamo\n");
		printf("2. Mostrar Reclamos\n");
		printf("3. Buscar Reclamo\n");
		printf("4. Cambiar Estado de Reclamo\n");
		printf("5. Ordenar por Fecha\n");
		printf("6. Guardar y Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		getchar(); // limpiar buffer
		
		switch(opcion) {
		case 1: agregarReclamo(&lista); break;
		case 2: mostrarReclamos(lista); break;
		case 3: buscarReclamo(lista); break;
		case 4: cambiarEstado(lista); break;
		case 5: ordenarPorFecha(&lista); break;
		case 6: guardarEnArchivo(ARCHIVO_RECLAMOS, lista); break;
		default: printf("Opcion invalida\n");
		}
	} while(opcion != 6);
	
	liberarLista(lista);
}

void agregarReclamo(Nodo** lista) {
	Reclamo nuevo;
	printf("Nombre: "); fgets(nuevo.nombre, 50, stdin); strtok(nuevo.nombre, "\n");
	printf("Direccion: "); fgets(nuevo.direccion, 100, stdin); strtok(nuevo.direccion, "\n");
	printf("Tipo de reclamo: "); fgets(nuevo.tipo, 50, stdin); strtok(nuevo.tipo, "\n");
	printf("Fecha (dd/mm/aaaa): "); fgets(nuevo.fecha, 15, stdin); strtok(nuevo.fecha, "\n");
	strcpy(nuevo.estado, "Pendiente");
	
	Nodo* nodoNuevo = (Nodo*)malloc(sizeof(Nodo));
	nodoNuevo->dato = nuevo;
	nodoNuevo->siguiente = *lista;
	*lista = nodoNuevo;
}

void mostrarReclamos(Nodo* lista) {
	if (lista == NULL) {
		printf("No hay reclamos para mostrar.\n");
		return;
	}
	
	printf("\n| %-3s | %-20s | %-25s | %-15s | %-10s | %-12s |\n", 
		   "Nº", "Nombre", "Dirección", "Tipo", "Fecha", "Estado");
	printf("|%s|\n", "-----|----------------------|---------------------------|-----------------|------------|--------------");
	
	int i = 1;
	while(lista != NULL) {
		Reclamo r = lista->dato;
		printf("| %-3d | %-20s | %-25s | %-15s | %-10s | %-12s |\n", 
			   i++, r.nombre, r.direccion, r.tipo, r.fecha, r.estado);
		lista = lista->siguiente;
	}
}

void buscarReclamo(Nodo* lista) {
	char criterio[50], criterioMin[50], campoMin[50];
	int opcion;
	
	printf("\nBuscar por: 1.Nombre  2.Tipo  3.Estado: ");
	scanf("%d", &opcion); getchar();
	printf("Ingrese criterio de busqueda: ");
	fgets(criterio, 50, stdin); strtok(criterio, "\n");
	
	strcpy(criterioMin, criterio);
	aMinusculas(criterioMin);
	
	int encontrados = 0;
	
	while(lista != NULL) {
		Reclamo r = lista->dato;
		
		if (opcion == 1) strcpy(campoMin, r.nombre);
		else if (opcion == 2) strcpy(campoMin, r.tipo);
		else if (opcion == 3) strcpy(campoMin, r.estado);
		else break;
		
		aMinusculas(campoMin);
		
		if (strcmp(campoMin, criterioMin) == 0) {
			printf("\nNombre: %s\nDireccion: %s\nTipo: %s\nFecha: %s\nEstado: %s\n",
				   r.nombre, r.direccion, r.tipo, r.fecha, r.estado);
			encontrados++;
		}
		lista = lista->siguiente;
	}
	
	if (encontrados == 0) {
		printf("No se encontraron resultados que coincidan.\n");
	}
}

void cambiarEstado(Nodo* lista) {
	char nombre[50];
	printf("Ingrese nombre del reclamo a modificar: ");
	fgets(nombre, 50, stdin); strtok(nombre, "\n");
	while(lista != NULL) {
		if(strcmp(lista->dato.nombre, nombre) == 0) {
			printf("Nuevo estado (Pendiente / En proceso / Resuelto): ");
			fgets(lista->dato.estado, 20, stdin); strtok(lista->dato.estado, "\n");
			printf("Estado actualizado con exito.\n");
			return;
		}
		lista = lista->siguiente;
	}
	printf("Reclamo no encontrado.\n");
}

void ordenarPorFecha(Nodo** lista) {
	if (*lista == NULL || (*lista)->siguiente == NULL) return;
	Nodo *i, *j;
	for(i = *lista; i != NULL; i = i->siguiente) {
		for(j = i->siguiente; j != NULL; j = j->siguiente) {
			if(strcmp(i->dato.fecha, j->dato.fecha) > 0) {
				Reclamo temp = i->dato;
				i->dato = j->dato;
				j->dato = temp;
			}
		}
	}
	printf("Reclamos ordenados por fecha.\n");
}

void guardarEnArchivo(const char* nombreArchivo, Nodo* lista) {
	FILE* f = fopen(nombreArchivo, "w");
	if (!f) {
		printf("No se pudo abrir el archivo para guardar.\n");
		return;
	}
	
	// Encabezado
	fprintf(f, "| %-3s | %-20s | %-25s | %-15s | %-10s | %-12s |\n", 
			"Nº", "Nombre", "Direccion", "Tipo", "Fecha", "Estado");
	fprintf(f, "|%s|\n", "-----|----------------------|---------------------------|-----------------|------------|--------------");
	
	// Contenido
	int i = 1;
	while(lista != NULL) {
		Reclamo r = lista->dato;
		fprintf(f, "| %-3d | %-20s | %-25s | %-15s | %-10s | %-12s |\n", 
				i++, r.nombre, r.direccion, r.tipo, r.fecha, r.estado);
		lista = lista->siguiente;
	}
	
	fclose(f);
	printf("Reclamos guardados en formato tabla en: %s\n", nombreArchivo);
}

Nodo* cargarDesdeArchivo(const char* nombreArchivo) {
	FILE* f = fopen(nombreArchivo, "r");
	if (!f) return NULL;
	
	char buffer[256];
	Nodo* lista = NULL;
	
	// Saltar encabezado
	fgets(buffer, sizeof(buffer), f); // Línea de encabezado
	fgets(buffer, sizeof(buffer), f); // Línea separadora
	
	Reclamo r;
	while (fgets(buffer, sizeof(buffer), f)) {
		sscanf(buffer, "| %*d | %49[^|]| %99[^|]| %49[^|]| %14[^|]| %19[^|]|",
			   r.nombre, r.direccion, r.tipo, r.fecha, r.estado);
		
		// Eliminar espacios sobrantes
		strtok(r.nombre, "\n"); strtok(r.direccion, "\n");
		strtok(r.tipo, "\n"); strtok(r.fecha, "\n"); strtok(r.estado, "\n");
		
		Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
		nuevo->dato = r;
		nuevo->siguiente = lista;
		lista = nuevo;
	}
	
	fclose(f);
	return lista;
}

void liberarLista(Nodo* lista) {
	while(lista != NULL) {
		Nodo* temp = lista;
		lista = lista->siguiente;
		free(temp);
	}
}

void aMinusculas(char* str) {
	for (int i = 0; str[i]; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] += 32;
		}
	}
}

int main() {
	menuPrincipal();
	return 0;
}
