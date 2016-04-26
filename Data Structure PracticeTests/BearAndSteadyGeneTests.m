//
//  BearAndSteadyGeneTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/26/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "BearAndSteadyGene.h"

@interface BearAndSteadyGeneTests : XCTestCase

@end

@implementation BearAndSteadyGeneTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testCase0
{
    int result = BSG_RunTestCase(BSG_case0Input);
    XCTAssert(result==BSG_case0Output);
}

- (void)testCase1
{
    int result = BSG_RunTestCase(BSG_case1Input);
    XCTAssert(result==BSG_case1Output);
}

- (void)testCase2
{
    int result = BSG_RunTestCase(BSG_case2Input);
    XCTAssert(result==BSG_case2Output);
}

- (void)testCase3
{
    int result = BSG_RunTestCase(BSG_case3Input);
    XCTAssert(result==BSG_case3Output);
}

- (void)testCase9
{
    int result = BSG_RunTestCase(BSG_case9Input);
    XCTAssert(result==BSG_case9Output);
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
