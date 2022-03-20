//
// Created by wolves on 2022/3/17.
//

#define Maxsize 50

typedef struct {
    int data[Maxsize];
    int length;
} SeqList;

void InitSeqList(SeqList &L) {
    for (int i = 0; i < Maxsize; ++i) {
        L.data[i] = 0;
    }
    L.length = 0;
}
