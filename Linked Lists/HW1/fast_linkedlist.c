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
node* initialize(node*, int); // creating first linked list
void search(node*, int, int);
node* insert(node*, int, int*);
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
    head = createNewDimensions(head, n);

    // 1. stage head -> NULL
    // 2. stage head -> x -> NULL
    // 3. stage head -> x -> y -> NULL 
    print(head);  
    printf("\n");

    search(head, 9, dim);
    search(head, 10, dim);
    search(head, 0, dim);
    search(head, 6, dim);
    search(head, 4, dim);

    printf("2.stage'in 1. elemani: ");
    printf("%d", head->next_col->next_row->data);
    printf("\n3.stage'in 2. elemani: ");
    printf("%d", head->next_col->next_col->next_row->next_row->data);
    printf("\n4.stage'in 2. elemani: ");
    printf("%d", head->next_col->next_col->next_col->next_row->next_row->data);
    //printf("\n5.stage'in 4. elemani: ");
    //printf("%d", head->next_col->next_col->next_col->next_row->next_row->next_col->next_row->data);

    printf("\ndim: %d\n", dim);
    printf("\nn: %d", n);
    printf("\n");
    head = insert(head, 10, &n);
    print(head); 
    head = createNewDimensions(head, n);
    printf("\nn: %d", n);
    printf("\n");
    print(head); 
    head = insert(head, 11, &n);
    head = createNewDimensions(head, n);
    printf("\n");
    printf("n: %d\n", n);
    print(head);  
    head = insert(head, 15, &n);
    head = createNewDimensions(head, n);
    printf("\n");
    printf("n: %d\n", n);
    print(head);  
    head = insert(head, 13, &n);
    head = createNewDimensions(head, n);
    head = insert(head, 12, &n);
    head = createNewDimensions(head, n);
    head = insert(head, 16, &n);
    head = createNewDimensions(head, n);
    head = insert(head, 17, &n);
    head = createNewDimensions(head, n);
    head = insert(head, 18, &n);
    head = createNewDimensions(head, n);
    head = insert(head, 19, &n);
    head = createNewDimensions(head, n);
    printf("\n");
    printf("n: %d\n", n);
    printf("\ndim: %d\n", dim);
    print(head);  

}

int count_dimension(int n){
    if((n+1)/2 == 1)
        return 1;
    return count_dimension((n+1)/2) + 1;
}

node * insert(node*head, int new_element, int *n){
    
    while(head->next_col!=NULL)
        head = head -> next_col;  // get cursor onto the main linkedlist

    head = initialize(head, new_element);
    *n = *n+1; // we use pointer and adress of n because we cannot pass n's value back with return in C language.
    printf("\nThe stages have been updated with new element.\n");

    return head;
}


node * initialize(node*head, int new_element){

    node* current = head;
    while(current -> next_row != NULL && new_element >= current -> next_row -> data)
        current = current -> next_row;
    
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

void search(node*head, int element, int dim){

    node*iter = head;
    iter = iter -> next_col; // first stage has no element
    int t=2;
  
    while(t!=dim+1){

        while (iter->next_row != NULL && element >= iter->next_row->data)
            iter = iter -> next_row;
        
        if(element == iter->data){
            printf("Element found at %d. stage\n", t);
            t=dim;
        }
        else if(t == dim)
            printf("There is no such element that matched with %d\n", element);
        
        
        iter = iter -> next_col;
        t++;
    }
}

void print(node*head){
    int t = 1;
    printf("1. stage: \nhead->NULL\n");
    head = head -> next_col; // we pass the first stage because there is no element.
    while(head != NULL){
        printf("%d. stage: \nhead->", ++t);
        node* iter = head;
        while(iter->next_row != NULL){ // we will travel until we reach the NULL at the end
            printf("%d ->", iter->next_row->data);
            iter = iter -> next_row;
        }
        printf("NULL\n");
        head = head -> next_col;
    }
}