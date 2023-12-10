#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 9

typedef int AdjMatrix[MAX][MAX];
typedef short int Set;

typedef struct{
	int arr[MAX];
	int top;
}Stack;

typedef struct{
	int arr[MAX];
	int front;
	int rear;
}Queue;

void populateAdjMatrix(AdjMatrix G);

void initStack(Stack *S);
void initQueue(Queue *Q);
void push(Stack *S, int elem);
int pop(Stack *S);
void enqueue(Queue *Q, int elem);
int dequeue(Queue *Q);

void dfs(AdjMatrix G, int start);
void bfs(AdjMatrix G, int start);

int main(){
	AdjMatrix A;
	populateAdjMatrix(A);
	dfs(A, 5);
	printf("\n");
	bfs(A, 5);
	return 0;
}

void populateAdjMatrix(AdjMatrix G){
	AdjMatrix graph = {0,1,0,0,0,0,0,0,1,
					   1,0,0,0,0,0,0,0,0,
					   0,0,0,1,1,1,0,0,1,
					   0,0,1,0,0,0,0,0,0,
					   0,0,1,0,0,0,0,1,0,
					   0,0,1,0,0,0,1,0,0,
					   0,0,0,0,0,1,0,1,1,
					   0,0,0,0,1,0,1,0,0,
					   1,0,1,0,0,0,1,0,0};
	memcpy(G, graph, sizeof(graph));
}

void initStack(Stack *S){
	S->top = -1;
}

void initQueue(Queue *Q){
	Q->front = 0;
	Q->rear = (Q->front - 1) % MAX;
}

void push(Stack *S, int elem){
	S->arr[++S->top] = elem;	
}

int pop(Stack *S){
	return S->arr[S->top--];
}

void enqueue(Queue *Q, int elem){
	Q->rear = (Q->rear + 1) % MAX;
	Q->arr[Q->rear] = elem;
}

int dequeue(Queue *Q){
	Q->front = (Q->front + 1) % MAX;
	return Q->arr[Q->front - 1 % MAX];
}

void dfs(AdjMatrix G, int start){
	Stack S;
	Set visited = 0;
	int x;
	int y;
	int len = (1 << MAX) - 1;
	initStack(&S);
	for(x = start; visited != len; x = pop(&S)){
		if((visited & 1 << x) == 0){
			for(y = MAX - 1; y > -1; y--){
				if(G[x][y] == 1 && (visited & 1 << y) == 0){
					push(&S, y);
				}
			}
			printf("%c ",'A' + x);
			visited |= 1 << x;
		}
	}
}

void bfs(AdjMatrix G, int start){
	Queue Q;
	Set visited = 0;
	int x;
	int y;
	int len = (1 << MAX) - 1;
	initQueue(&Q);
	for(x = start; visited != len; x = dequeue(&Q)){
		if((visited & 1 << x) == 0){
			for(y = 0; y < MAX; y++){
				if(G[x][y] == 1 && (visited & 1 << y) == 0){
					enqueue(&Q, y);
				}
			}
			printf("%c ",'A' + x);
			visited |= 1 << x;
		}	
	}
}
