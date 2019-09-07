#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 105
#define infinite 214748347
#define NIL -1
#define WHITE 2
#define GRAY 1
#define BLACK 0


struct edge
{
    int vertex;
    int weight;
    struct edge *next;

};

typedef struct
{
    struct edge *edges[MAXV + 1];
    int nvertex;
    int nedges;
}graph;

graph G;

void freeMemoryGraph()
{
     int idVertex;
     struct edge *nodeLeft, *nodeRight;
     for(idVertex=1; idVertex<=G.nvertex; idVertex++)
     {
         nodeLeft = G.edges[idVertex];
         while(nodeLeft != NULL)
         {
            nodeRight = nodeLeft ->next;
            free(nodeLeft);
            nodeLeft = nodeRight;
         }
         G.edges[idVertex] = NULL;
     }
}

void BFS(int s,int phi[],int d[]) //Breadth First Search
{
     struct edge *actualNode;
     int idVertex,u , v, color[MAXV];
     int arrayQueue[MAXV], idFrontQueue = 1 , idTailQueue = 1;

     for (idVertex=1; idVertex <= G.nvertex; idVertex++)
     {
         color[idVertex]=WHITE;
         d[idVertex] = infinite;
         phi[idVertex] = NIL;
     }
     color[s] = GRAY;
     d[s]=0;
     phi[s] = NIL;
     arrayQueue[idTailQueue] = s;
     idTailQueue++ ;

     while(idFrontQueue < idTailQueue)
     {
          u=arrayQueue [idFrontQueue];
          idFrontQueue++;
          actualNode = G.edges[u];
          while(actualNode != NULL)
          {
               v = actualNode -> vertex;
               if(color[v] == WHITE)
               {
                   color [v] = GRAY;
                   d[v] = d[u] +1;
                   phi[v] = u;
                   arrayQueue[idTailQueue] = v;
                   idTailQueue++;
               }
               actualNode = actualNode-> next;
           }
           color[u] = BLACK;
     }


}


void printGraph()
{
     int idVertex;
     struct edge *actualNode;
     printf("\nGraph by adjacency lists: \n\n");
     for(idVertex= 1; idVertex <=G.nvertex; idVertex++)
     {
           printf("[Vertex: %d] ",idVertex);
           actualNode =G.edges[idVertex];
           while(actualNode != NULL)
           {
                printf("-> (%d, %d)" ,actualNode->vertex,actualNode->weight);

                actualNode = actualNode->next;
           }
           printf("-> NULL\n");

     }
}

void solver(int s)
{
    int phi[MAXV],d[MAXV],idVertex;
    BFS(s,phi,d);

    printf("Array of Distances:\n");
    for(idVertex = 1;idVertex <= G.nvertex; idVertex++)
        printf("%d ", d[idVertex]);
    printf("\n\n");

    printf("Array of Phi:\n");
    for(idVertex=1;idVertex<= G.nvertex; idVertex++)
        printf("%d ",phi[idVertex]);
    printf("\n");
}




int main()
{
    int idCase, totalCases, n, m , u, v, w = 1;
    int idEdge, idVertex;
    struct edge *newNode, *actualNode;

    scanf("%d", &totalCases);
    for(idCase=1; idCase<= totalCases; idCase++)
    {
          scanf("%d %d", &n, &m);
          G.nvertex = n;
          G.nedges = m;

          for (idVertex=1; idVertex<=n; idVertex++)
          G.edges[idVertex] = NULL;

          for(idEdge=1; idEdge<=m; idEdge++)
          {
              scanf("%d %d", &u, &v);

              newNode =(struct edge *) malloc(sizeof(struct edge));
              newNode->vertex = v;
              newNode->weight = w;
              newNode->next = G.edges[u];
              G.edges[u] = newNode;

              newNode =(struct edge *)malloc(sizeof(struct edge));
              newNode->vertex =u;
              newNode-> weight =w;
              newNode->next = G.edges[v];
              G.edges[v] = newNode;
          }
        printGraph();
        solver(7);
        freeMemoryGraph();
     //   printGraph();

     }


  return 0;
}
