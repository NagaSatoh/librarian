#pragma once
#include <string>
#include <iostream>
#include <ctime>   // dùng time() và localtime()
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

// lấy ngày hiện tại ( ht sửa  ) 
    Date getToday() const 
{
    time_t t = time(nullptr);        // lấy thời gian hiện tại
        tm* local_tm = localtime(&t);    // chuyển sang ngày/tháng/năm
        Date today;
        today.day = local_tm->tm_mday;         // lấy ngày
        today.month = local_tm->tm_mon + 1;    // lấy tháng (tm_mon 0-11)
        today.year = local_tm->tm_year + 1900; // lấy năm
        if (today.day > 30) today.day = 30;    // 30 ngày/tháng
        return today;
}
// chuẩn hóa ngày tháng ( ht sửa ) 
    void normalizeDate(Date &d) const
{
    while(d.day > 30)          // nếu ngày lớn hơn 30, cộng tháng
   {
       d.day -= 30;
       d.month++;
   }
    while(d.month > 12 )      // nếu tháng lớn hơn 12, cộng năm
   {
       d.month -= 12;
       d.year ++;
   }
    if(d.day <= 0 ) d.day = 1;    // tránh trường hợp ngày âm
    if(d.month <= 0 ) d.month = 1;   // tránh trường hợp tháng âm
    if(d.year <0 ) d.year = 0;     // tránh trường hợp năm âm 
}
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
    void setBorrowDate(Date d) { borrowDate = d;normalizeDate(borrowDate);}  // chuẩn hóa ngày 
    void setDueDate(Date d) { dueDate = d;normalizeDate(dueDate); }
    void setReturnDate(Date d) { returnDate = d;normalizeDate(returnDate); }
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
// nếu borrowDate chưa set thì lấy ngày hôm nay ( ht sửa ) 
        if (borrowDate.day ==0 && borrowDate.month ==0 && borrowDate.year ==0)
        {
            borrowDate = getToday();
        }
// nếu dueDate chưa set thì mặc định = borrowDate + 14 ngày ( ht sửa ) 
        if (dueDate.day ==0 && dueDate.month == 0 && dueDate.year == 0) 
        {
            dueDate = borrowDate;
            dueDate.day +=14;
            normalizeDate(dueDate); // chuẩn hoa nếu tràn sang tháng/năm 
        }
        return true;
    }

    bool returnBook()
    {
        if (status != "Borrowed")
            return false;

        status = "Returned";

        // auto-set returnDate = system date? (tạm thời đặt bằng dueDate)
        // trong thực tế bạn sẽ lấy ngày hiện tại
        // set returnDate = ngày hiện tại 
        returnDate = getToday();  // nếu 1 người trả sách họ có thể trả sớm, đúng hạn hoặc trễ hạn
        normalizeDate(returnDate);
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
        normalizeDate(dueDate);   // dùng theo normalizeDate ở trên cho gọn ( ht sửa ) 
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

