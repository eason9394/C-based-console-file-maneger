#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include "command.h"

int main()
{
    const char commands[COMMAND_NUMBER][10] = {"list", "open", "switch", "exit"};
    const char description[COMMAND_NUMBER][35] = {"list the content in this directory",
                                                  "open the file", 
                                                  "switch the path", 
                                                  "exit the program"};
    char command[10];
    char path[MAX_PATH];
    
    printf("welcome to use file manager!\n");
    do {
        getcwd(path, sizeof(path));
        printf("\ncurrent path : %s\n", path);
        printf("Commands:\n");
        for(int i = 0; i < COMMAND_NUMBER; ++i) {
            printf("  %-10s\t\t\t%s\n", commands[i], description[i]);
        }
        printf("input conmmand: ");
        fflush(stdin);
        fgets(command, 10, stdin);
        if(strchr(command, '\n')){
            *strchr(command, '\n') = '\0';
        }
    }while(execute(path, command));
    return 0;
}