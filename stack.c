#include <stdio.h>
#include <stdlib.h>

// Using stack implementation and the structure for implementing LIFO approach in C 
typedef struct Lifo {
  int iTop, nSize; // top element index and capacity of stack
  int* pLifo; // pointer to stack   
} SLifo;      

// function signatures:
int CLifo(SLifo *p, int nSize); // constructor for the stack
int CLifo_getSize(SLifo *p); //get the size of stack
int CLifo_setSize(SLifo *p, int nSize); // if s>nSize, enlarge, in any other case return error code
int CLifo_push(SLifo *p, int n); // to push an element to stack
int CLifo_pop(SLifo *p); // to pop an element from stack
int CLifo_print(SLifo *p); // prints the contents of the stack
int d_CLifo(SLifo *p); // destructor for the stack

int main(){
  int n,nErrNo=1; // nErrNo for Error Number
  SLifo myLifo;

  printf("Enter a stack size > 0: ");scanf("%d",&n);
  nErrNo=CLifo(&myLifo,n);
  if (nErrNo){
    fprintf(stderr,"Error code %d while creating the stack\n",nErrNo);
    return 1;
  }
  printf("Push positive integers (pop with -1, end with -2)\n");
  while (n!=-2){
    scanf("%d",&n);
    if (n==-1) CLifo_pop(&myLifo);
    else if (n > 0) CLifo_push(&myLifo,n);
    CLifo_print(&myLifo);
  }

  d_CLifo(&myLifo);

  return 0;
}

// Implemented functions:
int CLifo(SLifo *p, int nSize){
  if (nSize <= 0) return 1; // error code for invalid stack size
  p->pLifo = (int*)malloc(nSize*sizeof(int));
  if(!p->pLifo) return 2; // error allocating memory 
  p->nSize = nSize;
  p->iTop = -1; // indicate the emptiness of stack
  return 0;
}

int CLifo_getSize(SLifo *p) {return p->nSize;}

int CLifo_setSize(SLifo *p, int nSize){
  if(nSize <= 0 || nSize < p->nSize) return 1; // error code for invalid stack size
  if(nSize == p->nSize) return 0; //exit in case sizes are same
  p->pLifo = (int *)realloc(p, nSize * sizeof(int));
  if(!p->pLifo) return 2; // error allocating memory 
  p->nSize = nSize;
  return 0;
}

int CLifo_push(SLifo *p, int n){
  if(p->iTop == p->nSize-1){
    printf("Error adding new element! Stack is full\n");
    return -1; // error code in case stack is full
  }else{
    p->iTop++; // increment the top element's index
    p->pLifo[p->iTop] = n;
  }
  return 0;
}

int CLifo_pop(SLifo *p){
  if(p->iTop == -1){
    printf("Error removing an element! Stack is already empty\n");
    return -1; // error code in case stack is already empty
  }
  p->iTop--; // decrement the top element's index
  return 0;
}

int CLifo_print(SLifo *p){
  if(p->iTop == -1){
    printf("---empty stack---\n");
    return 0;
  }
  for(int i = 0; i <= p->iTop; i++){
    printf("%d ", p->pLifo[i]);
  }
  printf("\n");
  return 0; 
}

int d_CLifo(SLifo *p){
  p->nSize = 0;
  p->iTop = -1; 
  free(p->pLifo); // free the memory allocated for stack
  return 0;
}