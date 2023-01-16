#ifndef GRAPH_
#define GRAPH_
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct GRAPH_NODE_ *pnode, node;
typedef struct edge_ *pedge, edge;
pnode nodes;//nodes list of our graph
int addNode (char *ndstr);
int *inputArray, numOfNodes, inputLength, minTSP, tmpWeight;
pnode get_node_by_id(int id);
void deleteNode(int node_num);
void add_edge(pedge edge, pnode node);
void printNodes();
void printEdges(pedge ed);
void freeEdges();
void delEdges(pnode n);
void freeNodes();
void buildGraph(char *data);
int shortest_path(int src, int dst);
int s(int a, int b,int silent);
int brute(pnode src, pnode dst);
void interpret(char *data);
void shuffle(int *array, size_t n);
void tsp(char*, size_t n);

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    short color, node_weight;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;


#endif
