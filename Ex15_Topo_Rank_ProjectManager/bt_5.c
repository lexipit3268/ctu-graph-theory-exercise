#include <stdio.h>
#define MAX_SIZE 20
#define MaxV 100
#define MaxLength 100
#define MaxN 100
#define aVC -999
#define dVC 999
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

int max(int a, int b){
	return (a>b)? a:b;
}
int min(int a, int b){
	return (a<b)?a:b;
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
int d[MaxN];
int main(){
	Graph G;
	int n,u,x,v,i;
  	freopen("project.txt","r",stdin);
	scanf("%d",&n);
	init_graph(&G,n+2);
	int alpha = n + 1, beta = n + 2;
	d[alpha] = 0;
	for(u = 1;u <= n; u++){
		scanf("%d",&d[u]);
		do {
			scanf("%d",&x);
			if ( x > 0){
				add_edge(&G,x,u);
			} 
		}while (x > 0);
	}
	
	for (u = 1; u <= n; u++){
		int deg_neg = 0;
		for (x = 1; x<=n;x++){
			if (G.A[x][u] > 0){
				deg_neg++;
			}
		}
		if (deg_neg == 0){
			//ko co bac vao, noi voi alpha
			add_edge(&G,alpha,u);
		}
	}
	
	for (u=1;u<=n;u++){
		int deg_pos = 0;
		for (v = 1; v<=n;v++){
			if (G.A[u][v] > 0){
				deg_pos++;
			}
		}
		if (deg_pos == 0){
			//ko co bac ra, noi voi beta
			add_edge(&G,u,beta);
		}
	}
	
	List L;
	topo_sort(&G,&L);
	
	int t[MaxN];
	t[alpha] = 0;
	for(i=2;i<=L.size;i++){
		int u = retrieve(&L,i);
		t[u] = aVC;
		for (x=1;x<=G.n;x++){
			if(G.A[x][u] > 0){
				t[u] = max(t[u],t[x] + d[x]);
			}
		}
	}
	
	int T[MaxN];
	T[beta] = t[beta];
	for (i=L.size-1;i>=1;i--){
		int u = retrieve(&L,i);
		T[u] = dVC;
		for (v = 1; v<=G.n;v++){
			if (G.A[u][v] > 0){
				T[u] = min (T[u], T[v] - d[u]);
			}
		}
	}
	for (int i = 1; i<=n;i++){
		printf("%d %d\n",t[i],T[i]);
	}
	return 0;
}

