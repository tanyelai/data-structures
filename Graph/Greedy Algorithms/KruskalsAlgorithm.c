#include <stdio.h>

#define MAX 30

struct edge{
  int u, v, w;
};
typedef struct edge EDGE;

struct e_l{
  EDGE data[MAX];
  int n;
};
typedef struct e_l EDGE_LIST;

EDGE_LIST elist;
EDGE_LIST spanlist;

int graph[MAX][MAX], n;

void kruskalAlg();
int find(int belongs[], int vertexno);
void applyUnion(int belongs[], int c1, int c2);
void sort();
void print();

// Applying Kruskal Algorithm
void kruskalAlg() {
  int belongs[MAX], i, j, cno1, cno2;
  elist.n = 0;

  for (i = 0; i < n; i++)
    for (j = 0; j < i; j++) {
      if (graph[i][j] != 0) {
        elist.data[elist.n].u = i;
        elist.data[elist.n].v = j;
        elist.data[elist.n].w = graph[i][j];
        elist.n++;
      }
    }

  sort();

  for (i = 0; i < n; i++)
    belongs[i] = i;

  spanlist.n = 0;

  for (i = 0; i < elist.n; i++) {
    cno1 = find(belongs, elist.data[i].u);
    cno2 = find(belongs, elist.data[i].v);

    if (cno1 != cno2) {
      spanlist.data[spanlist.n] = elist.data[i];
      spanlist.n = spanlist.n + 1;
      applyUnion(belongs, cno1, cno2);
    }
  }
}

int find(int belongs[], int vertexno) {
  return (belongs[vertexno]);
}

void applyUnion(int belongs[], int c1, int c2) {
  int i;

  for (i = 0; i < n; i++)
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

// Printing the result
void print() {
  int i, cost = 0;

  for (i = 0; i < spanlist.n; i++) {
    printf("\n%d - %d : %d", spanlist.data[i].u, spanlist.data[i].v, spanlist.data[i].w);
    cost = cost + spanlist.data[i].w;
  }

  printf("\nSpanning tree cost: %d", cost);
}

int main() {
  int i, j, total_cost;

  n = 6;

  graph[0][0] = 0;
  graph[0][1] = 4;
  graph[0][2] = 4;
  graph[0][3] = 0;
  graph[0][4] = 0;
  graph[0][5] = 0;
  graph[0][6] = 0;

  graph[1][0] = 4;
  graph[1][1] = 0;
  graph[1][2] = 2;
  graph[1][3] = 0;
  graph[1][4] = 0;
  graph[1][5] = 0;
  graph[1][6] = 0;

  graph[2][0] = 4;
  graph[2][1] = 2;
  graph[2][2] = 0;
  graph[2][3] = 3;
  graph[2][4] = 4;
  graph[2][5] = 0;
  graph[2][6] = 0;

  graph[3][0] = 0;
  graph[3][1] = 0;
  graph[3][2] = 3;
  graph[3][3] = 0;
  graph[3][4] = 3;
  graph[3][5] = 0;
  graph[3][6] = 0;

  graph[4][0] = 0;
  graph[4][1] = 0;
  graph[4][2] = 4;
  graph[4][3] = 3;
  graph[4][4] = 0;
  graph[4][5] = 0;
  graph[4][6] = 0;

  graph[5][0] = 0;
  graph[5][1] = 0;
  graph[5][2] = 2;
  graph[5][3] = 0;
  graph[5][4] = 3;
  graph[5][5] = 0;
  graph[5][6] = 0;

  kruskalAlg();
  print();
}