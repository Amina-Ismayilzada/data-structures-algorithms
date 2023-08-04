#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* node structure for Huffman tree */
typedef struct TNode {
  char cVal; // item
  int nFreq; // frequency of item
  struct TNode *pLeft; // pointer to left node/subtree
  struct TNode *pRight; // pointer to right node/subtree
} STNode;

/* linked list node to store nodes in increasing order of frequency */
typedef struct LLNode{
  STNode *pNode; // Huffman tree node
  struct LLNode *pNext; // link to next node
} SLLNode;

/* function to create new node for Huffman tree*/
STNode *newTreeNode(char cVal, int nFreq);
/* function to create new node for linked list*/
SLLNode *newLLNode(STNode *pNode);
/* function to insert a node into linked list in increasing order of freq */
void insertTreeNode(SLLNode **ppList, STNode *pNode);
/* function to build a Huffman tree from a given input string */
STNode *buildHuffmanTree(char *str);
/* function to print the Huffman tree */
void printHuffmanCodes(STNode *pNode,int code[],int nTop);
/* function to decode a Huffman-encoded string using the given Huffman tree */
void decodeHuffman(STNode *pNode, char *encodedStr);

int main(int argc, char const *argv[]){
  char str[]="si ton tonton tond mon tonton";
  STNode *pRoot=buildHuffmanTree(str);
  int code[256], nTop=0;
  printf("Huffman codes for \"%s\":\n", str);
  printHuffmanCodes(pRoot,code,nTop);

  char encodedStr[] = "110111100111100100111100100100100111100100111000111110101001111001001001001";
  printf("%s => ", encodedStr);
  decodeHuffman(pRoot, encodedStr);printf("\n");
  return 0;
}

STNode *newTreeNode(char cVal, int nFreq){ 
  STNode *pTemp=(STNode *)malloc(sizeof(STNode));
  pTemp->cVal=cVal; pTemp->nFreq=nFreq;
  pTemp->pLeft=NULL; pTemp->pRight=NULL;
  return pTemp;
}

SLLNode *newLLNode(STNode *pNode){
  SLLNode *pTemp=(SLLNode *)malloc(sizeof(SLLNode));
  pTemp->pNode=pNode;
  pTemp->pNext=NULL;
  return pTemp;
}

void insertTreeNode(SLLNode **ppList, STNode *pNode){
  SLLNode *pTemp=newLLNode(pNode);
  if(!(*ppList) || (*ppList)->pNode->nFreq > pTemp->pNode->nFreq){ //if inserting node is of greater frequency
    pTemp->pNext=*ppList; // insert the node as head of ll
    *ppList=pTemp;
  }else{ 
    SLLNode *pCurr=*ppList; 
    // loop through ll and find the correct position to insert node
    for(;pCurr->pNext && (pCurr->pNext)->pNode->nFreq <= pNode->nFreq;pCurr=pCurr->pNext); 
    pTemp->pNext=pCurr->pNext; 
    pCurr->pNext=pTemp;
  }
}

STNode *buildHuffmanTree(char *str){
  int freq[256]={0}; // to store freq of each character in string
  for(int i=0;i<strlen(str);i++) freq[str[i]]++; // iterate through string and update the corresponding element in the freq array
  SLLNode *pList=NULL;
  for(int i=0;i<256;i++){
    if(freq[i]>=1){ // create a new node for each character with freq at least 1
      STNode *pNode=newTreeNode(i,freq[i]);
      insertTreeNode(&pList,pNode); //insert to ll
    }
  }
  while(pList->pNext!=NULL){
    STNode *pLeft=pList->pNode; // right and left nodes with lowest freq
    STNode *pRight=pList->pNext->pNode;
    STNode *pParent=newTreeNode('\0', pLeft->nFreq+pRight->nFreq); //parent node with sum of freq of right and left nodes
    pParent->pLeft=pLeft; pParent->pRight=pRight;
    pList=(pList->pNext)->pNext;
    insertTreeNode(&pList, pParent);
  }
  return pList->pNode; // return root node(the last node of list)
}

void printHuffmanCodes(STNode *pNode,int code[],int nTop){
  if(pNode->pLeft){ 
    code[nTop]=0;
    printHuffmanCodes(pNode->pLeft,code,nTop+1);
  }
  if(pNode->pRight){
    code[nTop]=1;
    printHuffmanCodes(pNode->pRight, code, nTop+1);
  }
  if(!pNode->pLeft && !pNode->pRight){
    printf("%c: ",pNode->cVal);
    for(int i=0;i<nTop;i++) printf("%d", code[i]);
    printf("\n");
  }
}

void decodeHuffman(STNode *pNode, char *encodedStr){
  STNode *pCurr=pNode;
  for(int i=0;encodedStr[i] != '\0';i++){
    if(encodedStr[i] == '0'){ // if current bit is '0', go to the left child
      pCurr = pCurr->pLeft;
    }else if(encodedStr[i] == '1'){ // if current bit is '1', go to the right child
      pCurr = pCurr->pRight;
    }

    if(!pCurr->pLeft && !pCurr->pRight){ // if leaf node is reached, print the character
      printf("%c", pCurr->cVal);
      pCurr = pNode; // reset current node to root node for next character decoding
    }
  }
}
