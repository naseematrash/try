
#include <stdlib.h>
#include "graph.h"


int addNode (char *ndstr){  
 
  char *str = ndstr;
  int node_num = *str - '0';
  int res = 0;
  str++;
  pnode newNode =  NULL;
  
  
  if(get_node_by_id(node_num) == NULL){
    newNode = malloc(sizeof(struct GRAPH_NODE_));
             
    newNode->edges = NULL;
    newNode->node_weight=10000;
    newNode->color=0;
    newNode->node_num=node_num;
    newNode->next = nodes;
    nodes = newNode;
    }
    else{      
    newNode = get_node_by_id(node_num);
    delEdges(newNode);
    res = 1;
    }
    pedge edgPointer=NULL;
    if(*str != '\0')
      {
       newNode->edges = malloc(sizeof(struct edge_));

        newNode->edges->next = NULL;
        newNode->edges->endpoint = NULL;
        newNode->edges->weight=10000;
      }
    edgPointer = newNode->edges;
    pedge prv = NULL;
    while(*str != '\0' && *str != '\n' && *str != '\r')
    {                            
       edgPointer->endpoint = get_node_by_id((int)(*str -'0'));
       
       str++;     
       edgPointer->weight = (int)(*str - '0');  
       edgPointer->next = malloc(sizeof(struct edge_));

       edgPointer->next->endpoint = NULL;
       edgPointer->next->next = NULL;
       edgPointer->next->weight = 10000;
       prv = edgPointer;
       edgPointer = edgPointer->next;  
       str++;     
    }  
    if(nodes->edges != NULL)
       free(edgPointer);
     prv->next = NULL; 
  return res;
}


void deleteNode(int node_num){

  if(get_node_by_id(node_num) == NULL)
  {
    return ;
  }

  pnode delNode = get_node_by_id(node_num);
  pnode nodes_list = nodes;

  while(nodes_list != NULL){
 
  
    if(nodes_list->node_num == delNode->node_num)
     {       
    
       nodes_list = nodes_list->next;   
       continue;
     }
    
    pedge edg1 = nodes_list->edges; 
    if(edg1 == NULL)
       {

         nodes_list = nodes_list->next;
         continue;
       }
     
    if(edg1->endpoint->node_num == delNode->node_num)
      {
         nodes_list->edges = edg1->next; 
         free(edg1);                     
         nodes_list = nodes_list->next;  
         continue;                       
      }
    pedge head = edg1;
    edg1 = edg1->next;

    while(edg1 != NULL && edg1->endpoint->node_num != delNode->node_num)
    { 
     
       head = edg1;            
       edg1 = edg1->next;           
    }
    if(edg1 != NULL)
    {
   
      head->next = edg1->next;  
      free(edg1);
      
    }

    nodes_list = nodes_list->next;  
    
  }

  delEdges(get_node_by_id(node_num));
  nodes_list = nodes;
  pnode prvNode = nodes;
  if(nodes_list->node_num == node_num) 
     {
     
       nodes = nodes->next;
       free(prvNode);
       return;
     }
  nodes_list=nodes->next;
  prvNode = nodes_list;
  while(nodes_list!=NULL && nodes_list->node_num!=node_num){ 
      {
      
       prvNode = nodes_list; 
       nodes_list=nodes_list->next;   
      }
    if(nodes_list != NULL){
 
      prvNode->next = nodes_list->next;
      free(nodes_list);
      return;
    }
  }
  return;
}

void printNodes(){
pnode it = nodes;
while(it != NULL){
printf("node[%d] ->",it->node_num);
printEdges(it->edges);
it=it->next;
}
free(it);
}



pnode get_node_by_id(int id){
  pnode itr = nodes;
  while(itr!=NULL){
    if(itr->node_num == id)
        return itr;
    itr = itr->next;
  }
  free(itr);
  return NULL;
}
