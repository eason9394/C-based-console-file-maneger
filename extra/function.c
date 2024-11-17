#include<stdio.h>
#include <dirent.h>
#include<string.h>

void seeAllFile(int choice)
{
    struct dirent *entry;
    //dirent 是一個structure，再麻煩你們自己去查了，因為我也不太懂
    DIR *dir;
    char storage[500];

    //迴圈寫在主函式，讓使用者可以一直做這個動作，
    //我不知道為甚麼寫在這邊會錯，現在不想研究這個
    printf("*******************************************\n");
    printf("1: storage, 2: BGM, 3: test file, 9: Cancel\n");
    printf("*******************************************\n");
    
    //資料夾我暫時先把位置寫死，後面再看要怎麼修改
    //放在系統裡，或是給使用者自行決定?
    if(choice == 1){
    //查看儲存紀錄
        dir = opendir("C:\\Users\\user\\Desktop\\storage");
    } else if(choice == 2){
        //查看音樂清單(prototype 2 可以考慮在看的時候就可以聽)
        dir = opendir("C:\\Users\\user\\Desktop\\BGM");
    } else if(choice == 3){
        //test file(我有點不太懂test file詳細要幹嘛)
        //user story看起來可以整合進去search?
        dir = opendir("C:\\Users\\user\\Desktop\\testfile");
    } else if(choice == 999){
        //作弊檔案
        //是否要做一個VIP user? 讓查看作弊檔案的人有雙重認證
        dir = opendir("C:\\Users\\user\\Desktop\\cheatfile");
    } else {
        printf("Invalid choice\n");
    }

    if(dir == NULL){
        printf("Unable to open directory\n");
        return;
    }

        while ((entry = readdir(dir)) != NULL) {
        // 過濾掉 "." 和 ".."
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);  // 輸出檔案或目錄名稱
        }
    }
    closedir(dir);
}
    
void search(char key[])
{
    //快速尋找檔案
    char choice;
    printf("Do you know where the file is? : [Y/N]");   
    scanf("%c", &choice);
    if(choice == 'Y' || choice == 'y'){
        int where;
        printf("***************************\n");
        printf("1:storage 2:BGM 3:test file\n");
        printf("***************************\n");
        printf("Where is the file: ");
        scanf("%d", &where);

        DIR *dir;
        struct dirent *entry;
        char filename[500];

        if(where == 1){
           dir = opendir("C:\\Users\\user\\Desktop\\storage");
        } else if(where == 2){
            dir = opendir("C:\\Users\\user\\Desktop\\BGM");
        } else if (where == 3){
            dir = opendir("C:\\Users\\user\\Desktop\\testfile");
        } else {
            printf("Invalid choice\n");
        }
        if(dir == NULL){
            printf("Unable to open directory\n");
            return;
        }

        while ((entry = readdir(dir)) != NULL) {
            if (strstr(entry->d_name, key) != NULL) {
                printf("%s\n", entry->d_name);  
            }
        }

        closedir(dir); 
    } else if(choice == 'N' || choice == 'n'){
        //每個都要找
        struct dirent *entry;
        DIR *storageDir;
        DIR *BGMDir;
        DIR *testFileDir;
        //目前只鎖死只可以找這些資料夾，或許之後要想怎麼擴充這個功能?
        if(storageDir == NULL){
            printf("Unable to open directory\n");
            return;
        }
        while ((entry = readdir(storageDir)) != NULL) {
            if (strstr(entry->d_name, key) != NULL) {
                printf("%s\n", entry->d_name);  
            }
        }


        if(BGMDir == NULL){
            printf("Unable to open directory\n");
            return;
        }
        while ((entry = readdir(BGMDir)) != NULL) {
            if (strstr(entry->d_name, key) != NULL) {
                printf("%s\n", entry->d_name);  
            }
        }

        if(testFileDir == NULL){
            printf("Unable to open directory\n");
            return;
        }
        while ((entry = readdir(testFileDir)) != NULL) {
            if (strstr(entry->d_name, key) != NULL) {
                printf("%s\n", entry->d_name);  
            }
        }

    }
}
void interface(){
    int choice;
    char key[500];
    printf("*******************************************\n");
    printf("1: see all file, 2: search, 3: record, 9: Cancel\n");
    printf("*******************************************\n");
    printf("What do you want to do: ");
    scanf("%d", &choice);
    if(choice == 1){
        int choiceWhatYouWantToSee;
        scanf("%d", &choiceWhatYouWantToSee);

        while (choiceWhatYouWantToSee != 9){
            seeAllFile(choiceWhatYouWantToSee);
            scanf("%d", &choiceWhatYouWantToSee);
        }
    } else if(choice == 2){
        printf("What do you want to search: ");
        scanf("%s", key);
        search(key);
    }
}

//進度存檔，不太清楚我可以怎麼做，先放著
void record();