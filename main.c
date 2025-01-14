#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include "command.h"

int main()
{
    List * command = newList();
    char path[MAX_PATH];

    printf("welcome to use file manager!\n");
    do {
        getcwd(path, sizeof(path));
        printf("current path : %s\n", path);
        list_content(path);
        printf("\n");
        printf("Commands:\n");
        printf("  open\t\t\topen the file\n");
        printf("  switch\t\tswitch the path\n");
        printf("  move\t\t\tmove the file\n");
        printf("  copy\t\t\tcopy the file\n");
        printf("  mkfile\t\tcreate a new file\n");
        printf("  mkdir\t\t\tcreate a new directory\n");
        printf("  exit\t\t\texit the program\n");
        printf("input command: ");
        fflush(stdin);
        getList(command);
    }while(execute(path, command));
    freeList(command);
    command = NULL;
    return 0;
}