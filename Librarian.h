#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include "User.h"
#include "Book.h"

using namespace std;

class Librarian : public User {
private:
    string librarianID;
    string employeeID;
    string shiftTimings;

    vector<Book> books; // Librarian quản lý danh sách sách

    int findBookIndexByID(const string& bookID) const 
    {
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].getBookID() == bookID) {
                return i;
            }
        }
        return -1;
    }

public:
    Librarian()
        : librarianID(""), employeeID(""), shiftTimings("") {}

    Librarian(const string& librarianID, const string& employeeID, const string& shiftTimings)
        : librarianID(librarianID), employeeID(employeeID), shiftTimings(shiftTimings) {}

    Librarian(const string& email, const string& password)
        : User("", "", email, "", password), // gọi constructor User cha
          librarianID(""), employeeID(""), shiftTimings("") {}


    // ======== GET INFO (override) ========
    string getInfo() override {
        return "LibrarianID: " + librarianID +
               ", EmployeeID: " + employeeID +
               ", Shift: " + shiftTimings;
    }

    void registerMember() override {
        cout << "Librarian does not register members using this function.\n";
    }

    // =============================
    //       BOOK MANAGEMENT
    // =============================

    bool addBook()
    {
        string id, title, author, publisher, category, isbn;
        int year;

        cout << "Add new book - enter details\n";
        cout << "bookID: "; getline(cin, id);

        if (id.empty()) {
            cout << "bookID cannot be empty.\n";
            return false;
        }
        if (findBookIndexByID(id) != -1) {
            cout << "Book ID already exists.\n";
            return false;
        }

        cout << "title: "; getline(cin, title);
        cout << "author: "; getline(cin, author);
        cout << "publisher: "; getline(cin, publisher);
        cout << "publicationYear: ";

        while (!(cin >> year)) {
            cout << "Invalid input. Enter integer year: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "category: "; getline(cin, category);
        cout << "ISBN: "; getline(cin, isbn);

        books.emplace_back(id, title, author, publisher, year, category, isbn);
        cout << "Book added.\n";
        return true;
    }

    bool removeBook()
    {
        string id;
        cout << "Enter bookID to remove: ";
        getline(cin, id);

        int idx = findBookIndexByID(id);
        if (idx == -1) {
            cout << "Book not found.\n";
            return false;
        }

        books.erase(books.begin() + idx);
        cout << "Book removed.\n";
        return true;
    }

    bool updateBook()   // chuẩn UML
    {
        string id;
        cout << "Enter bookID to update: ";
        getline(cin, id);

        int idx = findBookIndexByID(id);
        if (idx == -1) {
            cout << "Book not found.\n";
            return false;
        }

        Book& b = books[idx];
        cout << "Current info:\n" << b.getBookInfo() << endl;

        string s;
        int yr;

        cout << "New title (blank = keep): ";
        getline(cin, s);
        if (!s.empty()) b.setTitle(s);

        cout << "New author (blank = keep): ";
        getline(cin, s);
        if (!s.empty()) b.setAuthor(s);

        cout << "New publisher (blank = keep): ";
        getline(cin, s);
        if (!s.empty()) b.setPublisher(s);

        cout << "New publicationYear (0 = keep): ";
        if (cin >> yr && yr != 0) b.setPublicationYear(yr);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "New category (blank = keep): ";
        getline(cin, s);
        if (!s.empty()) b.setCategory(s);

        cout << "New ISBN (blank = keep): ";
        getline(cin, s);
        if (!s.empty()) b.setISBN(s);

        cout << "Book updated.\n";
        return true;
    }

    // =============================
    //        BORROW MANAGEMENT
    // =============================

    void manageBorrowing()
    {
        cout << "Manage borrowing (b = borrow, r = return): ";
        char c;
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (c != 'b' && c != 'r') {
            cout << "Invalid option.\n";
            return;
        }

        string id;
        cout << "Enter bookID: ";
        getline(cin, id);

        if (findBookIndexByID(id) == -1) {
            cout << "Book not found.\n";
            return;
        }

        if (c == 'b')
            cout << "Borrow recorded for " << id << endl;
        else
            cout << "Return recorded for " << id << endl;
    }

    // =============================
    //        MEMBER MANAGEMENT
    // =============================

    bool removeMember()   // đúng tên UML
    {
        cout << "No member database implemented.\n";
        return false;
    }

    bool updateMember()   // đúng tên UML
    {
        cout << "No member database implemented.\n";
        return false;
    }

    // =============================
    //        REPORT GENERATION
    // =============================

    void generateReport()
    {
        cout << "\n===== LIBRARY REPORT =====\n";
        cout << "Total books: " << books.size() << endl;

        for (const auto& b : books)
            cout << " - " << b.getBookInfo() << endl;

        cout << "==========================\n";
    }
    bool login(const string& email, const string& password) override 
    {
        return this->email == email && this->password == password;
    }

    void logout() override 
    {
        cout << "[INFO] Librarian logged out.\n";
    }

    bool changePassword(const string& oldPassword, const string& newPassword) override 
    {
        if (password == oldPassword) 
        {
            password = newPassword;
            return true;
        }
        return false;
    }

    bool searchBook(const string& keyword) override 
    {
        // giả lập luôn true
        return true;
    }

};
