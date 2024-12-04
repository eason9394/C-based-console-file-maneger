#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "manager.h"

char * game_dir;//D://user/game/
char * music_dir;
char * save_dir;

char * get_dir(const char * folder)
{
    int line = 0;
    if(!strcmp("game", folder)) line = _GAME_LINE_;
    if(!strcmp("music", folder)) line = _MUSIC_LINE_;
    if(!strcmp("save", folder)) line = _SAVE_LINE_;
    if(line == 0) {
        printf("no folder\n");
        return NULL;
    }

    FILE * folder_position = fopen("folder_position.txt", "r");
    char * path = malloc(256 * sizeof(char));
    for(int i = 0; i < line; ++i) {
        fgets(path, 255, folder_position);
    }
    return path;
}

FILE * getData(const char * filename, const char * mode)
{
    save_dir = get_dir("save");

    char * path = calloc(strlen(save_dir) + strlen(filename) + 1 , sizeof(char));
    strcat(path, save_dir);
    path[strlen(save_dir) - 1] = '\0';
    strcat(path, filename);
    
    FILE * file = fopen(path, mode);
    free(save_dir);
    save_dir = NULL;
    free(path);
    path = NULL;
    return file;
}
