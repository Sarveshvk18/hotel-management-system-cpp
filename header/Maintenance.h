#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include "Booking.h"
#include "Hotel.h"

using namespace std;

class Maintenance {
private:
    vector<Booking> bookingdata;

public:
    Maintenance();
    ~Maintenance();
    
    // Function to load booking data from file
    void loadbookingdataFromFile(const string &filename);

    // Function to save booking data to file
    void savebookingdataToFile(const string &filename);

    // Function to add a new booking
    void pushbookingdata(Booking data);

    // Function to print booking details for a specific booking ID
    void printBookingDetails(long bookingID);

    // Function to cancel a booking by its booking ID
    void cancelBooking(long bookingID);

    // Function to print bookings with a specific check-in date
    void printBookingID(string date);

    // Function to print revenue details between two dates
    void printpricedetails(string fromdate, string todate);

    // Function to print booking details between two dates
    void printbookingdetails(string fromdate, string todate);
};

#endif // MAINTENANCE_H
