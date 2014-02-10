#include "euler.h"

int months[12] = {
    31, // January
    28, // February
    31, // March
    30, // April
    31, // May
    30, // June
    31, // July
    31, // August
    30, // September
    31, // October
    30, // November
    31, // December
};

typedef struct date {
    int year;
    int day;
    int month;
} date_t;

void add_month( date_t * d ) {
    d->day += months[d->month];
    if ( d->month == 1 ) { // Feb
        if (
                ( d->year % 400 == 0 )
                ||
                ( ( d->year % 4 == 0 ) && ( d->year % 100 != 0 ) )
        ) d->day++;
    }
    d->month++;
    if ( d->month == 12 ) {
        d->month = 0;
        d->year++;
    }
}

int main( int argc, char ** argv ) {
    int sundays = 0;
    date_t d = {
        1900,
        1,
        0
    };
    int i;
    for (i=0;i<12;i++) add_month(&d);
    while (d.year<2001) {
        if ( d.day % 7 == 0 ) sundays++;
        add_month(&d);
    }
    checkanswer( sundays, 171, "problem 19" );
    return(0);
}
