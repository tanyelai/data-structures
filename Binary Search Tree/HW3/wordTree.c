#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct n{
    char *filename;
    struct n *next_file;
    char *word;            // all void* types replaced by char*
    struct n *left;
    struct n *right;
};
typedef struct n node;


node * insertWord2BST(char*, node *);
void traverse(node *);
node * delete(node *, int);
int search(node *, int);
char *find_max(node *);
char *find_min(node *);
node *readFile_createTree(node*);
int compare(const char* , const char*);
char * removeBlanks(const char * );

int main(){

    node *bst = NULL;
    bst = readFile_createTree(bst);
    printf("Tree in-order:\n");
    traverse(bst);
    return 0;
}

void traverse(node *bst){
    //recursive function to print out the tree inorder
    if (bst == NULL){
        return;
    }

    traverse(bst->left);
    printf("%s ", bst->word);  
    traverse(bst->right);
}


/*int search(node *bst, int element){

}*/

node *readFile_createTree(node*bst){
    FILE *file;
    char in_name[10];
    char *token = NULL;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("Enter file name:\n");
    scanf("%s", in_name);

    file = fopen(in_name, "r");

    if (file == NULL)
        printf("Can't open %s for reading.\n", in_name);
    else
    {
        while ((read = getline(&line, &len, file)) != -1) {
            
            //printf("Retrieved line of length %zu:\n", read);
            printf("%s\n", line);

            
            token = strtok(line, " ");
            while( token != NULL ) {
                //printf("%s\n", token);
                token = strtok(NULL, " ");
                if(token == NULL)
                    break;
                bst = insertWord2BST(token, bst);
            }
            
            //traverse(bst);
            //printf("%s", bst->left->word);
            //traverse(bst);
        }
        fclose(file);
    }
    return bst;  
}


node * insertWord2BST(char *string ,node *bst){

    int res;
    if(bst == NULL){
        bst = (node*)malloc(sizeof(node));
        bst->word = malloc(strlen(string)+1);     // memory for string
        bst->word = strcpy(bst->word, string); 
        bst -> right = NULL;
        bst -> left = NULL;
    }
    else{
        res = strcmp(string, bst->word);
        //If the new string is 'less than' the bst, go left
        if(res < 0)
                bst->left = insertWord2BST(string, bst->left);
        else if(res > 0)
                bst->right = insertWord2BST(string, bst->right);
        else
            printf("The word '%s' is already exist.\n", string);
    }
    return bst;
    
}


/*node * delete(node *bst, int x){
    

}*/

char *find_max(node *bst){
    while(bst->right != NULL)
        bst = bst->right;
    return bst->word;
}

char *find_min(node *bst){
    while(bst->left != NULL)
        bst = bst->left;
    return bst->word;
}
