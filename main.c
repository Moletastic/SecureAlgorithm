#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "secure.h"
#include "utils/matrix.h"
#include "utils/colors.h"

int main(){
    
    WORD defecto = getInfo();
    HANDLE hConsole = getConsoleData();
    /* int procesos = 5;
    int recursos = 3;
    short i,j;
    int input_assign[5][3] = {
        {1,0,0}, 
        {0,1,2}, 
        {0,0,3}, 
        {1,0,3}, 
        {1,1,0}
    };

    int input_max[5][3] = {
        {4,4,4}, 
        {1,4,6}, 
        {3,2,5}, 
        {4,4,8}, 
        {5,1,10}
    };

    int input_required[5][3] = {
        {3,4,4},
        {1,3,4},
        {3,2,2},
        {3,4,5},
        {4,0,10}
    };

    bool input_solved[5] = {false, false, false, false, false};
    int input_init_memo[3] = {3,3,2}; */

    int procesos = 5;
    int recursos = 3;
    short i,j;
    int input_assign[5][3] = {
        {0,1,0}, 
        {2,0,0}, 
        {3,0,2}, 
        {2,1,1}, 
        {0,0,2}
    };

    int input_max[5][3] = {
        {7,5,3}, 
        {3,2,2}, 
        {9,0,2}, 
        {2,2,2}, 
        {4,3,3}
    };

    int input_required[5][3] = {
        {7,4,3},
        {1,2,2},
        {6,0,0},
        {0,1,1},
        {4,3,1}
    };

    bool input_solved[5] = {false, true, false, false, false};
    int input_init_memo[3] = {3,3,2};

    // Inicializaciones /
    TaskTable* table = malloc(sizeof(TaskTable));
    table->assign = (int**)malloc(procesos * sizeof(int*));
    table->max = (int**)malloc(procesos * sizeof(int*));
    table->required = (int**)malloc(procesos * sizeof(int*));
    table->solved = (bool*)malloc(procesos * sizeof(bool));
    table->init_memo = (int*)malloc(recursos* sizeof(int));
    table->memo = (int*)malloc(recursos* sizeof(int));
    table->n_process = procesos;
    table->n_resources = recursos; 

    for(i = 0; i < procesos; i++){
        table->assign[i] = (int*)malloc(recursos* sizeof(int));
        table->max[i] = (int*)malloc(recursos* sizeof(int));
        table->required[i] = (int*)malloc(recursos* sizeof(int));
    }

    for(i = 0; i < procesos; i++){
        for(j = 0; j < recursos; j++){
            table->assign[i][j] = input_assign[i][j];
            table->max[i][j] = input_max[i][j];
            table->required[i][j] = input_required[i][j];
        }
    }
    for(i = 0; i < procesos; i++){
        table->solved[i] = input_solved[i];
    }

    for(i = 0; i < recursos; i++){
        table->init_memo[i] = input_init_memo[i];
        table->memo[i] = input_init_memo[i];
    }

    // Inicializaciones /
    SecureAlgorithm(table);
    setColor(hConsole, defecto);
    return 0;
}


