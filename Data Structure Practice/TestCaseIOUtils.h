//
//  TestCaseIOUtils.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/4/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#ifndef TestCaseIOUtils_h
#define TestCaseIOUtils_h

#include <stdio.h>

int OpenTestCaseInputFile(FILE *fp, const char *path);
int CloseTestCaseInputFile(FILE *fp);
char *CaptureStdOut(int size);

#endif /* TestCaseIOUtils_h */
