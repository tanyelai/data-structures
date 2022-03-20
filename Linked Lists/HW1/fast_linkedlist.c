#include <stdio.h>
#include <stdlib.h>

struct n{
    int data;
    struct n * next_row;
    struct n * next_col;
};
typedef struct n node;


int count_dimension(int);
void print(node *);
//void search(node*, int);
node* initialize_first_stage(node*, int, int); // creating ftwintirst linked list
node* insert(node*, int);
node* delete(node*, int);
node* createOtherDimensions(node*, int);

int main(){

    int n, dim, i, new_element;
    printf("Enter how many elements you will enter");
    scanf("%d", &n);

    dim = count_dimension(n) + 2; // this is the amount of stages for first initialization.

    int* array = (int*)malloc(dim* sizeof(int));
    node* head[dim]; //same for doing null every i in head[i];
    for(i=0; i<dim-1; i++){
        head[i] = (node*)malloc(sizeof(node));
        head[i] -> next_row = NULL;
        if( i+1 == dim-1)
            head[i+1] -> next_row = NULL;
        head[i] -> next_col = head[i+1];
        // we will assume it's a special array of nodes to point stages
    }
    

    for (i=0; i<n; i++){
        printf("enter new element: ");
        scanf("%d", &new_element);
        array[i] = new_element;
        head[0] = initialize_first_stage(head[0], new_element, dim);
    }

    



}

int count_dimension(int n){

    if((n+1)/2 == 1)
        return 1;

    return count_dimension((n+1)/2) + 1;
}

int pick_new_elements(int n, int arr){

}

/*
void print(node*head){
    int i = 0;
    while(head != NULL){ // we will travel until we reach the NULL at the end
        i++;
        printf("%d. element: %d\n", i, head -> data);
        head = head -> next;
    }
}*/

node * initialize_first_stage(node*head, int new_element, int dim){

    node* current = head;
    while(current -> next_row != NULL && new_element >= current -> next_row -> data)
        current = current -> next_row;

    // we create array of nodes for next stages to reach later on 
    // we bound all temp nodes as columns
    int i;
    node* temp[dim];
    for(i=0; i<dim-1; i++){
        temp[i] = (node*)malloc(sizeof(node));
        if(i+1 == dim-1)
            temp[i+1] = (node*)malloc(sizeof(node));
        temp[i] -> next_col = temp[i+1];
    }
    
    // we initialize first dimension which is 0 for the program
    temp[0] -> next_row = current -> next_row;
    temp[0] -> data = new_element;
    current -> next_row = temp[0];
    return head;
    
}

node * initialize_new_stages(int i, node* head[i], int new_element, int dim){
    node* current = head;
    while(current -> next_row != NULL && new_element >= current -> next_row -> data)
        current = current -> next_row;
    
    
    
    return initialize_new_stages(i++, head[i], new_element, dim);
}