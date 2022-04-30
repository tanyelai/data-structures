#include <stdio.h>
#include <stdlib.h>

#define N 6  // Define the maximum number of vertices in the graph

// Data structure to store adjacency list nodes of the graph
struct n{
    int dest;
    struct n* next;
};
typedef struct n NODE;

struct g{
    struct n* head[N]; // An array of pointers to Node to represent an adjacency list
};
typedef struct g GRAPH;

struct e{
    int src, dest;
};
typedef struct e EDGE;

GRAPH * createGraph(EDGE *, int);
void printGraph(GRAPH *);

int main(){
    // input array containing edges of the graph (as per the above diagram)
    // (x, y) pair in the array represents an edge from x to y
    EDGE edges[] =
    {
        {0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}
    };
 
    // calculate the total number of edges
    int t = sizeof(edges)/sizeof(edges[0]);
 
    // construct a graph from the given edges
    GRAPH *graph = createGraph(edges, t);
 
    // Function to print adjacency list representation of a graph
    printGraph(graph);

    return 0;
}

GRAPH * createGraph(EDGE edges[], int t){

    GRAPH * graph = (GRAPH*)malloc(sizeof(GRAPH));
    int i;

    // initialize head pointer for all vertices
    for(i=0; i<N; i++)
        graph->head[i] = NULL;
    
    // add edges to the directed graph one by one
    for(i=0; i<t; i++){
        int src = edges[i].src;
        int dest = edges[i].dest;

        NODE * node = (NODE*)malloc(sizeof(NODE));
        node->dest = dest;
        node->next = graph->head[src];  // point node to the current head
        graph->head[src] = node;   // point head pointer to the node
    }
    return graph;
}

void printGraph(GRAPH * graph){
    int i;
    for(i=0; i<N; i++){
        // print current vertex and all its neighbors
        NODE * iter = graph->head[i];
        while (iter != NULL){
            printf("(%d —> %d)\t", i, iter->dest);
            iter = iter->next;
        }
        printf("\n");
    }
}