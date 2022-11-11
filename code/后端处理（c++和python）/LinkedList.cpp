#include"LinkedList.h"
#include"misc.h"
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>


int isHead(Link* list)
{
    assert(list != NULL);

    return (list->prev == NULL);
}


int isTail(Link* list)
{
    assert(list != NULL);

    return (list->next == NULL);
}


Link* addAfter(Link* list, int data)
{
    assert(list != NULL);
    assert(list->next != NULL);

    Link* newLink = (Link*)malloc(sizeof(Link));

    newLink->data = data;

    newLink->next = list->next;
    newLink->prev = list;

    list->next->prev = newLink;
    list->next = newLink;

    return newLink;
}


Link* addBefore(Link* list, int data)
{
    assert(list != NULL);
    assert(list->prev != NULL);

    Link* newLink = (Link*)malloc(sizeof(Link));

    newLink->data = data;

    newLink->next = list;
    newLink->prev = list->prev;

    list->prev->next = newLink;
    list->prev = newLink;

    return newLink;
}


int deleteLink(Link* list)
{
    assert(list != NULL);
    assert(list->next != NULL);
    assert(list->prev != NULL);

    int data = list->data;

    Link* linkToFree = removeLink(list);

    free(linkToFree);

    return data;
}


void addLinkBefore(Link* list, Link* newLink)
{
    assert(list != NULL);
    assert(list->prev != NULL);
    assert(newLink != NULL);

    newLink->next = list;
    newLink->prev = list->prev;

    newLink->next->prev = newLink;
    newLink->prev->next = list->prev;
}


Link* removeLink(Link* list)
{
    assert(list != NULL);
    assert(list->next != NULL);
    assert(list->prev != NULL);

    list->next->prev = list->prev;
    list->prev->next = list->next;

    list->next = NULL;
    list->prev = NULL;

    return list;
}


LinkedList* createLinkedList(void)
{
    LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));

    linkedList->head = (Link*)malloc(sizeof(Link));
    linkedList->tail = (Link*)malloc(sizeof(Link));

    linkedList->head->prev = NULL;
    linkedList->head->next = linkedList->tail;
    linkedList->head->data = (int)0xDEAD0000;

    linkedList->tail->prev = linkedList->head;
    linkedList->tail->next = NULL;
    linkedList->tail->data = (int)0xDEADFFFF;

    return linkedList;
}


void destroyLinkedList(LinkedList* linkedList)
{
    Link* curr = linkedList->head;
    while (curr != NULL)
    {
        Link* currNext = curr->next;
        free(curr);
        curr = currNext;
    }
    free(linkedList);
}


Link* addFirst(LinkedList* linkedList, int data)
{
    assert(linkedList != NULL);

    return addAfter(linkedList->head, data);
}


Link* addLast(LinkedList* linkedList, int data)
{
    assert(linkedList != NULL);

    return addBefore(linkedList->tail, data);
}


int getFirst(LinkedList* linkedList)
{
    assert(linkedList != NULL);
    assert(!isEmpty(linkedList));

    return linkedList->head->next->data;
}


int length(LinkedList* linkedList)
{
    int length = 0;
    Link* curr = linkedList->head->next;

    while (!isTail(curr))
    {
        length++;
        curr = curr->next;
    }

    return length;
}


int isEmpty(LinkedList* linkedList)
{
    assert(linkedList != NULL);

    return isTail(linkedList->head->next);
}

