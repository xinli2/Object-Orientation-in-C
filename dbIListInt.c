#include "dblListInt.h"
#include <stdlib.h>
#include <stdio.h>

DblList_Int *dblList_Int__alloc(int val)
{
    DblList_Int *ret = (DblList_Int*)malloc(sizeof(DblList_Int));
    if (ret == NULL) {
        printf("alloc error.\n");
        return NULL;
    } else {
        ret->next = NULL;
        ret->prev = NULL;
        ret->val = val;
    }
    return ret;
}

void dblList_Int__free(DblList_Int* this)
{
    if (this == NULL || this->prev != NULL || this->next != NULL) {
        printf("free error.\n");
    }
    if (this != NULL) {
        free(this);
    }
}
int          dblList_Int__getVal (DblList_Int* this)
{
    return this->val;
}

DblList_Int *dblList_Int__getNext(DblList_Int* this)
{
    return this->next;
}

DblList_Int *dblList_Int__getPrev(DblList_Int* this)
{
    return this->prev;
}

DblList_Int *dblList_Int__getHead(DblList_Int* this)
{
    if (this == NULL) {
        printf("get head error.\n");
        return NULL;
    }
    DblList_Int *p = this;
    while (p != NULL && p->prev != NULL) {
        p = p->prev;
    }
    return p;
}

DblList_Int *dblList_Int__getTail(DblList_Int* this)
{
    if (this == NULL) {
        printf("get tail error.\n");
        return NULL;
    }
    DblList_Int *p = this;
    while (p != NULL && p->next != NULL) {
        p = p->next;
    }
    return p;
}

void dblList_Int__addAfter(DblList_Int* this, DblList_Int* other)
{
    if (this == NULL || other == NULL || other->prev != NULL || other->next != NULL) {
        printf("add after error.\n");
        return;
    }
    other->prev = this;
    other->next = this->next;
    if (this->next != NULL) {
        this->next->prev = other;
    }
    this->next = other;
}

void dblList_Int__addTail(DblList_Int* this, int value)
{
    if (this == NULL) {
        printf("add tail error.\n");
        return;
    }
    DblList_Int *tail = dblList_Int__getTail(this);
    DblList_Int *other = dblList_Int__alloc(value);
    dblList_Int__addAfter(tail, other);
}

void dblList_Int__remove(DblList_Int* this)
{
    if (this == NULL || (this->next == NULL && this->prev == NULL)) {
        printf("remove error.\n");
        return;
    }
    DblList_Int *prev = this->prev;
    DblList_Int *next = this->next;
    if (prev != NULL) {
        prev->next = this->next;
    }
    if (next != NULL) {
        next->prev = this->prev;
    }
    this->next = NULL;
    this->prev = NULL;
}
