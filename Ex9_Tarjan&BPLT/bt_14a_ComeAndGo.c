#include <stdio.h>
#define MAX_SIZE 20
#define MaxV 100
#define MaxLength 100
#define WHITE 0
#define GRAY 1
#define BLACK 2
int mark[MaxV];
int color[MaxV];
int parent[MaxV];
int has_circle;
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
			G->A[i][j] = 0;
		}
	}
}

//them cung
//void add_edge(Graph *G, int x, int y){
//	G->A[x][y] = 1;
////	G->A[y][x] = 1;
//}

void add_edge(Graph *G, int x, int y, int p){
	if (p==1){
		G->A[x][y] += 1;
	} else if (p==2){
		G->A[x][y] += 1;
		G->A[y][x] += 1;
	}
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
		if(G->A[x][i] == 1){
			push_back(&L,i);
		}
	}
	return L;
}


void dfs(Graph *G, int u, int p){
	if (mark[u] == 1){
		return;
	}
	mark[u] = 1;
	color[u] = GRAY;
	List L = neighbors(G,u);
	int i;
	for (i=1;i<=L.size;i++){
		int v = retrieve(&L,i);
		if(v == p){
			continue;
		}
		if(color[v] == WHITE){
			dfs(G,v,u);
		} else if (color[v] == GRAY){
			has_circle = 1;
		}
	}
	color[u] = BLACK;
}

void print_list(List *L) {
    for (int i = 0; i < L->size; i++) {
        printf("%d\n", L->data[i]);
    }
//    printf("\n");
}

int num[MaxV], min_num[MaxV];
int k;
Stack S;
int on_stack[MaxV];
int countLTM;
int min(int a, int b){
	int m = a;
	if(a>b) m = b;
	return m;
}

int max(int a, int b){
	return (a>b)? a:b;
}
void SCC(Graph *pG, int u) {
    num[u] = min_num[u] = k; k++;
    push(&S, u);
    on_stack[u] = 1;
    for (int v = 1; v <= pG->n; v++) {
        if (adjacent(pG, u, v)) {
            if (num[v] < 0) {
                SCC(pG, v);
                min_num[u] = min(min_num[u], min_num[v]);
            } else if (on_stack[v]) {
                min_num[u] = min(min_num[u], num[v]);
            }
        }
    }

    if (num[u] == min_num[u]) {
        int w;
        countLTM++;
        do {
            w = top(&S);
            pop(&S);
            on_stack[w] = 0;
        } while (w != u);
    }
}

void printGraph(Graph *G){
	for (int i = 1; i <= G->n;i++){
		for (int j = 1; j <= G->n;j++){
			printf("%d ",G->A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(){
	Graph G;
	int n,m,u,v,e,p;
	freopen("DFS.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1;e <= m; e++){
		scanf("%d%d%d",&u,&v,&p);
		add_edge(&G,u,v,p);
	}
	for (int u = 1; u<= G.n; u++){
		num[u] = -1;
		min_num[u] = 0;
		on_stack[u] = 0;
	}
	k=1;
	makenull_Stack(&S);
	countLTM = 0;
	for (int u = 1; u<= G.n; u++){
		if (num[u] == -1){
			SCC(&G,u);
		}
	}
	if(countLTM == 1){
		printf("OKIE");
	} else {
		printf("NO");
	}

	return 0;
}

