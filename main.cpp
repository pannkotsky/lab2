#include <iostream>
#include <ncurses.h>
#include <menu.h>
#include "table.h"
#include "container.h"
#include "date.h"
#include "license.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

const char *choices[] = {
        "Add default license",
        "Add license with params",
        "Copy existing license",
        "View licenses",
        "Copy one license data into another",
        "Exit",
        (char *)nullptr,
};

typedef Container<License> LicensesList;


void create_license_default(LicensesList *ll);
void create_license(LicensesList *ll);
void print_licenses(LicensesList *ll);
void copy_license(LicensesList *ll);
int get_license_index_with_menu(LicensesList *ll);
void copy_license_data(LicensesList *ll);


int main() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    LicensesList licenses_list;
    ITEM **my_items;
    MENU *my_menu;
    int i;
    int n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
    bool exit = false;

    for (i = 0; i < n_choices; ++i) {
        my_items[i] = new_item(choices[i], choices[i]);
    }

    my_menu = new_menu((ITEM **)my_items);

    menu_opts_off(my_menu, O_SHOWDESC);
    post_menu(my_menu);
    refresh();

    while(!exit) {
        switch(getch()) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10:
                int selected = item_index(current_item(my_menu));
                pos_menu_cursor(my_menu);

                switch(selected) {
                    case 0:
                        create_license_default(&licenses_list);
                        break;
                    case 1:
                        create_license(&licenses_list);
                        break;
                    case 2:
                        copy_license(&licenses_list);
                        break;
                    case 3:
                        print_licenses(&licenses_list);
                        break;
                    case 4:
                        copy_license_data(&licenses_list);
                        break;
                    case 5:
                        exit = true;
                        break;
                }

                break;
        }
    }

    for (i = 0; i < n_choices; ++i) {
        free_item(my_items[i]);
    }

    unpost_menu(my_menu);
    free_menu(my_menu);

    endwin();
    return EXIT_SUCCESS;
}


void create_license_default(LicensesList *ll) {
    move(15, 0);
    clrtobot();
    auto license = new License;
    ll->append(license);
}


void create_license(LicensesList *ll) {
    move(15, 0);
    clrtobot();

    char fn[MAX_INPUT], ln[MAX_INPUT], n_str[MAX_INPUT], s_str[MAX_INPUT], y_str[MAX_INPUT], m_str[MAX_INPUT], d_str[MAX_INPUT];
    echo();

    move(17, 0);

    printw("Enter first name: ");
    flushinp();
    getstr(fn);

    printw("Enter last name: ");
    flushinp();
    getstr(ln);

    printw("Enter license number (max %d): ", MAX_NUMBER);
    flushinp();
    getstr(n_str);

    printw("Enter salary (in copecks, min %d, max %d): ", MIN_SALARY, MAX_SALARY);
    flushinp();
    getstr(s_str);

    printw("Enter the validity date\n");
    printw("Enter the year (%d - %d): ", MIN_YEAR, MAX_YEAR);
    flushinp();
    getstr(y_str);

    printw("Enter the month number: ");
    flushinp();
    getstr(m_str);

    printw("Enter the day: ");
    flushinp();
    getstr(d_str);

    noecho();

    uint n = atoi(n_str);
    uint s = atoi(s_str);
    uint y = atoi(y_str);
    uint m = atoi(m_str);
    uint d = atoi(d_str);

    move(15, 0);
    attron(COLOR_PAIR(2));
    License *license = License::create_safe(fn, ln, n, s, y, m, d);
    attroff(COLOR_PAIR(2));
    if (license == nullptr) return;
    ll->append(license);

    attron(COLOR_PAIR(1));
    printw("License created successfully!");
    attroff(COLOR_PAIR(1));
    clrtobot();
}


void print_licenses(LicensesList *ll) {
    move(15, 0);
    clrtobot();
    int column_sizes[] = {22, 22, 6, 13, 12};
    printTableTop(5, column_sizes);
    printw("%s %-20s %s %-20s %s %-4s %s %-11s %s %-10s %s\n",
           VERTICAL, "Last name", VERTICAL, "First name", VERTICAL, "No", VERTICAL,
           "Salary, UAH", VERTICAL, "Date valid", VERTICAL);
    printTableMiddle(5, column_sizes);
    int size = ll->get_length();
    int total_salary = 0;
    License *l;
    for (int i = 0; i < size; i++) {
        l = (*ll)[i];
        l->display();
        total_salary += *l;
    }
    printTableBottom(5, column_sizes);
    printw("Total salary: %.2f UAH", total_salary / 100.0);

}


void copy_license(LicensesList *ll) {
    move(15, 0);
    clrtobot();
    move(17, 0);
    int index = get_license_index_with_menu(ll);
    if (index == -1) return;

    License *l = (*ll)[index];
    auto new_l = new License(*l);
    ll->append(new_l);
}


int get_license_index_with_menu(LicensesList *ll) {
    int size = ll->get_length();
    if (size == 0) {
        move(15, 0);
        clrtobot();
        printw("No licenses yet, please add some");
        return -1;
    }

    ITEM **items;
    MENU *menu;
    WINDOW *menu_win;

    items = (ITEM **)calloc(size + 1, sizeof(ITEM *));

    auto names = new char*[size];

    for (int i = 0; i < size; ++i) {
        License *l = (*ll)[i];
        char *name = l->get_full_name();
        names[i] = name;
        items[i] = new_item(name, name);
    }
    items[size] = new_item((char *)nullptr, (char *)nullptr);

    menu = new_menu((ITEM **)items);
    menu_win = newwin(size, COLS, 19, 0);
    keypad(menu_win, TRUE);
    set_menu_win(menu, menu_win);

    /* Set menu option not to show the description */
    menu_opts_off(menu, O_SHOWDESC);

    printw("Choose license");

    post_menu(menu);
    refresh();

    int index = -1;

    while(index == -1) {
        switch(wgetch(menu_win)) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10:
                index = item_index(current_item(menu));
                break;
        }
    }

    move(17, 0);
    clrtobot();
    for (int i = 0; i < size; ++i) {
        delete[] names[i];
        free_item(items[i]);
    }
    delete[] names;

    unpost_menu(menu);
    free_menu(menu);

    return index;
}


void copy_license_data(LicensesList *ll) {
    move(15, 0);
    clrtobot();

    move(17, 0);
    printw("License to copy data from: ");
    int index_from = get_license_index_with_menu(ll);
    if (index_from == -1) return;

    move(17, 0);
    clrtobot();
    printw("License to copy data to: ");
    int index_to = get_license_index_with_menu(ll);
    if (index_to == -1) return;

    License *l_from = (*ll)[index_from];
    License *l_to = (*ll)[index_to];

    *l_to = *l_from;
    move(15, 0);
    clrtobot();
    attron(COLOR_PAIR(1));
    printw("Data copied created successfully!");
    attroff(COLOR_PAIR(1));
}
