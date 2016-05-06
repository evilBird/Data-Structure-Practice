//
//  TestingIOUtilities.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "TestingIOUtilities.h"

@implementation TestingIOUtilities

+ (size_t)getSizeOfFile:(NSString *)filePath{
    NSString *contents = [NSString stringWithContentsOfFile:filePath encoding:1 error:nil];
    size_t result = (contents.length * sizeof(char));
    return result;
}

+ (const char *)getContentsOfFile:(NSString *)filePath error:(NSError *__autoreleasing *)error{
    
    NSString *contents = [NSString stringWithContentsOfFile:filePath encoding:1 error:error];
    if (!contents)return NULL;
    return contents.UTF8String;
}

+ (int)output:(char *)output matchesExpected:(char *)expected{
    int result = strcmp(output, expected);
    return (result == 0);
}

@end
