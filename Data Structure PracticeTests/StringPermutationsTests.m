//
//  StringPermutationsTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/22/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "StringPermutations.h"

@interface StringPermutationsTests : XCTestCase {
    NSString *vCurrentTestCase;
    NSString *vCurrentAnswer;
}

@end

@implementation StringPermutationsTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    vCurrentTestCase = nil;
    vCurrentAnswer = nil;
}

- (void)testCase1{
    vCurrentTestCase = @"a";
    vCurrentAnswer = @"no answer";
    [self runCurrentTestCase];
}

- (void)testCase2{
    vCurrentTestCase = @"ab";
    vCurrentAnswer = @"ba";
    [self runCurrentTestCase];
}

- (void)testCase3{
    vCurrentTestCase = @"bb";
    vCurrentAnswer = @"no answer";
    [self runCurrentTestCase];
}

- (void)testCase4{
    vCurrentTestCase = @"hefg";
    vCurrentAnswer = @"hegf";
    [self runCurrentTestCase];
}

- (void)testCase5{
    vCurrentTestCase = @"dhck";
    vCurrentAnswer = @"dhkc";
    [self runCurrentTestCase];
}

- (void)testCase6{
    vCurrentTestCase = @"dkhc";
    vCurrentAnswer = @"hcdk";
    [self runCurrentTestCase];
}

- (void)runCurrentTestCase{
    const char *input = vCurrentTestCase.UTF8String;
    int outLength = ( vCurrentTestCase.length > 10 ) ? ((int)vCurrentTestCase.length+1) : 10;
    char output[outLength];
    RunTestCase(output, input);
    NSString *result = [NSString stringWithUTF8String:output];
    XCTAssert(nil!=result);
    BOOL success = [result isEqualToString:vCurrentAnswer];
    XCTAssertTrue(success);
    if (success) {
        NSLog(@"\n\nSUCCESS! OUTPUT = %@, INPUT = %@\n",vCurrentTestCase,result);
    }else{
        NSLog(@"\n\nFAILURE! OUTPUT = %@, ANSWER = %@, INPUT = %@\n",vCurrentTestCase,result,vCurrentAnswer);
    }
}


@end
