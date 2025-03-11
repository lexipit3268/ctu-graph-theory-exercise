#include <stdio.h>
#define MAX_SIZE 20
#define MaxV 100
#define MaxLength 100
#define MaxN 100
typedef int ElementType;

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

void printList(List *L) {
    for (int i = 0; i < L->size; i++) {
        printf("%d\n", L->data[i]);
    }
//    printf("\n");
}

void copyList(List *L1, List *L2){
	makenull(L1);
	L1->size = L2->size;
	for (int i = 0; i<=L2->size;i++){
		L1->data[i] = L2->data[i];
	}
}
typedef struct{
	int front,rear;
	int data[MaxN];
}Queue;

void makenull_Queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

//Them phan tu vao queue
void enQueue(Queue *Q, int x){
	Q->rear++;
	Q->data[Q->rear] = x;
}

int front(Queue *Q){
	return Q->data[Q->front];
}

void deQueue(Queue *Q){
	Q->front++;	
}

int isEmpty(Queue Q){
	return (Q.front > Q.rear);
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

void add_edge(Graph *G, int u, int v){
	G->A[u][v] = 1;
//	G->A[v][u] = 1;
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
	makenull(&L);
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
		for (int j = 1; j <= G->n;j++){
			printf("%d ",G->A[i][j]);
		}
		printf("\n");
	}
//	printf("\n");
}

void topo_sort(Graph *G,List *L){
	int d[MaxN];
	int u;
	for (u = 1; u <= G->n; u++){
		d[u] = 0;
	}
	for (u = 1; u <= G->n; u++){
		d[u] = degree(G,u);
	}
	Queue Q;
	makenull_Queue(&Q);
	for(int u = 1; u<= G->n;u++){
		if (d[u]==0){
			enQueue(&Q,u);
		}
	}
	makenull(L);
	while(!isEmpty(Q)){
		int u = front(&Q);
		deQueue(&Q);
		push_back(L,u);
		
		for(int v = 1; v <= G->n; v++){
			if (G->A[u][v] != 0){
				d[v]--;
				if (d[v] == 0){
					enQueue(&Q,v);
				}
			}
		}
	}
}

int r[MaxN]; 
void rank(Graph *G){
	int d[MaxN];
	for (int u = 1; u<=G->n;u++){
		d[u] = degree(G,u);
	}
	
	List s1, s2;
	makenull(&s1);
	for (int u = 1; u <= G->n;u++){
		if (d[u] == 0){
			push_back(&s1,u);
		}
	}
	int k = 0;
	while(s1.size > 0){
		makenull(&s2);
		for (int i = 1; i<=s1.size;i++){
			int u = retrieve(&s1,i);
			r[u] = k;
			for(int v = 1; v <= G->n; v++){
				if (G->A[u][v] != 0){
					d[v]--;
					if (d[v] == 0){
						push_back(&s2,v);
					}
				}
			}
		}
		copyList(&s1,&s2);
		k++;
	}
}
int main(){
	Graph G;
	int n,m,u,v,i;
  	freopen("topo.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(i = 1;i <= m; i++){
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	for (i = 1; i <= n; i++){
		r[i] = -1;
	}
	printGraph(&G);
	rank(&G);
	for (i=1;i<=n;i++){
		printf("r[%d] = %d\n",i,r[i]);
	}
	return 0;
}

