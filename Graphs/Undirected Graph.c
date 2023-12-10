#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 5
#define INF 0XFFFF

typedef char vertex;
typedef short int Set; // Computer Word Implementation of Set

/* Undirected AdjList Structure */
typedef struct{
	vertex tail;
	vertex head;
	int weight;
}EdgeType;

typedef struct{
	vertex adjVertex;
	int weight;
}AdjType;

typedef struct adjNode{
	AdjType info;
	struct adjNode *link;
}*AdjList;

typedef struct{
	AdjList head[MAX];
	int edgeCount;
}UndirectedAdjList;

/* Dijkstra's Algorithm Structure*/
typedef struct{
    int distance;
    int prevVertex;
}DijkstraSP[MAX];

/* Prim's Algorithm Structure */
typedef struct{
	EdgeType edges[MAX];
	int edgeCount;
	int minCost;
}PrimMST;

/* Initialize, Populate and Display */
void initUndirectedAdjList(UndirectedAdjList *L);
UndirectedAdjList populateAdjList();
void displayAdjList(UndirectedAdjList L);

/* Graph Traversals */
void dfs(UndirectedAdjList L);
void bfs(UndirectedAdjList L);

/* Dijkstra's Algorithm Functions */
DijkstraSP *dijkstraAlgo(UndirectedAdjList L, int startVertex);
void displayShortestPath(DijkstraSP D);

/* Prim's Algorithm Functions */
PrimMST primAlgo(UndirectedAdjList L, int startVertex);
void displayPrimMST(PrimMST T);

int main(){
	UndirectedAdjList graph;
	DijkstraSP *path;
	PrimMST tree;
	printf("THE UNDIRECTED WEIGHTED GRAPH IMPLEMENTED USING ADJACENCY LIST");
	graph = populateAdjList();
	displayAdjList(graph);
	path = dijkstraAlgo(graph, 0);
	displayShortestPath(*path);
	tree = primAlgo(graph, 3);
	displayPrimMST(tree);
	return 0;
}

/* Initialize, Populate and Display */
void initUndirectedAdjList(UndirectedAdjList *L){
	int x;
	for(x = 0; x < MAX; x++){
		L->head[x] = NULL;
	}
	L->edgeCount = 0;
}

UndirectedAdjList populateAdjList(){
	UndirectedAdjList A;
	int x;
	int y;
	int other;
	AdjList *trav, node;
	const int COUNT = 7;
	EdgeType data[] = {{'B', 'D', 2}, {'A', 'D', 1}, {'C', 'B', 5},
					  {'E', 'C', 5}, {'D', 'E', 1}, {'B', 'E', 2},
					  {'A', 'B', 6}};
	initUndirectedAdjList(&A);
	for(x = 0; x < MAX; x++){
		for(y = 0; y < COUNT; y++){
			if(data[y].tail == 'A' + x){
				for(trav = &A.head[x]; *trav != NULL && (*trav)->info.adjVertex < data[y].head; trav = &(*trav)->link){}
				node = (AdjList)malloc(sizeof(struct adjNode));
				if(node != NULL){
					node->info.adjVertex = data[y].head;
					node->info.weight = data[y].weight;
					node->link = *trav;
					*trav = node;
				}
				
				other = data[y].head - 'A';
				for(trav = &A.head[other]; *trav != NULL && (*trav)->info.adjVertex < data[y].tail; trav = &(*trav)->link){}
				node = (AdjList)malloc(sizeof(struct adjNode));
				if(node != NULL){
					node->info.adjVertex = data[y].tail;
					node->info.weight = data[y].weight;
					node->link = *trav;
					*trav = node;
				}
				A.edgeCount++;
			}
		}
	}
	return A;
}

void displayAdjList(UndirectedAdjList L){
	int x;
	AdjList temp;
		
	printf("\n\nThe Adjacency List ::");
	printf("\n%-8s", "VERTEX");
	printf("%-20s", "Adjacent vertices");
	printf("\n%-8s", "------");
	printf("%-20s", "-----------------");
	for(x = 0; x < MAX; x++){
		printf("\n%c :: ",'A' + x);
		for(temp = L.head[x]; temp != NULL; temp = temp->link){
			printf("%4c(%d)",temp->info.adjVertex, temp->info.weight);
		}
	}
}

/* Dijkstra's Algorithm Functions */
DijkstraSP *dijkstraAlgo(UndirectedAdjList L, int startVertex){
	DijkstraSP *D;
	Set visited = 0;
	int len = (1 << MAX) - 1;
	int x;
	int y;
	AdjList trav;
	int min = INF;
	int minVertex;
	int minDistance = 0;
	D = (DijkstraSP*)malloc(sizeof(DijkstraSP));
	if(D != NULL){
		for(x = 0; x < MAX; x++){
			(*D)[x].distance = (x == startVertex)? 0 : INF;
		}
		for(x = startVertex; visited != len; x = minVertex){
			visited |= 1 << x;
			for(trav = L.head[x]; trav != NULL; trav = trav->link){
				y = trav->info.adjVertex - 'A';
				if(trav->info.weight + minDistance < (*D)[y].distance){
					(*D)[y].distance = trav->info.weight + minDistance;
					(*D)[y].prevVertex = x;
				}
				if(min > (*D)[y].distance && (visited & 1 << y) == 0){
					min = (*D)[y].distance;
					minVertex = y;
				}
			}
			minDistance = min;
			min = INF;
		}
	}
	return D;
}

void displayShortestPath(DijkstraSP D){
	int x;
	printf("\n\nDijkstra's Algorithm ::");
	printf("\n%-8s", "VERTEX");
	printf("%-12s", "DISTANCE");
	printf("%-12s", "PREVIOUS");
    printf("\n%-8s%-12s%-12s", "------", "--------", "--------");
 
    //Write code here
    for(x = 0; x < MAX; x++){
        printf("\n%-8c%-12d%-12c",'A' + x, D[x].distance, 'A' + D[x].prevVertex);
    }
}

/* Prim's Algorithm Functions */
PrimMST primAlgo(UndirectedAdjList L, int startVertex){
	PrimMST P;
	Set visited = 0;
	AdjList trav;
	int x, y, z, j, k;
	int len = (1 << MAX) - 1;
	int min = INF;
	P.edgeCount = 0;
	P.minCost = 0;
	printf("\n\nPrim's Algorithm ::");
	printf("\nStart vertex is %d", startVertex);
	for(x = startVertex; visited != len; x = k){
		visited |= 1 << x;
		for(y = 0; y < MAX; y++){
			if((visited & 1 << y) != 0){
				for(trav = L.head[y]; trav != NULL; trav = trav->link){
					z = trav->info.adjVertex - 'A';
					if(trav->info.weight < min && (visited & 1 << z) == 0){
						min = trav->info.weight;
						j = y;
						k = z;
					}
				}
			}
		}
		if(min != INF){
			P.minCost += min;
			P.edges[P.edgeCount].tail = j;
			P.edges[P.edgeCount].head = k;
			P.edges[P.edgeCount++].weight = min;
			min = INF;
		}
	}
	return P;
}

void displayPrimMST(PrimMST T){
	int x;
	printf("\n%-7s%s", "Edge", "Cost");
	printf("\n%-7s%s","----","----");
 
    //Write code here
    for(x = 0; x < T.edgeCount; x++){
    	printf("\n(%d,%d)%5d",T.edges[x].tail, T.edges[x].head, T.edges[x].weight);
	}
	printf("\nMinimum Cost : %d",T.minCost);
}
