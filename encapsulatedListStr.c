#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encapsulatedListStr.h"

struct EncapsulatedList_Str{
    int length;
    EncNode_Str *head;
    EncNode_Str *tail;
};

struct EncapsulatedList_Str_Node{
    char *val;
    int dup;
    struct EncapsulatedList_Str_Node *next;
    struct EncapsulatedList_Str_Node *prev;
};

EncList_Str *encList_Str__alloc(){
    EncList_Str *ret = (EncList_Str*)malloc(sizeof(EncList_Str));
    if(ret == NULL){
        printf("alloc error!");
        return NULL;
    }
    ret->length = 0;
    ret->head = NULL;
    ret->tail = NULL;
    return ret;
}

void encList_Str__free(EncList_Str* this){
    if(this == NULL){
        fprintf(stderr, "List was NULL!\n");
        return;
    }
    EncNode_Str* curr = this->head;
    EncNode_Str* prev;
    while(curr != NULL){
        prev = curr;
        curr = curr->next;
        if(prev->dup == 1)
            free(prev->val);
        free(prev);
    }
    free(this);
}

void encList_Str__addHead(EncList_Str* this, char *string, int dup){
    if(this == NULL){
        fprintf(stderr, "List was NULL!\n");
        return;
    }

    char *toAdd;
    if(dup == 1){
        int length = strlen(string) + 1;
        toAdd = malloc(length * sizeof(char));
        memcpy(toAdd, string, length);
    }
    else
        toAdd = string;
    EncNode_Str *newHead = malloc(sizeof(EncNode_Str));
    newHead->val = toAdd;
    newHead->prev = NULL;
    newHead->next = this->head;
    newHead->dup = dup;
    if(this->head != NULL)
        this->head->prev = newHead;
    else
        this->tail = newHead;
    this->head = newHead;
    this->length++;
}

void encList_Str__addTail(EncList_Str* this, char *string, int dup){
    if(this == NULL){
        fprintf(stderr, "List was NULL!\n");
        return;
    }

    char *toAdd;
    if(dup == 1){
        int length = strlen(string) + 1;
        toAdd = malloc(length * sizeof(char));
        memcpy(toAdd, string, length);
    }
    else
        toAdd = string;
    EncNode_Str *newTail = malloc(sizeof(EncNode_Str));

    newTail->val = toAdd;
    newTail->prev = this->tail;
    newTail->next = NULL;
    newTail->dup = dup;
    if(this->head == NULL)
        this->head = newTail;
    else
        this->tail->next = newTail;
    this->tail = newTail;
    this->length++;
}

int encList_Str__count(EncList_Str* this){
    if(this == NULL){
        fprintf(stderr, "List was NULL!\n");
        return -1;
    }
    return this->length;
}

char *encList_Str__getMin(EncList_Str* this){
    if(this == NULL){
        fprintf(stderr, "List was NULL!\n");
        return NULL;
    }
    if(this->head == NULL){
        return NULL;
    }
    EncNode_Str *curr = this->head;
    char *toReturn = curr->val;
    while(curr != NULL){
        if(strcmp(toReturn, curr->val) > 0)
            toReturn = curr->val;
        curr = curr->next;
    }
    return toReturn;
}
char *encList_Str__getMax(EncList_Str* this){
    if(this == NULL){
        fprintf(stderr, "List was NULL!\n");
        return NULL;
    }
    if(this->head == NULL){
        return NULL;
    }
    EncNode_Str *curr = this->head;
    char *toReturn = curr->val;
    while(curr != NULL){
        if(strcmp(toReturn, curr->val) < 0)
            toReturn = curr->val;
        curr = curr->next;
    }
    return toReturn;
}

void encList_Str__merge(EncList_Str* left, EncList_Str* right){
    if(left == NULL || right == NULL){
        fprintf(stderr, "One of the lists were NULL!\n");
        return;
    }
    EncNode_Str* currLeft = left->head;
    EncNode_Str* currRight = right->head;
    while(currRight != NULL && currLeft != NULL){
        if(strcmp(currLeft->val, currRight->val) <= 0){
            currLeft = currLeft->next;
        }
        else{
            EncNode_Str* nextRight = currRight->next;
            currRight->prev = currLeft->prev;
            if(currRight->prev != NULL)
                currRight->prev->next = currRight;
            else
                left->head = currRight;
            currLeft->prev = currRight;
            currRight->next = currLeft;
            currRight = nextRight;
            if(currRight != NULL)
                currRight->prev = NULL;
        }
    }
    //All the remaining values in right list are > than the values in left list
    //Add tje rest of the right list to the end of the left list.
    if(currRight != NULL && left->head != NULL){
        left->tail->next = currRight;
        currRight->prev = left->tail;
        left->tail = right->tail;
        right->head = NULL;
        right->tail = NULL;
    }
        //Left list is empty, add the nodes from the right list into it.
    else if(currRight != NULL && left->head == NULL){
        left->head = right->head;
        left->tail = right->tail;
        right->head = NULL;
        right->tail = NULL;
    }
    //Otherwise, right was empty, so nothing needs to be done
    //Just need to ensure that the right list is emptied of pointers
    //that could now be in the middle of another list.
    right->head = NULL;
    right->tail = NULL;
    left->length = left->length + right->length;
    right->length = 0;
}

void encList_Str__append(EncList_Str* this, EncList_Str* other){
    if(this == NULL || other == NULL){
        fprintf(stderr, "append error!\n");
        return;
    }
    this->tail->next = other->head;
    other->head->prev = this->tail;
    this->tail = other->tail;
    other->head = NULL;
    other->tail = NULL;
    this->length = this->length + other->length;
    other->length = 0;
}

EncNode_Str *encList_Str__index(EncList_Str* this, int inx){
    if(this == NULL || inx >= this->length || inx < 0){
        fprintf(stderr, "inx error!\n");
        return NULL;
    }
    EncNode_Str *p;
    int i;
    if (inx >= this->length / 2) {
        p = this->tail;
        i = this->length - 1;
        while(i > inx){
            p = p->prev;
            i--;
        }
    }
    else {
        p = this->head;
        i = 0;
        while(i < inx){
            p = p->next;
            i++;
        }
    }
    return p;
}

EncList_Str *encList_Str__splitAt(EncList_Str* this, int inx){
    if(this == NULL || inx < 0 || inx > this->length){
        fprintf(stderr, "split error!\n");
        return NULL;
    }

    EncList_Str *sub = encList_Str__alloc();
    if(inx == this->length){
        return sub;
    }
    sub->head = encList_Str__index(this, inx);
    sub->tail = this->tail;
    if (sub->head != this->head) {
        this->tail = sub->head->prev;
        this->tail->next = NULL;
        sub->head->prev = NULL;
        sub->length = this->length - inx;
        this->length = this->length - sub->length;
    } else {
        this->head = NULL;
        this->tail = NULL;
        sub->length = this->length;
        this->length = 0;
    }
    return sub;
}

EncNode_Str *encList_Str__getHead(EncList_Str* this){
    if(this == NULL){
        fprintf(stderr, "get head error!\n");
        return NULL;
    }
    return this->head;
}

EncNode_Str *encList_Str__getTail(EncList_Str* this){
    if(this == NULL){
        fprintf(stderr, "get tail error!\n");
        return NULL;
    }
    return this->tail;
}

char        *encNode_Str__getStr (EncNode_Str* this){
    return this->val;
}

EncNode_Str *encNode_Str__getNext(EncNode_Str* this){
    return this->next;
}

EncNode_Str *encNode_Str__getPrev(EncNode_Str* this){
    return this->prev;
}
