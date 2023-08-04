#include <stdio.h>
#include <stdlib.h>

// Using structure to implement doubly linked list in c 
typedef struct Node {
  int nVal; // element
  struct Node *pNext; // pointer to next node
  struct Node *pPrev; // pointer to previous node
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
int LL_add(SNode **ppList,int n){
  SNode *pTemp=*ppList; 
  *ppList=(SNode *) malloc(sizeof(SNode));
  (*ppList)->nVal=n;
  (*ppList)->pNext=pTemp; 
  (*ppList)->pPrev=NULL;
  if (pTemp) pTemp->pPrev = *ppList; 
  return 0;
}

int LL_Print(SNode *pList) {
  SNode *pTemp=pList; 
  if (pList==NULL) {
    fprintf(stderr," ------ List is empty ------ \n");
    return 1;
  } 
  printf("\\-[%d]->",pList->nVal);
  while (pTemp->pNext) {
    pTemp=pTemp->pNext;
    printf(" <-[%d]->",pTemp->nVal);
  }
  printf("\b/\n");
  return 0;
}

int LL_del(SNode **ppList,int n){
  SNode *pTemp = *ppList, *pToDel;
  if (*ppList==NULL) return 1;

  // Delete from beginning 
  if ((*ppList)->nVal==n) {
    pToDel=*ppList;
    *ppList=(*ppList)->pNext;
    if (*ppList) (*ppList)->pPrev=NULL;
    free(pToDel);
    return 0;
  }   

  // Delete from certain position
  while (pTemp) {
    if (pTemp->nVal==n) {
      (pTemp->pPrev)->pNext = pTemp->pNext;
      if (pTemp->pNext) (pTemp->pNext)->pPrev = pTemp->pPrev;
      free(pTemp);
      return 0;
    }
    pTemp = pTemp->pNext;
  }
  fprintf(stderr," ------ No such number in the list ------ \n"); // if number not found
  return 1;
}


int LL_Destructor(SNode **ppList){
  while (*ppList) {
    SNode *pTemp = *ppList;
    *ppList = (*ppList)->pNext;
    free(pTemp);
    pTemp == NULL;
  }
  return 0;
}