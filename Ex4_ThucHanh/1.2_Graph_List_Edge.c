#include <stdio.h>
#define MaxV 20
typedef struct{
	int u,v;
	float w;
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

void add_edge_donCoHuong(Graph *G, int x, int y){
	for (int i = 0; i < G->m; i++) {
        if (G->edges[i].u == x && G->edges[i].v == y) {
//        	printf("trung cung");
            return; 
        }
    }
    G->edges[G->m].u = x;
    G->edges[G->m].v = y;
    G->m++;
}

void add_edge_donVoHuong(Graph *G, int x, int y){
	if (x==y){
	    return;
	}
	for (int i = 0; i < G->m; i++) {
        if ((G->edges[i].u == x && G->edges[i].v == y) || (G->edges[i].v == x && G->edges[i].u == y)) {
            return; 
        }
    }
    G->edges[G->m].u = x;
    G->edges[G->m].v = y;
    G->m++;
}

int degree(Graph *G, int x) {
    int i, count = 0;
    for (i = 0; i < G->m; i++) {
        if (G->edges[i].u == x) {
            count++;
        }
        if (G->edges[i].v == x){
        	count++;
		}
    }
    return count;
}

int adjacent(Graph *G, int x, int y){
	int i, adj = 0; 
	for (i = 0;i<G->m;i++){
		if (G->edges[i].u == x && G->edges[i].v == y) adj = 1;
		//co huong thi bo dong sau
		if (G->edges[i].u == y && G->edges[i].v == x) adj = 1;	
	}
	return adj;
}

void neighbours(Graph *G, int x){
	int i;
	printf("neighbours(%d) = ",x);
	for (i = 1; i<=G->n;i++){
		if (adjacent(G,x,i)!=0){
			printf("%d ",i);
		}
	}
}

int main() {
    Graph G;
    int n, m, u, v, i;
    freopen("edge.txt","r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(&G,n);
    for (i = 0; i < m; i++){
    	scanf("%d%d",&u,&v);
    	add_edge_donCoHuong(&G,u,v);
	}
    for (u = 1; u <= n; u++){
//        printf("neighbors(%d) = \n", u);
        neighbours(&G, u);
        printf("\n");
    }
    return 0;
}


