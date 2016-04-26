//
//  StringPermutations.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/22/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "StringPermutations.h"


typedef struct Set_{
    int numUniques;
    int table[256];
}Set;

void SetClear(Set *set){
    set->numUniques = 0;
    memset(set->table, 0, sizeof(int) * 256);
}

void SetInit(Set *set){
    SetClear(set);
}

int NumOccurencesOfValue(Set *set, int val){
    
    if (val < 0 || val > 255){
        return -1;
    }
    
    return (set->table[val]);
}

int SetContainsValue(Set *set, int val){
    return (NumOccurencesOfValue(set, val) > 0);
}

int SetAddValue(Set *set, int val){
    
    int count = NumOccurencesOfValue(set, val);
    if (count == -1){
        return count;
    }else if (count == 0){
        set->numUniques++;
    }
    
    count++;
    set->table[val] = count;
    return count;
}

int SetRemoveValue(Set *set, int val){
    int count = NumOccurencesOfValue(set, val);
    if (count == -1){
        return count;
    }
    
    set->table[val] = 0;
    set->numUniques--;
    return 0;
}

int SetUniqueValues(Set *set, int *uniqueValues){
    
    int outIdx = 0;
    for (int i = 0; i < 256; i++) {
        if (SetContainsValue(set, i)){
            uniqueValues[outIdx] = i;
            outIdx++;
        }
    }
    
    return 0;
}

int CompareStrings(const void *key1, const void *key2){
    
    return strcmp(key1, key2);
}

void PrintRanks(int *ranks, int n){
    for (int i =0; i < n; i ++) {
        int rank =  ranks[i];
        if (rank > 0){
            printf("%d:%d ",i,rank);
        }
    }
    printf("\n");
}

void PrintArray(int *arr, int n){
    
    for (int i = 0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void swap(int *ptr1, int *ptr2){
    int buf = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = buf;
}

int partition(int *ar, int l, int h, int *rank, int numRanks){
    int i;
    int p;
    int j;
    p = h;
    j = l;
    for (i = l; i < h; i++){
        if (ar[i] < ar[p]){
            swap(&ar[i],&ar[j]);
            rank[ar[j]] = (numRanks-j);
            rank[ar[i]] = (numRanks-i);
            j++;
        }
    }
    swap(&ar[p],&ar[j]);
    rank[ar[j]] = (numRanks-j);
    rank[ar[p]] = (numRanks-p);
    return (j);
}

void quicksort(int *ar, int l, int h, int *rank, int numRanks) {
    
    if ((h-l)>0){
        int p = partition(ar,l,h,rank,numRanks);
        quicksort(ar,l,p-1,rank,numRanks);
        quicksort(ar,p+1,h,rank,numRanks);
    }
}

int SortedIndexForRank(int rank, int maxRank){
    return maxRank-rank;
}

int PermuteString(char *output, const char *input, int length, int permuteIdx, Set *charSet, int *sortedUniques, int *ranks, int *indexSet){
    
    if (permuteIdx>=length || permuteIdx < 0 || charSet->numUniques <= 1){
        strcpy(output, "no answer");
        return -1;
    }
    
    // do stuff...
    char myString[length+1];
    
    char toPermute = input[permuteIdx];
    int rank = ranks[(int)toPermute];
    
    if (rank <= 1 || rank > charSet->numUniques){
        return 0;
    }
    
    
    int nextIdx = SortedIndexForRank(--rank,charSet->numUniques);
    int toSwap = sortedUniques[nextIdx];
    int idx = indexSet[toSwap];
    
    if (idx < 0 || idx > 256){
        return 0;
    }
    
    strcpy(myString, input);
    
    myString[permuteIdx] = (char)toSwap;
    myString[idx] = toPermute;
    
    printf("\t#%d: will mutate %s by swapping %c (rank %d, idx %d) with %c (rank %d, idx %d), result: %s\n",
           permuteIdx,
           input,
           toPermute,
           rank,
           permuteIdx,
           toSwap,
           rank-1,
           idx,
           myString);
    
    int cmp = CompareStrings((void *)myString, (void*)input);
    
    if (cmp <= 0){
        return 0;
    }
    
    strcpy(output, myString);
    
    return 1;
}

int StringLength(const char *string){
    
    char *ptr = (char *)string;
    int len = 0;
    while (*ptr) {
        len++;
        ptr++;
    }
    return len;
}

int SwapChars(char *char1, char *char2){
    char tmp = *char2;
    *char2 = *char1;
    *char1 = tmp;
    return 0;
}

int ReverseString(char *string, int l, int h){
    
    while (l < h) {
        SwapChars(&string[l], &string[h]);
        l++;
        h--;
    }
    
    return 0;
}

int RunTestCase(char *output, const char *input){
    int length = StringLength(input);
    char inputCopy[length];
    strcpy(inputCopy, input);
    int i = -1;
    int idx = 0;
    int max = length-1;
    
    while (idx < max) {
        char a = inputCopy[idx];
        char b = inputCopy[idx+1];
        if (a < b){
            i = idx;
        }
        
        idx++;
    }
    
    if (i < 0){
        strcpy(output, "no answer");
        return 0;
    }
    
    int j = i+1;
    idx = j+1;
    
    while (idx < length) {
        
        if (inputCopy[idx] > inputCopy[i]){
            j = idx;
        }
        
        idx++;
    }
    
    SwapChars(&inputCopy[i], &inputCopy[j]);
    ReverseString(inputCopy, i+1, max);
    strcpy(output, inputCopy);
    return 0;
}

int RunTestCase2(char *output, const char *input){
    printf("\n\n");
    printf("running test case with input string %s\n",input);
    char *inputPtr = (char *)input;
    Set charset;
    SetInit(&charset);
    int len = 0;
    int indexSet[256];
    memset(indexSet, -1, sizeof(int) * 256);
    
    while (*inputPtr) {
        SetAddValue(&charset, (int)(*inputPtr));
        int aChar = (int)(*inputPtr);
        indexSet[aChar] = len;
        inputPtr++;
        len++;
    }
    
    int i = len-1;
    int retval = 0;
    
    int uniques[charset.numUniques];
    SetUniqueValues(&charset, uniques);
    int ranks[256];
    memset(ranks, 0, sizeof(int) * 256);
    quicksort(uniques, 0, charset.numUniques-1, ranks, charset.numUniques);
    
    printf("\tsorted uniques: ");
    PrintArray(uniques, charset.numUniques);
    printf("\tranks: ");
    PrintRanks(ranks, 256);
    
    while (1) {
        
        retval = PermuteString(output, input, len, i, &charset, uniques, ranks, indexSet);
        
        if (retval != 0){
            break;
        }
        
        i--;
    }
    
    printf("\n\n");
    
    return 0;
}