//
//  StringSearching.c
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/10/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#include "StringSearching.h"

#define d   256     //ASCII Alphabet size

void RabinKarpSearch(char *pattern, char *text, int q){
    
    int M = (int)strlen(pattern);
    int N = (int)strlen(text);
    int i,j;
    int p = 0; //hash val for pattern
    int t = 0; //hash val for text
    int h = 1;
    
    for (i = 0; i < M-1; i++) h = (h*d)%q;
    
    //Get hash value of pattern and first text window
    for (i = 0; i < M; i++){
        p = (d*p + pattern[i])%q;
        t = (d*t + text[i])%q;
    }
    
    //Slide pattern over text one char at a time
    for (i = 0; i <= (N-M); i++){
        
        //If current hash values of pattern and text window match...
        if (p == t){
            
            //Walk through each char in the pattern and compare to text until we find a non-match
            for (j = 0; j < M; j++){
                if (text[i+j] != pattern[j]){
                    break;
                }
            }
            //if j was incremented to the length of pattern (M), we found a match
            if (j == M){
                printf("Pattern matches at index %d\n",i);
            }
            
            //Now calculate the hash value for the next text window by removing the leading digit and adding the trailing digit
            if ( i < N-M ){
                t = (d*(t- text[i]*h) + text[i+M])%q;
                //Make sure t is positive
                if (t < 0){
                    t = t+q;
                }
            }
        }
        
    }
    
}

int EqualCharSets(char *a, char *b){
    
    for (int i = 0; i < d; i++){
        if (a[i] != b[i]){
            return 0;
        }
    }
    
    return 1;
}
