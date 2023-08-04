#include<stdio.h>
#include<stdlib.h>

// Using structure to implement binary search tree in C
typedef struct Node {
  int nVal; // element
  struct Node *pLeft; // pointer to left node/subtree
  struct Node *pRight; // pointer to right node/subtree
} SNode;

// Function signatures:
SNode *BST_newNode(int n); // to create new node with provided value
SNode *BST_search(SNode *pTree, int n); // to search for provided element in the tree
SNode *BST_insert(SNode *pTree, int n); // to insert the provided element to the tree
SNode *BST_minValueNode(SNode *pTree); // to get the inorder successor of the tree
void BST_print(SNode *pTree); // to print out the tree
SNode *BST_del(SNode *pTree, int n); // to delete the provided element from the tree

int main() {
  SNode *pTree=NULL;
  int n;
  char cAction;
  
  do{
    printf("(a)dd, (d)elete, (q)uit: ");scanf(" %c",&cAction);
    if (cAction=='a'){
        printf("Enter a number to add to the tree: "); scanf(" %d",&n);
        pTree = BST_insert(pTree, n);
    } else if (cAction=='d'){
        printf("Enter a number to delete from the tree: "); scanf(" %d",&n);
        pTree = BST_del(pTree, n);
    }
    BST_print(pTree);
    printf("\n");
  }while(cAction!='q');

  return 0;
}

// Functions' implementations:
SNode *BST_newNode(int n){
  SNode *pTemp=(SNode *)malloc(sizeof(SNode));
  pTemp->nVal=n; 
  pTemp->pLeft=NULL; pTemp->pRight=NULL;
  return pTemp;
}

SNode *BST_search(SNode *pTree, int n){
  if (!pTree || pTree->nVal==n) return pTree; // tree is empty/null or n is present at tree
  if (pTree->nVal < n) return BST_search(pTree->pRight, n); // recursive call to search in right subtree
  return BST_search(pTree->pLeft, n); // recursive call to search in left subtree
}

SNode *BST_insert(SNode *pTree, int n){
  if (!pTree) return BST_newNode(n); // return a new node if the tree is empty/null
  if (pTree->nVal < n){ 
    pTree->pRight=BST_insert(pTree->pRight, n);
  } else if (pTree->nVal > n){
    pTree->pLeft=BST_insert(pTree->pLeft, n);
  } else {
    fprintf(stderr," ------ No duplicates allowed ------ \n"); //to avoid repetition of elements
  }
  return pTree;
}

SNode *BST_minValueNode(SNode *pTree) {
  SNode *pTemp=pTree;
  while(pTemp && pTemp->pLeft) pTemp=pTemp->pLeft; // find the minimum element in left subtree
  return pTemp;
}

void BST_print(SNode *pTree){ // reverse inorder traversal
  if(pTree){
    BST_print(pTree->pRight);
    printf(" %d ", pTree->nVal);
    BST_print(pTree->pLeft);
  }
}

SNode *BST_del(SNode *pTree, int n){
  if (!pTree) {
    fprintf(stderr," ------ No such number found  ------ \n");
    return pTree;
  }
  if (pTree->nVal < n) {
    pTree->pRight=BST_del(pTree->pRight, n);
  } else if (pTree->nVal > n) {
    pTree->pLeft=BST_del(pTree->pLeft, n);
  } else {
    // if there is one or no child
    if (!pTree->pRight) {
      SNode *pTemp=pTree->pLeft;
      free(pTree);
      return pTemp;
    } else if (!pTree->pLeft) {
      SNode *pTemp=pTree->pRight;
      free(pTree);
      return pTemp;
    }
    // if there are 2 child nodes
    SNode *pTemp=BST_minValueNode(pTree->pRight);
    pTree->nVal=pTemp->nVal;
    pTree->pRight=BST_del(pTree->pRight, pTemp->nVal);
  }
  return pTree;
}