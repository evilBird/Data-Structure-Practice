//
//  TestingIOUtilities.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TestingIOUtilities : NSObject

+ (size_t)getSizeOfFile:(NSString *)filePath;
+ (const char *)getContentsOfFile:(NSString *)filePath error:(NSError *__autoreleasing *)error;
+ (int)output:(char *)output matchesExpected:(char *)expected;

@end
