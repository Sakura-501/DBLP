#pragma once
using namespace std;
struct Link;

struct LinkedList
{
    struct Link* head; //!< head of the linked list, a dummy sentinel
    struct Link* tail; //!< tail of the linked list, a dummy sentinel
};

/*! \struct Link

    \brief Stores data and pointers to next and previous links.

*/

struct Link
{
    int data; //!< arbitrary data stored in the link
    struct Link* next; //!< the previous link in the chain
    struct Link* prev; //!< the next link in the chain
};

int isHead(Link* list);

int isTail(Link* list);

int deleteLink(Link* list);

Link* addAfter(Link* list, int data);

Link* addBefore(Link* list, int data);

void addLinkBefore(Link* list, Link* newLink);

Link* removeLink(Link* list);

LinkedList* createLinkedList(void);

void destroyLinkedList(LinkedList* linkedList);

Link* addFirst(LinkedList* linkedList, int data);

Link* addLast(LinkedList* linkedList, int data);

int getFirst(LinkedList* linkedList);

int length(LinkedList* linkedList);

int isEmpty(LinkedList* linkedList);

