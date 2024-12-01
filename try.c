#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// 定義三個資料夾
#define GAME_FOLDER "games"
#define MUSIC_FOLDER "music"
#define RECORD_FOLDER "record"

// 顯示目錄內容
void list_files(const char *folder) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    char searchPath[MAX_PATH];

    snprintf(searchPath, MAX_PATH, "%s\\*", folder);
    hFind = FindFirstFile(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("connot list folder: %s\n", folder);
        return;
    }

    printf("folder contain (%s):\n", folder);
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            printf("  %s\n", findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

// 開啟檔案
void open_file(const char *folder, const char *filename) {
    char fullPath[MAX_PATH];
    snprintf(fullPath, MAX_PATH, "%s\\%s", folder, filename);

    if (ShellExecute(NULL, "open", fullPath, NULL, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32) {
        printf("connot open file: %s\n", fullPath);
    } else {
        printf("opne file successd: %s\n", fullPath);
    }
}

// 主程式
int main() {
    char command[10];
    char folder[MAX_PATH] = GAME_FOLDER; // 預設進入 `game` 資料夾
    char filename[MAX_PATH];

    printf("welcome to use this file manage！\n");
    printf("usable folder: games, music, record\n");

    while (1) {
        printf("\ncurrent folder: %s\n", folder);
        printf("useful command: list, open, switch, exit\n");
        printf("input conmmand: ");
        scanf("%s", command);

        if (strcmp(command, "list") == 0) {
            list_files(folder);
        } else if (strcmp(command, "open") == 0) {
            printf("enter file name: ");
            scanf("%s", filename);
            open_file(folder, filename);
        } else if (strcmp(command, "switch") == 0) {
            printf("input target folder (game, music, record): ");
            scanf("%s", command);
            if (strcmp(command, "game") == 0 || strcmp(command, "music") == 0 || strcmp(command, "record") == 0) {
                strcpy(folder, command);
                printf("switch to folder: %s\n", folder);
            } else {
                printf("invalid folder name\n");
            }
        } else if (strcmp(command, "exit") == 0) {
            printf("quit the program\n");
            break;
        } else {
            printf("unknown command, please try again\n");
        }
    }

    return 0;
}
