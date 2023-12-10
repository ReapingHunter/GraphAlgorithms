#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 4
#define INF 0xffff

typedef int adjMatrix[MAX][MAX];

void populateGraph(adjMatrix G);
adjMatrix *floydWarshallAlgo(adjMatrix G);
void displayMatrix(adjMatrix G);
int main(){
	adjMatrix A;
	adjMatrix *B;
	populateGraph(A);
	B = floydWarshallAlgo(A);
	return 0;
}

void populateGraph(adjMatrix G){
	int data[] = {0,3,INF,7,
				  8,0,2,INF,
				  5,INF,0,1,
				  2,INF,INF,0};
	memcpy(G, data, sizeof(data));
}

adjMatrix *floydWarshallAlgo(adjMatrix G){
	adjMatrix *F;
	int k;
	int x;
	int y;
	F = (adjMatrix*)malloc(sizeof(adjMatrix));
	for(x = 0; x < MAX; x++){
		for(y = 0; y < MAX; y++){
			(*F)[x][y] = G[x][y];
		}
	}
	for(k = 0; k < MAX; k++){
		for(x = 0; x < MAX; x++){
			for(y = 0; y < MAX; y++){
				if((*F)[x][y] > (*F)[x][k] + (*F)[k][y]){
					(*F)[x][y] = (*F)[x][k] + (*F)[k][y];
				}
			}
		}
		printf("\n");
		displayMatrix(*F);
	}
	return F;
}

void displayMatrix(adjMatrix G){
	int x;
	int y;
	for(x = 0; x < MAX; x++){
		for(y = 0; y < MAX; y++){
			printf("%d ",G[x][y]);
		}
		printf("\n");
	}
}

