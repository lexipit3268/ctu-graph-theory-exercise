#include <stdio.h>
#define MaxV 20
#define MaxLength 20
#define MaxE 40
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

void makenull_List(List *L){
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
	makenull_List(&L);
	int i;
	for(i=1;i<=G->n;i++){
		if(G->A[i][x] == 1){
			push_back(&L,i);
		}
	}
	return L;
}
//Queueeeeee;
typedef struct{
	int data[MaxE];
	int front, rear;
}Queue;

void makenull_Queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

//Them phan tu vao queue
void push_Queue(Queue *Q, int x){
	Q->rear++;
	Q->data[Q->rear] = x;
}

int top(Queue *Q){
	return Q->data[Q->front];
}

void pop(Queue *Q){
	Q->front++;	
}

int isEmpty(Queue Q){
	return (Q.front > Q.rear);
}

List bfs(Graph *G, int x){
	Queue Q;
	makenull_Queue(&Q);
	int mark[MaxV];
	int i;
	for (i=1;i<=G->n;i++){
		mark[i] = 0;
	}
	push_Queue(&Q,x);
	List result;
	makenull_List(&result);
	while (!isEmpty(Q)){
		int u = top(&Q);
		pop(&Q);
		if (mark[u] == 1){
			continue;
		}
		push_back(&result,u);
		mark[u] = 1;
		List L;
		makenull_List(&L);
		L = neighbors(G,u);
		int v;
		for (i=1;i<=L.size;i++){
			v = retrieve(&L,i);
			if (mark[v] == 0){
				push_Queue(&Q,v);
			}
		}
	}
	return result;
}
int main(){
	Graph G;
	int n, m; //n dinh, m cung
	freopen("BFS.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_Graph(&G,n);
	int e, x, y;
	for(e = 1;e <= m; e++){
		scanf("%d%d",&x,&y);
		add_edge(&G,x,y);
	}
	int u;
	int mark_bfs[MaxV];
	for (u=1;u<=G.n;u++){
		mark_bfs[u] = 0;
	}
	for (u=1;u<=G.n;u++){
		if (mark_bfs[u] == 0){
			List L = bfs(&G,u);
			int i, v;
			for (i=1;i<=L.size;i++){
				v = retrieve(&L,i);
				printf("%d\n",v);
				mark_bfs[v] = 1;
			}
		}
	}
	return 0;
}
