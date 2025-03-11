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
	int A[MaxLength][MaxLength];
	int n;
}Graph;

void init_graph(Graph *G, int n){
	int i,j;
	G->n = n;
	for (i = 1; i<=n;i++){
		for (j=1;j<=n;j++){
			G->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int u, int v, int w){
	G->A[u][v] = w;
	G->A[v][u] = w;
}

//kiem tra lang gieng 2 dinh
int adjacent(Graph *G,int x, int y){
	return (G->A[x][y] != 0);
}

//Tinh bac VAO cua dinh x
int degree(Graph *G, int x){
	int deg = 0, i;
	for(i = 1; i<=G->n;i++){
		if (adjacent(G,i,x)){
			deg++;
		}
	}
	return deg;
}

List neighbors(Graph *G,int x){
	List L;
	makenull_List(&L);
	int i;
	for(i=1;i<=G->n;i++){
		if(G->A[x][i] != 0){
			push_back(&L,i);
		}
	}
	return L;
}

void printGraph(Graph *G){
	for (int i = 1; i <= G->n;i++){
		for (int j = i+1; j <= G->n;j++){
			if(G->A[i][j] != 0){
				printf("%d %d %d",i,j,G->A[i][j]);
			}
		}
		printf("\n");
	}
//	printf("\n");
}

int p[MaxLength], mark[MaxLength], pi[MaxLength];

int Prim(Graph *G, Graph *T, int s){
	int i, u, v, x;
	for (u = 1; u <= G->n; u++){
		pi[u] = oo;
		p[u] = -1;
		mark[u] = 0;
	}
	
	pi[s] = 0;
	
	for(i = 1; i < G->n; i++){
		int min_dist = oo;
		for (x = 1; x <= G->n;x++){
			if(mark[x] == 0 && pi[x] < min_dist){
				min_dist = pi[x];
				u = x;
			}
			mark[u] = 1;
			for(v =1; v<=G->n;v++){
				if (adjacent(G,u,v)){
					if(mark[v] == 0 && pi[v] > G->A[u][v]){
						pi[v] = G->A[u][v];
						p[v] = u;
					}
				}
			}
		}
	}
	
	init_graph(T,G->n);
	int sum_w = 0;
	for(u = 1; u<= G->n; u++){
		if(p[u] != -1){
			int w = G->A[p[u]][u];
			add_edge(T,p[u],u,w);
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
	Graph T;
	int sum_w = Prim(&G,&T,1);
	printf("%d\n",sum_w);
	printGraph(&T);
	return 0;
}
