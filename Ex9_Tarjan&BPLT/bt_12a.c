#include <stdio.h>
#define MAX_SIZE 20
#define MaxV 100
#define MaxLength 100
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NO_COLOR 0
#define BLUE 1
#define RED 2
int mark[MaxV];
int color[MaxV];
int has_circle;
int conflict;
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
void add_edge(Graph *G, int x, int y){
	G->A[x][y] = 1;
	G->A[y][x] = 1;
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


void dfs(Graph *G, int u){
	if (mark[u] == 1){
		return;
	}
	mark[u] = 1;
	color[u] = GRAY;
	List L = neighbors(G,u);
	int i;
	for (i=1;i<=L.size;i++){
		int v = retrieve(&L,i);
		if(color[v] == WHITE){
			dfs(G,v);
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

void colorize(Graph *G, int u, int c){
	color[u] = c;
	List L = neighbors(G,u);
	for(int i = 1; i <= L.size;i++)
	{
		int v = retrieve(&L,i);
		if(color[v] == NO_COLOR){
			colorize(G,v,3-c);
		} else 
		if (color[v] == color[u]){
			conflict = 1;
		}
	}
}

int conected(Graph *G){
	for(int u = 1; u <= G->n;u++){
		mark[u]=0;
	}
	dfs(G,1);
	for(int u = 1; u <= G->n;u++){
		if (mark[u]==0){
			return 0;
		}
	}
	return 1;
}

int BPLT(Graph *G){
	int count = 0;
	for (int u = 1; u <= G->n; u++){
		if (mark[u]==0){
			dfs(G,u);
			count++;
		}
	}
	return count;
}
int main(){
	Graph G;
	int n,m,u,v,e;
	freopen("DFS.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1;e <= m; e++){
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	for (e = 1; e <= n; e++){
		mark[e]=0;
		color[e] = NO_COLOR;
	}
	has_circle = 0;
	conflict = 0;
	for (e = 1; e<=n;e++){
		if(color[e] == NO_COLOR){
			colorize(&G,e,BLUE);
		}
	}
//	colorize(&G,1,BLUE);
	if (conflict == 1){
		printf("NO");
	} else {
		printf("YES");
	}
	return 0;
}

