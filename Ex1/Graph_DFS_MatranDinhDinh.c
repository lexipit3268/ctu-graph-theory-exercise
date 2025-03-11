#include <stdio.h>
#define MaxV 20
#define MaxLength 20
#define MaxStack 40
typedef struct{
	int A[MaxV][MaxV];
	int n;
}Graph;

void init_Graph(Graph *G, int n){
	int i,j;
	G->n = n;
	for (i = 1; i<=n;i++){
		for (j=i;j<=n;j++){
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
		if(G->A[i][x] == 1){
			push_back(&L,i);
		}
	}
	return L;
}
//STACKKKK
typedef struct{
	int data[MaxStack];
	int size;
}Stack;

void makenull_Stack(Stack *S){
	S->size = 0;
}
//Them dinh X vao stack
void push_s(Stack *S, int x){
	S->data[S->size] = x;
	S->size++;
}

//lay 1 dinh tai vi tri i
int top(Stack *S){
	return S->data[S->size-1];
}

void pop(Stack *S){
	S->size--;
}

int isEmpty(Stack S){
	return S.size==0;
}
void dfs(Graph *G, int x){
	//dua 1 dinh bat ky vao stack
	Stack S;
	makenull_Stack(&S);
	push_s(&S,x);
	int mark[MaxV];
	//khoi tao tat ca cac dinh chua duoc duyet
	int i,j;
	for(i=1;i<=G->n;i++){
		mark[i] = 0;	
	}
	
	while(!isEmpty(S)){
		int u = top(&S);
		pop(&S);
		if (mark[u] == 1) continue;
		printf("Duyet: %d\n",u);
		mark[u] = 1;
		List L = neighbors(G,u);
		for(i = 1;i<=L.size;i++){
			int v = retrieve(&L,i);
			if(mark[v] == 0){
				push_s(&S,v);
			}
		}
	}
}
int main(){
	Graph G;
	int n, m; //n dinh, m cung
	freopen("DFS.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_Graph(&G,n);
	int e, u, v;
	for(e = 1;e <= m; e++){
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	dfs(&G,1);
	return 0;
}
