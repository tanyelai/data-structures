#include <stdio.h>
#include <stdlib.h>

// ****************************************************************
// TASK: ADDING NEW EDGE TO THE MST AND UPDATE IT IF NECESSARY
// ****************************************************************

#define MAX 30

struct edge{
  int u, v, w;
};
typedef struct edge EDGE;

struct edge_list{
  EDGE data[MAX];
  int n;
};
typedef struct edge_list EDGE_LIST;

EDGE_LIST elist;
EDGE_LIST spanlist;

void kruskalAlg();
int find(int belongs[], int vertexno);
void applyUnion(int belongs[], int c1, int c2);
void sort();
void print();
void update_edges();
void add_new_edge();


int main() {
  int i, j, total_cost;

  FILE *fp = fopen("test.txt", "r");
  fscanf(fp, "%d", &elist.n);
  
  elist.n=0;
  while(!feof(fp)){
    fscanf(fp, "%d %d %d", &elist.data[elist.n].w, &elist.data[elist.n].u, &elist.data[elist.n].v);
    elist.n++;
  }
  kruskalAlg();
  print();
  add_new_edge();
}

// Applying Kruskal Algorithm
void kruskalAlg() {
  int belongs[MAX], i, j, cno1, cno2;
  sort();

  for (i = 0; i < elist.n; i++)
    belongs[i] = i;

  spanlist.n = 0;

  for (i = 0; i < elist.n; i++) {
    cno1 = find(belongs, elist.data[i].u);
    cno2 = find(belongs, elist.data[i].v);

    if (cno1 != cno2) {
      spanlist.data[spanlist.n] = elist.data[i];
      spanlist.n++;
      applyUnion(belongs, cno1, cno2);
    }
  }
}

// https://web.stanford.edu/class/archive/cs/cs161/cs161.1168/lecture15.pdf
// https://courses.cs.duke.edu/cps100e/fall09/notes/UnionFind.pdf
int find(int belongs[], int vertexno) {
  return (belongs[vertexno]);
}

void applyUnion(int belongs[],  int c1, int c2) {
  int i;

  for (i = 0; i < elist.n; i++)
    if (belongs[i] == c2)
      belongs[i] = c1;
}

// Sorting algorithm
void sort() {
  int i, j;
  EDGE temp;

  //bubble sort 
  for (i = 1; i < elist.n; i++)  // step
    for (j = 0; j < elist.n - 1; j++) 
      if (elist.data[j].w > elist.data[j + 1].w) {  // comparing weigths
        temp = elist.data[j];   // swapping 
        elist.data[j] = elist.data[j + 1];
        elist.data[j + 1] = temp;
      }
}

void update_edges(int x){
  spanlist.data[x].u = elist.data[elist.n].u;
  spanlist.data[x].v = elist.data[elist.n].v;
  spanlist.data[x].w = elist.data[elist.n].w;
}

void add_new_edge(){
  printf("\n\tADDING NEW EDGE\n\tEnter the weight, u and v. Leave a space in between: ");
  scanf("%d %d %d", &elist.data[elist.n].w, &elist.data[elist.n].u, &elist.data[elist.n].v);
  sort();
  int i, j;

  // The conditions for understanding the place that new edge creates cycle and being less than max weight of the cycle.
  for(i=0; i<spanlist.n; i++){ 
    if(elist.data[elist.n].u == spanlist.data[i].v){ // case 1 -> dest-src
      for(j=0; j<spanlist.n; j++){
        if(spanlist.data[i].u == spanlist.data[j].u && elist.data[elist.n].v == spanlist.data[j].v && elist.data[elist.n].w < spanlist.data[j].w){
          update_edges(j);
        }
      }
    }
    else if(elist.data[elist.n].v == spanlist.data[i].u){   // case 2 -> src-dest
      for(j=0; j<spanlist.n; j++){
        if(spanlist.data[i].v == spanlist.data[j].v && elist.data[elist.n].u == spanlist.data[j].u && elist.data[elist.n].w < spanlist.data[j].w){
          update_edges(j);
      }
    }
  }
    else if(elist.data[elist.n].u == spanlist.data[i].u){ // case 3 -> both source
      for(j=0; j<spanlist.n; j++){
        if(spanlist.data[i].v == spanlist.data[j].u && elist.data[elist.n].v == spanlist.data[j].v &&elist.data[elist.n].w < spanlist.data[j].w){
          update_edges(j);
        }
      }
    }
  }
  printf("\nNEW MST AFTER ADDING EDGE");
  print();
}


// Printing the result
void print() {
  int i, cost = 0;
  printf("\nU - V : Weight");
  for (i = 0; i < spanlist.n; i++) {
    printf("\n%d - %d : %d", spanlist.data[i].u, spanlist.data[i].v, spanlist.data[i].w);
    cost = cost + spanlist.data[i].w;
  }

  printf("\nSpanning tree cost: %d", cost);
}