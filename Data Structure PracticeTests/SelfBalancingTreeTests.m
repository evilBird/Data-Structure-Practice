//
//  SelfBalancingTreeTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/10/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "SelfBalancingTree.h"
#import "TestingIOUtilities.h"

static NSString *kInputFileFormat   = @"SelfBalancingTreeTestCase%dInput";
static NSString *kOutputFileFormat  = @"SelfBalancingTreeTestCase%dOutput";

@interface SelfBalancingTreeTests : XCTestCase

@end

@implementation SelfBalancingTreeTests

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
    if (outputBuffer){
        *outputBuffer = (char *)malloc(size + 1);
    }
    
    return [TestingIOUtilities getContentsOfFile:path error:&err];
}

- (void)runCaseNum:(int)caseNum
{
    const char *input = [self inputForTestCaseNum:caseNum];
    char *output = NULL;
    const char *expected = [self outputForTestCaseNum:caseNum outputBuffer:&output];
    SelfBalancingTreeRunTestCase(output, input);
    int result = [TestingIOUtilities output:output matchesExpected:(char *)expected];
    XCTAssert(result==1,"\nFAILED CASE %d\nOUTPUT:\n%s\nEXPECTED:\n%s\n",caseNum,output,expected);
}

- (void)testCase_0{
    
    int caseNum = 0;
    [self runCaseNum:caseNum];
}

- (void)testCase_1{
    
    int caseNum = 1;
    [self runCaseNum:caseNum];
}


@end
