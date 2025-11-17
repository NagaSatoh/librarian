#pragma once
#include <iostream>
#include <string>
using namespace std;

class User
{
protected:
    string userID;
    string name;
    string email;
    string phoneNumber;
    string password;

public:
    User() = default;

    User(const string& userID, const string& name, const string& email,
         const string& phoneNumber, const string& password)
        : userID(userID), name(name), email(email),
          phoneNumber(phoneNumber), password(password) {}

    virtual ~User() = default;

    // --- PURE VIRTUAL METHODS (theo class diagram) ---

    virtual bool login(const string& email, const string& password) = 0;

    virtual void logout() = 0;

    virtual string getInfo() = 0;

    virtual bool changePassword(const string& oldPassword, const string& newPassword) = 0;

    virtual bool searchBook(const string& keyword) = 0;

    virtual void registerMember() = 0;

    // --- GETTERS nếu cần ---
    string getUserID() const { return userID; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhoneNumber() const { return phoneNumber; }
};
