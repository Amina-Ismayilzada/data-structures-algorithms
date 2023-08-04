#include<stdio.h>
#include<stdlib.h>

// Function signatures: 
int* reallocateArray (int *npOldArray, int nOldSize, int nNewSize);  // to extend the array
int addValue(int nValue, int **nppArray, int *npArraySize); // to add provided value to the array
int removeValue(int nValue, int **nppArray, int *npArraySize); // to remove provided value from array
  
int main(){
  int i,n,nArraySize=5,*npArray;
  char cContinue;
  
  if ((npArray=calloc(nArraySize,sizeof(int)))==NULL) {
    fprintf(stderr,"\nWarning! Memory allocation error\n");
    exit(1);
  }
  npArray[0]=10; npArray[1]=13; npArray[2]=6;
  printf("Contents of array t[]     : ");
  for (i=0;i<nArraySize;i++) printf("%d ",npArray[i]);
  do{
    printf("\nEnter a positive integer to add or negative integer to suppress : ");
    scanf("%d",&n);
    if (n>0) addValue (n, &npArray, &nArraySize);
    else removeValue (n, &npArray, &nArraySize);
    printf("New contents of array t[] : ");
    for (i=0;i<nArraySize;i++) printf("%d ",npArray[i]);
    printf("\nSize: %d\n", nArraySize);
    printf("\nDo you want to continue (y/n) ?  : "); scanf(" %c",&cContinue);
  } while(cContinue=='y');
  exit(0);
}

// Functions' implementations: 
int* reallocateArray (int *npOldArray, int nOldSize, int nNewSize){
    if (nOldSize == nNewSize) return npOldArray; //return the old array if the size is same
    if (nOldSize < nNewSize) {
        int *npNewArray = (int *)realloc(npOldArray, nNewSize*sizeof(int));
        if(!npNewArray) return npOldArray; // error allocating memory
        return npNewArray;
    }
    return npOldArray; // in case of incorrect size, return the original array
}

int addValue(int nValue, int **nppArray, int *npArraySize){
    int i;
    for(i = 0; i < *npArraySize; i++){ // if there is an empty space for element in array
        if((*nppArray)[i] == 0){
            (*nppArray)[i] = nValue;
            return 0;
        }
    }
    // if the array is full, extend the array and increase its size
    *nppArray = reallocateArray(*nppArray, *npArraySize, ++(*npArraySize));
    (*nppArray)[i] = nValue;
    return 0;
}

int removeValue(int nValue, int **nppArray, int *npArraySize){
    int i;
    if ((*nppArray)[0] == 0) {
        fprintf(stderr," ------ The array is already empty!  ------ \n");
        return 1;
    }
    for(i = 0;  i < *npArraySize; i++ ){ // in case array is not full, find the last nonzero element
        if((*nppArray)[i] == 0){
            (*nppArray)[i-1] = 0; 
            return 0;
        }
    }
    (*nppArray)[i-1] = 0; //if array is full, delete the last element
    return 0;
}