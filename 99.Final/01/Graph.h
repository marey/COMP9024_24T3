#ifndef GRAPH_H
#define GRAPH_H

typedef long AdjMatrixElementTy;

// Max length of an identifier (e.g., a graph node's name) 
#define MAX_ID_LEN 127


// Storing information of a graph node
struct GraphNode {
    char name[MAX_ID_LEN + 1];
    int onstack;
};

struct Graph{
    /*
       Memory Layout:
                          -----------------------------------------------------------
        pAdjMatrix ---->  Element(0, 0),   Element(0, 1),    ...,       Element(0, n-1),     // each row has n elements
                          Element(1, 0),   Element(1, 1),    ...,       Element(1, n-1),
      
                          .....                            Element(u, v)     ...             // (n * u + v) elements away from Element(0, 0)
      
                          Element(n-1, 0), Element(n-1, 1),  ...,       Element(n-1, n-1)
                          ----------------------------------------------------------- 
                                      Adjacency Matrix on Heap

     */
    AdjMatrixElementTy *pAdjMatrix;
    /*
       Memory Layout
                        ---------------------------
                        pNodes[n-1]
       
       
                        pNodes[1]
       pNodes ----->    pNodes[0]
                       ----------------------------
                        struct GraphNode[n] on Heap
     */
    struct GraphNode *pNodes;
    // number of nodes
    long n;
    // whether it is a directed graph
    int isDirected;
};

// 0 <= u < n,  0 <= v < n
// ELement(u, v) is (n * u + v) elements away from Element(0, 0)
#define  MatrixElement(pGraph, u, v)  (pGraph)->pAdjMatrix[(pGraph)->n * (u) + (v)]

#define CONNECTED   1

struct Graph;
struct Graph *CreateGraph(long n, int isDirected);

void ReleaseGraph(struct Graph *pGraph);

void GraphAddUndirectedEdge(struct Graph *pGraph, long u, long v, AdjMatrixElementTy val);

void GraphAddDirectedEdge(struct Graph *pGraph, long u, long v, AdjMatrixElementTy val);

void GraphAddEdge(struct Graph *pGraph, long u, long v, AdjMatrixElementTy val);

void GraphAddNode(struct Graph *pGraph, long u, char *name);

void PrintGraph(struct Graph *pGraph);


void RecursiveDFS(struct Graph *pGraph);


void Graph2Dot(struct Graph *pGraph, 
               char *filePath,
               char *graphName,
               int isDirectedGraph,
               int displayLabel,
               int *visited,
               int displayVisited);

// Based on Graph2Dot()
void GenOneImage(struct Graph *pGraph, char *graphName, char *fileName, long seqNo, int *visited);

int HasCycle(struct Graph *pGraph);
#endif


