#include "colors.h"

void setColor(HANDLE hConsole, int color){
    SetConsoleTextAttribute(hConsole, color);
}

HANDLE getConsoleData(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    return hConsole;
}

WORD getInfo(){
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    return consoleInfo.wAttributes;
}

