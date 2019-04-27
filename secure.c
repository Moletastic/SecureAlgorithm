#include <stdlib.h>
#include <stdio.h>
#include "secure.h"
#include "utils/matrix.h"
#include "utils/colors.h"
#include <stdbool.h>

void showTaskTable(TaskTable* table, int proceso, bool intermedio) {
    int i, j;
    WORD defecto = getInfo();
    HANDLE hConsole = getConsoleData();
    setColor(hConsole, LIGHTBLUE);
    printf("+--+--+--+--+--+--+--+--+--+\n");
    for(i = 0; i < table->n_process; i++) {
        setColor(hConsole, LIGHTBLUE);
        printf("|");
        if(table->solved[i]) {
            printf("--|--|--|--|--|--|--|--|--|\n");
        }
        else {
            for(j = 0; j < table->n_resources; j++) {
                setColor(hConsole, LIGHTCYAN);
                if(intermedio && proceso == i) {
                    setColor(hConsole, LIGHTRED);
                    if(table->max[i][j] >= 10)
                        printf("%d", table->max[i][j]);
                    else
                        printf(" %d", table->max[i][j]);
                }
                else {
                    if(table->assign[i][j] >= 10)
                        printf("%d", table->assign[i][j]);
                    else
                        printf(" %d", table->assign[i][j]);
                }    
                setColor(hConsole, LIGHTBLUE);            
                printf("|");    
            }
            for(j = 0; j < table->n_resources; j++) {
                setColor(hConsole, LIGHTGREEN);
                if(intermedio && proceso == i)
                    setColor(hConsole, LIGHTRED);
                if(table->max[i][j] >= 10)
                    printf("%d", table->max[i][j]);
                else
                    printf(" %d", table->max[i][j]);
                setColor(hConsole, LIGHTBLUE);            
                printf("|");    
            }
            for(j = 0; j < table->n_resources; j++) {
                setColor(hConsole, LIGHTMAGENTA);
                if(intermedio && proceso == i) {
                    setColor(hConsole, LIGHTRED);                    
                    printf(" 0");
                }
                else {
                    if(table->required[i][j] >= 10)
                        printf("%d", table->required[i][j]);
                    else
                        printf(" %d", table->required[i][j]);
                }     
                setColor(hConsole, LIGHTBLUE);            
                printf("|");    
            }
            if(proceso != -99 && i == proceso && !intermedio) {
                setColor(hConsole, LIGHTRED);
                printf("<---- Proceso elegido");
            }
            printf("\n");
        }
    }
    setColor(hConsole, LIGHTBLUE);
    printf("+--+--+--+--+--+--+--+--+--+\n");
    if(proceso != -99 && !intermedio){
        showTaskTable(table, proceso, true);
    }
}

void showResources(TaskTable* table, int index, bool procedimiento) {  //Procedimiento true = asignar    ---  Procedimiento false = recuperar  
    int i;
    printf("\n+");
    for(i = 0; i < table->n_resources; i++)
        printf("------+");
    printf("\n|");
    for(i = 0; i < table->n_resources; i++)
        printf("--r%d--|", i);
    printf("\n+");
    for(i = 0; i < table->n_resources; i++)
        printf("------+");
    printf("\n|");
    if(procedimiento)
        for(i = 0; i < table->n_resources; i++){
            table->memo[i] -= table->required[index][i];
            if(table->memo[i] >= 10)
                printf("  %d  |", table->memo[i]);
            else
                printf("   %d  |", table->memo[i]);
        }
    else
        for(i = 0; i < table->n_resources; i++){
            table->memo[i] += table->max[index][i];
            if(table->memo[i] >= 10)
                printf("  %d  |", table->memo[i]);
            else
                printf("   %d  |", table->memo[i]);
        }
    printf("\n+------+------+------+");   
}

void algorithmResult(bool resultado) {

    if(!resultado) {
        printf("+--------------------------------------+\n| Las tareas no pudieron ser resueltas |\n+--------------------------------------+\n");
        printf("+--------------------------------------+\n|        El sistema es inseguro        |\n+--------------------------------------+\n");
    }
    else {
        printf("+--------------------------------------+\n|     Las tareas fueron resueltas!     |\n+--------------------------------------+\n");
        printf("+--------------------------------------+\n|         El sistema es seguro         |\n+--------------------------------------+\n");
    }
}

void checkSolvedProcesses(TaskTable* taskTable) {
    short i;
    for(i = 0; i < taskTable->n_process; i++){
        if(taskTable->solved[i] == true){
            printf("Proceso %d: Resuelto\n", i);
        } else {
            printf("Proceso %d: No resuelto\n", i);
        }
    }
}

int getNextTaskIndex(TaskTable* table){
    short i,j, counter, index = -1, sum = 0, temp_sum = 0;
    for(i = 0; i < table->n_process; i++){
        counter = 0;
        if(table->solved[i] == false){
            for(j = 0; j < table->n_resources; j++){
                if(table->required[i][j] <= table->memo[j]){
                    counter++;
                }
            }
            if(counter == table->n_resources){
                temp_sum = rowSum(table->max[i], table->n_resources);
                //printf("Enabled Task in index: %d\n", i);
                //printf("Required Memo: ");
                /* for(j = 0; j < table->n_resources; j++){
                    printf("%d ", table->required[i][j]);
                } */
                //printf("\nGain Memo: %d", temp_sum);
                //printf("\n");
                if(temp_sum > sum){
                    sum = temp_sum;
                    index = i;
                }
            }
        }
    }
    return index;
}

bool checkSolved(bool* solved, int length){
    short i;
    for(i = 0; i < length; i++){
        if(solved[i] == false){
            return false;
        }
    }
    return true;
}   

void SecureAlgorithm(TaskTable* table){
    short i,j, index;
    WORD defecto = getInfo();
    HANDLE hConsole = getConsoleData();

    while(checkSolved(table->solved, table->n_process) == false){
        index = getNextTaskIndex(table); // index = -1 ---> No se halló un proceso válido
        if(index == -1){break;}
        setColor(hConsole, WHITE);
        // printf("\nProceso actual -> %d", index);
        showTaskTable(table, index, false);
        setColor(hConsole, LIGHTRED);
        printf("\nAsignando memoria necesitada");
        printf("\nMemoria Actual: ");
        // for(i = 0; i < table->n_resources; i++){
        //     table->memo[i] -= table->required[index][i];
        //     printf("%d ", table->memo[i]);
        // }
        showResources(table, index, true);
        setColor(hConsole, LIGHTGREEN);
        printf("\nRecuperando memoria");
        printf("\nMemoria Actual: ");
        // for(i = 0; i < table->n_resources; i++){
        //     table->memo[i] += table->max[index][i];
        //     printf("%d ", table->memo[i]);
        // }
        showResources(table, index, false);
        setColor(hConsole, WHITE);
        printf("\nProceso %d Finalizado \n", index);
        setColor(hConsole, LIGHTGREEN);
        printf("\n");
        table->solved[index] = true;
    }
    if(index == -1){
        setColor(hConsole, LIGHTRED);
        algorithmResult(false);
    } else {
        setColor(hConsole, LIGHTGREEN);
        algorithmResult(true);
    }
}
