#include "../header/Date.h"

using namespace std;

// Constructor: Fetch today's date from the system
Date::Date() {
    // Get the current system time as a time_t object
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    
    // Convert time_t to tm structure
    struct tm *tm_now = localtime(&now);
    
    // Set the day, month, and year from tm structure
    day = tm_now->tm_mday;
    month = tm_now->tm_mon + 1;  // tm_mon is 0-based (0 = January)
    year = tm_now->tm_year + 1900; // tm_year is years since 1900
}

// Constructor with a date string in "DD-MM-YYYY" format
Date::Date(const string& dateStr) {
    parseDate(dateStr);
}

// Helper function to parse a date string in "DD-MM-YYYY" format
void Date::parseDate(const string& dateStr) {
    stringstream ss(dateStr);
    char delimiter; 
    ss >> day >> delimiter >> month >> delimiter >> year;
}

// Helper function to check if a year is a leap year
bool Date::isLeapYear(int y) {
    return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
}

// Helper function to check the number of days in a month
int Date::daysInMonth(int m, int y) {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(y) ? 29 : 28;
        default:
            return 0; 
    }
}

// Validate if the date is correct
bool Date::validate() {
    if (month < 1 || month > 12) return false;
    int daysInCurrentMonth = daysInMonth(month, year);
    return (day >= 1 && day <= daysInCurrentMonth); 
}

// Function to get the next day
void Date::nextDay() {
    day++;
    if (day > daysInMonth(month, year)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

// Convert the date back to "DD-MM-YYYY" string format
string Date::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << day << "-" << setw(2) << month << "-" << year;
    return ss.str();
}

// Comparison operators for date ranges
//operator overloading
bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator<=(const Date& other) const {
    return *this < other || *this == other;
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

// Function to check eligibility (age >= 18)
bool Date::iseligible() {
    Date currentDate; 
    if (currentDate.year - year > 18) {
        return true; 
    }
    if (currentDate.year - year == 18) {
        if (currentDate.month > month || (currentDate.month == month && currentDate.day >= day)) {
            return true;
        }
    }
    return false;
}
