#ifndef GRAPH_C
#define GRAPH_C

#include <stdlib.h>
#include "graph.h"

/////////////////////////////////////////////////////////////////////////////////////////////
/*   This will turn input char array into int array containing info how to build the graph */ 

void interpret(char *data){
 // initial handling.
 //printf("graph string=%s", data);
 int counter = 0;
 numOfNodes = 0 ;
 if(*data == 'A')
 {   
   data+=2;
  // printf("found A. data[2] = %c\n", *(data));
 }
 else return;
 /*     get number of nodes in the graph     */
 ////////////////////////////////////////////
 int x = 1, result=0;
 while(*data!=' '){
   if(x==10){
    result = result*x+ ((int)(*data-'0'));
    }
    else  
    {
      result+=((int)(*data-'0')) *x;      
    }
    x*=10;
    data++;
 }
 numOfNodes = result;
 
 ////////////////////////////////////////////////
/*     get length of char array containing input    */
 data++;
 char* d =data;
 
 //input is space separated.
 while(*d != '\0' && *d != '\r' && *d != '\n' )
 {
   if(*d == ' ')
     counter++;
   d++;
 }
 d = data;
// counter+1 has number of cells in inputArray
 
 inputArray = calloc((counter+1), sizeof(int));
 inputLength = counter;
 int m = 1, i=0;
 while(*d != '\0' && *d != '\r' && *d != '\n')
 { //loop through all data string..
 if(*d == '\0') break;
 if(m == 1)                           //valgrind -s --leak-check=full --error-exitcode=1 ./main < inputs/input1.txt > /dev/null
 inputArray[i] = 0;
 
 if(isdigit(*d)){    
    if(m==10){
    inputArray[i] = inputArray[i] * m + (int)(*d-'0');
   // printf("inputArray[%d]=%d\n",i ,inputArray[i]);
    }
    else
    {        
      inputArray[i]+=(int)(*d-'0')*m; //nonsense we're expecting a two digit number at the most.
     // printf("inputArray$[%d]=%d *d=%c\n",i ,inputArray[i],*d);     
    }
    }
 else{
    if(*d == 'n')
       inputArray[i] = -1;      
    if(*d == ' ')
      {
       i++;
       m=1;
       d++;
       continue; 
      }
     }    
 m*=10;
 d++; 
}
d = data;

}


//////////////////////////////////////////////////////////////////////////////////////////////
void buildGraph(char *data){

  interpret(data);   // now inputArray which is a int array contains graph input.
  data++;
  numOfNodes = *(++data)-'0';
  ////first we will create nodes list. from input, no edges yet.
  int idx=0;
  
  
  nodes = NULL;
  
  for(int i=0; i<numOfNodes;i++){
    pnode newNode = malloc(sizeof(struct GRAPH_NODE_));
    if(newNode == NULL)
      perror("memory erros:\n");
    newNode->edges = NULL;
    newNode->node_num=i;
    newNode->next = nodes;
    nodes = newNode;
  }
 
  ////////////////////////////////////////////////////////////////////////

  //// Now we will add edges to their designated nodes.     A 4 n 0 2 5 3 3  n 2 0 4 1 1  n 1 3 7 0 2
                                                        //     -1 0 2 5 3 3 -1 2 0 4 1 1 -1 1 3 7 0 2   <--inputArray
  idx = 0;
  
    while(idx<inputLength)
    {      
    if(inputArray[idx] == -1){
    idx++;
    
    pnode tempNode = get_node_by_id(inputArray[idx]);  // 0
    while (inputArray[idx] != -1)
    {  ////////////////////////////////////////////////////////////    
      //create new edge
      /////////////////////////////////////////////////////////////
      idx++; //2
      
      if(inputArray[idx] == -1 || idx>=inputLength) break;
  
      pedge newEdge = malloc(sizeof(struct edge_));
      newEdge->endpoint = get_node_by_id(inputArray[idx]); //2       
      newEdge->weight = inputArray[++idx];  //5
      //////////////////////////////////////////////////////////
      //attach new edge to head of edges list of designated node.
      //////////////////////////////////////////////////////////
      pedge tempEdge = tempNode->edges;      
      tempNode->edges = newEdge;      
      tempNode->edges->next = tempEdge;       
      //////////////////////////////////////////////////////////////       
    }
    continue;   // so inputArray[idx] would be -1 for next iteration.    
    }
    idx++;
  }
}

void freeNodes(){
  pnode hd = nodes;
  nodes = nodes->next;
  while(nodes != NULL)
  {
    free(hd);
    hd = nodes;
    nodes = nodes->next;
  }
  free(hd);
}

void freeEdges(){
   pnode cnodes = nodes;
   pedge temp;
   while (cnodes!=NULL)
   {  
   while(cnodes->edges!=NULL)
   {
      temp = cnodes->edges;
      if(cnodes->edges!=NULL){         
         cnodes->edges = cnodes->edges->next;
         free(temp);         
      }
   }
   cnodes=cnodes->next;
   }
}

#endif





/*  
// old version of buildGraph function

void buildGraph(char *data){

  interpret(data);   // now inputArray which is a int array contains graph input.
   char* p = data;
   int num_nodes = *data-'0';  //covert a char (digit) to int.
   int node_index, edge_dest, edge_weight;
   pedge pe = malloc(sizeof(struct edge_));
   if(pe == NULL)
       perror("Memory fault: ");
   
   pnode iterator = nodes;
   
   for(int i=0; i<num_nodes; i++){ // add (num_nodes) nodes to the graph, which is basically a list of nodes.
    iterator->node_num = i;
    //iterator->edge_count = 0;
    iterator->edges = malloc(sizeof(struct edge_));
    if(iterator->edges == NULL)
       perror("Memory fault: ");
    if(i==num_nodes-1)
       iterator->next = NULL; //last node.
    else
      {
         iterator->next = malloc(sizeof(struct GRAPH_NODE_));
         if(iterator->next == NULL)
       perror("Memory fault: ");
      }
    
    iterator =  iterator->next;
   }
   p++;
   
   while(*p != '\0' && *p != '\r' && *p != '\n'){ //loop through all data string..
        if(*p == ' ') continue;
        if(*p == 'n')
        {
          p++;
          node_index = *p - '0';  //take first number after n and goto next char.          
          p++;
        }
        
        iterator = nodes;// reset iterator
        int i;
        for(i=0;i<node_index;i++){//goto node from input.         
          iterator = iterator->next;
        }
        
        edge_dest = *p - '0';        
        p++;
        edge_weight = *p -'0';
        p++;
        pe->weight = edge_weight;        
        pe->endpoint = get_node_by_id(edge_dest);        
        add_edge(pe, iterator);            
        pe = malloc(sizeof(struct edge_));
        if(pe == NULL)
       perror("Memory fault: ");
   }
   free(pe);   
}






 */