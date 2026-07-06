#include <stdio.h>
#include "ordenes.h"

int main() {
    OrdenTrabajo ordenes[MAX_ORDENES];
    int total_ordenes = 0;
    int opcion = 0;

    cargar_ordenes(ordenes, &total_ordenes);

    do {
        printf("\n=== GESTION DE ORDENES ===\n");
        printf("1. Registrar orden\n");
        printf("2. Listar ordenes\n");
        printf("3. Buscar orden\n");
        printf("4. Actualizar orden\n");
        printf("5. Eliminar orden\n");
        printf("6. Guardar manual\n");
        printf("7. Salir\n");
        printf("==========================\nOpcion: ");
        
        scanf("%d", &opcion); 

        switch(opcion) {
            case 1: registrar_orden(ordenes, &total_ordenes); break;
            case 2: listar_ordenes(ordenes, total_ordenes); break;
            case 3: buscar_orden(ordenes, total_ordenes); break;
            case 4: actualizar_orden(ordenes, total_ordenes); break;
            case 5: eliminar_orden(ordenes, &total_ordenes); break;
            case 6: guardar_ordenes(ordenes, total_ordenes); break;
            case 7: 
                guardar_ordenes(ordenes, total_ordenes); 
                printf("Cerrando...\n"); 
                break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 7);

    return 0;
}
