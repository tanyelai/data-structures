#include <stdio.h>
#include <stdlib.h>

#define MAX 32

struct n{
    int item[MAX];
    int top;
};
typedef struct n STACK;

int isFull(STACK*);
int isEmpty(STACK*);
void push(STACK*, int);
void pop(STACK*);
void top(STACK*, int*);
void initStack(STACK*);
void print(STACK*);
void BinaryConverter(STACK* , int, int, char *);

int main(){

    STACK *s = (STACK*)malloc(sizeof(STACK));
    initStack(s);
    int x; 
    int SIZE = 8;
    unsigned int u_i;
    printf("Enter an integer: ");
    scanf("%d", &x);
    if(x > 127 || x < -128){
        SIZE += 8;
        if (x > 32768 || x < -32768){
            SIZE += 8;
            if(x > 8388607 || x < -8388608 ){
                SIZE += 8;
            }
        }
    }
    u_i = (unsigned int)x;
    char binaryString[SIZE];
    BinaryConverter(s, u_i, SIZE, &binaryString[SIZE]);
}

void BinaryConverter(STACK* s, int x, int SIZE, char binaryString[])
{
    int i = 0;
        for(i=SIZE-1; i>=0; i--){
            binaryString[i] = x & 0x1;
            push(s, binaryString[i]);
            x = x >> 1;
        }
        printf("binary string: ");
        for(i=0; i <= SIZE-1; i++)
            printf("%d", binaryString[i]);
        print(s);
        while(s->top != 0)
           pop(s);
        printf("\n");
}

void print(STACK* s){
    printf("\nSTACK:\n");
    for(int i = s->top-1; i >= 0; i--){
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
        printf("The stack is full. You cannot add '%d' to the stack\n", x);
    else{
        s->item[s->top++] = x;
        printf("Value: %d is pushed to the stack.\n", s->item[s->top-1]);
    }
}

void pop(STACK* s){
    if(isEmpty(s))
        printf("The stack is empty.\n");
    else
        printf("The popped value: %d\n", s->item[--s->top]);
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