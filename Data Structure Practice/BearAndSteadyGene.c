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
//#define BSG_DEBUG

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
    int changes[256];
    
    for (; i < len-1; i++){
        j = i+1;
        memset(changes,0,sizeof(int)*256);
#ifdef BSG_DEBUG
        printf("\nexecuting outer loop i = %d, j = %d, minLength = %d, flag = %d\n",
               i,j,minLength,flag);
        printf("counts:\n");
        PrintCharCounts(counts,alphabet);
        
#endif
        if ( counts[(int)string[i]] > n ){
            
            stringCopy[i] = NextReplacementChar(string[i], n, alphabet, counts, &flag);
            if (flag) break;
            counts[(int)string[i]]--;
            counts[(int)stringCopy[i]]++;
            changes[(int)string[i]]--;
            changes[(int)stringCopy[i]]++;
            
            int curLength = HUGE_VALUE;
#ifdef BSG_DEBUG
            printf("replaced char %c with %c...starting inner loop\n",
                   string[i],stringCopy[i]);
            printf("inner loop starting counts:\n");
            PrintCharCounts(counts,alphabet);
#endif
            for (j = i+1; j < len; j++){
                
                curLength = (j - i) + 1;
#ifdef BSG_DEBUG
                printf("executing inner loop i = %d j = %d curLength %d minLength %d flag %d\n",
                       i,j,curLength,minLength,flag);
#endif
                if ( counts[(int)string[j]] > n ){
                    
                    stringCopy[j] = NextReplacementChar(string[j], n, alphabet, counts, &flag);
                    counts[(int)string[j]]--;
                    counts[(int)stringCopy[j]]++;
                    changes[(int)string[j]]--;
                    changes[(int)stringCopy[j]]++;
#ifdef BSG_DEBUG
                    printf("replaced char %c with char %c\n",string[j],stringCopy[j]);
                    
#endif
                }
                
#ifdef BSG_DEBUG
                printf("counts:\n");
                PrintCharCounts(counts,alphabet);
#endif
                if (CountsAreSteady(n, counts, alphabet)){
                    minLength = ( curLength < minLength ) ? curLength : minLength;
#ifdef BSG_DEBUG
                    printf("counts are steady with minLength %d...WILL BREAK INNER LOOP\n",minLength);
#endif
                    break;
                }
                
                if ( curLength > minLength ){
#ifdef BSG_DEBUG
                    printf("curLength %d > minLength %d...WILL BREAK INNER LOOP\n",curLength, minLength);
#endif
                    break;
                }
                
                if (flag) break;
            }
        }
        
        if (flag) break;
#ifdef BSG_DEBUG
        printf("finished inner loop i = %d j = %d\n",i,j);
        PrintCharCounts(counts,alphabet);
        printf("undo changes:\n");
        PrintCharCounts(changes,alphabet);
#endif
        UndoCountChanges(counts, changes, alphabet);
        /*
         while ( j >= i ){
         
         if ( stringCopy[j] != string[j] ){
         counts[(int)stringCopy[j]]--;
         counts[(int)string[j]]++;
         #ifdef BSG_DEBUG
         printf("undo replace char %c with %c\n",string[j],stringCopy[j]);
         #endif
         }
         stringCopy[j] = string[j];
         j--;
         }
         */
#ifdef BSG_DEBUG
        printf("updated counts:\n");
        PrintCharCounts(counts,alphabet);
        printf("min length: %d\n\n",minLength);
#endif
    }
    
    minLength = ( minLength == HUGE_VALUE ) ? 0 : minLength;
    
    printf("%d\n",minLength);
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return minLength;
}