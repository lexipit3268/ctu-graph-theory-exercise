#include <stdio.h>
#define MaxM 100
#define MaxN 500
typedef int ElementType;
typedef struct{
	ElementType data[MaxN];
	int size;
}List;

void makenull_List(List *L){
	L->size = 0;
}

void push_back(List *l,int x){
	l->data[l->size] = x;
	l->size++;
}

int element_at(List *L, int i){
	return L->data[i-1];
}
//Graphhhhhh
typedef struct{
	List adj[MaxM];
	int n,m;
}Graph;

void init_graph(Graph *G, int n, int m){
	G->n = n;
	G->m = m;
	for (int i = 1; i <= G->n;i++){
		makenull_List(&G->adj[i]);
	}
}

void add_edge(Graph *G, int x, int y){
	if (x==y){
		push_back(&G->adj[x],y);
	} else {
		push_back(&G->adj[x],y);
		push_back(&G->adj[y],x);
	}
}

//co huong co the chua khuyen
void add_edge_2(Graph *G, int x, int y){
	push_back(&G->adj[x],y);
}

int degree(Graph *G, int x){
	return G->adj[x].size;
}

int adjacent(Graph *G, int x, int y){
	for (int i = 0; i < G->adj[x].size; i++){
		if (G->adj[x].data[i] == y){
			return 1;
		}
//		if (element_at(&G->adj[x],i) == y) return 1;
	}
	return 0;
}

//void neighbours(Graph *G, int x){
//	for (int i = 0; i < G->adj[x].size; i++){
//		printf("%d \n",G->adj[x].data[i]);
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
	makenull_List(&L);
	int i;
	for(i=0;i < G->adj[x].size;i++){
		push_back(&L,G->adj[x].data[i]);
	}
	sortList(&L);
	return L;
}

void printNeighbors(Graph *G){
	for (int i = 1; i <= G->n;i++){
		List L;
		makenull_List(&L);
		L = neighbors(G,i);
		printf("neighbours(%d) = ",i);
		for (int e = 0; e < L.size; e++){
			printf("%d ",L.data[e]);
		}
		printf("\n");
	}	
}

void print_list(List *L) {
    for (int i = 0; i < L->size; i++) {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}


int main() {
    Graph G;
	freopen("edge.txt","r",stdin);
	int m, n, u, v;
	scanf("%d%d",&n,&m);
    init_graph(&G, n, m);
	
	for(int i = 1; i<=m;i++){
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}

//    init_graph(&G, 5, 7);
//
//
//    add_edge_2(&G, 1, 2);
//    add_edge_2(&G, 1, 3);
//    add_edge_2(&G, 1, 4);
//    add_edge_2(&G, 2, 3);
//    add_edge_2(&G, 2, 5);
//    add_edge_2(&G, 4, 5);
//    add_edge_2(&G, 4, 4);
	
	printNeighbors(&G);
	for (int i = 1; i <= G.n;i++){
		printf("deg(%d) = %d\n",i,degree(&G,i));
	}
    return 0;
}


