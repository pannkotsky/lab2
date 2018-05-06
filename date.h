//
// Created by Valerii Kovalchuk on 5/6/18.
//

#ifndef LAB2_DATE_H
#define LAB2_DATE_H

#define MIN_YEAR 2000
#define MAX_YEAR 3000


class Date {
    uint year, month, day;
    // validators
    void check_year(uint y);
    void check_month(uint m);
    void check_day(uint y, uint m, uint d);
public:
    Date() { year = MIN_YEAR; month = 1; day = 1; }
    Date(const Date &d) { *this = d; }
    Date(uint y, uint m, uint d);
    uint get_year() { return year; }
    uint get_month() { return month; }
    uint get_day() { return day; }
};

bool is_year_leap(uint y);
bool is_day_valid(uint y, uint m, uint d);


void Date::check_year(uint y) {
    if (y < MIN_YEAR || y > MAX_YEAR) {
        throw std::invalid_argument("invalid year");
    }
}


void Date::check_month(uint m) {
    if (m < 1 || m > 12) {
        throw std::invalid_argument("invalid month");
    }
}


void Date::check_day(uint y, uint m, uint d) {
    if (!is_day_valid(y, m, d)) {
        throw std::invalid_argument("invalid month");
    }
}


Date::Date(uint y, uint m, uint d) {
    check_year(y);
    check_month(m);
    check_day(y, m, d);
    year = y;
    month = m;
    day = d;
}


bool is_year_leap(uint y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return y % 4 == 0;
}


bool is_day_valid(uint y, uint m, uint d) {
    if (d < 1 || d > 31) return false;
    if (m == 2) {
        if (d > 29) return false;
        if (is_year_leap(y) && d > 28) return false;
    }
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return false;
    return true;
}

#endif //LAB2_DATE_H
