//
// Created by wolves on 2022/3/27.
//

#include "LNode.cpp"
#include "iostream"

using namespace std;

void exercises1(LinkNode &L, int x) {
    LNode *node = L;
    while (node->data == x) {
        node = node->next;
        L = node;
    }
    while (node->next != NULL) {
        if (node->next->data == x) {
            node->next = node->next->next;
        }
        node = node->next;
    }
}

void exercises2(LinkNode &L, int x) {
    LNode *node = L;
    while (node->next != NULL) {
        LNode *p = node->next;
        if (p->data == x) {
            node->next = p->next;
            free(p);
        }
        node = node->next;
    }
}

void exercises3(LinkNode &L) {
    if (L->next != NULL) {
        exercises3(L->next);
    }
    printf("%d ", L->data);
}

LNode *exercises4(LinkNode &L) {
    LNode *node;
    if (L->next->next == NULL) {
        node = L->next;
        L->next = NULL;
        return node;
    }
    LinkNode head = L->next;
    while (head->next != NULL) {
        if (head->data > head->next->data) {
            node = head;
        }
        head = head->next;
    }
    LNode *p = node->next;
    node->next = node->next->next;
    p->next = NULL;
    return p;
}

LNode *exercises5_help(LNode *node1, LNode *node2) {
    if (node2->next == NULL) {
        node2->next = node1;
        return node2;
    }
    LNode *p = exercises5_help(node1->next, node2->next);
    node2->next = node1;
    if (node1->next == node2) {
        node1->next = NULL;
    }
    return p;
}

void exercises5(LinkNode node) {
    LinkNode head = node->next;
    if (head->next == NULL || head->next->next == NULL) {
        return;
    }
    node->next = exercises5_help(head, head->next);
}

LinkNode exercise6(LinkNode node) {
    LinkNode head = (LNode *) malloc(sizeof(LNode));
    head->head = true;
    head->next = head->next;
    LNode *p = head;
    node = node->next;
    while (node != NULL) {
        LNode *s = node;
        node = node->next;
        while (p->next != NULL && p->next->data <= s->data) {
            p = p->next;
        }
        s->next = p->next;
        p->next = s;
        p = head;
    }
    return head;
}

void exercises7(LinkNode &L, int x, int y) {
    LNode *p = L;
    while (p->next != NULL) {
        int temp = p->next->data;
        if (temp > x && temp < y) {
            p->next = p->next->next;
        }
        p = p->next;
    }
}


/**
 * 8/14
 * @param L1
 * @param L2
 * @return
 */
LinkNode exercises8(LinkNode &L1, LinkNode &L2) {
    int temp = GetListLength(L1) - GetListLength(L2);
    LNode *L3 = temp >= 0 ? L1 : L2;
    LNode *L4 = temp < 0 ? L1 : L2;
    for (int i = 0; i < temp; ++i) {
        L3 = L3->next;
    }
    while (L3 != NULL) {
        if (L3 == L4) {
            return L3;
        }
        L3 = L3->next;
        L4 = L4->next;
    }
    return NULL;
}

void exercises9(LinkNode &L) {
    while (L->next != NULL) {
        LinkNode node = L;
        LNode *min = L;
        while (node->next->next != NULL) {
            if (node->next->next->data < min->next->data) {
                min = node->next;
            }
            node = node->next;
        }
        printf("%d ", min->next->data);
        LNode *p = min->next;
        min->next = p->next;
        free(p);
    }
}

/**
 * 10/11
 * @param L
 * @param A
 * @param B
 */
void exercises10(LinkNode &L, LinkNode &A, LinkNode &B) {
    LinkNode node = L;
    LinkNode a = A;
    LinkNode b = B;
    while (node->next != NULL) {
        a->next = node->next;
        a = a->next;
        node = node->next;
        b->next = node->next;
        b = b->next;
        node = node->next;
    }
    a->next = NULL;
    b->next = NULL;
}

void exercises12(LinkNode &L) {
    LinkNode head = L->next;
    while (head->next != NULL) {
        if (head->data == head->next->data) {
            head->next = head->next->next;
            continue;
        }
        head = head->next;
    }
}

LinkNode exercises13(LinkNode &L1, LinkNode &L2) {
    LinkNode A = L1->next;
    LinkNode B = L2->next;
    LinkNode node = (LNode *) malloc(sizeof(LNode));
    node->head = true;
    LinkNode head = node;
    exercises5(L1);
    exercises5(L2);
    while (A != NULL && B != NULL) {
        if (A->data > B->data) {
            head->next = A;
            A = A->next;
        } else {
            head->next = B;
            B = B->next;
        }
        head = head->next;
    }
    head->next = A != NULL ? A : B;
    return node;
}

void exercises15(LinkNode &L1, LinkNode &L2, LinkNode &A) {
    LinkNode a = L1->next;
    LinkNode b = L2->next;
    LinkNode c = A;
    while (a != NULL && b != NULL) {
        if (a->data == b->data) {
            LNode *node = (LNode *) malloc(sizeof(LNode));
            node->data = a->data;
            c->next = node;
            a = a->next;
            b = b->next;
            c = c->next;
            continue;
        }
        a->data > b->data ? b = b->next : a = a->next;;
    }
}

/**
 * 16
 * KMP??????
 */

/**
 * 17
 * ?????????????????????????????????
 */

/**
 * 18
 * ??????????????????????????????????????????
 * ???????????????????????????
 * ????????????????????????
 * ???next???????????????????????????
 */

/**
 * 18
 * ??????????????????
 */

/**
 * 20
 * struct???2???date???????????????
 * ?????????????????????
 * ?????????????????????
 * ????????????????????????????????????next???????????????node->next?????????????????????
 * ???????????????node->pred->next=node->next;
 * ???????????????node1->pred->next=node
 * node->next=node1
 */

/**
 * 21
 * p-q=k
 */
int exercises21(LinkNode &L, int k) {
    LNode *p = L->next;
    LNode *q = L->next;
    int x = 0;
    while (q->next != NULL) {
        q = q->next;
        x++;
        if (x > k) {
            p = p->next;
        }
    }
    if (x < k) {
        return 0;
    }
    PrintNode(p);
    return 1;
}

/**
 * 22
 * ????????????
 * ????????????????????????
 * ??????????????????
 * ??????????????????
 * ??????????????????????????????????????????
 */

/**
 * 23
 * ?????????????????????n?????????????????????0
 * ???????????????[data]???????????????0?????????0?????????1?????????1????????????
 */
#define n 10

void exercises23(LinkNode &L) {
    int *arr = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        arr[i] = 0;
    }
    LinkNode &head = L;
    while (head->next != NULL) {
        int temp = abs(head->next->data);
        if (arr[temp] == 0) {
            arr[temp] = 1;
        } else {
            head->next = head->next->next;
            if (head->next == NULL) {
                break;
            }
        }
        head = head->next;
    }
}

/**
 * 24
 * ???????????????
 * ?????????????????????????????????????????????
 * ?????????????????????????????????????????????
 * ??????????????????NULL
 */

/**
 * ????
 * 25
 * ??????????????????????????????????????????????????????
 */

void test() {
    //LinkNode L1 = createLinkList();
    LinkNode L2 = createLinkedList();
    LinkNode L3 = L2;
    //LinkNode A = (LNode *) malloc(sizeof(LNode));
    //A->head = true;
    //LinkNode B = (LNode *) malloc(sizeof(LNode));
    //B->head = true;

    //exercises1(L1, 2);
    //exercises2(L2, 2);
    //exercises3(L2->next);
    //LNode *node = exercises4(L2);
    //cout << node->data << endl;
    //exercises5(L2);
    //L3 = exercise6(L2);
    //exercises7(L2, 4, 6);
    //exercises9(L2);
    //exercises10(L3, A, B);
    //exercises21(L2, 4);
    exercises23(L2);

    printf("\n");
    //PrintLinkList(L1);
    PrintLinkList(L3);
    //PrintLinkList(A);
    //PrintLinkList(B);
}