#include<assert.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#include <vector>
#include "bignumber.h"

#include"misc.h"
#include"LinkedList.h"
#include"degeneracy_helper.h"

vector<vector<BigNumber>> nCr;

void populate_nCr()
{
    const int maxrow = 1500;
    const int maxcol = 800;
    nCr.resize(maxrow + 1);
    for (int row = 0; row < maxrow + 1; ++row)
    {
        nCr[row].resize(maxcol + 1);
        for (int col = 0; col < maxcol + 1; ++col)
        {
            if (row == 0 || col == 0 || row == col) nCr[row][col] = 1;
            else nCr[row][col] = nCr[row - 1][col] + nCr[row - 1][col - 1];
        }
    }
}


void destroyCliqueResults(LinkedList* cliques)
{
    Link* curr = cliques->head->next;
    while (!isTail(curr))
    {
        free(&(curr->data));
        curr = curr->next;
    }
    destroyLinkedList(cliques);
}

void runAndPrintStatsCliques(LinkedList** adjListLinked, int n)
{
    populate_nCr();
    fflush(stderr);
    int max_k = 0;
    int deg = 0, m = 0;
    FILE* fp;
#ifdef _MSC_VER
    fopen_s(&fp, "authorclique.txt", "w");
#else
    fp = fopen("authorclique.txt", "w");
#endif
    fflush(stdout);
    NeighborListArray** orderingArray = computeDegeneracyOrderArray(adjListLinked, n);
    fflush(stdout);
    for (int i = 0; i < n; i++)
    {
        if (deg < orderingArray[i]->laterDegree) deg = orderingArray[i]->laterDegree;
        m += orderingArray[i]->laterDegree;
    }

    max_k = deg + 1;
    vector<BigNumber> cliqueCounts(max_k + 1);
    listAllCliquesDegeneracy_A(cliqueCounts, orderingArray, n, max_k);
    while (cliqueCounts[max_k] == 0) max_k--;
    fprintf(fp, "%d\n", max_k);
    BigNumber totalCliques = 0;
    for (int i = 1; i <= max_k; i++)
    {
        fprintf(fp, "%d %s\n", i, cliqueCounts[i].getString().c_str());
        totalCliques += cliqueCounts[i];
    }

    fprintf(fp, "%s\n", totalCliques.getString().c_str());
    fclose(fp);
    free(orderingArray);
    nCr.clear();
}



int findBestPivotNonNeighborsDegeneracyCliques(int** pivotNonNeighbors, int* numNonNeighbors,
    int* vertexSets, int* vertexLookup,
    int** neighborsInP, int* numNeighbors,
    int, int beginP, int beginR)
{
    int pivot = -1;
    int maxIntersectionSize = -1;

    // iterate over each vertex in P union X 
    // to find the vertex with the most neighbors in P.
    int j = beginP;
    while (j < beginR)
    {
        int vertex = vertexSets[j];
        int numPotentialNeighbors = std::min(beginR - beginP, numNeighbors[vertex]); //bug resolved by Shweta

        int numNeighborsInP = 0;

        int k = 0;
        while (k < numPotentialNeighbors)
        {
            int neighbor = neighborsInP[vertex][k];
            int neighborLocation = vertexLookup[neighbor];

            if (neighborLocation >= beginP && neighborLocation < beginR)
            {
                numNeighborsInP++;
            }
            else
            {
                break;
            }

            k++;
        }

        if (numNeighborsInP > maxIntersectionSize)
        {
            pivot = vertex;
            maxIntersectionSize = numNeighborsInP;
        }

        j++;
    }

    // compute non neighbors of pivot by marking its neighbors
    // and moving non-marked vertices into pivotNonNeighbors.
    // we must do this because this is an efficient way
    // to compute non-neighbors of a vertex in 
    // an adjacency list.

    // we initialize enough space for all of P; this is
    // slightly space inefficient, but it results in faster
    // computation of non-neighbors.
    * pivotNonNeighbors = (int*)calloc(beginR - beginP, sizeof(int));
    memcpy(*pivotNonNeighbors, &vertexSets[beginP], (beginR - beginP) * sizeof(int));

    // we will decrement numNonNeighbors as we find neighbors
    *numNonNeighbors = beginR - beginP;

    int numPivotNeighbors = std::min(beginR - beginP, numNeighbors[pivot]); //bug resolved by Shweta

    // mark the neighbors of pivot that are in P.
    j = 0;
    while (j < numPivotNeighbors)
    {
        int neighbor = neighborsInP[pivot][j];
        int neighborLocation = vertexLookup[neighbor];

        if (neighborLocation >= beginP && neighborLocation < beginR)
        {
            (*pivotNonNeighbors)[neighborLocation - beginP] = -1;
        }
        else
        {
            break;
        }

        j++;
    }

    // move non-neighbors of pivot in P to the beginning of
    // pivotNonNeighbors and set numNonNeighbors appriopriately.

    // if a vertex is marked as a neighbor, the we move it
    // to the end of pivotNonNeighbors and decrement numNonNeighbors.
    j = 0;
    while (j < *numNonNeighbors)
    {
        int vertex = (*pivotNonNeighbors)[j];

        if (vertex == -1)
        {
            (*numNonNeighbors)--;
            (*pivotNonNeighbors)[j] = (*pivotNonNeighbors)[*numNonNeighbors];
            continue;
        }

        j++;
    }

    return pivot;
}


void fillInPandXForRecursiveCallDegeneracyCliques(int vertex, int orderNumber,
    int* vertexSets, int* vertexLookup,
    NeighborListArray** orderingArray,
    int** neighborsInP, int* numNeighbors,
    int*, int*, int* pBeginR,
    int* pNewBeginX, int* pNewBeginP, int* pNewBeginR)
{
    int vertexLocation = vertexLookup[vertex];

    (*pBeginR)--;
    vertexSets[vertexLocation] = vertexSets[*pBeginR];
    vertexLookup[vertexSets[*pBeginR]] = vertexLocation;
    vertexSets[*pBeginR] = vertex;
    vertexLookup[vertex] = *pBeginR;

    *pNewBeginR = *pBeginR;
    *pNewBeginP = *pBeginR;

    //printf("Before 1st while\n");
    // swap later neighbors of vertex into P section of vertexSets
    int j = 0;
    while (j < orderingArray[orderNumber]->laterDegree)
    {
        int neighbor = orderingArray[orderNumber]->later[j];
        int neighborLocation = vertexLookup[neighbor];

        (*pNewBeginP)--;

        vertexSets[neighborLocation] = vertexSets[*pNewBeginP];
        vertexLookup[vertexSets[*pNewBeginP]] = neighborLocation;
        vertexSets[*pNewBeginP] = neighbor;
        vertexLookup[neighbor] = *pNewBeginP;

        j++;
    }

    *pNewBeginX = *pNewBeginP;

    // reset numNeighbors and neighborsInP for this vertex
    j = *pNewBeginP;
    //printf("Before 2nd while\n");
    while (j < *pNewBeginR)
    {
        int vertexInP = vertexSets[j];
        numNeighbors[vertexInP] = 0;
        free(neighborsInP[vertexInP]);
        neighborsInP[vertexInP] = (int*)calloc(std::min(*pNewBeginR - *pNewBeginP,
            orderingArray[vertexInP]->laterDegree
            + orderingArray[vertexInP]->earlierDegree), sizeof(int));

        j++;
    }

    // count neighbors in P, and fill in array of neighbors
    // in P
    j = *pNewBeginP;
    while (j < *pNewBeginR)
    {
        int vertexInP = vertexSets[j];

        int k = 0;
        while (k < orderingArray[vertexInP]->laterDegree)
        {
            int laterNeighbor = orderingArray[vertexInP]->later[k];
            int laterNeighborLocation = vertexLookup[laterNeighbor];

            if (laterNeighborLocation >= *pNewBeginP && laterNeighborLocation < *pNewBeginR)
            {
                neighborsInP[vertexInP][numNeighbors[vertexInP]] = laterNeighbor;
                numNeighbors[vertexInP]++;
                neighborsInP[laterNeighbor][numNeighbors[laterNeighbor]] = vertexInP;
                numNeighbors[laterNeighbor]++;
            }

            k++;
        }

        j++;
    }
}



void moveToRDegeneracyCliques(int vertex,
    int* vertexSets, int* vertexLookup,
    int** neighborsInP, int* numNeighbors,
    int*, int* pBeginP, int* pBeginR,
    int* pNewBeginX, int* pNewBeginP, int* pNewBeginR)
{

    int vertexLocation = vertexLookup[vertex];

    (*pBeginR)--;
    vertexSets[vertexLocation] = vertexSets[*pBeginR];
    vertexLookup[vertexSets[*pBeginR]] = vertexLocation;
    vertexSets[*pBeginR] = vertex;
    vertexLookup[vertex] = *pBeginR;

    // this is not a typo, initially newX is empty
    *pNewBeginX = *pBeginP;
    *pNewBeginP = *pBeginP;
    *pNewBeginR = *pBeginP;

    int sizeOfP = *pBeginR - *pBeginP;

    int j = (*pBeginP);
    while (j < (*pBeginR))
    {
        int neighbor = vertexSets[j];
        int neighborLocation = j;

        int numPotentialNeighbors = std::min(sizeOfP, numNeighbors[neighbor]);
        int k = 0;
        while (k < numPotentialNeighbors)
        {
            if (neighborsInP[neighbor][k] == vertex)
            {
                vertexSets[neighborLocation] = vertexSets[(*pNewBeginR)];
                vertexLookup[vertexSets[(*pNewBeginR)]] = neighborLocation;
                vertexSets[(*pNewBeginR)] = neighbor;
                vertexLookup[neighbor] = (*pNewBeginR);
                (*pNewBeginR)++;
            }

            k++;
        }

        j++;
    }

    j = (*pNewBeginP);

    while (j < *pNewBeginR)
    {
        int thisVertex = vertexSets[j];

        int numPotentialNeighbors = std::min(sizeOfP, numNeighbors[thisVertex]);

        int numNeighborsInP = 0;

        int k = 0;
        while (k < numPotentialNeighbors)
        {
            int neighbor = neighborsInP[thisVertex][k];
            int neighborLocation = vertexLookup[neighbor];
            if (neighborLocation >= *pNewBeginP && neighborLocation < *pNewBeginR)
            {
                neighborsInP[thisVertex][k] = neighborsInP[thisVertex][numNeighborsInP];
                neighborsInP[thisVertex][numNeighborsInP] = neighbor;
                numNeighborsInP++;
            }
            k++;
        }

        j++;
    }
}


void moveFromRToXDegeneracyCliques(int vertex,
    int* vertexSets, int* vertexLookup,
    int*, int* pBeginP, int* pBeginR)
{
    int vertexLocation = vertexLookup[vertex];

    //swap vertex into X and increment beginP and beginR
    vertexSets[vertexLocation] = vertexSets[*pBeginP];
    vertexLookup[vertexSets[*pBeginP]] = vertexLocation;
    vertexSets[*pBeginP] = vertex;
    vertexLookup[vertex] = *pBeginP;

    *pBeginP = *pBeginP + 1;
    *pBeginR = *pBeginR + 1;
}
LinkedList** readInGraphAdjListToDoubleEdges(int* n, int* m, char* fpath)
{
    int u, v; // endvertices, to read edges.

    FILE* fp;
    fopen_s(&fp,fpath, "r");
    if (!fp)
    {
        cout << fpath << endl;
        fprintf(stderr, "Could not open input file.\n");
        exit(1);
    }

    if (fscanf_s(fp, "%d %d", n, m) != 2)
    {
        fprintf(stderr, "Number of vertices: %d\n", *n);
        fprintf(stderr, "Number of edges: %d\n", *m);
        fprintf(stderr, "problem with line 1 in input file\n");
        exit(1);
    }

    LinkedList** adjList = (LinkedList**)calloc(max(*n,1), max(int(sizeof(LinkedList*)),1));
    /*calloc(max(x, 1), max(y, 1))*/

    int i = 0;
    while (i < *n)
    {
        adjList[i] = createLinkedList();
        i++;
    }

    i = 0;
    // double maxv = 0;
    while (i < *m)
    {
        if (fscanf_s(fp, "%d %d\n", &u, &v) != 2)
        {
            printf("problem with line %d in input file, u=%d, v=%d\n", i + 2, u, v);
            //exit(1);
        }
        assert(u < *n&& u > -1);
        assert(v < *n&& v > -1);
        assert(u != v);

        addLast(adjList[u], (int)v);
        addLast(adjList[v], (int)u);

        i++;
    }
    // printf("maxv = %lf \n", maxv);
    *m = (*m) * 2;

    fclose(fp);
    return adjList;
}