#include "../header/Maintenance.h"

Maintenance::Maintenance() {
    loadbookingdataFromFile("../data/bookingdata.txt");
}

Maintenance::~Maintenance() {
    savebookingdataToFile("../data/bookingdata.txt");
}

// Load booking data from the file
void Maintenance::loadbookingdataFromFile(const string &filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Could not open the file!" << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string firstname, lastname, dob, aadhar, checkindate, checkoutdate;
        int typeofroom, noofroom, bookingprice, days;
        long bookingid;
        bool status;

        // Read values from the file line
        iss >> firstname >> lastname >> dob >> aadhar >> checkindate >> checkoutdate >> typeofroom >> noofroom >> bookingid >> bookingprice >> days >> status;

        // Create a new Booking object and add it to the list
        Booking newBooking(firstname, lastname, dob, aadhar, checkindate, checkoutdate, typeofroom, noofroom, bookingid, bookingprice, days, status);
        bookingdata.push_back(newBooking);
    }

    infile.close();
}

// Save booking data to the file
void Maintenance::savebookingdataToFile(const string &filename) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Could not open the file for writing!" << endl;
        return;
    }

    for (const auto &booking : bookingdata) {
        outfile << booking.getname() << " "
                << booking.getdob() << " "
                << booking.getaadhar() << " "
                << booking.getcheckindate() << " "
                << booking.getcheckoutdate() << " "
                << booking.gettypeofroom() << " "
                << booking.getnoofroom() << " "
                << booking.getbookingid() << " "
                << booking.getbookingprice() << " "
                << booking.getnoofdays() << " "
                << booking.getstatus() << endl;
    }

    outfile.close();
}

// Add a new booking to the booking data and save to file
void Maintenance::pushbookingdata(Booking data) {
    bookingdata.push_back(data);
    savebookingdataToFile("../data/bookingdata.txt");
}

// Print the booking details for a given booking ID
void Maintenance::printBookingDetails(long bookingID) {
    bool found = false;
    for (const auto &booking : bookingdata) {
        if (booking.getbookingid() == bookingID) {
            cout << "Name: " << booking.getname() << endl;
            cout << "DOB: " << booking.getdob() << endl;
            cout << "Aadhar: " << booking.getaadhar() << endl;
            cout << "Check-in Date: " << booking.getcheckindate() << endl;
            cout << "Check-out Date: " << booking.getcheckoutdate() << endl;
            cout << "Type of Room: " << booking.gettypeofroom() << endl;
            cout << "Number of Rooms: " << booking.getnoofroom() << endl;
            cout << "Booking ID: " << booking.getbookingid() << endl;
            cout << (booking.getstatus() ? "Booking Price: " : "Cancelation Fee: ") << booking.getbookingprice() << endl;
            cout << "Booking Status: " << (booking.getstatus() ? "Booked" : "Cancelled") << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No booking found with ID: " << bookingID << endl;
    }
}

// Cancel a booking and update the booking status and room availability
void Maintenance::cancelBooking(long bookingID) {
    bool found = false;
    Date today;
    for (auto &booking : bookingdata) {
        if (booking.getbookingid() == bookingID) {
            if (booking.getstatus() && (today < booking.getcheckindate())) {
                cout << "Note: 25 percent cancellation fee will be deducted from the refund" << endl;
                cout << "Do you want to cancel this booking " << bookingID << "? (1 for yes, 0 for no)" << endl;
                int i;
                cin >> i;
                if (i == 1) {
                    cout << "Your booking has been cancelled !!!" << endl;
                    cout << "Refund successful (75 percent): " << (booking.getbookingprice() * .75) << endl;
                    booking.cancelbooking();
                    Hotel cancel;
                    cancel.roomcancelupdate(booking);
                }else{
                    cout << "Booking not cancelled" << endl;
                }
            } else {
                cout << "Sorry, you can't cancel old bookings/already cancelled booking" << endl;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No booking found with ID: " << bookingID << endl;
    }
}

// Print the list of booking IDs for a given check-in date
void Maintenance::printBookingID(string date) {
    bool found = false;
    int i = 1;
    for (const auto &booking : bookingdata) {
        if (booking.getcheckindate() == date) {
            cout << i << ". Booking ID: " << booking.getbookingid() << ", Guest Name: " << booking.getname() << endl;
            cout << "     Booking Status: " << (booking.getstatus() ? "Booked" : "Cancelled") << endl;
            found = true;
            i++;
        }
    }
    if (!found) {
        cout << "No booking found with check-in date: " << date << endl;
    } else {
        cout << "Enter the booking ID to view the details: ";
        long bookingid;
        cin >> bookingid;
        printBookingDetails(bookingid);
    }
}

// Print revenue details for a given date range
void Maintenance::printpricedetails(string fromdate, string todate) {
    bool found = false;
    int totalrevenue = 0;
    Date currentDate = fromdate;
    while (currentDate <= todate) {
        string date = currentDate.toString();
        for (const auto &booking : bookingdata) {
            if (booking.getcheckindate() == date) {
                totalrevenue += booking.getbookingprice();
                found = true;
            }
        }
        currentDate.nextDay();
    }
    if (!found) {
        cout << "No bookings happened between " << fromdate << " - " << todate << endl;
    } else {
        cout << "Total revenue for bookings between " << fromdate << " - " << todate << ": $" << totalrevenue << endl;
    }
}

// Print booking details between two dates
void Maintenance::printbookingdetails(string fromdate, string todate) {
    bool found = false;
    int i = 0;
    int type1 = 0, type2 = 0;
    Date currentDate = fromdate;
    while (currentDate <= todate) {
        string date = currentDate.toString();
        for (const auto &booking : bookingdata) {
            if (booking.getcheckindate() == date && booking.getstatus() == 1) {
                if (booking.gettypeofroom() == 1) {
                    type1 += (booking.getnoofroom() * booking.getnoofdays());
                } else {
                    type2 += (booking.getnoofroom() * booking.getnoofdays());
                }
                found = true;
                i++;
            }
        }
        currentDate.nextDay();
    }
    if (!found) {
        cout << "No bookings found between " << fromdate << " - " << todate << endl;
    } else {
        cout << "Total bookings: " << i << endl;
        cout << type1 + type2 << " rooms have been booked and occupied" << endl;
        cout << "No of Normal rooms: " << type1 << endl;
        cout << "No of Deluxe rooms: " << type2 << endl;
    }
}
