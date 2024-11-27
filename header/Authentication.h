#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <map>
#include <string>
#include <vector>
#include "Guest.h"
#include "Booking.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Authentication {
private:
    map<string, Guest> loginlist;
    const string FILENAME = "../data/login_data.txt";

public:
    Authentication();  // Constructor
    ~Authentication(); // Destructor

    bool login(string email, string password); 
    void pushbooking(string email, long bookingid);
    bool signup(string name, string email, string password);
    bool isadmin(string email);
    string getname(string email);
    long printbookingID(const string& email);

private:
    void saveToFile(); 
    void loadFromFile();
};

#endif // AUTHENTICATION_H
