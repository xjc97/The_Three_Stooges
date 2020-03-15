/*************************************************************************
	> File Name: sum.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 Mar 2020 02:16:20 PM CST
 ************************************************************************/

#include <stdio.h>
#include "sum.h"
#include "val.h"

int sum(int *x, int *y)
{
    val(x);
    puts("This is SUM Method!=============HDH");
    return *x + *y;
}
