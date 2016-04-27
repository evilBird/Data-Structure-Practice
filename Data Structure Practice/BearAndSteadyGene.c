//
//  BearAndSteadyGene.c
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/26/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#include "BearAndSteadyGene.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define HUGE_VALUE 100000000

void PrintCharCounts(int *counts, char *alphabet){
    int len = (int)strlen(alphabet);
    for (int i = 0; i<len; i++) printf("%c ",alphabet[i]);
    printf("\n");
    for (int i = 0; i<len; i++) printf("%d ",counts[(int)alphabet[i]]);
    printf("\n");
}

char NextReplacementChar(char toReplace, int len, char *alphabet, int *counts, int *flag){
    
    int numChars = (int)strlen(alphabet);
    char next = '\0';
    for (int i = 0; i < numChars; i ++){
        next = alphabet[i];
        if ( next != toReplace && counts[(int)next] < len ){
            *flag = 0;
            break;
        }else{
            *flag = 1;
        }
    }
    
    return next;
}

int CountsAreSteady(int steadyCt, int *counts, char *alphabet){
    int numChars = (int)strlen(alphabet);
    int retval = 1;
    for (int i = 0; i < numChars; i ++){
        if ( counts[(int)alphabet[i]] != steadyCt ){
            retval = 0;
            break;
        }
    }
    
    return retval;
}

void UndoCountChanges(int *counts, int *changes, char *alphabet){
    int numChars = (int)strlen(alphabet);
    for (int i = 0; i < numChars; i++){
        counts[(int)alphabet[i]] -= changes[(int)alphabet[i]];
    }
}

int BSG_RunTestCase(char *input) {
    
    int len = (int)strlen(input);
    char string[len+1];
    sscanf(input,"%d\n%s",&len,string);
    int n = len/4;
    int counts[256];
    memset(counts,0,sizeof(int)*256);
    char *alphabet = "AGCT";
    for (int i = 0; i < len; i++) counts[(int)string[i]]++;
#ifdef BSG_DEBUG
    printf("%s\n",string);
    printf("length %d min %d\n",len,len/4);
    printf("init counts:\n");
    PrintCharCounts(counts,alphabet);
#endif
    char stringCopy[len+1];
    strcpy(stringCopy,string);
    int i = 0;  //start index
    int j = 0;  //stop index
    int flag = 0;
    int minLength = HUGE_VALUE;
    int steady = 0;
    int lastSwap = -1;
    int maxIndex = len-1;
    for (; i < len-1; i++){
        
#ifdef BSG_DEBUG
        printf("\nexecuting outer loop i = %d, j = %d, minLength = %d, flag = %d\n",
               i,j,minLength,flag);
        printf("counts:\n");
        PrintCharCounts(counts,alphabet);
#endif
        
        int curLength = HUGE_VALUE;
#ifdef BSG_DEBUG
        printf("inner loop starting:\n");
#endif
        
        for (; j < len; j++){
            curLength = (j - i) + 1;
#ifdef BSG_DEBUG
            printf("executing inner loop i = %d j = %d curLength %d minLength %d flag %d\n",
                   i,j,curLength,minLength,flag);
#endif

            if (curLength >= minLength){
#ifdef BSG_DEBUG
                printf("PREV MIN LENGTH EXCEEDED @ %d\n",curLength);
#endif
                break;
            }
            
            if ( counts[(int)stringCopy[j]] > n ){
                
                char tmp = stringCopy[j];
                stringCopy[j] = NextReplacementChar(tmp, n, alphabet, counts, &flag);
                
                if (flag) {
#ifdef BSG_DEBUG
                    printf("FLAG!!!\n");
#endif
                    PrintCharCounts(counts, alphabet);
                    break;
                }else{
#ifdef BSG_DEBUG
                    printf("replaced %c with %c\n",tmp,stringCopy[i]);
#endif
                }
                
                counts[(int)tmp]--;
                counts[(int)stringCopy[j]]++;
                lastSwap = j;
            }
            
            steady = CountsAreSteady(n, counts, alphabet);
            
#ifdef BSG_DEBUG
            printf("counts:\n");
            PrintCharCounts(counts,alphabet);
#endif
            minLength = ( steady && curLength < minLength ) ? curLength : minLength;
            
            if (steady){
#ifdef BSG_DEBUG
                printf("STEADY @ %d\n",curLength);
#endif
                break;
            }
            
        }
        
        if (flag) break;
#ifdef BSG_DEBUG
        printf("finished inner loop i = %d j = %d\n",i,j);
        PrintCharCounts(counts,alphabet);
#endif

        if ( stringCopy[i] != string[i]){
            
            counts[(int)stringCopy[i]]--;
            counts[(int)string[i]]++;
            
        }
        
        
#ifdef BSG_DEBUG
        printf("min length: %d\n",minLength);
        printf("cur length: %d\n\n",curLength);
#endif
        j = lastSwap;
        if ( j < i){
            j = i;
        }
        
    }
    

    
    minLength = ( minLength == HUGE_VALUE ) ? 0 : minLength;
    
    printf("%d\n",minLength);
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return minLength;
}