#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "secure.h"
#include "utils/matrix.h"
#include "utils/colors.h"


int main(){
    
    WORD defecto = getInfo();
    HANDLE hConsole = getConsoleData();

    // // Inicializaciones /
    TaskTable* table = malloc(sizeof(TaskTable));
    FileToTaskTable(table, "procesos-recursos/ejemplo2.txt");

    // // Muestra de los procesos
    // // showTaskTable(table, -99);

    // Inicio Algoritmo /
    SecureAlgorithm(table);
    setColor(hConsole, defecto);

    return 0;
}