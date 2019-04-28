#ifndef SECURE_H_ 
#define SECURE_H_
#define MAX_DIMENSION 100
#include <stdbool.h>

typedef struct TaskTable {
    int** assign;
    int** max;
    int** required;
    bool* solved;
    int n_process;
    int n_resources;
    int* init_memo;
    int* memo; 
} TaskTable;


void showTaskTable(TaskTable* table, int n, bool intermedio);
void showResources(TaskTable* TaskTable, int index, bool procedimiento);
void checkSolvedProcesses(TaskTable* taskTable);
int getNextTaskIndex(TaskTable* table);
bool checkSolved(bool* solved, int length);
void SecureAlgorithm(TaskTable* table);
TaskTable* initTaskTable(short process, short resources, int** assign, int** max, int* init_memo);
void FileToTaskTable(TaskTable* table, char file[]); 
#endif // SECURE_H_