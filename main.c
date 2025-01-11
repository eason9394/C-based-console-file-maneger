#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include "command.h"

int main()
{
    List * command = newList(MAX_PATH);
    char path[MAX_PATH];
    
    printf("welcome to use file manager!\n");
    do {
        getcwd(path, sizeof(path));
        printf("current path : %s\n", path);
        list_content(path);
        printf("\nCommands:\n");
        printf("  open\t\t\topen the file\n");
        printf("  switch\t\tswitch the path\n");
        printf("  exit\t\t\texit the program\n");
        printf("input conmmand: ");
        fflush(stdin);
        getList(command);
    }while(execute(path, command));
    freeList(&command);
    return 0;
}