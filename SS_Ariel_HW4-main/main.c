#include <stdlib.h>
#include "graph.h"
#include "brute.c"
#include "edges.c"
#include "graph.c"
#include "nodes.c"
#define MAX_SIZE 300

int main (){
char mat[MAX_SIZE];

for(int i=0;i<MAX_SIZE;i++)
  mat[i] = '\0';


fgets(mat, MAX_SIZE, stdin);
                                  
int graphInfoSize = MAX_SIZE;
char dt[graphInfoSize];
int k;
char tmp[6];
for(int p = 0; p<6 ; p++)
   tmp[p] = '\0';
first:
graphInfoSize = 0;
for(int i=0;i<MAX_SIZE;i++)
   {       
       if(mat[i] == '\0' || mat[i] == 'B' || mat[i] == 'D' || mat[i] == 'S' || mat[i] == 'T') break;
       graphInfoSize++;
   }
if(graphInfoSize > 0) graphInfoSize+=1;   


for(int i=0;i<graphInfoSize;i++)
   dt[i] = mat[i];
dt[graphInfoSize-1] = '\0'; 

buildGraph(dt);

k = graphInfoSize-1;

 
while(mat[k]!='\0'){

int kx=0;

if(mat[k] == 'B'){   
k++;
for(int j=0;j<10;j++)
{
if(mat[k+j] == ' ') {continue;}
tmp[kx] = mat[k+j];
kx++;
}
addNode(tmp);  
k+=10;
}

if(mat[k] == 'D') 
  {

    deleteNode(mat[k+2]-'0');k++;

    }

if(mat[k] == 'S') 
{   
    s(mat[k+2]-'0', mat[k+4]-'0', 0);
    k+=2;
}

if(mat[k] == 'T')
{
   
    int n = mat[k+2]-'0';
    k+=2;
    char tt[n];
    k+=2;
    
    for(int y=0;y<n;y++)
    {
      tt[y] = mat[k];
      k+=2;      
    } 
    tt[n] = '\0'  ;
 
    tsp(tt, n);
    k--;
}

   if(mat[k] == 'A')
   {
     char matt[MAX_SIZE] ;
     for(int p=0; p<MAX_SIZE; p++)
       matt[p] ='\0';
     int j=0;
     while(mat[k] != '\0'){
       matt[j] = mat[k];
       j++;
       k++;
     }
     matt[j] ='\0';

     freeEdges();
     freeNodes();
     free(inputArray);
     strcpy(mat, matt);
     goto first;
   }
k++;
}


freeEdges();
freeNodes();
free(inputArray);
return 0;
}
