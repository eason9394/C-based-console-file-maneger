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

List * newList(int num)
{
    List * new = (List *)malloc(sizeof(List));
    new->num = num;
    if(num != 0) {
        new->node = newNode(0, NULL);
        Node * node = new->node;
        for(int i = 1; i < num; ++i) {
            node->next = newNode(0, NULL);
            node = node->next;
        }
        return new;
    }
    new->node = NULL;
    return new;
}

void getList(List * list)
{
    if(list == NULL) return;
    Node * node = list->node;
    char c;
    fflush(stdin);
    while((c = fgetc(stdin)) != '\n') {
        node->data = c;
        node = node->next;
    }
    node->data = '\0';
}

void printList(Node *list)
{
    if(list == NULL) return;

    while(list != NULL) {
        printf("%c", list->data);
        list = list->next;
    }
}

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

void splice(char * path, List * list)
{
    Node * node = list->node;
    path += strlen(path);
    *(path) = '\\';
    while(strlen(path) < MAX_PATH) {
        *(++path) = node->data;
        if(node->data == '\0') return;
        node = node->next;
    }
}

void freeList(List ** list)
{
    Node * node = (*list)->node;
    for(int i = 0; i < (*list)->num; ++i) {
        Node * deleted = node;
        node = node->next;
        free(deleted);
    }
    free(*list);
    list = NULL;
}