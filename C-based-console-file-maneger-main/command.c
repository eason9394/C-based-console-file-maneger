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
    if(compare(command, "copy") == 1) {
        char source[MAX_PATH], destination[MAX_PATH];
        printf("enter source file path : ");
        scanf("%s", source);
        printf("enter destination file path : ");
        scanf("%s", destination);
        copy_file(source, destination);
        return 1;
    }
    if(compare(command, "move") == 1) {
        char source[MAX_PATH], destination[MAX_PATH];
        printf("enter source file path : ");
        scanf("%s", source);
        printf("enter destination file path : ");
        scanf("%s", destination);
        move_file(source, destination);
        return 1;
    }
    if(compare(command, "mkdir") == 1) {
        char path[MAX_PATH];
        printf("enter directory path : ");
        scanf("%s", path);
        create_directory(path);
        return 1;
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
        DWORD attrs = GetFileAttributes(entry->d_name);
        if (attrs == INVALID_FILE_ATTRIBUTES) {
            printf("error");
        } else if (attrs & FILE_ATTRIBUTE_DIRECTORY) {
            printf("directory");
        } else {
            printf("regular");
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

void copy_file(char *source, char *destination) {
    if (!CopyFile(source, destination, FALSE)) {
        DWORD error = GetLastError();
        printf("Failed to copy file: %s to %s. Error code: %lu\n", source, destination, error);
        switch (error) {
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
    } else {
        printf("File copied successfully: %s to %s\n", source, destination);
    }
}

void move_file(char *source, char *destination) {
    if (!MoveFile(source, destination)) {
        DWORD error = GetLastError();
        printf("Failed to move file: %s to %s. Error code: %lu\n", source, destination, error);
        switch (error) {
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
    } else {
        printf("File moved successfully: %s to %s\n", source, destination);
    }
}

void create_directory(char *path) {
    if (!CreateDirectory(path, NULL)) {
        DWORD error = GetLastError();
        printf("Failed to create directory: %s. Error code: %lu\n", path, error);
        switch (error) {
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
    } else {
        printf("Directory created successfully: %s\n", path);
    }
}