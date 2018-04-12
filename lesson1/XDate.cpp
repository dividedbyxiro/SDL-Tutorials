#include "XDate.h"
#include <stdio.h>

XDate::XDate()
{
    day = month = year = 0;
}

XDate::XDate(int newDay, int newMonth, int newYear)
{
    printf("called xdate constructor");
    day = newDay * 10;
    month = newMonth;
    year = newYear;
}
