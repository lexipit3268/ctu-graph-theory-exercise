#include <stdio.h>
#define MAX_SIZE 20
#define MaxV 100
#define MaxLength 100
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
//	G->A[y][x] = 1;
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
		if(G->A[i][x] == 1){
			push_back(&L,i);
		}
	}
	return L;
}

int mark[MaxV];
List dfs(Graph *G, int x){
	Stack S;
	makenull_Stack(&S);
	push(&S,x);
	List result;
	makenull(&result);
	while(!isEmpty(&S)){
		int u = top(&S);
		pop(&S);
		if(mark[u] != 0 ) continue;
		push_back(&result,u);
		mark[u] = 1;
		for (int i = G->n; i > 0; i--)
			if (adjacent(G, u, i)) push(&S, i); 
	}
	return result;
}

void print_list(List *L) {
    for (int i = 0; i < L->size; i++) {
        printf("%d\n", L->data[i]);
    }
//    printf("\n");
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
	}
	for (u=1;u<=G.n;u++){
		if (mark[u] == 0){
			List L = dfs(&G,u);
// 			int i, v;
//			for (i=1;i<=L.size;i++){
//				v = retrieve(&L,i);
//				printf("%d\n",v);
//				mark[v] = 1;
//			}
			print_list(&L);	
		}
	}

}

