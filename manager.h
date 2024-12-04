#ifndef _GAME_LINE_
    #define _GAME_LINE_ 1
    #define _MUSIC_LINE_ 2
    #define _SAVE_LINE_ 3
#endif

extern char * game_dir;//D://user/game/
extern char * music_dir;
extern char * save_dir;

char * get_dir(const char * );
char * get_game_dir();
char * get_music_dir();
char * get_save_dir();
FILE * getData(const char * , const char * );