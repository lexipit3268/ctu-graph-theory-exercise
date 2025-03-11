#include <stdio.h>
#define MAXN 100
#define NO_EDGE 0
#define oo 999
typedef struct{
	int C[MAXN][MAXN];
	int F[MAXN][MAXN];
	int n, m;
}Graph;

void init_graph(Graph *G, int n){
	G->n = n;
	G->m = 0;
	for (int i = 1; i <= G->n; i++){
		for (int j = 1; j <= G->n; j++){
			G->C[i][j] = 0;
		}
	}
}
typedef struct{
	int dir;
	int p;
	int sigma;
}Label;

Label labels[MAXN];

typedef struct{
	int rear,front;
	int data[MAXN];
}Queue;

void makenull_Queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

int emptyQueue(Queue *Q){
	return Q->front > Q->rear;
}

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

int min(int a, int b){
	return (a < b)? a:b;
}
void init_flow(Graph *G){
	for (int i = 1; i <= G->n; i++){
		for (int j = 1; j <= G->n; j++){
			G->F[i][j] = 0;
		}
	}
}
int FordFulkerson(Graph *G, int s, int t){
	init_flow(G);
	int max_flow = 0;
	Queue Q;
	do{

		//xoa nhan cu
		for(int u  = 1; u<= G->n; u++)
			labels[u].dir  = 0;
		//Gan nhan s: (+,s,oo);
		labels[s].dir = +1;
		labels[s].p = s;
		labels[s].sigma = oo;
		makenull_Queue(&Q);
		enQueue(&Q,s);		
		
		int found = 0;
		while(!emptyQueue(&Q)){
			int u = front(&Q); deQueue(&Q);
			for(int v = 1; v <= G->n; v++){
				if (G->C[u][v] != NO_EDGE && labels[v].dir == 0 && G->F[u][v] < G->C[u][v]){
					labels[v].dir = +1;
					labels[v].p = u;
					labels[v].sigma = min(labels[u].sigma, G->C[u][v] - G->F[u][v]);
					enQueue(&Q,v);
				}
			}
			
			for(int x = 1; x <= G->n; x++){
				if(G->C[x][u] != NO_EDGE && labels[x].dir == 0 && G->F[x][u]  > 0){
					labels[x].dir = -1;
					labels[x].p = u;
					labels[x].sigma = min(labels[u].sigma, G->F[x][u]);
					enQueue(&Q,x);
				}
			}
			if(labels[t].dir != 0){
				found = 1;
				break;
			}
		}
		if (found == 1){
			int sigma = labels[t].sigma;
			int u = t;
			while (u != s){
				int p = labels[u].p;
				if (labels[u].dir > 0){
					G->F[p][u] += sigma;
				} else {
					G->F[p][u] -= sigma;
				}
				u = p;
			}
			max_flow += sigma;
		} else 
			break;
	}while(1);
	return max_flow;
}

int main(){
	Graph G; 
	int n, m, u, v, e, c;
	freopen("edge.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	
	for(e = 0; e < m; e++){
		scanf("%d%d%d",&u,&v,&c);
		G.C[u][v] = c;
	}
	
	int max_flow = FordFulkerson(&G, 1, n);
	printf("Max flow: %d\n",max_flow);
	
	printf("S: ");
	for (u = 1; u <= n; u++){
		if(labels[u].dir != 0){
			printf("%d ",u);
		}
	}
	printf("\n");
	printf("T: ");
	for (u = 1; u <= n; u++){
		if(labels[u].dir == 0){
			printf("%d ",u);
		}
	}
	printf("\n");
	return 0;
}
