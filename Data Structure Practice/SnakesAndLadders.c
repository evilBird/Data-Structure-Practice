//
//  SnakesAndLadders.c
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/4/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#include "SnakesAndLadders.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "TestCaseIOUtils.h"

int SnakesAndLaddersRunTestCase(char *results){
    
    int T;
    scanf("%d",&T);
    char *ptr = results;
    //printf("T = %d\n",T);
    for (int t = 0; t < T; t++){
        int N;
        scanf("%d",&N);
        //printf("N Ladders = %d\n",N);
        int ladders[101];
        memset(ladders,0,sizeof(int)*100);
        for (int n = 0; n < N; n++){
            int start,end;
            scanf("%d %d",&start,&end);
            //printf("Ladder %d: %d %d\n",n,start,end);
            ladders[end] = start;
        }
        
        int M;
        scanf("%d",&M);
        //printf("M Snakes = %d\n",M);
        int snakes[101];
        memset(snakes, 0, sizeof(int)*100);
        for (int m = 0; m < M; m++){
            int start,end;
            scanf("%d %d",&start,&end);
            //printf("Snake %d: %d %d\n",m,start,end);
            snakes[start] = end;
        }
        
        int spos = 1;
        int epos = 100;
        int pos = epos;
        int steps = 0;
        int rolls = 0;
        while (pos > spos) {
            if (ladders[pos-1] == 0){
                pos--;
                steps++;
                if (steps/6 == 1){
                    steps = 0;
                    rolls++;
                }
            }else{
                rolls++;
                //printf("ladder from %d to %d\n",pos,ladders[pos-1]);
                pos = ladders[pos-1];
            }
            
        }
        
        int size = sprintf(ptr, "rolls = %d\n",rolls);
        ptr+=size;
        
    }
    return 0;
}
