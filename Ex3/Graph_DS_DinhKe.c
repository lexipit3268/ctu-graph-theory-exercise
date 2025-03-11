#include <stdio.h>
#define MaxM 100
#define MaxN 500
typedef struct{
	int data[MaxN];
	int size;
}List;

void makenull_List(List *L){
	L->size = 0;
}

void push_back(List *l,int x){
	l->data[l->size] = x;
	l->size++;
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
	push_back(&G->adj[x],y);
	push_back(&G->adj[y],x);
}

int degree(Graph *G, int x){
	return G->adj[x].size;
}

int adjacent(Graph *G, int x, int y){
	for (int i = 0; i < G->adj[x].size; i++){
		if (G->adj[x].data[i] == y){
			return 1;
		}
	}
	return 0;
}

void neighbours(Graph *G, int x){
	for (int i = 0; i < G->adj[x].size; i++){
		printf("%d ",G->adj[x].data[i]);
	}
}

void print_list(List *L) {
    for (int i = 0; i < L->size; i++) {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

// Ki?m tra k?t qu?
int main() {
    Graph G;

    // Kh?i t?o d? th? v?i 5 d?nh và 6 c?nh
    init_graph(&G, 5, 6);

    // Thêm các c?nh vào d? th?
    add_edge(&G, 1, 2);
    add_edge(&G, 1, 3);
    add_edge(&G, 1, 4);
    add_edge(&G, 2, 3);
    add_edge(&G, 2, 5);
    add_edge(&G, 4, 5);

    // In danh sách k? c?a t?ng d?nh
    printf("Adjacency lists:\n");
    for (int i = 1; i <= G.n; i++) {
        printf("Vertex %d: ", i);
        print_list(&G.adj[i]);
    }

    // Ki?m tra b?c c?a t?ng d?nh
    printf("\nDegrees of vertices:\n");
    for (int i = 1; i <= G.n; i++) {
        printf("Degree of vertex %d: %d\n", i, degree(&G, i));
    }

    // Ki?m tra tính k? c?a hai d?nh
    printf("\nAdjacency checks:\n");
    printf("Are vertices 1 and 2 adjacent? %s\n", adjacent(&G, 1, 2) ? "Yes" : "No");
    printf("Are vertices 1 and 5 adjacent? %s\n", adjacent(&G, 1, 5) ? "Yes" : "No");

    // Ki?m tra các d?nh k? c?a m?t d?nh (neighbours)
    printf("\nNeighbours of vertex 1: ");
    neighbours(&G, 1);
    printf("\nNeighbours of vertex 2: ");
    neighbours(&G, 2);

    return 0;
}


