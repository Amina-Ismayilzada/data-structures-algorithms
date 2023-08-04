#include<stdio.h>
#include<stdlib.h>

// Using structure to implement AVL tree in C
typedef struct Node {
  int nVal, nHeight; // element and its height
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
int BST_getHeight(SNode *pTree); // getter of the height of tree
int BST_getBalanceFactor(SNode *pTree); // getter of the balance factor of tree
SNode *BST_leftRotate(SNode *pTree); // implementation of left rotation
SNode *BST_rightRotate(SNode *pTree); // implementation of right rotation
int max(int i, int j); // to get the maximum of 2 integers 

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
int BST_getHeight(SNode *pTree){
  if (pTree==NULL) return 0; // if tree is empty/null, the height is 0
  return pTree->nHeight;
}

int BST_getBalanceFactor(SNode *pTree){ 
    if (pTree==NULL) return 0;
    // balance factor = (height of left subtree) - (height of right subtree)
    return BST_getHeight(pTree->pLeft) - BST_getHeight(pTree->pRight);
}

SNode *BST_newNode(int n){
  SNode *pTemp=(SNode *)malloc(sizeof(SNode));
  pTemp->nVal=n;
  pTemp->pLeft=NULL; pTemp->pRight=NULL;
  pTemp->nHeight=1;
  return pTemp;
}

SNode *BST_search(SNode *pTree, int n){
  if (pTree->nVal==n || pTree==NULL) return pTree; // tree is empty/null or n is present in the tree
  if (pTree->nVal < n) return BST_search(pTree->pRight, n); // recursive call to search in right subtree
  return BST_search(pTree->pLeft, n); // recursive call to search in left subtree
}

SNode *BST_insert(SNode *pTree, int n){
  if (pTree==NULL) return BST_newNode(n); // return a new node if the tree is empty/null
  if (pTree->nVal < n) {
    pTree->pRight=BST_insert(pTree->pRight, n);
  } else if (pTree->nVal > n) {
    pTree->pLeft=BST_insert(pTree->pLeft, n);
  } else {
    fprintf(stderr," ------ No duplicates allowed ------ \n"); // to avoid repetition of elements
    return pTree;
  }

  // fix the balance of tree updating to the balance factor of each node
  pTree->nHeight = max(BST_getHeight(pTree->pLeft), BST_getHeight(pTree->pRight)) + 1;
  int nBalance=BST_getBalanceFactor(pTree);

  if(nBalance > 1 && pTree->pLeft->nVal > n) return BST_rightRotate(pTree); // RR rotation
  if(nBalance < -1 && pTree->pRight->nVal < n) return BST_leftRotate(pTree); // LL rotation
  if(nBalance > 1 && pTree->pLeft->nVal < n){ // LR rotation
    pTree->pLeft = BST_leftRotate(pTree->pLeft);
    return BST_rightRotate(pTree);
  }
  if(nBalance < -1 && pTree->pRight->nVal > n){ //RL rotation
    pTree->pRight = BST_rightRotate(pTree->pRight);
    return BST_leftRotate(pTree);
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
    printf("%d ", pTree->nVal);
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
    if ((!pTree->pRight) || (!pTree->pLeft)) { // if there is only one child
      SNode *pTemp= pTree->pRight ?  pTree->pRight : pTree->pLeft;
      if (!pTemp) { // if it is a leaf node(has no child nodes)
        pTemp = pTree;
        pTree = NULL;
      } else { // has one child
        pTree->nVal = pTemp->nVal;
        pTree->pLeft = pTemp->pLeft;
        pTree->pRight = pTemp->pRight;
        pTree->nHeight = pTemp->nHeight;
      }
      free(pTemp);
    } else { // if the node has 2 children
      SNode *pTemp=BST_minValueNode(pTree->pRight);
      pTree->nVal=pTemp->nVal;
      pTree->pRight=BST_del(pTree->pRight, pTemp->nVal);
    }
  }
  if(pTree == NULL) return pTree; //if value is not found
  
  // fix the balance of tree updating the balance factor of each node
  pTree->nHeight = max(BST_getHeight(pTree->pLeft), BST_getHeight(pTree->pRight)) + 1;
  int nBalance=BST_getBalanceFactor(pTree);

  if(nBalance > 1 && BST_getBalanceFactor(pTree->pLeft) >= 0) return BST_rightRotate(pTree); // RR rotation
  if(nBalance < -1 && BST_getBalanceFactor(pTree->pRight) <= 0) return BST_leftRotate(pTree); // LL rotation
  if(nBalance > 1 && BST_getBalanceFactor(pTree->pLeft) < 0){ // LR rotation
    pTree->pLeft = BST_leftRotate(pTree->pLeft);
    return BST_rightRotate(pTree);
  }
  if(nBalance < -1 && BST_getBalanceFactor(pTree->pRight) > 0){ // RL rotation
    pTree->pRight = BST_rightRotate(pTree->pRight);
    return BST_leftRotate(pTree);
  }
  return pTree;
}

int max(int i, int j){
  if (i < j) return j;
  return i;
}

SNode *BST_leftRotate(SNode *pTree){
    SNode *pTempRight = pTree->pRight; // pointer to right subtree of the tree
    SNode *pTempLeft = pTempRight->pLeft; // pointer to the left subtree of right subtree of tree
    pTempRight->pLeft = pTree; 
    pTree->pRight = pTempLeft;
    pTree->nHeight = max(BST_getHeight(pTree->pRight), BST_getHeight(pTree->pLeft)) + 1;
    pTempRight->nHeight = max(BST_getHeight(pTempRight->pRight), BST_getHeight(pTempRight->pLeft)) + 1;
    return pTempRight;
}

SNode *BST_rightRotate(SNode *pTree){
  SNode *pTempLeft = pTree->pLeft;  // pointer to left subtree of the tree
  SNode *pTempRight = pTempLeft->pRight; // pointer to the right subtree of left subtree of tree
  pTempLeft->pRight = pTree;
  pTree->pLeft = pTempRight;
  pTree->nHeight = max(BST_getHeight(pTree->pRight), BST_getHeight(pTree->pLeft)) + 1;
  pTempLeft->nHeight = max(BST_getHeight(pTempLeft->pRight), BST_getHeight(pTempLeft->pLeft)) + 1;
  return pTempLeft;
}