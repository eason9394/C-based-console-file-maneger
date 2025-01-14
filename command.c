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
    if(compare(command, "move") == 1) {
        move_file();
        return 1;
    }
    if(compare(command, "copy") == 1) {
        copy_file();
        return 1;
    }
    if(compare(command, "mkfile") == 1) {
        create_file(path);
        return 1;
    }
    if(compare(command, "mkdir") == 1) {
        create_directory(path);
        return 1;
    }
    if (compare(command, "exit") == 1) {
        return 0;
    }
    system("cls");
    printf("illegal command, please try again\n");
    return 1;
}

//get name from stdin and return 1; if nothing input, return 0
int get_name(char * path)
{
    List * name = newList();
    getList(name);
    if(name->num == 0) {
        system("cls");
        printf("Illegal operation! You must enter somthing\n");
        freeList(name);
        name = NULL;
        return 0;
    }
    splice(path, name);
    freeList(name);
    name = NULL;
    return 1;
}

void list_content(const char * path)
{
    if(path == NULL) return;
    DIR * dir = opendir(path);
    struct dirent * entry;
    if(dir == NULL) {
        printf("open failed\n");
        return;
    }
    printf("content :\n");

    //print file type
    while (entry = readdir(dir)) {
        if(strlen(entry->d_name) > 20)
            printf("  %s\n\t\t\t\t\t", entry->d_name);
        else
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
    printf("enter file name : ");
    if(!get_name(path)) return;

    system("cls");
    if(ShellExecute(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32) {
        printf("Failed to open file\n");
        return;
    }
    printf("Successed to open file\n");
    return;
}

void switch_directory(char * path)
{
    printf("input target folder : ");
    if(!get_name(path)) return;

    system("cls");
    if(chdir(path)) {
        printf("Failed to switch\n");
        return;
    }
    printf("Successed to switch\n");
    return;
}

void move_file()
{
    char source[MAX_PATH], destination[MAX_PATH];
    printf("enter source file path : ");
    scanf("%s", source);
    printf("enter destination file path : ");
    scanf("%s", destination);

    system("cls");
    if (!MoveFile(source, destination)) {
        DWORD error = GetLastError();
        printf("Failed to move file: %s to %s. Error code: %lu\n", source, destination, error);
        switch(error) {
            case ERROR_FILE_NOT_FOUND:
                printf("Source file not found.\n");
                break;

            case ERROR_PATH_NOT_FOUND:
                printf("Destination path not found.\n");
                break;

            case ERROR_ACCESS_DENIED:
                printf("Access denied.\n");
                break;

            case ERROR_SHARING_VIOLATION:
                printf("File is being used by another process.\n");
                break;

            case ERROR_ALREADY_EXISTS:
                printf("A file with the same name already exists at the destination.\n");
                break;

            default:
                printf("An unknown error occurred.\n");
                break;
        }
        return;
    }
    printf("File moved successfully: %s to %s\n", source, destination);
}

void copy_file()
{
    char source[MAX_PATH], destination[MAX_PATH];
    printf("enter source file path : ");
    scanf("%s", source);
    printf("enter destination file path : ");
    scanf("%s", destination);

    system("cls");
    if (!CopyFile(source, destination, FALSE)) {
        DWORD error = GetLastError();
        printf("Failed to copy file: %s to %s. Error code: %lu\n", source, destination, error);
        switch(error) {
            case ERROR_FILE_NOT_FOUND:
                printf("Source file not found.\n");
                break;

            case ERROR_PATH_NOT_FOUND:
                printf("Destination path not found.\n");
                break;

            case ERROR_ACCESS_DENIED:
                printf("Access denied.\n");
                break;

            case ERROR_SHARING_VIOLATION:
                printf("File is being used by another process.\n");
                break;

            default:
                printf("An unknown error occurred.\n");
                break;
        }
        return;
    }
    printf("File copied successfully: %s to %s\n", source, destination);
}

void create_file(char * path)
{
    printf("enter file name: ");
    if(!get_name(path)) return;

    system("cls");
    FILE * new = fopen(path, "w");
    if(new == NULL) {
        printf("Failed to create file\n");
        return;
    }
    printf("Successed to create file\n");
    fclose(new);
}

void create_directory(char * path)
{
    printf("enter folder name: ");
    if(!get_name(path)) return;

    system("cls");
    if (!CreateDirectory(path, NULL)) {
        DWORD error = GetLastError();
        printf("Failed to create directory: %s. Error code: %lu\n", path, error);
        switch(error) {
            case ERROR_ALREADY_EXISTS:
                printf("Directory already exists.\n");
                break;

            case ERROR_PATH_NOT_FOUND:
                printf("Path not found.\n");
                break;

            case ERROR_ACCESS_DENIED:
                printf("Access denied.\n");
                break;

            default:
                printf("An unknown error occurred.\n");
                break;
        }
        return;
    }
    printf("Directory created successfully: %s\n", path);
}