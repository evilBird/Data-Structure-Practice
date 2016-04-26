//
//  StringPermutations.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/22/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#ifndef StringPermutations_h
#define StringPermutations_h
#import <Foundation/Foundation.h>

void PrintArray(int *arr, int n);
void swap(int *ptr1, int *ptr2);
int partition(int *ar, int l, int h, int *rank, int numRanks);
void quicksort(int *ar, int l, int h, int *rank, int numRanks);
int RunTestCase(char *output, const char *input);

#endif /* StringPermutations_h */
