#include <stdio.h>
#include <stdlib.h>

// Using queue implementation and the structure for implementing FIFO approach in C
typedef struct Fifo {
  int iEnQueue, iDeQueue, nSize; // i for "Index", n for "iNteger"
  int* pFifo;                    // p for "Pointer"
} SFifo;                         // S for "Structure"

// function signatures:
int constructFifo(SFifo *p, int n); // constructor for queue
int enQueue(SFifo *p, int n); // to add element to queue
int deQueue(SFifo *p); // to delete element from queue
int printQueue(SFifo*p); // to print out the queue
int destructFifo(SFifo *p); // to destruct the whole queue

int main(){
  int n, nErrNo=1; // nErrNo for Error Number
  SFifo myFifo;

  printf("Enter a queue size > 0: ");
  scanf("%d", &n);
  nErrNo = constructFifo(&myFifo, n);
  if (nErrNo){
    fprintf(stderr, "Error code %d while creating the queue\n", nErrNo);
    return 1;
  }

  printf("enQueue positive numbers (dequeue with -1, end with -2)\n");
  while (1){
    scanf("%d", &n);
    if (n == -2) break;
    if (n == -1) deQueue(&myFifo);
    else enQueue(&myFifo, n);
    printQueue(&myFifo);
  }

  destructFifo(&myFifo);
  return 0;
}

// implemented functions:
int constructFifo(SFifo *p, int n){
    if (n <= 0) return -1; // no negative integers accepted
    p->pFifo = (int *)malloc(n * sizeof(int));
    if(p->pFifo){
        p->nSize = n;
        p->iDeQueue = -1; // indicate the emptiness of stack
        p->iEnQueue = -1;
        return 0;
    }
    return -1; // error allocating memory
}

int enQueue(SFifo *p, int n){
    if(p->iEnQueue == p->nSize-1){ // check if the queue is full before inserting an element
        printf("Queue is full\n");
        return -1;
    }
    if(p->iEnQueue == -1 && p->iDeQueue == -1) p->iDeQueue++; // if the inserted element is the first in queue
    p->iEnQueue++;
    p->pFifo[p->iEnQueue] = n;
    return 0;
}

int deQueue(SFifo *p){
    if(p->iEnQueue == -1 && p->iDeQueue == -1){ // before deleting an element, check if it's already empty
        printf("The queue is already empty\n");  
        return -1;      
    }
    p->iDeQueue++;
    if (p->iDeQueue > p->iEnQueue) p->iDeQueue = p->iEnQueue = -1; // if the queue becomes empty 
    
    return 0;
}

int printQueue(SFifo*p){
    if(p->iEnQueue == -1 && p->iDeQueue == -1){
        printf("The queue is empty\n");
        return -1;
    }
    for(int i = p->iDeQueue; i <= p->iEnQueue; i++) printf("%d ", p->pFifo[i]);
    printf("\n");
    return 0; 
}

int destructFifo(SFifo *p){
    free(p->pFifo);
    p->iDeQueue = p->iEnQueue = -1;
    p->nSize = 0;
    p->pFifo = NULL;
    return 0;
}
