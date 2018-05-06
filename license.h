//
// Created by Valerii Kovalchuk on 5/6/18.
//

#ifndef LAB2_LICENSE_H
#define LAB2_LICENSE_H

#define MIN_NAME 2
#define MAX_NAME 20
#define MAX_NUMBER 9999
#define MIN_SALARY 200000
#define MAX_SALARY 1000000000

typedef const char* str;


class License {
    char *first_name, *last_name;
    uint number, salary;
    Date date_valid;
    // validators
    void check_first_name(str fn);
    void check_last_name(str ln);
    void check_number(uint n);
    void check_salary(uint s);
public:
    License();
    License(License &l);
    License(str fn, str ln, uint n, uint s, uint y, uint m, uint d);
    ~License();
    char *get_first_name() { return first_name; }
    char *get_last_name() { return last_name; }
    char *get_full_name() {
        auto res = new char[strlen(first_name) + 1 + strlen(last_name) + 1];
        sprintf(res, "%s %s", first_name, last_name);
        return res;
    }
    uint get_number() { return number; }
    uint get_salary() { return salary; }
    Date get_date() { return date_valid; }
    static License *create_safe(str fn, str ln, uint n, uint s, uint y, uint m, uint d);
    void display();
};


void License::check_first_name(str fn) {
    if (strlen(fn) < MIN_NAME) {
        throw std::invalid_argument("first name is too short");
    }
    if (strlen(fn) > MAX_NAME) {
        throw std::invalid_argument("first name is too long");
    }
}


void License::check_last_name(str ln) {
    if (strlen(ln) < MIN_NAME) {
        throw std::invalid_argument("last name is too short");
    }
    if (strlen(ln) > MAX_NAME) {
        throw std::invalid_argument("last name is too long");
    }
}


void License::check_number(uint n) {
    if (n < 1 || n > MAX_NUMBER) {
        throw std::invalid_argument("invalid number");
    }
}


void License::check_salary(uint s){
    if (s < MIN_SALARY || s > MAX_SALARY) {
        throw std::invalid_argument("invalid salary");
    }
}


License::License() {
    first_name = new char[5];
    strcpy(first_name, "Jane");
    last_name = new char[4];
    strcpy(last_name, "Doe");
    number = 0;
    salary = 0;
}


License::License(License &l) {
    first_name = new char[strlen(l.first_name) + 1];
    strcpy(first_name, l.first_name);
    last_name = new char[strlen(l.last_name) + 1];
    strcpy(last_name, l.last_name);
    number = l.number;
    salary = l.salary;
    date_valid = l.date_valid;
}


License::License(str fn, str ln, uint n, uint s, uint y, uint m, uint d) {
    check_first_name(fn);
    check_last_name(ln);
    check_number(n);
    check_salary(s);
    date_valid = Date(y, m, d);
    first_name = new char[strlen(fn) + 1];
    strcpy(first_name, fn);
    last_name = new char[strlen(ln) + 1];
    strcpy(last_name, ln);
    number = n;
    salary = s;
}

License::~License() {
    std::cout << "Calling destructor for " << first_name << " " << last_name << std::endl;
    delete[] first_name;
    delete[] last_name;
}


License *License::create_safe(str fn, str ln, uint n, uint s, uint y, uint m, uint d) {
    try {
        return new License(fn, ln, n, s, y, m, d);
    } catch (std::invalid_argument &e) {
        printw("Couldn't create SaleEntity: %s", e.what());
        return nullptr;
    }
}


void License::display() {
    printw("%s %-20s %s %-20s %s %4d %s %11.2f %s %02d.%02d.%04d %s\n",
           VERTICAL, last_name, VERTICAL, first_name, VERTICAL, number, VERTICAL,
           salary / 100.0, VERTICAL, date_valid.get_day(), date_valid.get_month(), date_valid.get_year(), VERTICAL);
}

#endif //LAB2_LICENSE_H
