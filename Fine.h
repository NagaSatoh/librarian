#pragma once
#include <string>
#include <sstream>
#include "Borrow.h"

using namespace std;

class Fine
{
private:
    string fineID;
    double amount;
    Date fineDate;
    bool paidStatus;
    string borrowingID;

public:
    Fine()
        : fineID(""), amount(0.0), fineDate{0, 0, 0},
          paidStatus(false), borrowingID("") {}

    Fine(const string& f_ID, double a, Date f_Date,
         bool p_Status, const string& b_ID)
        : fineID(f_ID), amount(a), fineDate(f_Date),
          paidStatus(p_Status), borrowingID(b_ID) {}

    // Getters
    string getFineID() const { return fineID; }
    double getAmount() const { return amount; }
    Date getFineDate() const { return fineDate; }
    bool getPaidStatus() const { return paidStatus; }
    string getBorrowingID() const { return borrowingID; }

    // Setters
    void setFineID(const string& f_ID) { fineID = f_ID; }
    void setAmount(double a) { amount = a; }
    void setFineDate(Date f_Date) { fineDate = f_Date; }
    void setPaidStatus(bool p_Status) { paidStatus = p_Status; }
    void setBorrowingID(const string& b_ID) { borrowingID = b_ID; }

    // ++++++++++++ METHODS +++++++++++++

    // UML: calculateFine() : double
    double calculateFine() const
    {
        return amount; // có thể mở rộng để tính theo Borrow
    }

    // UML: payFine() : bool
    bool payFine()
    {
        if (paidStatus)
            return false;

        paidStatus = true;
        return true;
    }

    // Implement thiếu trong code gốc
    bool applyFine()
    {
        if (amount <= 0)
            return false;

        paidStatus = false;
        return true;
    }

    // UML: getFineInfo() : string
    string getFineInfo() const
    {
        stringstream ss;
        ss << "FineID: " << fineID
           << "\nAmount: " << amount
           << "\nFine Date: " << fineDate.day << "/" << fineDate.month << "/" << fineDate.year
           << "\nPaid Status: " << (paidStatus ? "Paid" : "Unpaid")
           << "\nBorrowing ID: " << borrowingID;
        return ss.str();
    }
};
