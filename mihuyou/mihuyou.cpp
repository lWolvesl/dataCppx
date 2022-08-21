//
// Created by wolves on 2022/8/7.
//

#include "stdio.h"

typedef struct Queue{
    char data;
    struct Queue* next;
} Queue;

struct Queue init(){
    Queue queue;
    queue.next = NULL;
    return queue;
}

void addNew(char s,Queue* head){
    Queue* node = head;
    while (node->next != NULL){
        node = node->next;
    }
    Queue queue;
    queue.data = s;
    queue.next = NULL;
    node->next = &queue;
}

int getState(char c){
    switch (c) {
        case 'w':return 0;
        case 'i':return 1;
        case 't':return 2;
        case 'f':return 3;
        case 'g':return 4;
        case 's':return 5;
        case 'b':return 6;
        default:return -1;
    }
}

void pop(Queue* head){
    head = head->next;
}

int getTypes(Queue* head){
    Queue* node = head;
    int s[7] = {0,0,0,0,0,0,0};
    while(node->next != NULL){
        node = node->next;
        s[getState(node->data)] = 1;
    }
    int le = 0;
    for (int i = 0; i < 7; ++i) {
        if(s[i] == 1){
            le++;
        }
    }
    return le;
}

void run(){
    Queue head = init();
    int q;
    scanf("%d",&q);
    for (int i = 0; i < q; ++i) {
        int c;
        scanf("%d",&c);
        if(c == 3){
            printf("%d\n", getTypes(&head));
        }
        if(c == 1){
            char s;
            scanf("%s",&s);
            addNew(s,&head);
        }
        if(c == 2){
            pop(&head);
        }
    }
}
