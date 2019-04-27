#include <stdlib.h>
#include <stdio.h>
#include "secure.h"
#include "utils/matrix.h"
#include <stdbool.h>

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
    while(checkSolved(table->solved, table->n_process) == false){
        index = getNextTaskIndex(table);
        if(index == -1){break;}
        printf("\nProceso actual -> %d", index);
        printf("\nAsignando memoria necesitada");
        printf("\nMemoria Actual: ");
        for(i = 0; i < table->n_resources; i++){
            table->memo[i] -= table->required[index][i];
            printf("%d ", table->memo[i]);
        }
        printf("\nRecuperando memoria");
        printf("\nMemoria Actual: ");
        for(i = 0; i < table->n_resources; i++){
            table->memo[i] += table->max[index][i];
            printf("%d ", table->memo[i]);
        }
        printf("\n");
        table->solved[index] = true;
    }
    if(index == -1){
        printf("\nLas tareas no pudieron ser resueltas");
    } else {
        printf("\nTareas resueltas");
    }
}
