#include <stdio.h>
#define oo 999
#define MaxLength 50

typedef struct{
	int size;
	int data[MaxLength];
}List;

void makenull_List(List *L){
	L->size=0;
}
void push_back(List *L, int x){
	L->data[L->size] = x;
	L->size++;
}
int retrieve(List *L, int p){
	return L->data[p-1];
}
int emptyList(List *L){
	return L->size==0;
}

typedef struct{
	int u, v;
	int w;
}Edge;

typedef struct{
	Edge edges[MaxLength];
	int n,m;
}Graph;

void init_graph(Graph *G, int n){
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G, int u, int v, int w){
	if (u==v){
	    return;
	}
	if (u > v) {
        int temp = u;
        u = v;
        v = temp;
    }
	for (int i = 0; i < G->m; i++) {
        if ((G->edges[i].u == u && G->edges[i].v == v) || (G->edges[i].v == u && G->edges[i].u == v)) {
            return; 
        }
    }
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m].w = w;
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

List neighbours(Graph *G, int x){
	List L; makenull_List(&L);
	int i;
	for (i = 1; i<=G->n;i++){
		if (adjacent(G,x,i)!=0){
			push_back(&L,i);
		}
	}
	return L;
}

void swap(Edge *a, Edge *b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void sortGraph(Graph *G) {
    for (int i = 0; i < G->m - 1; i++) {
        for (int j = 0; j < G->m - i - 1; j++) {
            if (G->edges[j].w > G->edges[j+1].w) {
                swap(&G->edges[j], &G->edges[j+1]);
            }
        }
    }
}

void printGraph(Graph *G) {
    for (int i = 0; i < G->m; i++) {
        printf("%d %d %d\n", G->edges[i].u, G->edges[i].v, G->edges[i].w);
    }
}

int parent[MaxLength];
int findRoot(int u){
	while(parent[u] != u){
		u = parent[u];
	}
	return u;
}

int Kruskal(Graph *G, Graph *T){
	init_graph(T,G->n);
	for (int u = 1; u <= G->n; u++){
		parent[u] = u;
	}
	int sum_w = 0;
	for(int e = 0; e < G->m; e++){
		int u = G->edges[e].u;
		int v = G->edges[e].v;
		int w = G->edges[e].w;
		int root_u = findRoot(u);
		int root_v = findRoot(v);
		if(root_u != root_v){
			add_edge(T,u,v,w);
			parent[root_v] = root_u;
			sum_w+=w;
		}
	}
	return sum_w;
}

int main(){
	Graph G;
	freopen("edge.txt","r",stdin);
	int n,m,u,v,w,e;
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	sortGraph(&G);
	
	Graph T;
	int sum_w = Kruskal(&G,&T);
	sortGraph(&T);
	printf("%d\n",sum_w);
	printGraph(&T);
	return 0;
}
