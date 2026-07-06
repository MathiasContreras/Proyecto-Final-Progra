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
        // Usamos nuestra propia funcion
        if (comparar_cadenas(ordenes[i].codigo_orden, codigo) == 1) {
            return i;
        }
    }
    return -1;
}

float calcular_costo_total(float costo_base, int horas) {
    return costo_base + (horas * TARIFA_HORA);
}
