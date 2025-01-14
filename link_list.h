typedef struct node{
    char data;
    struct node * next;
}Node;

typedef struct list{
    int num;
    Node * node;
}List;

Node * newNode(char, Node *);
List * newList();
void getList(List *);
void printList(Node *);
int compare(List *, char *);
void splice(char *, List *);
void freeList(List *);