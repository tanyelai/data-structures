#include <stdio.h>
#include <stdlib.h>

struct n{
    int data;
    struct n *left;
    struct n *right;
};
typedef struct n node;

node * insert(node *, int);
void traverse(node *);
node * delete(node *, int);
int search(node *, int);
int find_max(node *);
int find_min(node *);



int main(){

    node *bst = NULL;
    int element;
    bst = insert(bst, 10);
    bst = insert(bst, 15);
    bst = insert(bst, 120);
    bst = insert(bst, 20);
    bst = insert(bst, 30);
    bst = insert(bst, 40);
    bst = insert(bst, 70);
    element = search(bst, 300);
    printf("\n If the results is 1, we found the element. Otherwise, it is not found. \n Result: %d\n", element);
    element = search(bst, 120);
    printf("\n If the results is 1, we found the element. Otherwise, it is not found. \n Result: %d\n", element);
    printf("\nTree elements: ");
    traverse(bst);

    printf("\n max: %d, min: %d\n", find_max(bst), find_min(bst));  

    return 0;
}

void traverse(node *bst){
    
    if (bst == NULL){
        return;
    }

    traverse(bst->left);
    printf("%d ", bst->data);
    traverse(bst->right);
}

int search(node *bst, int element){

    if (bst == NULL)
        return -1;
    else if (bst->data == element)
        return 1;

    if (search(bst->right, element) == 1)
        return 1;
    else if (search(bst->left, element) == 1)
        return 1;
    
    return -1;

}

node * insert(node *bst, int x){

    if (bst == NULL){
        node * root = (node*)malloc(sizeof(node));
        root->left = NULL;
        root->right = NULL;
        root->data = x;
        return root;
    }
    else if (bst->data < x)
        bst->right = insert(bst->right, x);
    else
        bst->left = insert(bst->left, x);
    
    return bst;
}

int find_max(node *bst){
    while(bst->right != NULL)
        bst = bst->right;
    return bst->data;
}

int find_min(node *bst){
    while(bst->left != NULL)
        bst = bst->left;
    return bst->data;
}