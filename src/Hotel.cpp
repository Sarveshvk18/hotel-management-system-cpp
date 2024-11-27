#include "../header/Hotel.h"

// Constructor to load the room availability data for the next 7 days
Hotel::Hotel() {
    loadAvailabilityFromFile("../data/availability.txt");
}

// Destructor to save the room availability data before the program ends
Hotel::~Hotel() {
    saveAvailabilityToFile("../data/availability.txt");
}

// Function to load the availability of rooms from a file
void Hotel::loadAvailabilityFromFile(const string &filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Could not open the file!" << endl;
        return;
    }
    Date today;  // Today's date
    Date nextday = today;  // Start from the next day
    nextday.nextDay();  // Move to the next day
    
    map<string, vector<Room>> tempAvailability;
    string line;

    // Read the file and only store the next seven days in tempAvailability
    while (getline(infile, line)) {
        istringstream iss(line);
        string date;
        int roomType, quantity;
        iss >> date;
        Date fileDate(date);
        
        // Only process dates after today
        if (today < fileDate) {
            while (iss >> roomType >> quantity) {
                Room room(roomType, quantity);
                tempAvailability[date].push_back(room);
            }
        }
    }
    infile.close();

    // Ensure we have 7 consecutive days' data starting from the next day
    Date currentDate = nextday;
    for (int i = 0; i < 7; ++i) {
        string currentDateStr = currentDate.toString();
        if (tempAvailability.find(currentDateStr) == tempAvailability.end()) {
            // Initialize rooms with default availability
            tempAvailability[currentDateStr] = { Room(1, 10), Room(2, 10) };
        }
        currentDate.nextDay();  // Move to the next day
    }
    
    // Transfer the data to the main availability map
    availability = move(tempAvailability);
}

// Function to print the current availability of rooms
//Admin use
void Hotel::printAvailability() {
    for (const auto &entry : availability) {
        const string &date = entry.first;
        const vector<Room> &rooms = entry.second;
        cout << "Date: " << date << endl;
        for (const Room &room : rooms) {  // Loop through each room for the date
            cout << " Room Type: " << ((room.roomType==1)?"Normal":"Delux")
                 << ", Quantity: " << room.quantity 
                 << endl;
        }
        cout << endl;  // Space after each date for clarity
    }
}

// Function to save the availability data to a file
void Hotel::saveAvailabilityToFile(const string &filename) {
    ofstream outfile(filename);
    for (const auto &entry : availability) {
        outfile << entry.first;
        for (const Room &room : entry.second) {
            outfile << " " << room.roomType << " " << room.quantity;
        }
        outfile << endl;
    }
    outfile.close();
}

// Function to check if rooms are available for a booking
bool Hotel::isRoomAvailable(Booking &booking) {
    string startDate = booking.getcheckindate();
    string endDate = booking.getcheckoutdate();
    int roomType = booking.gettypeofroom();
    int noofRooms = booking.getnoofroom();
    
    Date currentDate = startDate;
    vector<pair<string, Room*>> reservedRooms;
    int days = 0;
    
    while (currentDate < endDate) {
        string dateStr = currentDate.toString();
        bool foundRoom = false;
        
        if (availability.find(dateStr) != availability.end()) {
            for (Room &room : availability[dateStr]) {
                if (room.roomType == roomType && room.quantity >= noofRooms) {
                    reservedRooms.push_back({dateStr, &room});
                    days++;
                    foundRoom = true;
                    break;
                }
            }
        }

        if (!foundRoom) {
            cout << "Sorry, not enough rooms available for the entire duration." << endl;
            return false;
        }

        currentDate.nextDay();  // Move to the next date
    }

    int price = days * noofRooms * (roomType == 1 ? 1000 : 1750);
    cout << endl<<"Rooms available!!!"<<endl<<endl<<"Your Bill"<<endl;
    cout<< "Pay Rupees " << price << " to confirm your booking...(Just enter the price amount)" << endl;
    int payment;
    cin >> payment;

    if (payment == price) {
        for (auto &reserved : reservedRooms) {
            reserved.second->quantity -= noofRooms;  
        }
        cout<<endl<<"Your Booking Receipt:"<<endl;
        cout << "Booked " << noofRooms << ((roomType == 1) ? " Normal" : " Deluxe") 
             << ((noofRooms < 2) ? " room for " : " rooms for ") << days << ((days < 2) ? " day " : " days ") << endl;
        cout << "Check In Date: " << startDate << endl;
        cout << "Check Out Date: " << endDate << endl;
        saveAvailabilityToFile("../data/availability.txt");
        booking.confirmbooking(price, days);
        return true;
    } else {
        cout << "Payment mismatch. Booking failed!!!" << endl;
        return false;
    }
}

// Function to update room availability when a booking is cancelled
void Hotel::roomcancelupdate(Booking &booking) {
    string startDate = booking.getcheckindate();
    string endDate = booking.getcheckoutdate();
    int roomType = booking.gettypeofroom();
    int noofRooms = booking.getnoofroom();
    
    Date currentDate = startDate;
    while (currentDate < endDate) {
        string dateStr = currentDate.toString();
        if (availability.find(dateStr) != availability.end()) {
            for (Room &room : availability[dateStr]) {
                if (room.roomType == roomType) {
                    room.quantity += noofRooms;
                }
            }
        }
        currentDate.nextDay();  // Move to the next date
    }
}
