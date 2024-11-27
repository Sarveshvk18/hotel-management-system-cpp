#include "../header/Booking.h"

using namespace std;

// Constructor with parameters for user booking details
Booking::Booking(string firstname, string lastname, string dob, string aadhar, string checkindate,
                 string checkoutdate, int typeofroom, int noofroom) {
    this->firstname = firstname;
    this->lastname = lastname;
    this->dob = dob;
    this->aadhar = aadhar;
    this->checkindate = checkindate;
    this->checkoutdate = checkoutdate;
    this->typeofroom = typeofroom;
    this->noofroom = noofroom;
    loadbookid("../data/bookingid.txt");  
}

// Overloaded constructor for all details
Booking::Booking(string firstname, string lastname, string dob, string aadhar, string checkindate,
                 string checkoutdate, int typeofroom, int noofroom, long bookingid, int bookingprice, 
                 int days, bool status) {
    this->firstname = firstname;
    this->lastname = lastname;
    this->dob = dob;
    this->aadhar = aadhar;
    this->checkindate = checkindate;
    this->checkoutdate = checkoutdate;
    this->typeofroom = typeofroom;
    this->noofroom = noofroom;
    this->bookingid = bookingid;
    this->bookingprice = bookingprice;
    this->status = status;
    this->days = days;
    loadbookid("../data/bookingid.txt");  
}

// Destructo
Booking::~Booking() {
    savebookid("../data/bookingid.txt"); 
}

// Getter methods
string Booking::getname() const { return firstname + " " + lastname; }
string Booking::getdob() const { return dob; }
string Booking::getaadhar() const { return aadhar; }
string Booking::getcheckindate() const { return checkindate; }
string Booking::getcheckoutdate() const { return checkoutdate; }
int Booking::gettypeofroom() const { return typeofroom; }
int Booking::getnoofroom() const { return noofroom; }
int Booking::getnoofdays() const { return days; }
long Booking::getbookingid() const { return bookingid; }
int Booking::getbookingprice() const { return bookingprice; }
bool Booking::getstatus() const { return status; }

// Method to confirm booking
void Booking::confirmbooking(int price, int day) {
    bookingprice = price;
    days = day;
    status = 1;  
    setBookingID();
    cout<<"Booking ID: "<<bookingid<<endl;
}

// Method to cancel booking
void Booking::cancelbooking() {
    this->bookingprice = bookingprice / 4;  
    this->status = 0;  
}

// Set the Booking ID using the static variable
void Booking::setBookingID() {
    bookingid = currentbookingID++;  
}

// Load the current booking ID from a file
void Booking::loadbookid(const string& filename) {
    ifstream file(filename);
    if (file.is_open() && file.peek() != ifstream::traits_type::eof()) {
        file >> currentbookingID;  
        file.close();
    } else {
        currentbookingID = 100000;  
    }
}

// Save the current booking ID to a file
void Booking::savebookid(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << currentbookingID;  
        file.close();
    }
}
long Booking::currentbookingID = 100000;