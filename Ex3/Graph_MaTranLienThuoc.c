#include <stdio.h>
#define MaxN 100
#define MaxM 500
#define MaxLength 100
typedef int ElementType;
typedef struct{
	int A[MaxN][MaxM];
	int n,m;
}Graph;

typedef struct{
	ElementType data[MaxLength];
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

void init_graph(Graph *G, int n, int m){
	int i, j;
	G->n = n;
	G->m = m;
	for (i=1;i<=G->n;i++){
		for(j=1;j<=G->m;j++){
			G->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int e, int x, int y){
	G->A[x][e] = 1;
	G->A[y][e] = 1;
}

int degree(Graph *G, int x){
	int i, deg = 0;
	for (i = 0; i <= G->m ;i++){
		if (G->A[x][i] !=0 ){
			deg++;
		}
	}
	return deg;
}
int adjacent(Graph *G, int x, int y){
	int e;
	for (e = 1; e <= G->m; e++) {
		if (G->A[x][e] != 0){
			if (G->A[y][e] != 0){
				return 1;
			}
		}
	}
	return 0;
}

//void neighbours(Graph *G, int x){
//	printf("\n\n Neighbours %d = ",x);
//	for (int i = 1;i<=G->n;i++){
//		if (adjacent(G,x,i) && x!=i){
//			printf("%d ",i);
//		}
//	}
//}

void swap(int *a, int *b){
	int temp = *a;
	*a=*b;
	*b=temp;
}

void sortList(List *L) {
    for (int i = 0; i < L->size - 1; i++) {
        for (int j = i + 1; j < L->size; j++) {
            if (L->data[i] > L->data[j]) {
                swap(&L->data[i], &L->data[j]);
            }
        }
    }
}

List neighbors(Graph *G,int x){
	List L;
	makenull(&L);
	int e,j, mark[100];
	
	for ( e=1; e<=G->n; e++)
		mark[e] = 0;
	//e
	for(e=1;e<=G->m;e++){
		if(G->A[x][e] != 0)
		{
			for (j=1;j<=G->n;j++){
				if(G->A[j][e] != 0 &&  x != j && !mark[j]){
					push_back(&L,j);
					mark[j]=1;
				}
			}
		}
	}

	return L;
}

void printNeighbors(Graph *G){
	for (int i = 1; i <= G->n;i++){
		List L;
		makenull(&L);
		L = neighbors(G,i);
		printf("neighbours(%d) = ",i);
		for (int e = 0; e < L.size; e++){
			printf("%d ",L.data[e]);
		}
		printf("\n");
	}	
}
void printGraph(Graph *G){
	for (int i = 1; i <= G->n;i++){
		for (int j = 1; j <= G->n;j++){
			printf("%d ",G->A[i][j]);
		}
		printf("\n");
	}
}
int main() {
	int n, m, u, v;
	freopen("edge.txt","r",stdin);
	Graph G;
	scanf("%d %d",&n,&m);
	init_graph(&G, n, m); 
	for (int i = 1; i<=G.m;i++){
		scanf("%d%d",&u,&v);
		add_edge(&G,i,u,v);
	}

	int i, j;
	for (i = 1; i <= G.n; i++) {
		for (j = 1; j <= G.m; j++) {
			printf("%d ", G.A[i][j]);
		}
		printf("\n");
	}
//	for (i=1;i<=G.n;i++){
//		printf("deg(%d) = %d\n",i,degree(&G,i));
//	}
//	List L = neighbors(&G,1);
//	for (i=0;i<L.size;i++){
//		printf("%d ",L.data[i]);
//	}
	printNeighbors(&G);
	return 0;
}





