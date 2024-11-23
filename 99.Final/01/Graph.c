#include <stdio.h>    // printf(), scanf()
#include <stdlib.h>   // malloc()
#include <string.h>   // memset()
#include <assert.h>   // assert()
#include "Stack.h"
#include "Graph.h"

/*
    Create a graph which can contain n nodes
 */
struct Graph *CreateGraph(long n, int isDirected) {
    assert(n > 0);
    struct Graph *pGraph = (struct Graph *) malloc(sizeof(struct Graph));
    assert(pGraph);
    pGraph->pAdjMatrix = (AdjMatrixElementTy *) malloc(sizeof(AdjMatrixElementTy) * n * n);
    pGraph->pNodes = (struct GraphNode *) malloc(sizeof(struct GraphNode) * n);
    assert(pGraph->pAdjMatrix && pGraph->pNodes);
    memset(pGraph->pAdjMatrix, 0, sizeof(AdjMatrixElementTy) * n * n);
    memset(pGraph->pNodes, 0, sizeof(struct GraphNode) * n);
    pGraph->n = n;
    pGraph->isDirected = isDirected;
    
    return pGraph;
}

void ReleaseGraph(struct Graph *pGraph) {
    assert(pGraph);
    free(pGraph->pNodes);
    free(pGraph->pAdjMatrix);
    free(pGraph);
}

static int IsLegalNodeNum(struct Graph *pGraph, long u) {
    return (u >= 0) && (u < pGraph->n); 
}

/*
    Add an undirected edge between u and v
 */

void GraphAddUndirectedEdge(struct Graph *pGraph, long u, long v, AdjMatrixElementTy val) {
    if (IsLegalNodeNum(pGraph, u) && IsLegalNodeNum(pGraph, v)) {
        MatrixElement(pGraph, u, v) = val;
        MatrixElement(pGraph, v, u) = val;
    }
}

/*
    Add a directed edge from u to v
 */
void GraphAddDirectedEdge(struct Graph *pGraph, long u, long v, AdjMatrixElementTy val) {
    if (IsLegalNodeNum(pGraph, u) && IsLegalNodeNum(pGraph, v)) {
        MatrixElement(pGraph, u, v) = val;
    }
}

/*
    Add a directed edge from u to v, or an undirected edge between u and v
 */
void GraphAddEdge(struct Graph *pGraph, long u, long v, AdjMatrixElementTy val) {
    if (pGraph->isDirected) {
        GraphAddDirectedEdge(pGraph, u, v, val);
    } else {
        GraphAddUndirectedEdge(pGraph, u, v, val);
    }

}

void GraphAddNode(struct Graph *pGraph, long u, char *name) {
    if (IsLegalNodeNum(pGraph, u)) {        
        snprintf(pGraph->pNodes[u].name, MAX_ID_LEN, "%s", name);
    }
}

// for debugging
void PrintGraph(struct Graph *pGraph) {
    printf("**********  The Adjacency Matrix ************* \n");
    for (long u = 0; u < pGraph->n; u++) {
        for (long v = 0; v < pGraph->n; v++) {
            printf("%ld ", (long) (MatrixElement(pGraph, u, v)));
        }
        printf("\n");
    }
    printf("\n****** Graph Nodes ********\n");
    for (long u = 0; u < pGraph->n; u++) {
        printf("Graph Node %ld: %s\n", u, pGraph->pNodes[u].name);
    }
    printf("\n");
}

#define FILE_NAME_LEN  255

void GenOneImage(struct Graph *pGraph, char *graphName, char *fileName, long seqNo, int *visited) {
    char dotFileName[FILE_NAME_LEN+1] = {0};
    char pngFileName[FILE_NAME_LEN+1] = {0};
    char command[(FILE_NAME_LEN+1)*4] = {0};
    
    snprintf(dotFileName, FILE_NAME_LEN, "%s_%04ld.dot", fileName, seqNo);
    snprintf(pngFileName, FILE_NAME_LEN, "%s_%04ld.png", fileName, seqNo);

    Graph2Dot(pGraph, dotFileName, graphName, pGraph->isDirected, 0, visited, 1);

    snprintf(command, FILE_NAME_LEN*4, "dot -T png %s -o %s", dotFileName, pngFileName);
    
    // Execute the command in a child process (fork() + exec() on Linux)
    system(command); 

}

/*
    Dot Files
 */
void Graph2Dot(struct Graph *pGraph, 
               char *filePath,
               char *graphName,
               int isDirectedGraph,
               int displayLabel,
               int *visited,
               int displayVisited) {
    FILE *dotFile = fopen(filePath, "w");
    /*
        FIXME:  check sanity of the parameters.
     */
    if (dotFile) {
        char *edgeConnectorStr = "";
        if (isDirectedGraph) {
            edgeConnectorStr = "->";
            fprintf(dotFile, "digraph %s {\n", graphName);
        } else {
            edgeConnectorStr = "--";
            fprintf(dotFile, "graph %s {\n", graphName);
        }

        for (long u = 0; u < pGraph->n; u++) {
            long vStart = u;
            if (isDirectedGraph) {
                vStart = 0;
            }
            for (long v = vStart; v < pGraph->n; v++) {
                long val = MatrixElement(pGraph, u, v);
                if (val) {
                    fprintf(dotFile, "\"%s\" %s {\"%s\"}", 
                            pGraph->pNodes[u].name, 
                            edgeConnectorStr, 
                            pGraph->pNodes[v].name);
                    if (displayLabel) {
                        fprintf(dotFile, " [label=\"%ld\"]", val);
                    }
                    fprintf(dotFile, "\n"); 
                }
            }
        }

        for (long i = 0; i < pGraph->n; i++) {
            if (displayVisited && visited && visited[i]) {
                if (pGraph->pNodes[i].onstack) {
                    fprintf(dotFile, "\"%s\" [color=red] [shape=box]\n", pGraph->pNodes[i].name);
                } else {
                    fprintf(dotFile, "\"%s\" [color=red]\n", pGraph->pNodes[i].name);
                }
            } else {
                if (pGraph->pNodes[i].onstack) {
                    fprintf(dotFile, "\"%s\"  [shape=box]\n", pGraph->pNodes[i].name);
                } else {
                    fprintf(dotFile, "\"%s\"\n", pGraph->pNodes[i].name);
                }
            }
        }                
        fprintf(dotFile, "}\n");
        fclose(dotFile);
    }                
}


#if 1
static long dfsImageCnt = 0;

static void DepthFirstSearch(struct Graph *pGraph, long u, int *visited) {
    visited[u] = 1;
    printf("visiting %s\n", pGraph->pNodes[u].name);
    
    dfsImageCnt++;

    if (pGraph->isDirected) {
        GenOneImage(pGraph, "DfsDirected", "images/DfsDirected", dfsImageCnt, visited);
    } else {
        GenOneImage(pGraph, "DfsUndirected", "images/DfsUndirected", dfsImageCnt, visited);
    }

    // recursively visit the adjacent nodes of u, if they have not been visited yet
    for(long v = 0; v < pGraph->n; v++) {
        if (MatrixElement(pGraph, u, v) == CONNECTED && !visited[v]) {
            DepthFirstSearch(pGraph, v, visited);
        }
    }
}

void RecursiveDFS(struct Graph *pGraph) {
    int *visited = (int *) malloc(pGraph->n * sizeof(int));
    //memset(visited, 0, sizeof(int) * pGraph->n);
    for (long v = 0; v < pGraph->n; v++) {
        visited[v] = 0;
    }

    dfsImageCnt = 0;

    if (pGraph->isDirected) {
        GenOneImage(pGraph, "DfsDirected", "images/DfsDirected", dfsImageCnt, visited);
    } else {
        GenOneImage(pGraph, "DfsUndirected", "images/DfsUndirected", dfsImageCnt, visited);
    }

    for (long u = 0; u < pGraph->n; u++) {
        if (!visited[u]) {
            DepthFirstSearch(pGraph, u, visited);
        }
    }
    printf("\n");
    free(visited);
}
#endif

/*
    if v is already on stack
        return the number of nodes in a cycle    
    else
        return 0
 */
static int GetNumOfNodesInCycle(struct Graph *pGraph, long v, struct Stack *pNodesOnStack) {
    // Not used now.
    (void) pGraph;
    // number of node in a cycle
    int n = 0;
    // whether v is on stack
    int isOnStack = 0;
    // Get an iterator of the stack
    StackIterator it = GetIterator(pNodesOnStack);
    
    // visit each element
    while (HasNext(&it)) {
        STACK_ITEM_T nodeId = NextItem(&it);
        n++;
        if (nodeId == v) {
            isOnStack = 1;
            break;
            //return n;
        }
    }
    if (!isOnStack) {
        n = 0;
    }
    printf("\n----- Test whether node %ld is on stack: NumOfNodesInCycle = %d -----\n", v, n);
    PrintStack(pNodesOnStack);
    printf("------------------------------------------------------------------\n\n");
    return n;
}

//#define  STOP_DETECTION_AT_FIRST_CYCLE

static long cycles = 0;
static long imgCnt = 0;

static void PrintNodesInCycle(struct Graph *pGraph, long v, struct Stack *pNodesOnStack) {
    // Get an iterator of the stack
    StackIterator it = GetIterator(pNodesOnStack);
    
    cycles++;

    if (pGraph->isDirected) {
        printf("\n\t\t****************** Cycle %ld detected (directed) *****************\n\t\t", cycles);
    } else {
        printf("\n\t\t****************** Cycle %ld detected (undirected) *****************\n\t\t", cycles);
    }
    /*
        v == 2
        Stack: 6  7  4  2  0

        Nodes in a cycle: 
        6 7 4 2


     */
    PrintStack(pNodesOnStack);
    printf("\t\tnode %ld is on stack\n", v);
    printf("\t\tNodes in a cycle: \n\t\t");
    // visit each element
    while (HasNext(&it)) {
        STACK_ITEM_T nodeId = NextItem(&it);
        printf("%ld ", nodeId);
        if (nodeId == v) {
            break;
        }
    }
    printf("\n\t\t****************************************************************\n");
}

static int DetectCycle(struct Graph *pGraph, long u, int *visited, struct Stack *pNodesOnStack) {
    visited[u] = 1;
    pGraph->pNodes[u].onstack = 1;
    // Push u onto the data stack
    StackPush(pNodesOnStack, u);    
    int cycleDetected = 0;
    // recursively visit the adjacent nodes of u, if they have not been visited yet
    for(long v = 0; v < pGraph->n; v++) {
        if (MatrixElement(pGraph, u, v)) {
            if (!visited[v]) {
                if (DetectCycle(pGraph, v, visited, pNodesOnStack)) {
                    cycleDetected = 1;                 
                    break;                 
                }
            } else {
                if (pGraph->pNodes[v].onstack) {
                    int nodesInCycle = GetNumOfNodesInCycle(pGraph, v, pNodesOnStack);
                    if (nodesInCycle > 0) {
                        if (!pGraph->isDirected) {
                            if (nodesInCycle == 2) {
                                continue;
                            }
                        }
                        PrintNodesInCycle(pGraph, v, pNodesOnStack);
                        cycleDetected = 1;
                        break;
                    }
                }
            }
        }
    }
    StackPop(pNodesOnStack);
    pGraph->pNodes[u].onstack = 0;
    return cycleDetected;
}

int HasCycle(struct Graph *pGraph) {
    int cyclic = 0;
    int *visited = (int *) malloc(pGraph->n * sizeof(int));
    struct Stack *pNodesOnStack = CreateStack();
    //memset(visited, 0, sizeof(int) * pGraph->n);
    for (long v = 0; v < pGraph->n; v++) {
        visited[v] = 0;
        pGraph->pNodes[v].onstack = 0;
    }
    for (long u = 0; u < pGraph->n; u++) {
        if (!visited[u]) {
            if (DetectCycle(pGraph, u, visited, pNodesOnStack)) {
                cyclic = 1;               
                break;
            }
        }
    }
    free(visited);
    //assert(StackIsEmpty(pNodesOnStack));
    ReleaseStack(pNodesOnStack); 
    return cyclic;
}



