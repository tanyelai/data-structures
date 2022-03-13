// A BASELINE FOR FEATURES OF CIRCULAR LINKED LISTS IN C LANG.
// longer explanations for transactions is explained in linkedlist.c file

#include <stdio.h>
#include <stdlib.h>

struct n{
    int x;
    struct n * next;
};
typedef struct n node;

// circular linked list has no end, the last element of list points root again
void print(node *); // display the list elements
node * add(node *, int); // adding to the end without sorting
node * insert(node *, int); // adding with ascending sort
node * delete(node *, int);   // deleting an element from linked list


int main(){
    node * root; // pointer for holding the head of list
    root = NULL;

    // node*idx will be used to point root, can be considered as [index] of root
    // linked lists use sequential access

    int i, new_element;
    root = delete(root, 1);
    for(i=0; i<6; i++){
        printf("enter new element: ");
        scanf("%d", &new_element);
        root = insert(root, new_element);
    }
    printf("Before Deletion: \n");
    print(root);

    root = delete(root, 3);
    root = delete(root, 7);
    root = delete(root, 2);
    root = delete(root, 4);

    printf("After Deletion: \n");
    // while printing
    // if list have 0 element after last deletion and if you want to give information as there is no element
    // you might need to add extra codes to check that case 
    // | check print & deletion function and take your time to understand why it will not work as its purpose without our extension |
    print(root);

    // ___________________________________________________________________________________
    // EXP: in circular linked list we point root -> next = root while we have one element
    // which cause we cannot know what is next of root after deletion
    // it is given randomly by RAM, so you need to assign it as you can control even there is no element
    // as well as you cannot do the deletion control while there is no element in the list
    // the program will be exploded as expected if you are not control it. 
    // ___________________________________________________________________________________
}

void print(node*idx){
    int i = 0;
    node * iter = idx;

    if(idx == NULL)  // added extra code to solve segmentation fault which arise after deleting last element in the list
        printf("The list has no element to display.\n");
    else{   
        do{         // we want to root pointer as end point so we can understand we reach the end of the list.
            i++;
            printf("%d. element: %d\n", i, iter -> x);
            iter = iter -> next;
        }while(iter != idx);
    }
}


node * add(node*idx, int new_element){

    if (idx == NULL){
        idx = (node*) malloc(sizeof(node));
        idx -> x = new_element;
        idx -> next = idx;
        return idx;
    }

    node * iter = idx; 
    while(iter -> next != idx){
        iter = iter -> next;
    }
    
    node * tmp = (node*) malloc(sizeof(node));
    tmp -> next = idx;
    iter -> next = tmp;
    tmp -> x = new_element;
    return idx;
}

node * insert(node*idx, int new_element){

    if(idx == NULL){          // if linkedlist is empty
        idx = add(idx, new_element);
        return idx;
    }

    else{
        node * temp = (node*) malloc(sizeof(node));

        if (idx -> x >= new_element){        // add element as root
            temp -> next = idx;
            temp -> x = new_element;
            node * iter = idx;
            while(iter -> next != idx)
                iter = iter -> next;
            iter -> next = temp;
            return temp; // send temp as new root, it is important to update root's pointer in main
        }

        node * iter = idx;
        while(iter -> next != idx && iter -> next -> x < new_element)
            iter = iter -> next;

        temp -> next = iter -> next;    
        temp -> x = new_element;
        iter -> next = temp;
        return idx;
    }
}

node * delete(node*idx, int element){

    if(idx == NULL){
        printf("There is no element to remove. List has 0 element.\n");
        return idx;
    }
    else if(idx -> next == idx && idx -> x == element)
    {
        printf("Your last element has removed. From now, you have 0 element in the list.");
        node * tmp = idx;
        idx = NULL; // 0 element has remained.
        free(tmp);
        return idx; 
    }
    else if(idx -> x == element){ // if the root equals to element we search (in other words first element of the list)
        node * iter = idx;
        while(iter -> next != idx) // we must change the next of last element to point new root.
            iter = iter -> next;

        node * tmp = idx;
        idx = idx -> next;
        iter -> next = idx; // we change last element's next -> new root
        free(tmp);
        return idx;      
    }
    else{
        node * iter = idx;
        while(iter -> next != idx && iter -> next -> x != element)
            iter = iter -> next;

        if(iter -> next == idx){
            printf("There is no such element in the list.\n");
            return idx;
        }

        node * tmp = iter -> next;
        iter -> next = iter -> next -> next;
        free(tmp);
        return idx;
    }
}