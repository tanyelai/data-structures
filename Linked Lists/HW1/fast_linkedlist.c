#include <stdio.h>
#include <stdlib.h>

struct n{
    int data;
    struct n * next_row;
    struct n * next_col;
};
typedef struct n node;

// ***********************************************************************************************************
// important to not get confused -> "next_row" is not for up-down, it basically points next element of same row
// row can be considered as same linked list (same stage)
// column can be considered as helper pointer to be able to reach next linked list (next stage)
// "next_col" points connected element of next stage
// ***********************************************************************************************************


int count_dimension(int);
void print(node *);
//void search(node*, int);
node* initialize(node*, int); // creating ftwintirst linked list
node* insert(node*, int);
node* delete(node*, int);
node* createNewDimensions(node*, int);

int main(){

    int n, dim, i, new_element;
    printf("Enter how many elements you will enter: ");
    scanf("%d", &n);

    dim = count_dimension(n) + 2; // this is the amount of stages for first initialization.

    node*head = (node*) malloc(sizeof(node));
    head -> data = -1;
    head -> next_row = NULL;
    head -> next_col = NULL;

    for (i=0; i<n; i++){
        printf("enter new element: ");
        scanf("%d", &new_element);
        head = initialize(head, new_element);
    }
    print(head);

    head = createNewDimensions(head, n);

    //print(head);  
    printf("\n");
    printf("5.stage'in 1. elemani: ");
    printf("%d", head->next_col->next_row->data);
    printf("\n4.stage'in 2. elemani: ");
    printf("%d", head->next_col->next_col->next_row->next_row->data);
    printf("\n3.stage'in 5. elemani: ");
    printf("%d", head->next_col->next_col->next_col->next_row->next_row->next_row->next_row->next_row->data);
}

int count_dimension(int n){
    if((n+1)/2 == 1)
        return 1;
    return count_dimension((n+1)/2) + 1;
}


void print(node*head){
    int i = 0;
    head = head->next_row;
    while(head != NULL){ // we will travel until we reach the NULL at the end
        i++;
        printf("%d. element: %d\n", i, head -> data);
        head = head -> next_row;
    }
}

node * initialize(node*head, int new_element){

    node* current = head;
    while(current -> next_row != NULL && new_element >= current -> next_row -> data)
        current = current -> next_row;
    
    // we need temporary box to not lose linked list at the space while changing pointers
    // we have to point the linked list if we break it without adding new point, we cannot reach that list again
    node * temp = (node*) malloc(sizeof(node));

    temp -> next_row = current -> next_row;
    temp -> next_col = NULL;
    temp -> data = new_element;
    current -> next_row = temp;
    return head;
}


node * createNewDimensions(node* head, int dim){
    int t = (dim+1)/2;

    node * new_stage_head = (node*)malloc(sizeof(node));
    new_stage_head -> data = -1;
    new_stage_head -> next_row = NULL;
    new_stage_head -> next_col = head;
    //printf("Error\n");
    //printf("%d", dim);
    int i;
    node*iter = head->next_row;
    while(t >= 1){
        int new_element;
        new_element = iter->data;
        new_stage_head = initialize(new_stage_head, new_element); // we use past init function for creating new nodes
        node*finder=new_stage_head->next_row;
        while(finder->data != new_element)
            finder = finder -> next_row;

        finder->next_col = iter;
        if(iter->next_row != NULL)
            iter = iter -> next_row -> next_row;              
        t--;
    }
    if (dim == 1){
        node * new_stage_head = (node*)malloc(sizeof(node));
        new_stage_head -> data = -1;
        new_stage_head -> next_row = NULL;
        new_stage_head -> next_col = head;
        return new_stage_head;   
    }

    //return new_stage_head;
    return createNewDimensions(new_stage_head, (dim+1)/2);
}