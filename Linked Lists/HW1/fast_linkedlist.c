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
    printf("Enter how many elements you will enter");
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

    head = createNewDimensions(head, dim);

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
    printf("Error");
    node * new_stage_head = (node*)malloc(sizeof(node));
    new_stage_head -> data = -1;
    new_stage_head -> next_row = NULL;
    new_stage_head -> next_col = head;
    printf("Error");
    int i;
    node*iter = head->next_row;
    for (i=0; i<dim; i=i+2){
        int new_element;
        while(iter -> next_row != NULL){
            new_element = iter->data;
            new_stage_head = initialize(new_stage_head, new_element);
            node*finder=new_stage_head;
            while(finder->next_row->data != new_element || finder->next_row != NULL)
                finder = finder -> next_row;

            finder->next_row->next_col = iter;
            iter = iter -> next_row -> next_row;
        }
    }

    return createNewDimensions(new_stage_head, ((dim+1)/2));
}