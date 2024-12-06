#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include "command.h"

int execute(char * path, const char * command)
{
    if(strcmp(command, "list") == 0) {
        list_content(path);
        return 1;
    }
    if(strcmp(command, "open") == 0) {
        open_file(path);
        return 1;
    }
    if(strcmp(command, "switch") == 0) {
        switch_directory(path);
        return 1;
    }
    if (strcmp(command, "exit") == 0) {
        return 0;
    }
    system("cls");
    printf("illegal command, please try again\n");
    return 1;
}

void list_content(const char * path)
{
    DIR * dir = opendir(path);
    struct dirent * entry;

    system("cls");
    if(dir == NULL) {
        printf("open failed\n");
        return;
    }
    printf("content :\n");
    //print file type
    while (entry = readdir(dir)) {
        printf("  %-20s\t\t\t", entry->d_name);
        switch(entry->d_type) {
            case DT_UNKNOWN:
                printf("unkown");
                break;
            case DT_DIR:
                printf("directory");
                break;
            case DT_REG:
                printf("regular");
                break;
            default:
                printf("error");
        }
        printf("\n");
    }
    closedir(dir);
}

void open_file(char * path)
{
    char file[MAX_NAME] = {0};
    printf("enter file name : ");
    fflush(stdin);
    fgets(file, MAX_NAME, stdin);
    if(strchr(file, '\n')){
        *strchr(file, '\n') = '\0';
    }
    strncat(path, "\\", MAX_PATH - strlen(path));
    strncat(path, file, MAX_PATH - strlen(path));

    system("cls");
    if(ShellExecute(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32) {
        printf("open file failed\n");
        return;
    }
    printf("open file successed\n");
    return;
}

void switch_directory(char * path)
{
    printf("input target folder : ");
    char folder[MAX_NAME] = {0};
    fflush(stdin);
    fgets(folder, MAX_NAME, stdin);
    if(strchr(folder, '\n')){
        *strchr(folder, '\n') = '\0';
    }
    strncat(path, "\\", MAX_PATH - strlen(path));
    strncat(path, folder, MAX_PATH - strlen(path));

    system("cls");
    if(chdir(path)) {
        printf("switch failed\n");
        return;
    }
    printf("switch successed\n");
    return;
}
