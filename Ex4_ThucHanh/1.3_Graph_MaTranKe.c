#include <stdio.h>
#define MaxV 20
#define MaxLength 20
#define MaxStack 40
typedef struct{
	int A[MaxV][MaxV];
	int n, m;
}Graph;

void init_Graph(Graph *G, int n){
	int i,j;
	G->n = n;
	G->m = 0;
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
//	G->m++;
}

//don do thi CO HUONG	
void add_edge_2(Graph *G, int x, int y){
	G->A[x][y] = 1;
}

//do thi vo huong (co the chua cung va da khuyen)
void add_edge_3(Graph *G, int x, int y){
	if (x==y){
		G->A[x][y] += 1;
	} else {
		G->A[x][y] += 1;
		G->A[y][x] += 1;
	}
}

void add_edge_4(Graph *G, int x, int y){
	G->A[x][y] += 1;
}

//kiem tra lang gieng 2 dinh
int adjacent(Graph *G,int x, int y){
	return (G->A[x][y] != 0);
}

//Tinh bac cua dinh x
int degree(Graph *G, int x){
	int deg = 0, i;
	for(i = 1; i<=G->n;i++){
		deg+= G->A[x][i];
	}
	return deg + G->A[x][x];
}

int degree2(Graph *G, int x){
	int deg = 0, i;
	for(i = 1; i<=G->n;i++){
		deg+= G->A[x][i] + G->A[i][x];
	}
	return deg;
}

int indegree(Graph *G, int x){
	int deg = 0, i;
	for (i=1;i<=G->n;i++){
		if (G->A[i][x] != 0){
			deg+=G->A[i][x];
		}
	}
	return deg;
}

int outdegree(Graph *G, int x){
	int deg = 0, i;
	for (i=1;i<=G->n;i++){
		if (G->A[x][i] != 0){
			deg+=G->A[x][i];
		}
	}
	return deg;
}

void maxdeg(Graph *G){
	int i, e, max = 1;
	for(e=1;e<G->n;e++){
		if (degree(G,e) > max){
			max = degree(G,e);
			i = e;
		}
	}
	printf("Max Degree: Dinh = %d, Bac = %d\n",i, max);
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
	int i;
	for(i=1;i<=G->n;i++){
		if(G->A[x][i] != 0){
			push_back(&L,i);
		}
	}
	sortList(&L);
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
	printf("\n");
}

int main(){
	Graph G;
	int n, m; //n dinh, m cung
	freopen("edge.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_Graph(&G,n);
	int e, u, v;
	for(e = 1;e <= m; e++){
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	printGraph(&G);
	for(e=1;e<=n;e++){
		printf("%d %d\n",e,degree(&G,e));
	}
	printf("\n");
	maxdeg(&G);
	printNeighbors(&G);
	return 0;
}
