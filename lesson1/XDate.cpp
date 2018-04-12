#include "XDate.h"
#include <stdio.h>

XDate::XDate()
{
	printf("empty constructor called\n");
    day = month = year = 0;
}

XDate::XDate(int newDay, int newMonth, int newYear)
{
    printf("called xdate constructor\n");
    day = newDay * 10;
    month = newMonth;
    year = newYear;
}

XDate::~XDate()
{
	printf("empty destructor called\n");
}
