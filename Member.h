#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "User.h"
#include "Borrow.h"
#include <fstream>
#include <sstream>

using namespace std;

class Member : public User
{
private:
    string memberID;
    string address;
    string membershipType;
    Date membershipDate;

    vector<Borrow> borrowingHistory;   // lịch sử mượn sách

public:
    // Default Constructor
    Member()
        : User(), memberID(""), address(""), membershipType(""), membershipDate{0,0,0} {}

    // Full Constructor
    Member(const string& userID, const string& name, const string& email,
           const string& phone, const string& password,
           const string& id, const string& add, const string& type, Date d)
        : User(userID, name, email, phone, password),
          memberID(id), address(add), membershipType(type), membershipDate(d) {}

    // Login Constructor
    Member(const string& email, const string& password)
        : User("", "", email, "", password),
          memberID(""), address(""), membershipType(""), membershipDate{0,0,0} {}

    // Getters / Setters
    string getMemberID() const { return memberID; }
    string getAddress() const { return address; }
    string getMembershipType() const { return membershipType; }
    Date getMembershipDate() const { return membershipDate; }

    void setMemberID(const string& id) { memberID = id; }
    void setAddress(const string& add) { address = add; }
    void setMembershipType(const string& type) { membershipType = type; }
    void setMembershipDate(Date d) { membershipDate = d; }

    // -------------------------------------------------
    // Override Pure Virtual Methods from User
    // -------------------------------------------------

    bool login(const string& email, const string& password) override
    {
        return (this->email == email && this->password == password);
    }

    void logout() override
    {
        cout << name << " has logged out." << endl;
    }

    bool changePassword(const string& oldPassword, const string& newPassword) override
    {
        if (oldPassword != password) return false;
        if (newPassword == password) return false;

        password = newPassword;
        return true;
    }

    bool searchBook(const std::string& keyword) {
        std::ifstream file("books.csv");
        if (!file.is_open()) {
            std::cout << "[ERROR] Cannot open books.csv" << std::endl;
            return false;
        }

        std::string line;
        // Bỏ qua dòng header
        std::getline(file, line);

        bool found = false;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string title, author, genre, height, publisher;

            std::getline(ss, title, ',');
            std::getline(ss, author, ',');
            std::getline(ss, genre, ',');
            std::getline(ss, height, ',');
            std::getline(ss, publisher, ',');

            // Chuyển tất cả về lowercase nếu muốn tìm không phân biệt chữ hoa/thường
            if (title.find(keyword) != std::string::npos ||
                author.find(keyword) != std::string::npos ||
                publisher.find(keyword) != std::string::npos) {
                std::cout << "Found book: " << title << " by " << author
                        << " | Genre: " << genre
                        << " | Publisher: " << publisher << std::endl;
                found = true;
            }
        }

        if (!found)
            std::cout << "No books found for keyword: " << keyword << std::endl;

        return found;
    }


    void registerMember() override
    {
        cout << "Member registered successfully: " << memberID << endl;
    }

    // -------------------------------------------------
    // Member class specific methods
    // -------------------------------------------------

    bool updateMemberDetails()
    {
        cout << "Updating details for MemberID: " << memberID << endl;
        
        string newName, newEmail, newPhone;
        
        cout << "New Name (leave blank to keep current): ";
        getline(cin, newName);
        if (!newName.empty()) name = newName;

        cout << "New Email (leave blank to keep current): ";
        getline(cin, newEmail);
        if (!newEmail.empty()) email = newEmail;

        cout << "New Phone (leave blank to keep current): ";
        getline(cin, newPhone);
        if (!newPhone.empty()) phoneNumber = newPhone;

        cout << "Profile updated.\n";
        return true;
    }

    string getInfo() override
    {
        return "Member Info:\n"
               "Name: " + name +
               "\nEmail: " + email +
               "\nPhone: " + phoneNumber +
               "\nMember ID: " + memberID +
               "\nAddress: " + address +
               "\nMembership Type: " + membershipType +
               "\nMembership Date: "
               + to_string(membershipDate.day) + "/" 
               + to_string(membershipDate.month) + "/"
               + to_string(membershipDate.year);
    }

    void viewBorrowingHistory()
    {
        cout << "\n--- Borrowing History for MemberID: " << memberID << " ---\n";
        if (borrowingHistory.empty()) {
            cout << "No borrow records.\n";
            return;
        }

        for (const Borrow& b : borrowingHistory) {
            Date bd = b.getBorrowDate();
            cout << "- BookID: " << b.getBookID()
                << " | Borrowed: " << bd.day << "/" << bd.month << "/" << bd.year
                << " | Status: " << b.getStatus() << endl;
        }
    }


    void addBorrowRecord(const Borrow& b)
    {
        borrowingHistory.push_back(b);
    }
    vector<Borrow>& getBorrowingHistory() { return borrowingHistory; }
};
