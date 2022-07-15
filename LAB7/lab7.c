#include <stdio.h>
#include <malloc.h>

enum ErrorType {
    BAD_LINES = 0,
    BAD_VERTICIES = 1,
    BAD_VERTEX = 2,
    BAD_EDGES = 3,
    IMPOSSIBLE_SORT = 4,
    SUCCESS = 5
};

int CheckVerticesEdges(int N, int M) {
    if (M > (N * (N + 1) / 2) || M < 0)
        return BAD_EDGES;
    if (N > 2000 || N < 0)
        return BAD_VERTICIES;
    return SUCCESS;
}

int CreateGraph (char* graph, int n, int m) {
    int count = 2, s, f;

    for (int i = 0; i < m; ++i) {
        if (2 != scanf("%d %d", &s, &f))
            return 0;

        if ((s < 1) || (f < 1) || (s > n) || (f > n))
            return BAD_VERTEX;

        --s; --f;
        ++count;
        graph[s * n + f] = 1;
    }
    if (count < m + 2)
        return BAD_LINES;
    return SUCCESS;
}

// -1 - серый, 0 - белый, 1 - черный
int DFS(short v, int n, char* graph, short* used, short* cur, short* t) {
    if(used[v] > 0)   return 0;
    if(used[v] == -1)
        return IMPOSSIBLE_SORT; //Вершина серая -> цикл

    used[v] = -1;

    for (short i = n - 1; i >= 0; --i) {
        if (graph[v * n + i] == 1) {
            if (IMPOSSIBLE_SORT == DFS(i, n, graph, used, cur, t))
                return IMPOSSIBLE_SORT;
        }
    }
    --(*t);
    used[v] = *t; 
    return 0;
}

void SortGraph(int n, short* used) {
    short counter = 1;
    while(counter <= n) {
        for (short i = 0; i < n ; ++i) {
            if(used[i] == counter)
                printf("%d ", i + 1);
        }
        counter++;
    }
}

void Clean (char* graph, short* used) {
    if (graph) free(graph);
    if (used)  free(used);
}

int main() {
    char *Exceptions[] = {
            "bad number of lines",
            "bad number of vertices",
            "bad vertex",
            "bad number of edges",
            "impossible to sort"
    };

    short num;
    int M = 0, N = 0;

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

    char *graph = (char*)calloc(N * N, sizeof(char));

    if (SUCCESS != (num = CreateGraph(graph, N, M))) {
        printf("%s", Exceptions[num]);
        Clean(graph, NULL);
        return 0;
    }

    short *used = (short*)calloc(N + 1, sizeof(short));
    short cur = 0;

    short t = (short)N + 1;
    for (short i = 0; i < N; ++i) {
        if (IMPOSSIBLE_SORT == DFS(i, N, graph, used, &cur, &t)) {
            printf("%s", Exceptions[4]);
            Clean(graph, used);
            return 0;
        }
    }

    SortGraph(N, used);

    Clean(graph, used);
    return 0;
}
