#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include "command.h"

int execute(char * path, List * command)
{
    if(compare(command, "open") == 1) {
        open_file(path);
        return 1;
    }
    if(compare(command, "switch") == 1) {
        switch_directory(path);
        return 1;
    }
    if (compare(command, "exit") == 1) {
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

            case DT_FIFO:
                printf("FIFO");
                break;

            case DT_CHR:
                printf("character device");
                break;

            case DT_DIR:
                printf("directory");
                break;

            case DT_BLK:
                printf("block device");
                break;

            case DT_REG:
                printf("regular");
                break;

            case DT_LNK:
                printf("stmbolic link");
                break;

            case DT_SOCK:
                printf("local-domain socket");
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
    List * filename = newList(MAX_PATH);
    printf("enter file name : ");
    getList(filename);
    splice(path, filename);
    freeList(&filename);

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
    List * folder = newList(MAX_PATH);
    printf("input target folder : ");
    getList(folder);
    splice(path, folder);
    freeList(&folder);

    system("cls");
    if(chdir(path)) {
        printf("switch failed\n");
        return;
    }
    printf("switch successed\n");
    return;
}
