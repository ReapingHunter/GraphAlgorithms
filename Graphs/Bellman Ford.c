#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 7
#define INF 0xffff

typedef int adjMatrix[MAX][MAX];

typedef struct{
	int src, dest;
	int weight;
}EdgeList;

typedef struct{
	EdgeList edges[MAX * (MAX - 1) / 2];
	int distance[MAX];
	int edgeCount;
}BellmanPath;

void populateGraph(adjMatrix G);
void initBellman(BellmanPath *B, int startVertex);
BellmanPath bellmanFordAlgo(adjMatrix G, int startVertex);
void displayBellmanFord(BellmanPath B);

int main(){
	adjMatrix A;
	BellmanPath B;
	populateGraph(A);
	B = bellmanFordAlgo(A, 0);
	return 0;
}

void populateGraph(adjMatrix G){
	int graph[] = {INF,6,5,5,INF,INF,INF,
				  INF,INF,INF,INF,-1,INF,INF,
				  INF,-2,INF,INF,1,INF,INF,
				  INF,INF,-2,INF,INF,-1,INF,
				  INF,INF,INF,INF,INF,INF,3,
				  INF,INF,INF,INF,INF,INF,3,
				  INF,INF,INF,INF,INF,INF,INF};
	memcpy(G, graph, sizeof(graph));
}

void initBellman(BellmanPath *B, int startVertex){
	int x;
	B->edgeCount = 0;
	for(x = 0; x < MAX; x++){
		B->distance[x] = (x == startVertex)? 0 : INF;
	}
}

BellmanPath bellmanFordAlgo(adjMatrix G, int startVertex){
	BellmanPath B;
	int k;
	int x;
	int y;
	int changed = 1;
//	int u;
//	int v;
	initBellman(&B, startVertex);
//	for(u = 0; u < MAX; u++){ // PopulateList
//		for(v = 0; v < MAX; v++){
//			if(G[u][v] != INF){
//				B.edges[B.edgeCount].src = u;
//				B.edges[B.edgeCount].dest = v;
//				B.edges[B.edgeCount++].weight = G[u][v];
//			}
//		}
//	}
	displayBellmanFord(B);
	for(k = 0; k < MAX - 1 && changed == 1; k++){
		changed = 0;
		for(x = 0; x < MAX; x++){
			for(y = 0; y < MAX; y++){
				if(B.distance[y] > B.distance[x] + G[x][y]){
					B.distance[y] = B.distance[x] + G[x][y];
					changed = 1;
				}
			}
		}
		displayBellmanFord(B);
	}
		
	return B;
}

void displayBellmanFord(BellmanPath B){
	int x;
    printf("\n%-10s%-10s%", "Vertex", "Distance");
 
    //Write code here
    for(x = 0; x < MAX; x++){
        printf("\n%-10c%-10d",'A' + x, B.distance[x]);
    }
}

