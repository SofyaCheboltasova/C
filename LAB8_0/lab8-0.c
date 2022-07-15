#include <stdio.h>
#include <malloc.h>
#define INT_MAX 2147483647

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

typedef struct node{
    int from, to;
    int length;
}node;

int CheckVerticesEdges(int N, int M) {
    if (M > (N * (N - 1) / 2) || M < 0)
        return BAD_EDGES;
    if (N > 5000 || N < 0)
        return BAD_VERTICIES;
    if (N == 1 && M == 0)
        return EMPTY;
    return SUCCESS;
}

int CreateGraph(node* graph, char* used, int N, int M) {
    short begin, end;
    int count = 2, length;

    for (int i = 0; i < M; ++i) {
        if (3 != scanf("%hi %hi %d", &begin, &end, &length))
            return BAD_LINES;

        if ((begin < 1) || (end < 1) || (begin > N) || (end > N))
            return BAD_VERTEX;

        if (length < 0 || length > INT_MAX)
            return BAD_LENGTH;

        ++count;
        used[--begin] = 1; 
        used[--end] = 1;

        graph[i].from = begin; 
        graph[i].to = end;
        graph[i].length = length;
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
        else 
            used[i] = 0;
    }
    return SUCCESS;
}

void swap (node* a, node* b){
    node c = *a;
    *a = *b;
    *b = c;
}

void QuickS (node* graph, int left, int right) {
    int L = left, R = right;
    int pivot = graph[(left + right) / 2].length;

    while (L <= R) {
        while (graph[L].length < pivot) 
            ++L;
        while (graph[R].length > pivot) 
            --R;

        if (L <= R) 
            swap(&graph[L++], &graph[R--]);
    }
    
    if (left < R)  
        QuickS(graph, left, R);
        
    if (right > L) 
        QuickS(graph, L, right);
}

int find_set (int v, int* parent) {
    if (parent[v] == v)
        return v;
    return parent[v] = find_set(parent[v], parent);
}

void union_sets (int a, int b, int* parent) {
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b) 
        parent[b] = a;
}


void Cruskal(int m, node* graph, int* parent) {
    for(int i = 0; i < m; ++i) {
        int x, y;
        x = graph[i].from;
        y = graph[i].to;

        if (find_set(x, parent) != find_set(y, parent)) {
            printf("%d %d\n", x + 1, y + 1);
            union_sets(x, y, parent);
        }
    }
}

void Clean (node* graph, char* used, int* parent) {
    if (used)    free(used);
    if (parent)  free(parent);
    if (graph)   free(graph);

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

    node *graph = (node*) calloc(M, sizeof(node));
    char *used = (char*) calloc(N, sizeof(char));
    int *parent = (int*) calloc(N, sizeof(int));
    for(int i = 0; i < N; ++i)
        parent[i] = i;

    if (SUCCESS != (num = CreateGraph(graph, used, N, M))) {
        printf("%s", Exceptions[num]);
        Clean(graph, used, parent);
        return 0;
    }

    if (SUCCESS != (num = CheckSpanningTree(N, used))) {
        printf("%s", Exceptions[num]);
        Clean(graph, used, parent);
        return 0;
    }

    QuickS(graph, 0, M - 1);

    Cruskal(M, graph, parent);
    Clean(graph, used, parent);

    return 0;
}
