#include "../header/Hotel.h"
#include "../header/Booking.h"
#include "../header/Maintenance.h"
#include "../header/Validation.h"
#include "../header/Authentication.h"
#include <iostream>
using namespace std;
void userloggedin(string& email,Authentication& start, Maintenance& data){
    cout << "Welcome to the XYZ Hotel !" << endl;
    while(true){
    cout<<"__________________________"<<endl;
    cout<<"-----MENU-----"<<endl;
    cout<<"Click 1 for Hotel Room Reservation"<<endl;
    cout<<"Click 2 for Booking Status/History"<<endl;
    cout<<"Click 3 for Cancel Booking"<<endl;
    cout<<"Click 4 for Terms and Conditions"<<endl;
    cout<<"Click 0 to Log Out"<<endl;
    int value;
    cin>>value;
    if(value==1){
        string firstname, lastname, dob, aadhar, checkin, checkout;
        int roomtype, noofrooms;
        do{
        cout<<"Enter guest first name: ";
        cin>>firstname;
        }while(!isValidName(firstname));
        do{
        cout<<"Enter guest last name: ";
        cin>>lastname;
        }while(!isValidName(lastname));
        do{
        cout<<"Enter DOB(DD-MM-YYYY): ";
        cin>>dob;
        }while(!isValidDOB(dob));
        do{
        cout<<"Enter aadharcard no: ";
        cin>>aadhar;
        }while(!isValidAadhaar(aadhar));
        do{
        cout<<"Enter checkindate: ";
        cin>>checkin;
        }while(!isvalidcheckindate(checkin));
        do{
        cout<<"Enter checkoutdate: ";
        cin>>checkout;
        }while(!isvalidcheckoutdate(checkin, checkout));
        do{
        cout<<"Enter roomtype 1 for Normal 2 for Delux: ";
        cin>>roomtype;
        if (!cin || (roomtype != 1 && roomtype != 2)) {
            cout << "Invalid input! Please enter 1 for Normal or 2 for Delux.\n";
            cin.clear();  
            cin.ignore();
        }
        }while(!(roomtype==1 || roomtype==2));
        do{
        cout<<"Enter no of rooms(2 adults in single room max): ";
        cin>>noofrooms;
        if (!cin || noofrooms <= 0 || noofrooms >= 6) {
            cout << "Invalid input! Please enter a number between 1 and 5.\n";
            cin.clear();  
            cin.ignore();  
        }
        }while(!(noofrooms > 0 && noofrooms <= 5));
        cout<<"__________________________"<<endl;
        Booking user1(firstname, lastname, dob, aadhar, checkin, checkout, roomtype, noofrooms);
        Hotel hotel;
        if(hotel.isRoomAvailable(user1)){
            cout<<"Thanks for choosing our hotel, Happy Staying :)"<<endl;
            start.pushbooking(email, user1.getbookingid());
            data.pushbookingdata(user1);
        }else{
            cout<<"Room not available"<<endl;
        }
    }else if(value==2){
        cout<<"Your Booking History"<<endl;
        long bookingid=start.printbookingID(email);
        if(bookingid!=0)
        {
        data.printBookingDetails(bookingid);
        }
    }else if(value==3){
        cout<<"Your Booking History"<<endl;
        long bookingid=start.printbookingID(email);
        if(bookingid!=0)
        {
        data.cancelBooking(bookingid);
        }
    }else if(value==4){
        cout<<"Terms and condition"<<endl;
        cout<<"1. Guest should be adult 18+"<<endl;
        cout<<"2. Only 7 days pre booking is open"<<endl;
        cout<<"3. While checkin guest aadhar card should match with given details(Name, aadhar no, DOB)"<<endl;
        cout<<"4. Cancellation available only for future dates"<<endl;
        cout<<"5. In a single room 2 members only allowed"<<endl;
    }else if(value==0){
        cout<<"Logged Out..."<<endl;
        break;
    }else{
        cout<<"Enter proper value"<<endl;
    }
    }
};
void adminloggedin(Maintenance& data){
    while(true){
    cout<<"__________________________"<<endl;
    cout<<"-----Admin Menu-Report-----"<<endl;
    cout<<"1.Search by BookingID"<<endl;
    cout<<"2.Search by Checkin Date"<<endl;
    cout<<"3.Revenue report between Dates(Price)"<<endl;
    cout<<"4.Booking report between Dates(Type and no of rooms)"<<endl;
    cout<<"5.View Room Availability"<<endl;
    cout<<"0.Log Out"<<endl;
    int value;
    cin>>value;
    if(value==1){
        long bookingid;
        cout<<"Enter booking ID: ";
        cin>>bookingid;
        cout<<"__________________________"<<endl;
        data.printBookingDetails(bookingid);
    }else if(value==2){
        string date;
        do{
        cout<<"Enter Checkin Date: ";
        cin>>date;
        }while(!(isvalidcheckindate(date)));
        cout<<"__________________________"<<endl;
        data.printBookingID(date);
    }else if(value==3){
        string fromdate;
        string todate;
        do{
        cout<<"Enter From Date: ";
        cin>>fromdate;
        }while(!(isvalidcheckindate(fromdate)));
        do{
        cout<<"Enter To Date: ";
        cin>>todate;
        }while(!isvalidcheckoutdate(fromdate, todate));
        cout<<"__________________________"<<endl;
        data.printpricedetails(fromdate, todate);
        
    }else if(value==4){
        string fromdate;
        string todate;
        do{
        cout<<"Enter From Date: ";
        cin>>fromdate;
        }while(!(isvalidcheckindate(fromdate)));
        do{
        cout<<"Enter To Date: ";
        cin>>todate;
        }while(!isvalidcheckoutdate(fromdate, todate));
        cout<<"__________________________"<<endl;
        data.printbookingdetails(fromdate, todate);
        
    }else if(value==5){
        cout<<"Availabilty Details"<<endl;
        Hotel availabilty;
        availabilty.printAvailability();
        cout<<"__________________________"<<endl;
    }else if(value==0){
        cout<<"Logged Out..."<<endl;
        cout<<"__________________________"<<endl;
        break;
    }else{
        cout<<"Enter proper value"<<endl;
    }
    }
};
int main(){
    Authentication start;
    Maintenance data;
    int login;
    while(true){
    cout<<"__________________________"<<endl;
    cout<<"-----Welcome to the Hotel Management System-----"<<endl;
    cout<<"1. Login"<<endl;
    cout<<"2. Sign-UP"<<endl;
    cout<<"0. Exit"<<endl;
    cin>>login;
    if(login==1){
        string username, password;
        cout<<"Enter your username: ";
        cin>>username;
        cout<<"Enter your password: ";
        cin>>password;
        cout<<"__________________________"<<endl;
        if(start.login(username, password)){
            if(start.isadmin(username))
            {
                cout<<"Welcome to Administration :)"<<endl;
                adminloggedin(data);
            }else{
            cout<<"Welcome Back "<<start.getname(username)<<" :)"<<endl;
            userloggedin(username, start, data);
            }
        }
    }else if(login==2){
        string name, email, password;
        do{
        cout<<"Enter your name: ";
        cin>>name;
        }while(!isValidName(name));
        do{
        cout<<"Enter your email: ";
        cin>>email;
        }while(!isValidEmail(email));
        cout<<"Enter your password: ";
        cin>>password;
        if(start.signup(name, email, password)){
            cout<<"Welcome "<<name<<" :)"<<endl;
            userloggedin(email, start, data);
        }
    }else if(login==0){
        cout<<"Thankyou Happy Staying..."<<endl;
        break;
    }else{
        cout<<"Please enter the valid input !!!"<<endl;
    }
    }
    return 0;
}