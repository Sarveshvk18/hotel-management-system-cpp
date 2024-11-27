#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

class Date {
private:
    int day, month, year; 

    // Helper function to parse a date string in "DD-MM-YYYY" format
    void parseDate(const string& dateStr);

public:
    // Constructor: Fetch today's date from the system
    Date();

    // Constructor with a date string in "DD-MM-YYYY" format
    Date(const string& dateStr);

    // Helper function to check if a year is a leap year
    bool isLeapYear(int y);

    // Helper function to check the number of days in a month
    int daysInMonth(int m, int y);

    // Validate if the date is correct (e.g., not 31-11-2024)
    bool validate();

    // Function to get the next day
    void nextDay();

    // Convert the date back to "DD-MM-YYYY" string format
    string toString() const;

    // Comparison operators for date ranges
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator==(const Date& other) const;

    // Function to check eligibility (age >= 18)
    bool iseligible();
};

#endif // DATE_H
