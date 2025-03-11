#include <stdio.h>
#define MAX_SIZE 20
#define MaxV 100
#define MaxLength 100
#define oo 999
//Tao list
typedef struct{
	int data[MaxLength];
	int size;
}List;

void makenull(List *L){
	L->size = 0;
}
//them 1 dinh vao cuoi ds
void push_back(List *l,int x){
	l->data[l->size] = x;
	l->size++;
}
//lay 1 dinh tai vi tri i
int retrieve(List *l, int i){
	return l->data[i-1];
}

typedef struct{
	int u, v;
	int w;
}Edge;

typedef struct{
	Edge edges[MaxV];
	int n, m;
}Graph;

void init_graph(Graph *G, int n){
	G->n = n;
	G->m = 0;
}

void add_edgeD(Graph *G, int u, int v, int w){
	for (int i = 0; i < G->m; i++) {
        if (G->edges[i].u == u && G->edges[i].v == v) {
            return; 
        }
    }
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->edges[G->m].w = w;
    G->m++;
}

void add_edgeND(Graph *G, int u, int v, int w){
	if (u==v){
	    return;
	}
	for (int i = 0; i < G->m; i++) {
        if ((G->edges[i].u == u && G->edges[i].v == v) || (G->edges[i].u == v && G->edges[i].v == u)) {
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
	int i;
	List res;makenull(&res);
	printf("neighbours(%d) = ",x);
	for (i = 1; i<=G->n;i++){
		if (adjacent(G,x,i)!=0){
			push_back(&res,i);
		}
	}
	return res;
}

int pi[MaxV];
int p[MaxV];
int negative_cycle = 0;
void BellmanFord(Graph *G, int s){
	int u, v, w, i, k;
	for (u = 1; u<= G->n; u++){
		pi[u] = oo;
		p[u] = -1;
	}
	pi[s] = 0;
	p[s] = -1;
	
	for(i = 1; i < G->n; i++){
		//duyet qua cac cung
		for (k = 0; k < G->m; k++){
			u = G->edges[k].u;
			v = G->edges[k].v;
			w = G->edges[k].w;
			if (pi[u] == oo ) continue;
			if (pi[u] + w < pi[v]){
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
	for (k = 0; k < G->m; k++){
		u = G->edges[k].u;
		v = G->edges[k].v;
		w = G->edges[k].w;
		if (pi[u] + w < pi[v]){
			negative_cycle = 1;
			break;
		}
	}
}
int main(){
	Graph G;
	int n,m,u,v,e,w;
  	freopen("path.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1;e <= m; e++){
		scanf("%d%d%d",&u,&v,&w);
		add_edgeD(&G,u,v,w);
	}
	int s, t;
	scanf("%d%d",&s,&t);
	BellmanFord(&G,s);
	if (pi[t] != oo) {
	    printf("%d",pi[t]);
	} else {
	    printf("-1");
	}
	return 0;
}

