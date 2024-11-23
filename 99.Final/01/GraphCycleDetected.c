#include <stdio.h>
#include "Graph.h"

static int DetectCycle(struct Graph *pGraph, int u, int *visited, int *trace) {
    visited[u] =  1;
    // 设置当前正在跟踪的 10
    trace[u] = 1;
    int cyclic = 0;

    for(long v = 0; v < pGraph->n; v++)  {
        if (MatrixElement(pGraph, u, v))  {
            // 如果当前的点没有访问过
            if (!visited[v]) {
                // 子递归继续访问
                if (DetectCycle(pGraph, v, visited, trace)) {
                    cyclic = 1;             
                    break;                  
                }
            } else if (trace[u] == 1) { // 表示正在跟进的的地方，肯定存在环
                // 存在环的情况
                cyclic = 1;
                break;
            }
        }

    }
    // 设置为当前不是跟进的路线上
    trace[u] = 0;
    return cyclic;
}

static int DetectCycle(struct Graph *pGraph, int u, int *visited, int *trace) {
    // ____Q1___
    visited[u] = 1;
    // 设置当前正在跟踪的 10
    // ____Q2____
    trace[u] = 1;
    int cyclic = 0;

    for(long v = 0; v < pGraph->n; v++)  {
        if (MatrixElement(pGraph, u, v) == CONNECTED)  {
            // 如果当前的点没有访问过
            // if (_____Q4____) {
            // if (visited[v] == 0) {
            if (!visited[v]) {
                // 子递归继续访问
                if (DetectCycle(pGraph, v, visited, trace)) {
                    // 存在环的情况
                    cyclic = 1;
                    // _____Q6_____            
                    break;                  
                }
            } else if (trace[v] == 1) { // 表示正在跟进的的地方，肯定存在环
                // 存在环的情况
                cyclic = 1;
                break;
            }
        }

    }
    // 设置为当前不是跟进的路线上
    // 
    trace[u] = 0;
    return cyclic;
}

int IsCyclic(struct Graph *pGraph) { // pgraph is a directed graph
    int *visited = (int *) mallac(pGraph ->n * sizeof(int));
    int *onStack = (int *) malloc(pGraph->n * sizeof(int));

    assert(visited && onStack);

    for (long u = 0; u < pGraph ->n; u++){
        visited[u] = 0;
        onStack[u] = 0;

    }
    int cyclic = 0;

    for (long u =0; u < pGraph->n; u++) {
        if (!visited[u]) {
            if (DetestCycle(pGraph, u, visited, onStack)) {
                cyclic = 1;
                break;
            }
        }
    }

    free(visited);
    free(onStack);
    return cyclic;

}