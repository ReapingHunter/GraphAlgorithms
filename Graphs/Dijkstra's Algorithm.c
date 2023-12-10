#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 5
#define INFINITY 0XFFFF

typedef int undirectedAdjMatrix[MAX][MAX]; // INFINITY IF NO EDGE
typedef short int Set; // Computer Word Implementation of Set

// Structure definition of Shortest distance from one vertex to all
typedef struct{
    int distance;
    int prevVertex;
}ShortestDistance[MAX]; 

void populateGraph(undirectedAdjMatrix G);
void displayGraph(undirectedAdjMatrix G);
ShortestDistance *dijkstraAlgo(undirectedAdjMatrix G, int startVertex);
void displayDijkstra(ShortestDistance D);

int main(){
    undirectedAdjMatrix A;
    ShortestDistance *D;
    populateGraph(A);
    D = dijkstraAlgo(A, 0);
    displayDijkstra(*D);
    return 0;
}

void populateGraph(undirectedAdjMatrix G){
    undirectedAdjMatrix graph = {INFINITY, 6, INFINITY, 1, INFINITY,
                                 6, INFINITY, 5, 2, 2,
                                 INFINITY, 5, INFINITY, INFINITY, 5,
                                 1, 2, INFINITY, INFINITY, 1,
                                 INFINITY, 2, 5, 1, INFINITY};
    memcpy(G, graph, sizeof(graph));
}
/* Dijkstra's Algorithm
	
	OBJECTIVE:
	Find the shortest distance between any two vertices in a graph
	
	ALGORITHM:
	Step 0:	Let vertex x be the starting vertex
			Let the distance from vertex x to itself be ZERO
			Let the distance from vertex x to any vertex except for itself be UNKNOWN and therefore, INFINITY
	
	Step 1: VISIT the VERTEX with the SMALLEST KNOWN DISTANCE  and examine its ADJACENT VERTICES. For the first iteration, visit vertex x.
	Step 2:	For the current vertex, calculate the distance of each ADJACENT VERTICES from the STARTING VERTEX
		Step 2B: If the CALCULATED DISTANCE of a vertex is less than the KNOWN DISTANCE, update the SHORTEST DISTANCE
		Step 2C: UPDATE the PREVIOUS VERTEX for each of the UPDATED DISTANCES
	Step 3:	ADD the CURRENT VERTEX to the SET/LIST of VISITED VERTICES
	Step 4: REPEAT Steps 1 to 3 until ALL VERTICES have been VISITED

*/
ShortestDistance *dijkstraAlgo(undirectedAdjMatrix G, int startVertex){
	ShortestDistance *D;
	Set visited = 0;
	int x;
	int y;
	int minDistance = 0;
	int minVertex;
	int min = INFINITY;
	int len = (1 << MAX) - 1;
	D = (ShortestDistance*)malloc(sizeof(ShortestDistance));
	if(D != NULL){
		for(x = 0; x < MAX; x++){
			(*D)[x].distance = (x == startVertex)? 0 : INFINITY;
		}
		for(x = startVertex; visited != len; x = minVertex){
			visited |= 1 << x;
			for(y = 0; y < MAX; y++){
				if(G[x][y] + minDistance < (*D)[y].distance){
					(*D)[y].distance = G[x][y] + minDistance;
					(*D)[y].prevVertex = x;
				}
				if(min > (*D)[y].distance && (visited & 1 << y) == 0){
					min = (*D)[y].distance;
					minVertex = y;
				}
			}
			minDistance = min;
			min = INFINITY;
			

		}
	}
    return D;
}

void displayGraph(undirectedAdjMatrix G){
    int x;
    int y;
    for(x = 0; x < MAX; x++){
        for(y = 0; y < MAX; y++){
            printf("%d ",G[x][y]);
        }
        printf("\n");
    }
}

void displayDijkstra(ShortestDistance D){
    int x;
    printf("\n%-10s%-10s%-10s", "Vertex", "Distance", "Previous");
 
    //Write code here
    for(x = 0; x < MAX; x++){
        printf("\n%-10c%-10d%-10c",'A' + x, D[x].distance, 'A' + D[x].prevVertex);
    }
    
}
