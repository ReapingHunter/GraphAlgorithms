#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 7
#define INF 0XFFFF

typedef int undirectedAdjMatrix[MAX][MAX];
typedef int Set[MAX]; // bit-vector

typedef struct{
	int u;
	int v;
	int weight;
}EdgeType;

typedef struct{
	EdgeType edges[MAX * (MAX - 1) / 2];
	int edgeCount;
}EdgeList;

typedef struct{
	EdgeType edges[MAX * (MAX - 1) / 2];
	int edgeCount;
	int minCost;
}KruskalMST;

void populateGraph(undirectedAdjMatrix G);
KruskalMST kruskalAlgo(undirectedAdjMatrix G);
int isVisited(Set S);
void displayGraph(undirectedAdjMatrix G);
void displayKruskal(KruskalMST K);
void displayList(EdgeList L);

int main(){
	undirectedAdjMatrix A;
	KruskalMST B;
	populateGraph(A);
	B = kruskalAlgo(A);
	displayKruskal(B);
	return 0;
}

void populateGraph(undirectedAdjMatrix G){
	undirectedAdjMatrix graph = {INF,2,INF,4,INF,4,INF,
								 2,INF,7,1,3,8,5,
								 INF,7,INF,INF,10,INF,6,
								 4,1,INF,INF,2,INF,INF,
								 INF,3,10,2,INF,INF,INF,
								 4,8,INF,INF,INF,INF,1,
								 INF,5,6,INF,INF,1,INF};
								 
	undirectedAdjMatrix graph12 = {INF,2,INF,4,INF,5,INF,
								 2,INF,7,1,3,8,4,
								 INF,7,INF,INF,10,INF,6,
								 4,1,INF,INF,2,INF,INF,
								 INF,3,10,2,INF,INF,INF,
								 5,8,INF,INF,INF,INF,1,
								 INF,4,6,INF,INF,1,INF};

	undirectedAdjMatrix graph2 = {INF,7,INF,5,INF,INF,INF,
								  7,INF,8,9,7,INF,INF,
								  INF,8,INF,INF,5,INF,INF,
								  5,9,INF,INF,15,6,INF,
								  INF,7,5,15,INF,8,9,
								  INF,INF,INF,6,8,INF,11,
								  INF,INF,INF,INF,9,11,INF};
								  
	undirectedAdjMatrix graph3 = {INF,2,INF,1,4,INF,6,
								  2,INF,3,3,INF,7,4,
								  INF,3,INF,5,INF,8,INF,
								  1,3,5,INF,9,INF,INF,
								  4,INF,INF,9,INF,INF,INF,
								  INF,7,8,INF,INF,INF,INF,
								  6,4,INF,INF,INF,INF,INF};
	memcpy(G, graph12, sizeof(graph3));
}

void displayGraph(undirectedAdjMatrix G){
	int x, y;
	for(x = 0; x < MAX; x++){
		for(y = 0; y < MAX; y++){
			printf("%d ",G[x][y]);
		}
		printf("\n");
	}
}
KruskalMST kruskalAlgo(undirectedAdjMatrix G){
	KruskalMST K = {{}, 0, 0};
	EdgeList A = {{}, 0};
	Set S = {0};
	Set T = {0};
	int x, y, j, k, join = 0;
	int weight;
	for(x = 0; x < MAX; x++){ // Sorted List
		for(y = 0; y < MAX; y++){
			if(G[x][y] != INF){
				for(j = 0; j < A.edgeCount && (A.edges[j].u != y || A.edges[j].v != x); j++){}
				if(j == A.edgeCount){
					for(j = 0; j < A.edgeCount && A.edges[j].weight <= G[x][y]; j++){}
					if(j < A.edgeCount){
						for(k = A.edgeCount; k >= j; k--){
							A.edges[k+1] = A.edges[k];
						}
					}
					if(A.edgeCount < MAX * (MAX - 1) / 2){
						A.edges[j].u = x;
						A.edges[j].v = y;
						A.edges[j].weight = G[x][y];
						A.edgeCount += 1;
					}
					
				}
			}
		}
	}
	displayList(A);
	
	// Kruskal Proper
	for(j = 0; isVisited(S) == 0; j++){
		x = A.edges[j].u;
		y = A.edges[j].v;
		weight = A.edges[j].weight;
		if(S[x] == 0 && S[y] == 0 && T[x] == 1 && T[y] == 1){
			S[y] = 1;
		}
		if((S[x] != 1 || S[y] != 1)){
			K.edges[K.edgeCount].u = x;
			K.edges[K.edgeCount].v = y;
			K.edges[K.edgeCount++].weight = weight;
			K.minCost += weight;
			if(j == 0 || S[x] == 1 || S[y] == 1){ 
				S[x] = 1;
				S[y] = 1;
			} else{
				T[x] = 1;
				T[y] = 1;
			}
		}
		
	}
	return K;
}

int isVisited(Set S){
	int x;
	for(x = 0; x < MAX && S[x] == 1; x++){}
	return (x == MAX)? 1 : 0;
}
void displayKruskal(KruskalMST K){
	int x;
	printf("\n%-7s%s", "Edge", "Cost");
	printf("\n%-7s%s","----","----");
	for(x = 0; x < K.edgeCount; x++){
		printf("\n(%d,%d)%5d",K.edges[x].u, K.edges[x].v, K.edges[x].weight);
	}
	printf("\nMinimum Cost : %d",K.minCost);
}

void displayList(EdgeList L){
	int x;
	printf("\nEdge count :: %d",L.edgeCount);
	printf("\n%5s%10s%10s","Src","Dest","Weight");
	for(x = 0; x < L.edgeCount; x++){
		printf("\n%5c%10c%10d",'A' + L.edges[x].u, 'A' + L.edges[x].v,L.edges[x].weight);
	}
}
