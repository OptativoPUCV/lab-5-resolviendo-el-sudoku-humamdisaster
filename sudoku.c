#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i, j, k;

    //filas
    for (i = 0; i < 9; i++){
       int visto[10] = {0};
       for (j = 0; j < 9; j++){
        int val = n->sudo[i][j];
        if (val != 0){
            if (visto[val]) return 0;
            visto[val] = 1;
        }
       }
    }
    //columnas
    for (j = 0; j < 9; j++){
      int visto[10] = {0};
      for (i = 0; i < 9; i++){
        int val = n->sudo[i][j];
        if (val != 0){
            if (visto[val]) return 0;
            visto[val] = 1;
        }
      }
    }
    //submatrices 3x3
    for (k = 0; k < 9 ; k++){
      int visto[10] = {0};
      for (int p = 0; p < 9; p++){
        int i = (k/3)*3 + (p/3);
        int j = (k%3)*3 + (p%3);
        int val = n->sudo[i][j];
        if (val != 0){
            if (visto[val]) return 0;
            visto[val] = 1;
        }
      }
    }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int fila = -1, col =-1;

    for (int i = 0; i < 9 && fila == -1; i++){
        for (int j = 0; j < 9 && fila == -1; j++){
            if (n->sudo[i][j] == 0){
                fila = i;
                col = j;
            }
        }
    }
    if (fila == -1 && col == -1){
        return list;
    }
    for (int num = 1; num <= 9; num++){
        Node* new = copy(n);
        new->sudo[fila][col] = num;
        if (is_valid(new)) pushBack(list, new);
        else free(new);
    }
    return list;
}


int is_final(Node* n){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (n->sudo[i][j] == 0) return 0;
        }
    }
    return 1;
}


Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
  push(stack, initial);

  while (!is_empty(stack)){
    Node* current = top(stack);
    pop(stack);
    (*cont)++;
    if (is_final(current)){
        return current;
    }
    List* adj = get_adj_nodes(current);
    Node* adjNode = first(adj);
    while (adjNode != NULL){
        push(stack, adjNode);
        adjNode = next(adj);
    }
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/