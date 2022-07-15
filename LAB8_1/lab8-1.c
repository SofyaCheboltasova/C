#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#define INT_MAX 2147483647
#define INT_MAX1 2147483648

enum ErrorType {
    BAD_VERTICIES,
    BAD_EDGES,
    BAD_VERTEX,
    BAD_LENGTH,
    BAD_LINES,
    NO_SPANNING_TREE,
    EMPTY,
    SUCCESS
};

int CheckVerticesEdges(int N, int M) {
    if (M > (N * (N - 1) / 2) || M < 0)
        return BAD_EDGES;
    if (N > 5000 || N < 0)
        return BAD_VERTICIES;
    if (N == 1 && M == 0)
        return EMPTY;
    return SUCCESS;
}

int CreateGraph(int* graph, char* used, int N, int M) {
    short begin, end;
    int count = 2, length;

    for (int i = 0; i < M; ++i) {
        if (3 != scanf("%hi %hi %d", &begin, &end, &length))
            return BAD_LINES;

        if ((begin < 1) || (end < 1) || (begin > N) || (end > N))
            return BAD_VERTEX;

        if (length < 0 || length > INT_MAX)
            return BAD_LENGTH;

        --begin; --end;
        ++count;
        used[begin] = 1; used[end] = 1;

        graph[end * N + begin] = length;
        graph[begin * N + end] = length;
    }
    if (count < M + 2)
        return BAD_LINES;
    return SUCCESS;
}

int CheckSpanningTree(int n, char* used) {
    if(!n) return NO_SPANNING_TREE;

    for(int i = 0; i < n; ++i) {
        if(!used[i])
            return NO_SPANNING_TREE;
        else used[i] = 0;
    }
    return SUCCESS;
}

int PrintPrim(int begin, int n, int* graph, char* used, int* end_edge, long long* min_edge) {
    min_edge[begin] = 0;

    for(int i = 0; i < n; ++i) {
        int vertex = -1;

        for(int j = 0; j < n; ++j)
            if(!used[j] && (vertex == -1 || min_edge[j] < min_edge[vertex]))
                vertex = j;

        if(end_edge[vertex] != -1)
           printf("%d %d\n", vertex + 1, end_edge[vertex] + 1);

        used[vertex] = 1;

        for(int j = 0; j < n; ++j) {
            if(!used[j] && graph[vertex * n + j] && graph[vertex * n + j] < min_edge[j]){
                min_edge[j] = graph[vertex * n + j];
                end_edge[j] = vertex;
            }
        }
    }
    return SUCCESS;
}

void Clean (int* graph, char* used, long long* min_edge, int* end_edge) {
    if (used)      free(used);
    if (graph)     free(graph);
    if (min_edge)  free(min_edge);
    if (end_edge)  free(end_edge);
}

int main() {
    char *Exceptions[] = {
            "bad number of vertices",
            "bad number of edges",
            "bad vertex",
            "bad length",
            "bad number of lines",
            "no spanning tree",
            "",
    };
    int num, M = 0, N = 0;

    if (scanf("%d", &N) != 1) {
        printf("%s", Exceptions[0]);
        return 0;
    }

    if (scanf("%d", &M) != 1) {
        printf("%s", Exceptions[0]);
        return 0;
    }

    if (SUCCESS != (num = CheckVerticesEdges(N, M))) {
        printf("%s", Exceptions[num]);
        return 0;
    }

    int* graph  = (int*) calloc(N * N, sizeof(int));
    assert(graph);

    char* used  = (char*)calloc(N, sizeof(char));
    assert(used);

    int* end_edge = (int*)calloc(N * N, sizeof(int));
    assert(end_edge);
    for(int i = 0; i < N; ++i)
        end_edge[i] = -1;

    long long* min_edge = (long long*)calloc(N, sizeof(long long));
    assert(min_edge);
    for(int i = 0; i < N; ++i)
        min_edge[i] = INT_MAX1;

    if (SUCCESS != (num = CreateGraph(graph, used, N, M))){
        printf("%s", Exceptions[num]);
        Clean(graph, used, min_edge, end_edge);
        return 0;
    }

    if (SUCCESS != (num = CheckSpanningTree(N, used))){
        printf("%s", Exceptions[num]);
        Clean(graph, used, min_edge, end_edge);
        return 0;
    }

    if (SUCCESS != (num = PrintPrim(0, N, graph, used, end_edge, min_edge))){
        printf("%s", Exceptions[num]);
        Clean(graph, used, min_edge, end_edge);
        return 0;
    }
    Clean(graph, used, min_edge, end_edge);
    return 0;
}

