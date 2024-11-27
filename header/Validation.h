// Validation.h
#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
using namespace std;

bool isValidEmail(string& email);
bool isValidName(string& name);
bool isValidDOB(string& dob);
bool isvalidcheckindate(string& checkin);
bool isvalidcheckoutdate(string& checkin, string& checkout);
bool isValidAadhaar(string& aadhaar);

#endif // VALIDATION_H
