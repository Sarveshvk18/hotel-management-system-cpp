#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "Date.h"
#include "Booking.h"

using namespace std;

// Class representing a single room with a type and quantity
class Room {
public:
    int roomType; // 1 for AC Normal, 2 for AC Delux
    int quantity;

    Room(int type, int quantity) 
        : roomType(type), quantity(quantity) {}
};

// Main Hotel class
class Hotel {
private:
    map<string, vector<Room>> availability; 

public:
    // Constructor and Destructor
    Hotel();
    ~Hotel();

    // Functions to load and save room availability from/to a file
    void loadAvailabilityFromFile(const string &filename);
    void saveAvailabilityToFile(const string &filename);

    // Function to check if rooms are available for the booking
    bool isRoomAvailable(Booking &booking);

    // Function to update room availability when a booking is cancelled
    void roomcancelupdate(Booking &booking);

    // Function to print the current availability
    //Admin
    void printAvailability();
};

#endif // HOTEL_H
