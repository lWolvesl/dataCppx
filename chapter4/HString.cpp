//
// Created by wolves on 2022/7/15.
//
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"

//串结构
typedef struct
{
    char *ch;   //指向字符串所在空间首地址
    int   length; //记录字符串长度
}HString;

void InitHString(HString *s){
    s->ch = NULL;
    s->length = 0;
}

void PrintString(HString *s){
    for (int i = 0; i < s->length; ++i) {
        printf("%c",s->ch[i]);
    }
    printf("\n");
}

void StrAssign(HString *s,char *c){
    int Clength = strlen(c);
    if(s->ch != NULL){
        free(s->ch);
    }
    s->ch = (char*)malloc(sizeof(char) * Clength);
    assert(s->ch != NULL);
    for (int i = 0; i < Clength; ++i) {
        s->ch[i] = c[i];
    }
    s->length = Clength;
}

void StrCopy(HString *s,HString *h){
    if(s->ch != NULL){
        free(s->ch);
    }
    s->ch = (char*)malloc(sizeof(char) * h->length);
    assert(s->ch != NULL);
    assert(s->ch != NULL);
    for (int i = 0; i < h->length; ++i) {
        s->ch[i] = h->ch[i];
    }
    s->length = h->length;
}

bool StrEmpty(HString *s){
    if(s->ch == NULL){
        return true;
    }
    return false;
}

int StrCompare(HString *s,HString *h){
    return s->length - h->length;
}