#include <stdio.h>
#define MaxV 20
typedef struct{
	int u,v;
}Edge;
typedef struct{
	Edge edges[MaxV];
	int m,n;
}Graph;

void init_graph(Graph *G, int n){
	G->m=0;
	G->n = n;
}

void add_edge(Graph *G, int x, int y){
	G->edges[G->m].u = x;
	G->edges[G->m].v = y;
	G->m++;
}

int degree(Graph *G, int x){
	int i, count = 0;
	for (i=0;i<G->m;i++){
		if (G->edges[i].u == x || G->edges[i].v == x){
			count++;
		}
	}
	return count;
}

int adjacent(Graph *G, int x, int y){
	int i, adj = 0; 
	for (i = 0;i<G->m;i++){
		if (G->edges[i].u == x && G->edges[i].v == y) adj = 1;
		if (G->edges[i].u == y && G->edges[i].v == x) adj = 1;	
	}
	return adj;
}

void neighbours(Graph *G, int x){
	int i;
	printf("Dinh ke cua %d = ",x);
	for (i = 0; i<G->m;i++){
		if (adjacent(G,x,i)){
			printf("%d ",i);
		}
	}
}

int main() {
    Graph G;
    int n = 4, u;
    init_graph(&G, n);

    add_edge(&G, 1, 2);
    add_edge(&G, 1, 3);
    add_edge(&G, 1, 3);
    add_edge(&G, 1, 4);
    add_edge(&G, 3, 4);


    for (u = 1; u <= n; u++)
        printf("deg(%d) = %d\n", u, degree(&G, u));

    return 0;
}



