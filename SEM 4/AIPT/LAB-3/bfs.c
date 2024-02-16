#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure to represent a queue
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Function to create an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    if (queue->rear == -1)
        return 1;
    else
        return 0;
}

// Function to add an element to the queue
void enqueue(Queue* queue, int value) {
    if (queue->rear == MAX_SIZE - 1)
        printf("Queue is full!");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

// Function to remove an element from the queue
int dequeue(Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Queue is empty!");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = -1;
            queue->rear = -1;
        }
    }
    return item;
}

// Function to perform BFS traversal
void BFS(int adjacencyMatrix[][MAX_SIZE], int vertices, int startVertex) {
    int visited[MAX_SIZE] = {0};
    Queue* queue = createQueue();

    visited[startVertex] = 1;
    printf("BFS traversal: %d ", startVertex);

    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);

        for (int i = 0; i < vertices; i++) {
            if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                printf("%d ", i);
                enqueue(queue, i);
            }
        }
    }

    free(queue);
}

int main() {
    int vertices, startVertex;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    int adjacencyMatrix[MAX_SIZE][MAX_SIZE];

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }

    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);

    BFS(adjacencyMatrix, vertices, startVertex);

    return 0;
}
