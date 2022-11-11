#pragma once

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <vector>
#include "bignumber.h"

#include"misc.h"
#include"LinkedList.h"
#include"degeneracy_helper.h"
using namespace std;


void listAllCliquesDegeneracyRecursive_A(vector<BigNumber>& cliqueCounts,
    int* vertexSets, int* vertexLookup,
    int** neighborsInP, int* numNeighbors,
    int beginX, int beginP, int beginR, int max_k, int rsize, int drop);

void listAllCliquesDegeneracy_A(vector<BigNumber>& cliqueCounts, NeighborListArray** orderingArray,
    int size, int max_k);

