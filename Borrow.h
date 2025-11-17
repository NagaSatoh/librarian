#pragma once
#include <string>
#include <iostream>
using namespace std;

struct Date
{
    int day;
    int month;
    int year;
};

class Borrow
{
private:
    string borrowID;
    string memberID;
    string bookID;
    Date borrowDate;
    Date dueDate;
    Date returnDate;
    string status;  // "Borrowed", "Returned", "Overdue"

public:
    // ----------------------------
    // Constructors
    // ----------------------------
    Borrow()
        : borrowID(""), memberID(""), bookID(""),
          borrowDate{0,0,0}, dueDate{0,0,0}, returnDate{0,0,0},
          status("Pending") {}

    Borrow(const string& br_ID, const string& m_ID, const string& b_ID,
           Date b_Date, Date d_Date, Date r_Date, const string& s)
        : borrowID(br_ID), memberID(m_ID), bookID(b_ID),
          borrowDate(b_Date), dueDate(d_Date), returnDate(r_Date),
          status(s) {}

    // ----------------------------
    // Getters (const)
    // ----------------------------
    string getBorrowID() const { return borrowID; }
    string getMemberID() const { return memberID; }
    string getBookID() const { return bookID; }
    Date getBorrowDate() const { return borrowDate; }
    Date getDueDate() const { return dueDate; }
    Date getReturnDate() const { return returnDate; }
    string getStatus() const { return status; }

    // ----------------------------
    // Setters
    // ----------------------------
    void setBorrowID(const string& id) { borrowID = id; }
    void setMemberID(const string& m) { memberID = m; }
    void setBookID(const string& b) { bookID = b; }
    void setBorrowDate(Date d) { borrowDate = d; }
    void setDueDate(Date d) { dueDate = d; }
    void setReturnDate(Date d) { returnDate = d; }
    void setStatus(const string& s) { status = s; }

    // ----------------------------
    // Utility: Convert Date to string
    // ----------------------------
    string dateToString(const Date& d) const
    {
        return to_string(d.day) + "/" +
               to_string(d.month) + "/" +
               to_string(d.year);
    }

    // ----------------------------
    // Utility: Days between dates
    // approx
    // ----------------------------
    int daysBetween(const Date& date1, const Date& date2) const
    {
        int days1 = date1.year * 365 + date1.month * 30 + date1.day;
        int days2 = date2.year * 365 + date2.month * 30 + date2.day;
        return days2 - days1;
    }

    // ----------------------------
    // UML Methods
    // ----------------------------

    bool borrowBook()
    {
        if (status == "Borrowed")
            return false;

        status = "Borrowed";
        return true;
    }

    bool returnBook()
    {
        if (status != "Borrowed")
            return false;

        status = "Returned";

        // auto-set returnDate = system date? (tạm thời đặt bằng dueDate)
        // trong thực tế bạn sẽ lấy ngày hiện tại
        returnDate = dueDate;
        return true;
    }

    double calculateOverdueFine()
    {
        if (status != "Returned")
            return 0.0;

        int overdueDays = daysBetween(dueDate, returnDate);

        if (overdueDays <= 0)
            return 0.0;

        return overdueDays * 0.5; // 0.5 currency unit per day
    }

    bool extendDueDate()
    {
        // Add 7 days
        dueDate.day += 7;

        // Normalize date if > 30
        while (dueDate.day > 30) 
        {
            dueDate.day -= 30;
            dueDate.month++;

            if (dueDate.month > 12)
            {
                dueDate.month = 1;
                dueDate.year++;
            }
        }

        return true;
    }

    // ----------------------------
    // For printing record
    // ----------------------------
    string toString() const
    {
        return "BorrowID: " + borrowID +
               " | MemberID: " + memberID +
               " | BookID: " + bookID +
               " | BorrowDate: " + dateToString(borrowDate) +
               " | DueDate: " + dateToString(dueDate) +
               " | ReturnDate: " + dateToString(returnDate) +
               " | Status: " + status;
    }
};
