#ifndef XDATE_H_INCLUDED
#define XDATE_H_INCLUDED

class XDate
{
public:
    XDate();
//    {
//        day = month = year = 0;
//    }
    XDate(int newDay, int newMonth, int newYear);
//    {
//        day = newDay;
//        month = newMonth;
//        year = newYear;
//    }
	~XDate();
    int day;
    int month;
    int year;

};


#endif // XDATE_H_INCLUDED
