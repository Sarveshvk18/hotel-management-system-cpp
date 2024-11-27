#include "../header/Guest.h"

// Constructor
Guest::Guest(string name, string email, string password, bool admin, vector<long> booking) {
    this->name = name;
    this->email = email;
    this->password = password;
    this->admin = admin;
    this->booking = booking;
}

// Method to add a booking to the guest's history
void Guest::addbooking(long bookingid) {
    booking.push_back(bookingid);
}

// Getter methods 
string Guest::getName() const {
    return name;
}

string Guest::getEmail() const {
    return email;
}

string Guest::getPassword() const {
    return password;
}

vector<long> Guest::getBooking() const {
    return booking;
}

bool Guest::getAdmin() const {
    return admin;
}
