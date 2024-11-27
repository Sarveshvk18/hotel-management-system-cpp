#include "../header/Authentication.h"

using namespace std;

// Constructor: loads data from file
Authentication::Authentication() {
    loadFromFile(); 
}

// Destructor: saves data to file
Authentication::~Authentication() {
    saveToFile();  
}

// Login method
bool Authentication::login(string email, string password) {
    if (loginlist.find(email) != loginlist.end()) {
        if (loginlist[email].getPassword() == password) {
            cout << "Login Successful!!!" << endl;
            return true;
        } else {
            cout << "Wrong password" << endl;
            return false;
        }
    } else {
        cout << "No account found" << endl;
        return false;
    }
}

// Add a booking ID for a user
void Authentication::pushbooking(string email, long bookingid) {
    auto it = loginlist.find(email);
    if (it != loginlist.end()) {
        Guest* guestPtr = &it->second;
        guestPtr->addbooking(bookingid);
        saveToFile();
    } else {
        cout << "Can't add booking to history. Guest not found." << endl;
    }
}

// Signup method
bool Authentication::signup(string name, string email, string password) {
    if (loginlist.find(email) == loginlist.end()) {
        Guest user(name, email, password);
        loginlist[email] = user;
        cout << "Signup Successful!!!" << endl;
        saveToFile();
        return true;
    } else {
        cout << "Signup Failed" << endl;
        return false;
    }
}

// Check if the user is an admin
bool Authentication::isadmin(string email) {
    return loginlist[email].getAdmin();
}

// Get the user's name by email
string Authentication::getname(string email) {
    return loginlist[email].getName();
}

// Print the booking ID for a user
long Authentication::printbookingID(const string& email) {
    // Check if the email exists in the map
    auto it = loginlist.find(email);
    if (it != loginlist.end()) {
        // Retrieve the Guest object associated with the email
        const Guest& guest = it->second;
        if (guest.booking.empty()) {
            cout << "No booking history available" << endl;
            return 0;
        } else {
            for (size_t i = 0; i < guest.booking.size(); ++i) {
                cout << i + 1 << ". " << guest.booking[i] << endl;
            }
            while (true) {
                size_t value;
                cout << "Enter which booking you want to view(Option): " << endl;
                cin >> value;
                if (value > 0 && value <= guest.booking.size()) {
                    cout << "Booking ID: " << guest.booking[value - 1] << endl;
                    return guest.booking[value - 1];
                } else {
                    cout << "Enter a valid value..." << endl;
                }
            }
        }
    } else {
        cout << "Email not found in login list." << endl;
        return 0;
    }
}

// Save data to file
void Authentication::saveToFile() {
    ofstream file(FILENAME, ios::out | ios::trunc);
    if (file.is_open()) {
        for (const auto& [email, guest] : loginlist) {
            file << email << " " << guest.getName() << " " << guest.getPassword() << " " << guest.getAdmin();
            // Write the booking vector
            const vector<long>& booking = guest.getBooking();
            for (size_t i = 0; i < booking.size(); ++i) {
                file << " " << booking[i]; // Write each booking ID separated by a space
            }
            file << endl; // Move to the next line for the next guest
        }
        file.close();
    } else {
        cerr << "Unable to open file for saving login data" << endl;
    }
}

// Load data from file
void Authentication::loadFromFile() {
    ifstream file(FILENAME);
    if (!file.is_open()) {
        cout << "Error opening file: " << FILENAME << endl;
        return; 
    }
    if (file.is_open()) {
        string email, name, password;
        string line;
        bool admin;
        while (getline(file, line)) {
            stringstream ss(line);
            ss >> email >> name >> password >> admin;
            vector<long> booking;
            long bookingID;
            while (ss >> bookingID) {
                booking.push_back(bookingID);
            }

            Guest user(name, email, password, admin, booking);
            loginlist[email] = user;
        }
        file.close();
    } else {
        cout << "No previous login data found. Starting fresh." << endl;
    }
}
