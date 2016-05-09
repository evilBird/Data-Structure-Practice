//
//  SnakesAndLaddersTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/4/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "TestingIOUtilities.h"
#import "SnakesAndLadders.h"
#import "GraphPractice.h"

static NSString *kInputFileFormat   = @"SnakesAndLaddersTestCase%dInput";
static NSString *kOutputFileFormat  = @"SnakesAndLaddersTestCase%dOutput";

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

- (NSString *)pathForFileWithFormat:(NSString *)format caseNum:(int)caseNum{
    NSBundle *bundle = [NSBundle bundleForClass:[self class]];
    NSString *caseName = [NSString stringWithFormat:format,caseNum];
    NSString *path = [bundle pathForResource:caseName ofType:@"txt"];
    XCTAssert(path!=nil);
    return path;
}

- (const char *)inputForTestCaseNum:(int)caseNum{
    NSError *err = nil;
    NSString *path = [self pathForFileWithFormat:kInputFileFormat caseNum:caseNum];
    return [TestingIOUtilities getContentsOfFile:path error:&err];
}

- (const char *)outputForTestCaseNum:(int)caseNum outputBuffer:(char **)outputBuffer{
    NSError *err = nil;
    NSString *path = [self pathForFileWithFormat:kOutputFileFormat caseNum:caseNum];
    size_t size = [TestingIOUtilities getSizeOfFile:path];
    *outputBuffer = (char *)malloc(size + 1);
    return [TestingIOUtilities getContentsOfFile:path error:&err];
}

- (void)runCaseNum:(int)caseNum
{
    const char *input = [self inputForTestCaseNum:caseNum];
    char *output = NULL;
    const char *expected = [self outputForTestCaseNum:caseNum outputBuffer:&output];
    SnakesAndLaddersRunTestCase(output, input);
    int result = [TestingIOUtilities output:output matchesExpected:(char *)expected];
    XCTAssert(result==1,"\nFAILED CASE %d\nOUTPUT:\n%s\nEXPECTED:\n%s\n",caseNum,output,expected);
}

- (void)testDataStructures{
    TestGraphPractice();
}

- (void)testCase0{
    
    int caseNum = 0;
    [self runCaseNum:caseNum];
}

- (void)testCase1{
    int caseNum = 1;
    [self runCaseNum:caseNum];
}

- (void)testCase2{
    int caseNum = 2;
    [self runCaseNum:caseNum];
}

- (void)testCase3{
    int caseNum = 3;
    [self runCaseNum:caseNum];
}

- (void)testCase4{
    int caseNum = 4;
    [self runCaseNum:caseNum];
}

- (void)testCase6{
    int caseNum = 6;
    [self runCaseNum:caseNum];
}

@end
