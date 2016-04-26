//
//  Data_Structure_PracticeTests.m
//  Data Structure PracticeTests
//
//  Created by Travis Henspeter on 4/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "MyDataStructures.h"
#import "MyDataStructureUtils.h"
#import "StringPermutations.h"

#define DATA_COUNT  10

@interface Data_Structure_PracticeTests : XCTestCase

@end

@implementation Data_Structure_PracticeTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}
- (void)testProblem19_1{
    
}

#define Blank   0
#define X       13
#define O       17

#define UL      {0,0}
#define LL      {2,0}

#define UR      {0,2}
#define LR      {2,2}

typedef struct TicTacToe_{
    int board[3][3];
}TicTacToe;

void ClearBoard(TicTacToe *ticTacToe){
    for (int i = 0; i < 3; i ++)
        for (int j = 0; j < 3; j++)
            ticTacToe->board[i][j] = Blank;
}

void PrintBoard(TicTacToe *ticTacToe){
    for (int i = 0; i < 3; i ++){
        printf("\n");
        for (int j = 0; j < 3; j ++){
            printf("[%d] ",(ticTacToe->board[i][j]));
        }
    }
    printf("\n");
}

void RandomizeBoard(TicTacToe *ticTacToe){
    int states[3] = {Blank,X,O};
    for (int i = 0; i < 3; i ++)
        for (int j = 0; j < 3; j++)
            ticTacToe->board[i][j] = states[(int)arc4random_uniform(3)];
}

int SumRow(TicTacToe *ticTacToe, int row){
    int sum = 0;
    for (int j = 0; j < 3; j++)
        sum += ticTacToe->board[row][j];
    return sum;
}

int SumColumn(TicTacToe *ticTacToe, int col){
    int sum = 0;
    for (int i = 0; i < 3; i++)
        sum += ticTacToe->board[i][col];
    return sum;
}

int SumDiagnoal(TicTacToe *ticTacToe, int *start, int *stop){
    int i_0 = start[0];
    int i_1 = stop[0];
    int i_increment = ( i_0 > i_1 ) ? ( -1 ) : ( 1 );
    int j_0 = start[1];
    int j_1 = stop[1];
    int j_increment = ( j_0 > j_1 ) ? ( -1 ) : ( 1 );
    int i = i_0;
    int j = j_0;
    int sum = 0;
    
    while (i != i_1 && j != j_1) {
        
        sum += ticTacToe->board[i][j];
        
        i+=i_increment;
        j+=j_increment;
    }
    
    return sum;
}

int WinnerIsX(int sum){
    float rat = ((float)sum/(float)X);
    int result = ((rat - 3.) == 0.0);
    return result;
}

int WinnerIsO(int sum){
    float rat = ((float)sum/(float)O);
    int result = ((rat - 3.) == 0.0);
    return result;
}

int FindWinner(TicTacToe *ticTacToe){
    
    int winner = Blank;
    
    for (int i = 0; i < 3; i ++) {
        
        int rowResult = SumRow(ticTacToe, i);
        
        if(WinnerIsX(rowResult)){
            winner = X;
            break;
        }else if (WinnerIsO(rowResult)){
            winner = O;
            break;
        }
    }
    
    if (winner != Blank) {
        return winner;
    }
    
    for (int j = 0; j < 3; j ++){
        
        int colResult = SumColumn(ticTacToe, j);
        if(WinnerIsX(colResult)){
            winner = X;
            break;
        }else if (WinnerIsO(colResult)){
            winner = O;
            break;
        }
    }
    
    if (winner != Blank){
        return winner;
    }
    int start1[2] = UL;
    int stop1[2] = LR;
    
    int diag1Result = SumDiagnoal(ticTacToe, start1, stop1);
    
    if(WinnerIsX(diag1Result)){
         return X;
    }else if (WinnerIsO(diag1Result)){
        return O;
    }
    
    int start2[2] = LL;
    int stop2[2] = UR;
    
    int diag2Result = SumDiagnoal(ticTacToe, start2, stop2);
    
    if(WinnerIsX(diag2Result)){
        return X;
    }else if (WinnerIsO(diag2Result)){
        return O;
    }
    
    return Blank;
}

- (void)doTestProblem19_2{
    TicTacToe ttt;
    ClearBoard(&ttt);
    RandomizeBoard(&ttt);
    PrintBoard(&ttt);
    int winner = FindWinner(&ttt);
    if (winner == X) {
        printf("\nX WINS\n");
    }else if (winner == O){
        printf("\nO WINS\n");
    }else{
        printf("\nNO WINNER\n");
    }
    
    printf("\n");
}

- (void)testProblem19_2{
    
    int iter = 50;
    for (int i = 0; i < iter; i ++) {
        [self doTestProblem19_2];
    }
}

int getMax(int val1, int val2){
    int c = val1 - val2;
    int k = ( c >> 31 );
    int k1 = k & 0x1;
    int max = val1 - k1 * c;
    return max;
}

- (void)testProblem19_4{
    int iters = 20;
    for (int i = 0; i < iters; i ++) {
        int val1 = arc4random_uniform(1000);
        int val2 = arc4random_uniform(1000);
        int max = getMax(val1, val2);
        printf("\n max of %d and %d = %d\n",val1,val2,max);
    }
}

- (void)testAHashTable
{
    
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testSinglyLinkedListStuff{
    
    SinglyLinkedList *list = SinglyLinkedListCreate(MatchIntegersFunction);
    
    for (int i = 0; i < DATA_COUNT; i ++) {
        int* randomInteger = (int*)(malloc(sizeof(int)));
        randomInteger[0] = arc4random_uniform(10000);
        SinglyLinkedListAppend(list, (void*)randomInteger);
    }
    
    SinglyLinkedListPrintVisual(list, FormatIntegerData);
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}


@end
