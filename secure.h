#ifndef SECURE_H_ 
#define SECURE_H_
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

void checkSolvedProcesses(TaskTable* taskTable);
int getNextTaskIndex(TaskTable* table);
bool checkSolved(bool* solved, int length);
void SecureAlgorithm(TaskTable* table);

#endif // SECURE_H_