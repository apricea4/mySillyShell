//
//
//
#include "requiredIncludes.h"
#include "linkedList.h"

LinkedList * linkedList()
{
    LinkedList * myList = (LinkedList *)calloc(1, sizeof(LinkedList));

    myList -> head = (Node *)calloc(1, sizeof(Node));
    return myList;


}




void addLast(LinkedList * theList, Node * nn)
{
    if( theList == NULL || nn == NULL)
    {
        exit(-99);

    }

    Node *cur = theList->head->next;

    while(cur -> next != NULL )
    {
        cur = cur->next;

    }

    cur -> next = nn;
    nn -> prev = cur;
    nn -> next = NULL;
    theList -> size++;



}


void addFirst(LinkedList * theList, Node * nn)
{

    if( theList == NULL || nn == NULL)
    {
        exit(-99);

    }

    if(theList->size == 0)
    {
        theList->head->next = nn;
        nn->prev = theList->head;
        theList->size++;

    }
    else
    {

        Node * front = theList -> head -> next;
        theList -> head -> next = nn;
        nn -> prev = theList -> head;
        nn -> next = front;
        front -> prev = nn;
        theList -> size++;

    }




}

void removeFirst(LinkedList * theList, void (*removeData)(void *))
{
    if(theList == NULL || theList -> size == 0)
    {
        exit(-99);
    }


    Node *n = theList -> head -> next;
    theList->head->next = n->next;
    n->next->prev = theList->head;

    removeData(n -> data);
    theList -> size--;
    n->next = NULL;
    n->prev = NULL;
    free(n);
    n = NULL;


}



void removeLast(LinkedList * theList, void (*removeData)(void *))
{

    if(theList == NULL || theList -> size == 0)
    {
        exit(-99);
    }

    Node *last = theList -> head -> next;
    while(last->next != NULL)
    {
        last = last->next;
    }
    theList -> size--;
    removeData(last -> data);
    last->next = NULL;
    last->prev->next = NULL;
    last->prev = NULL;
    free(last);

    last = NULL;

}

void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *))
{

    if(theList == NULL || theList -> size == 0 || nn == NULL || nn -> data == NULL)
    {
        exit(-99);
    }
    Node *cur = theList->head->next;
    while(cur !=NULL)
    {
        if(compare(nn->data,cur->data) == 0)
        {
            if(cur->next == NULL)
            {
                cur->prev->next = NULL;
                cur->prev = NULL;
                removeData(nn->data);
            }

            else
            {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                removeData(nn->data);
            }

            theList -> size--;
            free(cur);
            cur=NULL;

        }
        else
        {
            cur = cur ->next;
        }


    }
    free(nn);
    nn = NULL;


}

void clearList(LinkedList * theList, void (*removeData)(void *))
{
    if(theList -> size == 0)
    {
        return;
    }
    Node *cur = theList->head->next;
    Node *trace = theList->head->next;

    while(cur != NULL)
    {

        removeData(cur->data);
        free(cur);
        cur = NULL;
        trace = trace->next;
        cur = trace;

    }
    free(trace);
    trace = NULL;
    free(theList->head);
    theList->size = 0;



}



void printList(const LinkedList * theList, void (*convertData)(void *))
{
    if(theList -> size == 0 || theList == NULL)
    {
        printf("Empty List");
        return;
    }
    Node *cur = theList -> head -> next;
    while(cur != NULL)
    {
        convertData(cur->data);
        cur = cur->next;
    }

}


