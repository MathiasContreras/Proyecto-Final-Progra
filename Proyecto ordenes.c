#ifndef ORDENES_H
#define ORDENES_H

#define MAX_ORDENES 100
#define TARIFA_HORA 10.0
#define ARCHIVO_DATOS "ordenes.csv"

typedef struct {
    char codigo_orden[16];
    char nombre_cliente[50];
    char equipo[50];
    char tipo_trabajo[50];
    float costo_base;
    int horas_trabajo;
} OrdenTrabajo;


void cargar_ordenes(OrdenTrabajo *ordenes, int *contador);
void guardar_ordenes(OrdenTrabajo *ordenes, int contador);


void registrar_orden(OrdenTrabajo *ordenes, int *contador);
void listar_ordenes(OrdenTrabajo *ordenes, int contador);
void buscar_orden(OrdenTrabajo *ordenes, int contador);
void actualizar_orden(OrdenTrabajo *ordenes, int contador);
void eliminar_orden(OrdenTrabajo *ordenes, int *contador);


int comparar_cadenas(char s1[], char s2[]);
int contiene_subcadena(char texto[], char sub[]);
int validar_codigo(char codigo[]);
int buscar_indice(OrdenTrabajo *ordenes, int contador, char codigo[]);
float calcular_costo_total(float costo_base, int horas);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenes.h"


int comparar_cadenas(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return 0; 
        }
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return 1;
    }
    return 0;
}


int contiene_subcadena(char texto[], char sub[]) {
    int i = 0, j = 0;
    if (sub[0] == '\0') return 1; 

    while (texto[i] != '\0') {
        j = 0;
       
        while (texto[i + j] != '\0' && sub[j] != '\0' && texto[i + j] == sub[j]) {
            j++;
        }
       
        if (sub[j] == '\0') {
            return 1; 
        }
        i++;
    }
    return 0; 
}

int validar_codigo(char codigo[]) {
    int i = 0;
    if (codigo[0] == '\0') return 0;

    while (codigo[i] != '\0') {
        int es_mayuscula = (codigo[i] >= 'A' && codigo[i] <= 'Z');
        int es_minuscula = (codigo[i] >= 'a' && codigo[i] <= 'z');
        int es_numero = (codigo[i] >= '0' && codigo[i] <= '9');

        if (es_mayuscula == 0 && es_minuscula == 0 && es_numero == 0) return 0; 
        i++;
    }
    
    if (i > 15) return 0;
    return 1;
}

int buscar_indice(OrdenTrabajo *ordenes, int contador, char codigo[]) {
    for (int i = 0; i < contador; i++) {
        
        if (comparar_cadenas(ordenes[i].codigo_orden, codigo) == 1) {
            return i;
        }
    }
    return -1;
}

float calcular_costo_total(float costo_base, int horas) {
    return costo_base + (horas * TARIFA_HORA);
}

void registrar_orden(OrdenTrabajo *ordenes, int *contador) {
    if (*contador >= MAX_ORDENES) {
        printf("Error: Límite máximo alcanzado.\n");
        return;
    }

    OrdenTrabajo nueva_orden;
    char entrada_codigo[50]; 

    printf("\n--- Registrar Orden ---\n");
    
    while (1) {
        printf("Código (sin espacios, máx 15): ");
        scanf(" %s", entrada_codigo); 

        if (validar_codigo(entrada_codigo) == 0) {
            printf("Error: Código inválido.\n");
        } else if (buscar_indice(ordenes, *contador, entrada_codigo) != -1) {
            printf("Error: El código ya existe.\n");
        } else {
            strcpy(nueva_orden.codigo_orden, entrada_codigo);
            break;
        }
    }

    printf("Cliente: ");
    scanf(" %[^\n]", nueva_orden.nombre_cliente); 

    printf("Equipo: ");
    scanf(" %[^\n]", nueva_orden.equipo);

    printf("Trabajo: ");
    scanf(" %[^\n]", nueva_orden.tipo_trabajo);

    do {
        printf("Costo base (> 0): ");
        scanf("%f", &nueva_orden.costo_base);
    } while (nueva_orden.costo_base <= 0);

    do {
        printf("Horas (>= 0): ");
        scanf("%d", &nueva_orden.horas_trabajo);
    } while (nueva_orden.horas_trabajo < 0);

    ordenes[*contador] = nueva_orden;
    (*contador)++;
    printf("Registrada exitosamente.\n");
}

void listar_ordenes(OrdenTrabajo *ordenes, int contador) {
    if (contador == 0) {
        printf("\nNo hay órdenes.\n");
        return;
    }

    printf("\n%-15s | %-20s | %-15s | %-10s | %-6s | %-10s\n", 
           "Código", "Cliente", "Equipo", "C. Base", "Horas", "C. Total");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < contador; i++) {
        float total = calcular_costo_total(ordenes[i].costo_base, ordenes[i].horas_trabajo);
        printf("%-15s | %-20s | %-15s | $%-9.2f | %-6d | $%-9.2f\n",
               ordenes[i].codigo_orden, ordenes[i].nombre_cliente, ordenes[i].equipo,
               ordenes[i].costo_base, ordenes[i].horas_trabajo, total);
    }
}

void buscar_orden(OrdenTrabajo *ordenes, int contador) {
    if (contador == 0) return;
    
    char busqueda[50];
    printf("\nBuscar (código exacto o parte del nombre del cliente): ");
    scanf(" %[^\n]", busqueda);

    for (int i = 0; i < contador; i++) {
       
        if (comparar_cadenas(ordenes[i].codigo_orden, busqueda) == 1 || 
            contiene_subcadena(ordenes[i].nombre_cliente, busqueda) == 1) {
            
            float total = calcular_costo_total(ordenes[i].costo_base, ordenes[i].horas_trabajo);
            printf("Código: %s | Cliente: %s | Equipo: %s | C.Total: $%.2f\n",
                   ordenes[i].codigo_orden, ordenes[i].nombre_cliente, ordenes[i].equipo, total);
        }
    }
}

void actualizar_orden(OrdenTrabajo *ordenes, int contador) {
    char codigo[16];
    char respuesta;
    
    printf("\nCódigo a modificar: ");
    scanf(" %s", codigo);

    int posicion = buscar_indice(ordenes, contador, codigo);
    if (posicion == -1) {
        printf("No encontrada.\n");
        return;
    }

    printf("Cliente actual: %s. Desea cambiarlo? (s/n): ", ordenes[posicion].nombre_cliente);
    scanf(" %c", &respuesta);
    if (respuesta == 's' || respuesta == 'S') {
        printf("Nuevo cliente: ");
        scanf(" %[^\n]", ordenes[posicion].nombre_cliente);
    }

    printf("Equipo actual: %s. Desea cambiarlo? (s/n): ", ordenes[posicion].equipo);
    scanf(" %c", &respuesta);
    if (respuesta == 's' || respuesta == 'S') {
        printf("Nuevo equipo: ");
        scanf(" %[^\n]", ordenes[posicion].equipo);
    }

    printf("Trabajo actual: %s. Desea cambiarlo? (s/n): ", ordenes[posicion].tipo_trabajo);
    scanf(" %c", &respuesta);
    if (respuesta == 's' || respuesta == 'S') {
        printf("Nuevo trabajo: ");
        scanf(" %[^\n]", ordenes[posicion].tipo_trabajo);
    }

    printf("Costo base actual: %.2f. Desea cambiarlo? (s/n): ", ordenes[posicion].costo_base);
    scanf(" %c", &respuesta);
    if (respuesta == 's' || respuesta == 'S') {
        float nuevo_costo;
        printf("Nuevo costo: ");
        scanf("%f", &nuevo_costo);
        if (nuevo_costo > 0) ordenes[posicion].costo_base = nuevo_costo;
    }

    printf("Horas actuales: %d. Desea cambiarlo? (s/n): ", ordenes[posicion].horas_trabajo);
    scanf(" %c", &respuesta);
    if (respuesta == 's' || respuesta == 'S') {
        int nuevas_horas;
        printf("Nuevas horas: ");
        scanf("%d", &nuevas_horas);
        if (nuevas_horas >= 0) ordenes[posicion].horas_trabajo = nuevas_horas;
    }

    printf("Actualizada exitosamente.\n");
}

void eliminar_orden(OrdenTrabajo *ordenes, int *contador) {
    char codigo[16];
    char confirmacion;
    
    printf("\nCódigo a eliminar: ");
    scanf(" %s", codigo);

    int posicion = buscar_indice(ordenes, *contador, codigo);
    if (posicion == -1) {
        printf("No encontrada.\n");
        return;
    }

    printf("¿Eliminar %s? (s/n): ", codigo);
    scanf(" %c", &confirmacion);

    if (confirmacion == 's' || confirmacion == 'S') { 
        for (int i = posicion; i < *contador - 1; i++) {
            ordenes[i] = ordenes[i + 1];
        }
        (*contador)--;
        printf("Eliminada.\n");
    } else {
        printf("Cancelado.\n");
    }
}