#include <stdlib.h>
#include "graph.h"


void red () {
  printf("\033[1;31m");
}

void black () {
  printf("\033[0;30m");
}

void reset () {
  printf("\033[0m");
}



void add_edge(pedge edg, pnode node){
   pedge edge_itr = node->edges;

   if(edge_itr == NULL)
   {
     node->edges = (pedge)malloc(sizeof(struct edge_));
     node->edges->endpoint = edg->endpoint;
     node->edges->weight = edg->weight;
     node->edges->next= NULL;
     return;
   }
   
   while(edge_itr->next!=NULL)
     edge_itr = edge_itr->next;   

   edge_itr->next = (pedge)malloc(sizeof(struct edge_));
   edge_itr->next->endpoint = edg->endpoint;
   edge_itr->next->weight = edg->weight;
   edge_itr->next->next = NULL;

}

void printEdges(pedge ed){
  pedge edg = ed;
  while(edg != NULL){
      if(edg->endpoint != NULL)
      printf("edge{#%d, W%d}-> ", edg->endpoint->node_num, edg->weight);            
      edg = edg -> next;
  }
  printf("| \n");
  free(edg);  
}

void printEdgesColor(pedge ed, pedge ec){
  pedge edg = ed;
  while(edg != NULL){
      if(edg->endpoint != NULL)
      {
      if(edg == ec)
       red();
      printf("edge{#%d, W%d}-> ", edg->endpoint->node_num, edg->weight);
      reset();            
            
      }
      edg = edg -> next;
  }
  printf("| \n");
  free(edg);  
}

void delEdges(pnode n){
  pedge it = n->edges;
  while (it != NULL)
  {
    pedge temp = it;
    it=it->next;
    free(temp);
  }
  n->edges = NULL;
}