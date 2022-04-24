#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct l{
    struct l *next;
    char *filename;
};
typedef struct l list;

struct n{
    struct l *files;
    char *word;            
    struct n *left;
    struct n *right;
};
typedef struct n node;

node * insertWord2BST(char*, char*, node *);
node * delete(node *, int);
void search(char*, node *);
node *readFile_createTree(node*);
void delete_tree(node* );
void inOrder(node *);
void preOrder(node *);
void postOrder(node *);
char *find_max(node *);
char *find_min(node *);

int main(){
    node *bst = NULL;
    bst = readFile_createTree(bst);
    printf("Tree in-order:\n");
    //printf("Word %s in File: %s\n", bst->word, bst->next_file->filename);
    //printf("Word %s in File: %s\n", bst->right->word, bst->next_file->filename);

    search("the", bst);
    search("with", bst);
    search("beach", bst);
    printf("\ninorder:\n");
    inOrder(bst);
    printf("\npreorder:\n");
    preOrder(bst);
    printf("\npostorder:\n");
    postOrder(bst);
    return 0;
}


//searches elements in the tree
void search(char *string, node* bst)  // no need for **
{
    int res;
    if( bst != NULL ) {
        res = strcmp(string, bst->word);
        if( res < 0)
            search(string, bst->left);
        else if( res > 0)
            search(string, bst->right);
        else{
            printf("\n'%s' found! in following files:\n", string);
            
            while(bst->files->next != NULL){
                printf("%s\n", bst->files->filename);
                bst->files = bst->files->next;
            }
            printf("%s\n", bst->files->filename);
        }
    }
    else printf("\nNot in the tree.\n");
    return;
}

node *readFile_createTree(node*bst){
    FILE *file;
    char in_name[10];
    char *token = NULL;
    char *line = NULL;
    char *filename = NULL;
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
            printf("%s\n", line);

            token = strtok(line, " ");
            filename = token;
            filename[strlen(filename)-1] = '\0';
            while( token != NULL ) {
                token = strtok(NULL, " ");
                if(token == NULL)
                    break;
                bst = insertWord2BST(filename, token, bst);
            }
        }
        fclose(file);
    }
    return bst;  
}


node * insertWord2BST(char *filename, char *string ,node *bst){

    int res,res2;
    if(bst == NULL){
        bst = (node*)malloc(sizeof(node));
        bst->word = malloc(strlen(string)+1);     // memory for word
        bst->word = strcpy(bst->word, string); 
        bst -> right = NULL;
        bst -> left = NULL;
        // init first appear of word
        bst->files = (list*)malloc(sizeof(list));
        bst->files->filename = malloc(strlen(filename)+1);
        bst->files->filename = strcpy(bst->files->filename, filename);
        bst->files->next = NULL;
    }
    else{
        res = strcmp(string, bst->word);
        //If the new string is 'less than' the bst, go left
        if(res < 0)
            bst->left = insertWord2BST(filename, string, bst->left);
        else if(res > 0)
            bst->right = insertWord2BST(filename, string, bst->right);
        else{
            printf("The word '%s' is already exist.\n", string);

            list*iter = bst->files;
            while(iter->next != NULL)
                iter = iter->next;

            iter->next = (list*) malloc(sizeof(list));
            iter->next->filename = malloc(strlen(filename)+1);
            iter->next->filename = strcpy(iter->next->filename, filename);
            iter -> next -> next = NULL;
            return bst;
        }
            
    
    }
    return bst;
    
}

/*node * searchInFiles(char *filename, node *bst){
    
}*/


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

void preOrder(node *bst) {
    if (bst == NULL){
        return;
    }
    printf("%s ", bst->word);
    preOrder(bst->left);
    preOrder(bst->right);
}

void postOrder(node *bst) {
    if (bst == NULL){
        return;
    }
    postOrder(bst->left);
    postOrder(bst->right);
    printf("%s ", bst->word);
}

void inOrder(node *bst) {
    if (bst == NULL){
        return;
    }
    inOrder(bst->left);
    printf("%s ", bst->word);
    inOrder(bst->right);
}

void delete_tree(node* bst){
    if( bst != NULL ) {
        delete_tree(bst->left);
        delete_tree(bst->right);
        free(bst->word);         // free the key
        free(bst);
    }
}