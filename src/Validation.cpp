
#include <iostream>
#include <string>
#include <cctype>
#include "../header/Validation.h"
#include "../header/Date.h"

using namespace std;

// Function to validate email
bool isValidEmail(string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    if (atPos == std::string::npos || dotPos == std::string::npos) {
        return false;
    }
    if (atPos < 1 || dotPos < atPos + 2 || dotPos == email.length() - 1) {
        return false;
    }
    return true;
}

// Function to validate name
bool isValidName(string& name) {
    for (char c : name) {
        if (!std::isalpha(c) && c != ' ') {
            return false;
        }
    }
    return !name.empty();
}

// Function to validate DOB in DD-MM-YYYY format
bool isValidDOB(string& dob) {
    Date date=dob;
    if(date.validate()){
        if(date.iseligible()){
            return true;
        }else{
            cout<<"Guest should be 18+ adults"<<endl;
            return false;
        }
        
    }else{
        cout<<"Enter proper DOB"<<endl;
        return false;
    }
}

// Function to validate check-in date
bool isvalidcheckindate(string& checkin) {
    Date date=checkin;
    if(date.validate()){
            return true;
    }else{
        cout<<"Enter proper Checkin Date"<<endl;
        return false;
    }
}

// Function to validate check-out date
bool isvalidcheckoutdate(string& checkin, string& checkout) {
    Date date=checkout;
    Date check=checkin;
    if(date.validate()){
        if(check<checkout){
            return true;
        }else{
            cout<<"Checkout/To date should be after the checkin/from date"<<endl;
            return false;
        }
    }else{
        cout<<"Enter proper Checkout Date"<<endl;
        return false;
    }
}

// Function to validate Aadhaar number
bool isValidAadhaar(string& aadhaar) {
    if (aadhaar.length() != 12) {
        return false;
    }
    for (char c : aadhaar) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}
