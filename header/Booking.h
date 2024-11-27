#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Booking {
private:
    string firstname;
    string lastname;
    string dob;
    string aadhar;
    string checkindate;
    string checkoutdate;
    int days;
    int typeofroom;
    int noofroom;
    long bookingid;
    int bookingprice;
    bool status; // 1 for room booked, 0 for booking cancelled
    static long currentbookingID; 

public:
    // Constructor with parameters for booking details
    Booking(string firstname, string lastname, string dob, string aadhar, string checkindate,
            string checkoutdate, int typeofroom, int noofroom);

    // Overloaded constructor for all details
    Booking(string firstname, string lastname, string dob, string aadhar, string checkindate,
            string checkoutdate, int typeofroom, int noofroom, long bookingid, int bookingprice, 
            int days, bool status);

    // Destructor
    ~Booking();

    // Getter methods
    string getname() const;
    string getdob() const;
    string getaadhar() const;
    string getcheckindate() const;
    string getcheckoutdate() const;
    int gettypeofroom() const;
    int getnoofroom() const;
    int getnoofdays() const;
    long getbookingid() const;
    int getbookingprice() const;
    bool getstatus() const;

    // Methods to confirm or cancel a booking
    void confirmbooking(int price, int day);
    void cancelbooking();

    // Set the Booking ID
    void setBookingID();

private:
    // methods to load and save booking ID
    void loadbookid(const string& filename);
    void savebookid(const string& filename);
};

#endif // BOOKING_H
