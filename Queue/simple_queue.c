#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct n{
    int item[MAX];
    int front;
    int rear;
};
typedef struct n queue;

int isFull(queue*);
int isEmpty(queue*);
void enqueue(queue*, int);
void dequeue(queue*, int*);
void initQueue(queue*);
void print(queue*);

int main(){

    queue *q = (queue*)malloc(sizeof(queue));
    initQueue(q);

    int dequeued_element;
    enqueue(q, 5);
    enqueue(q, 10);
    print(q);
    enqueue(q, 20);
    dequeue(q, &dequeued_element);
    printf("dequeued element: %d", dequeued_element);
    print(q);


    return 0;
}

void initQueue(queue *q){
    q->front = -1;
    q->rear = -1;
}

void print(queue* q){
    printf("QUEUE:\n");
    for(int i = q->front+1; i < q->rear; i++){
        printf("|%d|-", q->item[i]);
    }
}

int isEmpty(queue *q){
    if(q->front == -1)
        return 1;
    else
        return 0;
}

int isFull(queue *q){
    if(q->rear == MAX)
        return 1;
    else
        return 0;
}

void enqueue(queue *q, int value){
    if(isFull(q))
        printf("The queue is full. You cannot add '%d' to the queue\n", value);
    else{
        q->rear++;
        q->item[q->rear] = value;
        }
}

void dequeue(queue *q, int *x){
    if(isEmpty(q))
        printf("The queue is empty.\n");
    else
        *x = q->item[++q->front];
}