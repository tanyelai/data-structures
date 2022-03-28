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
node* delete(node*, int, int*);
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
    
    printf("\n\nTASK 2: PRINT EVERY STAGE\n");
    print(head);  
    printf("\n");


    printf("\n\nTASK 3: SEARCH:\n");
    search(head, 7, dim);
    search(head, 3, dim);
    search(head, 5, dim);
    search(head, 10, dim);

    // 6.a TASK
    /*
    printf("\n");
    head = insert(head, 1, &n);
    printf("\nElement count: %d\n", n);
    print(head);
    head = insert(head, 8, &n);
    printf("\nElement count: %d", n);
    printf("\n");
    print(head);  
    head = insert(head, 20, &n);
    printf("Element count: %d\n", n);
    print(head);  
    */

    // 6.b TASK
    
    printf("\n");
    head = delete(head, 4, &n);
    printf("Element count: %d\n", n);
    print(head);
    printf("\n");
    head = delete(head, 6, &n);
    printf("Element count: %d\n", n);
    print(head);
    printf("\n");
    head = delete(head, 20, &n);
    printf("Element count: %d\n", n);
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
    head = createNewDimensions(head, *n);
    printf("\nNew element has been added to stages.\n");

    return head;
}

node * delete(node*head, int element, int *n){

    node*safe_quit = head; // we use head in trace to functionalize the other methods
                           // so if we cannot find element we do not want to send new head pointer
                           // we should protect the pointer which points head of the stages.
    while(head->next_col!=NULL)
        head = head -> next_col;  // get cursor onto the main linkedlist

    node * iter = head;
    while(iter -> next_row != NULL && iter -> next_row -> data != element)
        iter = iter -> next_row;

    if(iter -> next_row == NULL){
        printf("There is no such element in the list.\n");
        return safe_quit;
    }

    node * tmp = iter -> next_row;
    iter -> next_row = iter -> next_row -> next_row;
    free(tmp);
    *n = *n-1;
    head = createNewDimensions(head, *n);
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
            printf("Element '%d' found at %d. stage\n", element, t);
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