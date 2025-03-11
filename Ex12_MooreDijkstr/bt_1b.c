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
	G->A[v][u] = w;
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
int mark[MaxV];
int pi[MaxV];
int p[MaxV];

void mooreDijkstra(Graph *G, int s){
	int u, v, i;
	for (u = 1; u <= G->n; u++){
		pi[u] = oo;
		p[u] = -1;
		mark[u] = 0;
	}
	pi[s] = 0;
	p[s] = -1;
	
	for (i=1; i<G->n;i++){
		//tim mark[u] = 0 và pi[u] nho nhat
		int j, min_pi = oo;
		for (j = 1; j <= G->n;j++){
			if (mark[j] == 0 && pi[j] < min_pi){
				min_pi = pi[j];
				u = j;
			}
		}
		//danh dau
		mark[u] = 1;
		//cap nhat pi va p cua dinh ke v 
		for (v = 1; v <= G->n; v++){
			if (G->A[u][v] != NO_EDGE && mark[v] == 0){
				if (pi[u] + G->A[u][v] < pi[v]){
					pi[v] = pi[u] + G->A[u][v];
					p[v] = u;
				}
			}
		}
	}
}

void printPath(int s, int v) {
    if (v == s) {
        printf("%d ", s);
        return;
    }
    if (p[v] == -1) {
        return;
    }
    printPath(s, p[v]);
    printf("%d ", v);
}
int main(){
	Graph G;
	int n,m,u,v,e,w;
	freopen("path.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1;e <= m; e++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	printGraph(&G);
	mooreDijkstra(&G,1);
	for (u = 1; u <= G.n;u++){
		printf("pi[%d] = %d, p[%d] = %d\n",u,pi[u],u,p[u]);
	}
	for (u = 1; u <= G.n;u++){
		printPath(1,u);
		printf("\n");
	}
//	for (u = 1; u <= G.n; u++) {
//        printf("Duong di tu 1 den %d: ", u);
//        int k = 0;
//        int path[MaxV];
//        int current = u;
//        while (current != -1) {
//            path[k] = current;
//            k++;
//            current = p[current];
//        }
//        for (int i = k - 1; i >= 0; i--) {
//            printf("%d ", path[i]);
//        }
//        printf("\n");
//    }
	return 0;
}

