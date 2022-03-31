#include <stdio.h>
#include <stdlib.h>


#define MAX 10

struct n{
    int item[MAX];
    int top;
};
typedef struct n STACK;

int isFull(STACK*);
int isEmpty(STACK*);
void push(STACK*, int);
int pop(STACK*);
void top(STACK*, int*);
void initStack(STACK*);
void print(STACK*);

int main(){

    STACK *s = (STACK*)malloc(sizeof(STACK));
    initStack(s);
    int x;
    push(s, 5);
    push(s, 10);
    push(s, 15);
    push(s, 20);
    push(s, 20);
    push(s, 20);
    push(s, 20);
    x = pop(s);
    printf("%d\n",x);
    x = pop(s);
    printf("%d\n",x);

    print(s);
}

void print(STACK* s){
    printf("STACK:\n");
    for(int i = 0; i < s->top; i++){
        printf("|%d|\n", s->item[i]);
    }
}

void initStack(STACK* s){
    s->top = 0;
}

int isFull(STACK* s){
    if(s->top == MAX)
        return 1;
    else
        return 0;
}

int isEmpty(STACK* s){
    if(s->top == 0)
        return 1;
    else
        return 0;
}

void push(STACK* s, int x){
    if(isFull(s))
        printf("The stack is full.\n");
    else
        s->item[s->top++] = x;
}

int pop(STACK* s){
    if(isEmpty(s)){
        printf("The stack is empty.\n");
        return 0;
    }
    else
        return s->item[--s->top];
}

void top(STACK* s, int *x){
    int adr;
    if (isEmpty(s))
        printf("The stack is empty.");
    else{
        adr = s->top-1;
        *x = s->item[adr];
    }

}