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