#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "link_list.h"

Node * newNode(char data, Node * next)
{
    Node * new = (Node *)malloc(sizeof(Node));
    new->data = data;
    new->next = next;
    return new;
}

List * newList()
{
    List * new = (List *)malloc(sizeof(List));
    new->num = 0;
    new->node = NULL;
    return new;
}

//put the string into linklist, the limitation of length is MAX_PATH
void getList(List * list)
{
    if(list == NULL) return;

    //initiallize list
    Node * node = list->node;
    for(int i = 0; i < list->num; ++i) {
        Node * deleted = node;
        node = node->next;
        free(deleted);
    }
    list->num = 0;
    list->node = NULL;
    node = NULL;

    char c;
    fflush(stdin);
    while((c = fgetc(stdin)) != '\n' && list->num < MAX_PATH - 1) {
        ++list->num;
        if(list->node == NULL) {
            list->node = newNode(c, NULL);
            node = list->node;
            continue;
        }
        node->next = newNode(c, NULL);
        node = node->next;
    }
    if(node != NULL)
        node->next = newNode('\0', NULL);
}

void printList(Node *list)
{
    if(list == NULL) return;

    while(list != NULL) {
        printf("%c", list->data);
        list = list->next;
    }
}

//compare linklist and array, if the same, it'll return 1; return 0 if it isn't; return -1 if error happened
int compare(List * list, char * a)
{
    if(list == NULL) return -1;
    if(a == NULL) return -1;
    Node * node = list->node;
    for(int i = 0; node->data != '\0' && *a != '\0'; ++i) {
        if(node->data != *a) return 0;
        node = node->next;
        a = a + 1;
    }
    if(node->data == '\0' && *a == '\0') return 1;
    return 0;
}

//connect path and list, the formula is path\list
void splice(char * path, List * list)
{
    if(path == NULL) return;
    if(list == NULL) return;
    if(list->num == 0) return;

    Node * node = list->node;
    path += strlen(path);
    *(path) = '\\';
    while(strlen(path) < MAX_PATH) {
        *(++path) = node->data;
        if(node->data == '\0') return;
        node = node->next;
    }
}

void freeList(List * list)
{
    Node * node = list->node;
    for(int i = 0; i < list->num; ++i) {
        Node * deleted = node;
        node = node->next;
        free(deleted);
    }
    free(list);
}