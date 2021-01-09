/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa1
* List.c
* Implementation file for List ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

/* structs defaulted all private */
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

/* Node Alias for NodeObj */
typedef NodeObj* Node;

/* ListObj Type */
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

/* Constructors - Destructors */

/* newNode() */
Node newNode(int d){
    Node N = malloc(sizeof(NodeObj));
    N->data = d;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

/* freeNode() */
void freeNode(Node* pN){
    if( pN != NULL && *pN!= NULL){
        free(*pN);
        *pN = NULL;
    }
}

/* newList() */
List newList() {
    List L;
    L =  malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}

/* freeList() */
void freeList(List* pL){
    if ( pL != NULL && *pL != NULL ){
        while( length(*pL) > 0 ) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

/* Access Functions */
int front(List L){
    if (L == NULL){
        printf("List Error: calling front() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);
}

int back(List L){
    if (L == NULL){
        printf("List Error: calling back() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}

int length(List L){
    if (L == NULL){
        printf("List Error: calling length() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

int index(List L){
    if (L->cursor == NULL){
        return -1;
    }
    return L->index;
}

int get(List L){
    /*PreCondition If Statements*/
    if(L == NULL){
        printf("List Error: calling get() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling get() with an undefined Cursor\n");
        exit(EXIT_FAILURE);
    }
    /*Get current node and return its data*/
    return L->cursor->data;
}

int equals(List A, List B){
    if (A == NULL || B == NULL){ /*if either list is NULL exit with error */
        printf("List Error: calling equals() with a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    int equal = 0; /* default to false "0" */
    Node F = A->front;
    Node N = B->front;
    
    if (A->length == B->length){ equal = 1; } /* if lengths are not same return false "0"*/
    /* look at each data point until they are not equal or lists are equal */
    while(F!=NULL && N!=NULL && equal > 0){
        if (F->data != N->data){ equal = 1; } /* if data is equal flag*/
        F = F->next;
        N = N->next;
    }
    return equal;
}

/* Manipulation Functions */
void clear(List L){
    while(length(L) > 0){
        deleteFront(L);
    }
}

void set(List L, int x){
    if(L == NULL){
        printf("List Error: calling set() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling set() with an undefined Cursor\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

void moveFront(List L){
    if (L != NULL){
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L){
    if (L != NULL){
        L->cursor = L->back;
        L->index = length(L) - 1; /* length is always +1 the index*/
    }
}

void movePrev(List L){
    if (L->cursor != NULL){ /* Only do something if cursor != NULL */
        /* if at front already then cursor is set to undefined*/
        if (L->cursor == L->front){
            L->cursor = NULL;
            L->index = -1;
        }
        else{ /* move cursor 1 step to front */
            L->cursor = L->cursor->prev;
            L->index -= 1;
        }
    }
}

void moveNext(List L){
    if (L->cursor == NULL){ return; }
    /* Only do something if cursor != NULL */
    /* if at back already then cursor is set to undefined*/
    if (L->cursor == L->back){
        L->cursor = NULL;
        L->index = -1;
    }
    else{ /* move cursor 1 step to back */
        L->cursor = L->cursor->next;
        L->index++;
        }
}

void prepend(List L, int x){
    if (L == NULL){
        printf("List Error: calling prepend() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if(L->front == NULL && L->back == NULL){ /* if L isEmpty() */
        L->front = L->back = N;
    }else{
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
    }
    L->length++;
    L->index++;
}

void append(List L, int x){
    if (L == NULL){
        printf("List Error: calling append() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->front == NULL && L->back == NULL){ /* if L isEmpty() */
        L->front = L->back = N;
    }else{ /*if L !isEmpty() then set N prev to the back and L->back to N*/
        L->back->next = N; /* current last elements "next" to N */
        N->prev = L->back;
        L->back = N;
    }
    L->length++;
}
void insertBefore(List L, int x){
    if(L == NULL){
        printf("List Error: calling insertBefore() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling insertBefore() with an undefined Cursor\n");
        exit(EXIT_FAILURE);
    }
    /* Check to see if cursor is current at front to make things easier. */
    if (L->cursor == L->front) {prepend(L, x); return;};
    /* Otherwise, Insert before wherever cursor is*/
    Node temp = newNode(x);
    temp->next = L->cursor;
    temp->prev = L->cursor->prev;
    L->cursor->prev = temp;
    temp->prev->next = temp;
    L->index++;
    L->length++;
}

void insertAfter(List L, int x){
    if(L == NULL){
        printf("List Error: calling insertAfter() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling insertAfter() with an undefined Cursor\n");
        exit(EXIT_FAILURE);
    }
    /* Check to see if cursor is current at back to make things easier. */
    if (L->cursor == L->back ) {append(L, x); return;};
    /* Otherwise, Insert before wherever cursor is*/
    Node temp = newNode(x);
    temp->next = L->cursor->next;
    temp->prev = L->cursor;
    L->cursor->next = temp;
    temp->next->prev = temp;
   // L->index++;
    L->length++;
}

void deleteFront(List L){
    if(L == NULL){
        printf("List Error: calling deleteFront() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor = L->front){ /* If cursor points at Front its now undefined*/
        L->cursor = NULL;
        L->index = -1;
    }
    if(length(L) == 1){ /* Special Case for deleteFront on singular List*/
        freeNode(&L->front);
        L->index -= 1;
        L->length -= 1;
        return;
    }
    /* Set newFront Node to 2nd element, free up the current front and set L->front */
    Node newFront = NULL;
    newFront = L->front->next;
    L->front = newFront;
    freeNode(&L->front->prev);
    L->index -= 1;
    L->length -= 1;
}

void deleteBack(List L){
    if(L == NULL){
        printf("List Error: calling deleteBack() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor = L->back){ /* If cursor points at back its now undefined*/
        L->cursor = NULL;
        L->index = -1;
    }
    Node newBack = NULL;
    newBack = L->back->prev;
    L->back = newBack;
    freeNode(&L->back->next);
    L->length -= 1;
}

void delete(List L){
    if(L == NULL){
        printf("List Error: calling delete() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling delete() with an undefined Cursor\n");
        exit(EXIT_FAILURE);
    }
    /* Check to see if cursor is current at front or back to make things easier. */
    if (L->cursor == L->front) {deleteFront(L); return;};
    if (L->cursor == L->back ) {deleteBack(L); return;};
    /* Otherwise */
    /* Cursors Previous Nodes "Next" is Cursors Next Node. "Keep the List intact"*/
    L->cursor->prev->next = L->cursor->next;
    freeNode(&L->cursor); /*freeNode should set cursor = Null and free memory*/
    L->index = -1; /*Undefined Cursor Index set*/
    L->length -= 1;
}

/* Other Functions */
void printList(FILE* out, List L){
    /*Grabbed from Q.c Test it also make work for file*/
    Node temp = NULL;
    if (L == NULL){
        printf("List Error: calling printList() on NULL List Reference.\n");
        exit(EXIT_FAILURE);
    }
    for (temp = L->front; temp != NULL; temp = temp->next){
        printf("Print to file here");
    }
}

List copyList(List L){
    List copy = newList();
    Node temp = L->front;
    while (length(copy) != length(L)){
        append(copy, temp->data);
        temp = temp->next;
    }
    return copy;
}