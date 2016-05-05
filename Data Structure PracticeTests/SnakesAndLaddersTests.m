//
//  SnakesAndLaddersTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/4/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "TestCaseIOUtils.h"
#import "SnakesAndLadders.h"

#include <unistd.h>
#include <sys/shm.h>

@interface SnakesAndLaddersTests : XCTestCase

@end

@implementation SnakesAndLaddersTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (const char *)inputPathForTestCase:(int)caseNumber
{
    NSBundle *bundle = [NSBundle bundleForClass:[self class]];
    NSString *caseName = [NSString stringWithFormat:@"SnakesAndLaddersTestCase%dInput",caseNumber];
    NSString *path = [bundle pathForResource:caseName ofType:@"txt"];
    XCTAssertNotNil(path);
    return path.UTF8String;
}

- (const char *)outputPathForTestCase:(int)caseNumber
{
    NSBundle *bundle = [NSBundle bundleForClass:[self class]];
    NSString *caseName = [NSString stringWithFormat:@"SnakesAndLaddersTestCase%dOutput",caseNumber];
    NSString *path = [bundle pathForResource:caseName ofType:@"txt"];
    XCTAssertNotNil(path);
    return path.UTF8String;
}

- (void)testCase0{
    const char *path = [self inputPathForTestCase:0];
    FILE *fp;
    OpenTestCaseInputFile(fp, path);
    char output[1000];
    SnakesAndLaddersRunTestCase(output);
    printf("output: %s\n",output);
    CloseTestCaseInputFile(fp);
}

- (void)testCase1{
    const char *path = [self inputPathForTestCase:1];
    FILE *fp;
    char output[1000];
    OpenTestCaseInputFile(fp, path);
    SnakesAndLaddersRunTestCase(output);
    CloseTestCaseInputFile(fp);
}

- (void)testReadFromStdOut
{
    char *mycapture = CaptureStdOut(100);    // capture first 100 bytes
    printf("Hello World");           // sample test string
    sleep(1);
    fprintf(stderr, "\nCaptured: %s\n", mycapture);
    
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
