#pragma once
using namespace std;


#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

#include"misc.h"
#include"LinkedList.h"


struct NeighborList
{
    int vertex; //!< the vertex that owns this neighbor list
    LinkedList* earlier; //!< a linked list of neighbors that come before this vertex in the ordering
    LinkedList* later; //!< a linked list of neighbors that come after this vertex in the ordering
    int orderNumber; //!< the position of this verex in the ordering
};

typedef struct NeighborList NeighborList;


struct NeighborListArray
{
    int vertex; //!< the vertex that owns this neighbor list
    int* earlier; //!< an array of neighbors that come before this vertex in an ordering
    int earlierDegree; //!< the number of neighbors in earlier
    int* later; //!< an array of neighbors that come after this vertex in an ordering
    int laterDegree; //!< an array of neighbors that come after this vertex in an ordering
    int orderNumber; //!< the position of this verex in the ordering
};

typedef struct NeighborListArray NeighborListArray;

NeighborListArray** computeDegeneracyOrderArray(LinkedList** list, int size);
