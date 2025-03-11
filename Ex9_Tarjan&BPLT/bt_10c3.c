#include<stdio.h>
#define Max_Vertices 100

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n;
} Graph;

void InitGraph(Graph *G, int n) {
    G->n = n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            G->A[i][j] = 0;
        }
    }
}

void AddEdge(Graph *G, int u, int v) {
    G->A[u][v] += 1;
}

int Adjacent(Graph *G, int u, int v) {
    return (G->A[u][v] != 0);
}

#define WHILE 0
#define GRAY 1
#define BLACK 2

int color[Max_Vertices], parent[Max_Vertices];
int isCircle = 0, circleStartPoint, circleEndPoint;

void DFS(Graph* G, int u) {
    color[u] = GRAY;

    for (int v = 1; v <= G->n; v++) {
        if (Adjacent(G, u, v)) {
            if (color[v] == WHILE) {
                parent[v] = u;
                DFS(G, v);
            } else if (color[v] == GRAY) {
                isCircle = 1;
                circleStartPoint = v;
                circleEndPoint = u;
            }
        }
    }

    color[u] = BLACK;
}

void PrintCircle(int u) {
    if (u == circleStartPoint) {
        printf("%d ", u);
        return;
    }
    PrintCircle(parent[u]);
    printf("%d ", u);
}

int main() {
    Graph G;
    int n, m;
    freopen("DFS.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    InitGraph(&G, n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        AddEdge(&G, u, v);
    }

    for (int i = 1; i <= n; i++) {
        color[i] = WHILE;
        parent[i] = -1;
    }

    isCircle = 0;

    for (int u = 1; u <= n; u++) {
        if (color[u] == WHILE) {
            DFS(&G, u);
        }
    }

    if (!isCircle) {
        printf("-1");
    } else {
        PrintCircle(circleEndPoint);
    }

    return 0;
}

