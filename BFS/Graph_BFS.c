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
		if(adjacent(G,x,i)){
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

void bfs(Graph *G, int u){
	Queue Q;
	makenull_Queue(&Q);
	int mark[MaxV];
	int i;
	for (i=1;i<=G->n;i++){
		mark[i] = 0;
	}
	push_Queue(&Q,u);
	while (!isEmpty(Q)){
		int u = top(&Q);
		pop(&Q);
		if (mark[u] == 1){
			continue;
		}
		printf("%d\n",u);
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
}
int main(){
	Graph G;
	int n, m; //n dinh, m cung
	freopen("BFS.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_Graph(&G,n);
	int e, u, v;
	for(e = 1;e <= m; e++){
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	bfs(&G,1);
//	List L = neighbors(&G,1);
//	printf("Dinh ke cua 1: ");
//	for (e = 0; e < L.size; e++){
//		printf("%d ",L.data[e]);
//	}
	return 0;
}
