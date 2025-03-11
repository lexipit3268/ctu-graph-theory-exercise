#include <stdio.h>
#define MAX_SIZE 20
#define MaxV 100
#define MaxLength 100
#define oo 999
#define NO_EDGE -10
typedef int ElementType;
typedef struct{
	ElementType data[MAX_SIZE];
	int top_idx;
}Stack;

void makenull_Stack(Stack *S){
	S->top_idx = -1;
}
void push(Stack *S, ElementType x){
	S->top_idx++;
	S->data[S->top_idx] = x;
}
ElementType top(Stack *S){
	return S->data[S->top_idx];
}
void pop(Stack *S){
	S->top_idx--;
}

int isEmpty(Stack *S){
	return S->top_idx==-1;
}

typedef struct{
	int A[MaxV][MaxV];
	int n;
}Graph;

void init_graph(Graph *G, int n){
	int i,j;
	G->n = n;
	for (i = 1; i<=n;i++){
		for (j=1;j<=n;j++){
			G->A[i][j] = -10;
		}
	}
}

void add_edge(Graph *G, int u, int v, int w){
	G->A[u][v] = w;
//	G->A[v][u] = w;
}

//kiem tra lang gieng 2 dinh
int adjacent(Graph *G,int x, int y){
	return (G->A[x][y] != 0);
}

//Tinh bac cua dinh x
int degree(Graph *G, int x){
	int deg = 0, i;
	for(i = 1; i<=G->n;i++){
		if (adjacent(G,i,x)){
			deg++;
		}
	}
	return deg;
}
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

List neighbors(Graph *G,int x){
	List L;
	makenull(&L);
	int i;
	for(i=1;i<=G->n;i++){
		if(G->A[x][i] != 0){
			push_back(&L,i);
		}
	}
	return L;
}

void print_list(List *L) {
    for (int i = 0; i < L->size; i++) {
        printf("%d\n", L->data[i]);
    }
//    printf("\n");
}

int min(int a, int b){
	int m = a;
	if(a>b) m = b;
	return m;
}

int max(int a, int b){
	return (a>b)? a:b;
}

void printGraph(Graph *G){
	for (int i = 1; i <= G->n;i++){
		for (int j = 1; j <= G->n;j++){
			printf("%d ",G->A[i][j]);
		}
		printf("\n");
	}
//	printf("\n");
}
int pi[MaxV][MaxV];
int next[MaxV][MaxV];
void FloyWarshall(Graph *G){
	int u, v, k;
	for (u=1;u<=G->n;u++){
		for (v=1;v<=G->n;v++){
			pi[u][v] = oo;
			next[u][v] = -1;
		}
	}
	for(u=1;u<=G->n;u++){
		pi[u][u] = 0;
	}
	for (u=1;u<=G->n;u++){
		for (v=1;v<=G->n;v++){
			if (G->A[u][v] != NO_EDGE){
				pi[u][v] = G->A[u][v];
				next[u][v] = v;
			}
		}
	}
	for (k=1;k<=G->n;k++){
		for(u=1;u<=G->n;u++){
			for(v=1;v<=G->n;v++){
				if (pi[u][k] == oo || pi[k][v] == oo){
					continue;
				} else{
					if (pi[u][k] + pi[k][v] < pi[u][v]){
						pi[u][v] = pi[u][k] + pi[k][v];
						next[u][v] = next[u][k];
					}
				}
			}
		}
	}

}

//void printPath(int s, int v) {
//    if (v == s) {
//        printf("%d ", s);
//        return;
//    }
//    if (p[v] == -1) {
//        return;
//    }
//    printPath(s, p[v]);
//    printf("%d ", v);
//}

int main(){
	Graph G;
	int n,m,u,v,w,i,j;
 	freopen("path.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(i = 1;i <= m; i++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	FloyWarshall(&G);
	for (i=1; i <= G.n;i++){
		for(j=1; j<=G.n;j++){
			if(pi[i][j] == oo){
				printf("%d -> %d: NO PATH\n",i,j);
			} else {
				printf("%d -> %d: %d\n",i,j,pi[i][j]);
			}
		}
	}
	return 0;
}

