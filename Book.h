#ifndef BOOK_H
#define BOOK_H
#include <sstream>
#include <string>
using namespace std;

class Book {
private:
    string bookID;
    string title;
    string author;
    string publisher;
    int publicationYear;
    string category;
    string ISBN;
    int stock; // thêm theo UML

public:
    // Default constructor
    Book()
    {
        bookID = "";
        title = "";
        author = "";
        publisher = "";
        publicationYear = 0;
        category = "";
        ISBN = "";
        stock = 0;
    }

    // Full constructor
    Book(const string& bookID,
         const string& title,
         const string& author,
         const string& publisher,
         int publicationYear,
         const string& category,
         const string& ISBN,
         int stock = 0)  // cho phép đặt stock luôn
    {
        this->bookID = bookID;
        this->title = title;
        this->author = author;
        this->publisher = publisher;
        this->publicationYear = publicationYear;
        this->category = category;
        this->ISBN = ISBN;
        this->stock = stock;
    }

    // Getters
    string getBookID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getPublisher() const { return publisher; }
    int getPublicationYear() const { return publicationYear; }
    string getCategory() const { return category; }
    string getISBN() const { return ISBN; }
    int getStock() const { return stock; }

    // Setters
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
    void setPublisher(const string& p) { publisher = p; }
    void setPublicationYear(int y) { publicationYear = y; }
    void setCategory(const string& c) { category = c; }
    void setISBN(const string& isbn) { ISBN = isbn; }
    void setStock(int s) { stock = s; }

    // Return full book info
    string getBookInfo() const
    {
        stringstream ss;
        ss << "BookID: " << bookID << "\n"
           << "Title: " << title << "\n"
           << "Author: " << author << "\n"
           << "Publisher: " << publisher << "\n"
           << "Publication Year: " << publicationYear << "\n"
           << "Category: " << category << "\n"
           << "ISBN: " << ISBN << "\n"
           << "Stock: " << stock << "\n";
        return ss.str();
    }

    // Check if book is available
    bool checkAvailability() const
    {
        return stock > 0;
    }

    // Decrease stock when borrowed
    bool decreaseStock()
    {
        if (stock > 0) {
            stock--;
            return true;
        }
        return false;
    }

    // Increase stock when returned
    bool increaseStock()
    {
        stock++;
        return true;
    }
};

#endif
