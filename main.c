#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "secure.h"
#include "utils/matrix.h"
#include "utils/colors.h"

void inicializacionTabla(TaskTable* table, char archivo[]);

int main(){
    
    WORD defecto = getInfo();
    HANDLE hConsole = getConsoleData();

    // // Inicializaciones /
    TaskTable* table = malloc(sizeof(TaskTable));
    inicializacionTabla(table, "procesos-recursos/ejemplo1.txt");

    // // Muestra de los procesos
    // // showTaskTable(table, -99);

    // Inicio Algoritmo /
    SecureAlgorithm(table);
    setColor(hConsole, defecto);

    return 0;
}


void inicializacionTabla(TaskTable* table, char archivo[]) {

    int i, j;
    FILE *f = fopen(archivo, "r");
    char string[100];

    char *ptr;

    int cant_proc;
    int cant_rec;
    int recursos_ini[100];
    int recursos_asig[100][100];
    int recursos_max[100][100];
    char delim[] = ";";

    if(f == NULL) {
        printf("No se puede abrir el archivo ...");
        return;
    }

    if(fgets(string, 100, f) != NULL) {
        ptr = strtok(string, delim);
        cant_proc = atoi(ptr);
        if(cant_proc < 1 || cant_proc > 10){
            printf("No se puede abrir el archivo ...");
            return;
        } 
    }
    else {
        printf("No se puede abrir el archivo ...");
        return;
    }

    if(fgets(string, 100, f) != NULL) {
        ptr = strtok(string, delim);
        cant_rec = atoi(ptr);
        if(cant_rec < 1 || cant_rec > 10){
            printf("No se puede abrir el archivo ...");
            return;
        } 
    }
    else {
        printf("No se puede abrir el archivo ...");
        return;
    }

    if(fgets(string, 100, f) != NULL) {
        ptr = strtok(string, delim);
        recursos_ini[0] = atoi(ptr);
        if(recursos_ini[0] < 0){
            printf("No se puede abrir el archivo ...");
            return;
        }
        for(i = 1; i < cant_rec; i++) {
            ptr = strtok(NULL, delim);
            recursos_ini[i] = atoi(ptr);
        }
    }
    else {
        printf("No se puede abrir el archivo ...");
        return;
    }

    for(int i = 0; i < cant_proc; i++) {
        if(fgets(string, 100, f) != NULL) {
            ptr = strtok(string, delim);
            recursos_asig[i][0] = atoi(ptr);
            if(recursos_asig[i][0] < 0){
                printf("No se puede abrir el archivo ...");
                return;
            }
            for(j = 1; j < cant_rec; j++) {
                ptr = strtok(NULL, delim);
                recursos_asig[i][j] = atoi(ptr);
            }
            ptr = strtok(NULL, delim);
            recursos_max[i][0] = atoi(ptr);        
            if(recursos_max[i][0] < 0){
                printf("No se puede abrir el archivo ...");
                return;
            }
            for(j = 1; j < cant_rec; j++) {
                ptr = strtok(NULL, delim);
                recursos_max[i][j] = atoi(ptr);
            }
        }
        else {
            printf("No se puede abrir el archivo ...");
            return;
        }
    } 

    table->n_process = cant_proc;
    table->n_resources = cant_rec; 
    table->assign = (int**)malloc(cant_proc * sizeof(int*));
    table->max = (int**)malloc(cant_proc * sizeof(int*));
    table->required = (int**)malloc(cant_proc * sizeof(int*));
    table->solved = (bool*)malloc(cant_proc * sizeof(bool));
    table->init_memo = (int*)malloc(cant_rec* sizeof(int));
    table->memo = (int*)malloc(cant_rec* sizeof(int));

    for(i = 0; i < cant_proc; i++){
        table->assign[i] = (int*)malloc(cant_rec* sizeof(int));
        table->max[i] = (int*)malloc(cant_rec* sizeof(int));
        table->required[i] = (int*)malloc(cant_rec* sizeof(int));
    }

    for(i = 0; i < cant_proc; i++){
        for(j = 0; j < cant_rec; j++){
            table->assign[i][j] = recursos_asig[i][j];
            table->max[i][j] = recursos_max[i][j];
            table->required[i][j] = table->max[i][j] - table->assign[i][j];
        }
    }
    for(i = 0; i < cant_proc; i++){
        table->solved[i] = false;
    }

    for(i = 0; i < cant_rec; i++){
        table->init_memo[i] = recursos_ini[i];
        table->memo[i] = recursos_ini[i];
    }

}