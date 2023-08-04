#include <stdio.h>
#include <stdlib.h>

// Using structure to implement circular singly linked list in C
typedef struct Node {
  int nVal; // element
  struct Node *pNext; // pointer to next node
} SNode;

// Function declarations:
int LL_add(SNode **ppList,int n); // to add the provided element to list
int LL_del(SNode **ppList,int n); // to delete the provided element from list 
int LL_Print(SNode *pList); // to print out the list
int LL_Destructor(SNode **ppList); // to destroy the whole list

int main() {
  SNode *pList=NULL;
  int n;
  char cAction;

  do{
    printf("(a)dd, (d)elete, (D)estruct, (q)uit: ");scanf(" %c",&cAction);
    if (cAction=='a'){
      printf("Enter a number to add to the list: ");scanf(" %d",&n);
      LL_add(&pList, n);
    } else if (cAction=='d'){
      printf("Enter a number to remove from the list: ");scanf(" %d",&n);
      LL_del(&pList, n);
    } else if (cAction=='D'){
      LL_Destructor(&pList);
    }
    LL_Print(pList);
    printf("\n");
  } while(cAction!='q');

  return 0;
}

// Functions' implementations:
int LL_add(SNode **ppList,int n) {
  SNode *pTemp=*ppList; 
  *ppList=(SNode *) malloc(sizeof(SNode));
  (*ppList)->nVal=n;
  if (!pTemp) (*ppList)->pNext=*ppList; // if the list was empty, new node's next points to itself
  else{
    (*ppList)->pNext=pTemp;
    while (pTemp->pNext && pTemp->pNext != (*ppList)->pNext){ // otherwise, traverse until the end
      pTemp = pTemp->pNext;
    }
    pTemp->pNext = *ppList; // point the last node to the first
  }
  return 0;
}

int LL_Print(SNode *pList) {
  SNode *pTemp=pList; 
  if (pList==NULL) {
    fprintf(stderr," ------ List is empty ------ \n");
    return 1;
  } 
  printf("[%d]->",pList->nVal);
  while (pTemp->pNext != pList) {
    pTemp=pTemp->pNext;
    printf("[%d]->",pTemp->nVal);
  }
  printf("\b/\n");
  return 0;
}

int LL_del(SNode **ppList,int n) {
  SNode *pCurr = *ppList;
  SNode *pPrev = *ppList;

  if (*ppList==NULL) return 1;

  // Delete at beginning
  if ((*ppList)->nVal==n) {
    if ((*ppList)->pNext==*ppList) { // if the list contains 1 node
      free(*ppList);
      *ppList = NULL;
      return 0;
    } else {
      while(pCurr->pNext != *ppList) pCurr=pCurr->pNext; 
      *ppList = pPrev->pNext;
      pCurr->pNext = *ppList;
      free(pPrev);
      return 0; 
    }
  }

  // Delete from certain position
  while(pCurr && pCurr->pNext != *ppList){
    if (pCurr->pNext->nVal == n) {
      SNode *pToDel=pCurr->pNext;
      pCurr->pNext=pCurr->pNext->pNext;
      free(pToDel);
      return 0;
    }
    pCurr = pCurr->pNext;
  }
  fprintf(stderr," ------ No such number in the list ------ \n");  // if number not found
  return 1;
}

int LL_Destructor(SNode **ppList) {
  if (!*ppList) return 1;
  if ((*ppList)->pNext == *ppList) { // if the list contains 1 node
    free(*ppList);
    *ppList = NULL;
    return 0;
  } else {
    SNode *pTemp = *ppList;
    while ((*ppList)->pNext != pTemp) {
      SNode *pToDel = *ppList;
      *ppList = (*ppList)->pNext;
      free(pToDel);
    }
    free(*ppList);
    *ppList = NULL;
  }
  return 0;
}
