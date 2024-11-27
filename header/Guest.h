#ifndef GUEST_H
#define GUEST_H

#include <string>
#include <vector>
#include <iostream>
#include "Booking.h"

using namespace std;

class Guest {
private:
    string name;
    string password;
    string email;
    bool admin;

public:
    vector<long> booking;  // Stores the booking IDs for the guest

    // Constructor with default values for member variables
    Guest(string name = "", string email = "", string password = "", bool admin = false, vector<long> booking = {});

    // Method to add a booking to the guest's history
    void addbooking(long bookingid);

    // Getter methods to access the member variables
    string getName() const;
    string getEmail() const;
    string getPassword() const;
    vector<long> getBooking() const;
    bool getAdmin() const;
};

#endif // GUEST_H
