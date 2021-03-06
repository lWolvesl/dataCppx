//
// Created by wolves on 2022/7/15.
//
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"
#include "time.h"
#include "../tools.cpp"

//串结构
typedef struct {
    char *ch;   //指向字符串所在空间首地址
    int length; //记录字符串长度
} HString;

void InitHString(HString *s) {
    s->ch = NULL;
    s->length = 0;
}

void PrintString(HString s) {
    for (int i = 0; i < s.length; ++i) {
        printf("%c", s.ch[i]);
    }
    printf("\n");
}

void StrAssign(HString *s, char *c) {
    int Clength = strlen(c);
    if (s->ch != NULL) {
        free(s->ch);
    }
    s->ch = (char *) malloc(sizeof(char) * Clength);
    assert(s->ch != NULL);
    for (int i = 0; i < Clength; ++i) {
        s->ch[i] = c[i];
    }
    s->length = Clength;
}

void StrCopy(HString *s, HString *h) {
    if (s->ch != NULL) {
        free(s->ch);
    }
    s->ch = (char *) malloc(sizeof(char) * h->length);
    assert(s->ch != NULL);
    for (int i = 0; i < h->length; ++i) {
        s->ch[i] = h->ch[i];
    }
    s->length = h->length;
}

bool StrEmpty(HString *s) {
    if (s->ch == NULL) {
        return true;
    }
    return false;
}

int StrCompare(HString s, HString h) {
    return s.length - h.length;
}

int StrString(HString *s) {
    return s->length;
}

void SubString(HString *s, HString *T, int pos, int len) {
    s->length = len;
    if (s->ch != NULL) {
        free(s->ch);
    }
    s->ch = (char *) malloc(sizeof(char) * len);
    assert(s->ch != NULL);
    for (int i = 0; i < len; ++i) {
        s->ch[i] = T->ch[pos + i];
    }
}

void Concat(HString *S, HString *s1, HString *s2) {
    S->length = s1->length + s2->length;
    if (S->ch != NULL) {
        free(S->ch);
    }
    S->ch = (char *) malloc(sizeof(char) * S->length);
    assert(S->ch != NULL);
    for (int i = 0; i < s1->length; ++i) {
        S->ch[i] = s1->ch[i];
    }
    for (int i = 0; i < s2->length; ++i) {
        S->ch[s1->length + i] = s2->ch[i];
    }
}

//朴素(简单)模式匹配算法
int Index(HString S, HString T) {
    if (StrCompare(S, T) < 0) {
        return -1;
    }
    for (int i = 0, j = 0; i < S.length;) {
        if (S.ch[i + j] == T.ch[j]) {
            j++;
            if (j == T.length) {
                return i;
            }
        } else {
            if (i + j >= S.length) {
                break;
            }
            j = 0;
            i++;
        }
    }
    return -1;
}

void ClearString(HString *s) {
    if (s->ch != NULL) {
        free(s->ch);
    }
    s->length = 0;
}

void DestroyString(HString *s) {
    free(s);
}

//快速创建字符串
HString createStr(char *T) {
    HString S;
    InitHString(&S);
    StrAssign(&S, T);
    return S;
}

//KMP 计算next数组
int *get_next(HString T) {
    int *next = (int *) malloc(sizeof(int) * (T.length));
    int i = 0, j = -1;
    next[0] = -1;
    while (i < T.length) {
        if (j == -1 || T.ch[i] == T.ch[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    return next;
}

int Index_KMP(HString S, HString T) {
    int *next = get_next(T);
    int i = 0, j = 0;
    while (i + T.length < S.length) {
        if (S.ch[i + j] == T.ch[j]) {
            j++;
            if (j == T.length) {
                return i;
            }
        } else {
            i = i + j - next[j];
            j = next[j];
            if (j == -1) {
                j++;
            }
        }
    }
    free(next);
    return -1;
}

void testKMP(){
    HString S = createStr("ababcbfaosfaijfpicnzoinflfknietnldaiopjpaciancimzcaocacmzicabababcacbab");
    HString T = createStr("abcac");

    int index = Index_KMP(S, T);
    printf("%d\n", index);
}

void test() {
    starts();
    testKMP();
    //HString T = createStr("ababaaababaa");
    //HString T = createStr("abaabcac");
    //HString T = createStr("google");

}