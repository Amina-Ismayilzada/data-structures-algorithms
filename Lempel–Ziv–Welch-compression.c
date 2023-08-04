#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DICT_SIZE 4096 // Maximum size of the dictionary

char *str = "eddie edited it did eddie edit it"; //string to be compressed
void encode(char *str); // function to encode the input string

int main() {
  encode(str);
  return 0;
}

void encode(char *str){
  int i, j, nCode, nDictSize = 0;
  char **ppDict=(char **)malloc(DICT_SIZE*sizeof(char *));
  
  char initialDict[256] = ""; // extract initial dictionary(letters) from the input string
  for (i=0;i<strlen(str);i++) {
    char c[2]={str[i], '\0'};
    if (!strchr(initialDict, c[0])) {
      strcat(initialDict, c);
    }
  }
  nDictSize = strlen(initialDict); // get the size of initial dict
  
  for (i = 0; i < nDictSize; i++) {  //copy the initial dictionary to ppDict
    char *pNewStr=(char *)malloc(2*sizeof(char));
    pNewStr[0]=initialDict[i];
    pNewStr[1]='\0';
    ppDict[i]=pNewStr;
  }
  
  // encoding process
  char *pCurrStr=(char *)malloc(2*sizeof(char));
  pCurrStr[0]=str[0]; 
  pCurrStr[1]='\0';
  
  for(i=1;i<strlen(str);i++){ // iterate over the remaining characters of the input string
    char *pNewStr=(char *)malloc((strlen(pCurrStr) + 2)*sizeof(char)); 
    strcpy(pNewStr, pCurrStr);
    pNewStr[strlen(pCurrStr)]=str[i];
    pNewStr[strlen(pCurrStr)+1]='\0';

    for(j=0;j<nDictSize;j++) {  // check if the new string exists in the dictionary
      if(strcmp(ppDict[j], pNewStr)==0) { // if it does, store its index in nCode and break the loop
        nCode=j; 
        break;
      }
    }

    if(j==nDictSize) { // if it doesn't exist, add to dict
      ppDict[nDictSize]=(char *)malloc((strlen(pNewStr)+1)*sizeof(char)); 
      strcpy(ppDict[nDictSize], pNewStr);
      nDictSize++;
      pCurrStr=(char *)malloc(2*sizeof(char)); // reset the current string to the current character
      pCurrStr[0]=str[i];
      pCurrStr[1]='\0';
    } else { // if new string exists in dict, set the current string to new string
      pCurrStr=(char *)malloc((strlen(pNewStr)+1)*sizeof(char));
      strcpy(pCurrStr, pNewStr);
    }

    free(pNewStr);
  }

  // print the dictionary and free memory
  for (i = 0;i<nDictSize;i++) {
    printf("%d: %s\n", i, ppDict[i]); 
    free(ppDict[i]);
  }
  free(ppDict); 
  free(pCurrStr);
}