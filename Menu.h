#pragma once
#include "User.h"
#include "Member.h"
#include "Librarian.h"
#include "Book.h"
#include "Fine.h"
#include "Borrow.h"
#include "User_handle_file.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Menu {
private:
    User* currentUser;

public:
    Menu() : currentUser(nullptr) {}

    void doMenu() {
        int choice;
        while (true) {
            if (currentUser == nullptr) {
                displayMainMenu();
                cout << "Choice: ";
                cin >> choice;
                cin.ignore(); // tránh lỗi getline

                switch (choice) {
                    case 1:
                        login();
                        break;
                    case 2: // regisster member
                    {
                        Member newMember;
                        newMember.registerMember();
                        break;
                    }
                    case 0:
                        cout << "Goodbye!" << endl;
                        return;
                    default:
                        cout << "Invalid choice. Try again." << endl;
                }
            } else {
                // Khi đã login
                if (dynamic_cast<Librarian*>(currentUser)) {
                    displayLibrarianMenu();
                } else if (dynamic_cast<Member*>(currentUser)) {
                    displayMemberMenu();
                }
            }
        }
    }

    void login() 
    {
        string email, password;
        cout << "*** PLEASE ENTER ***" << endl;
        cout << "Email: ";
        getline(cin, email);
        cout << "Password: ";
        getline(cin, password);

        User* found = UserRepository::loadUserByEmail(email, password);
        if (found && found->login(email, password)) {
            currentUser = found;
            cout << "[SUCCESS] Login successful." << endl;
        } else {
            cout << "[ERROR] Incorrect email or password." << endl;
            if (found) delete found;
        }
    }

    void displayMainMenu() {
        cout << "=== MAIN MENU ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register Member" << endl;
        cout << "0. Exit" << endl;
    }

    void displayMemberMenu() {
        int choice;
        Member* mem = dynamic_cast<Member*>(currentUser);
        if (!mem) return;

        while (true) {
            cout << "\n=== MEMBER MENU ===\n";
            cout << "1. View borrowed books\n";
            cout << "2. Pay fines\n";
            cout << "3. Search books\n";  // mới
            cout << "0. Logout\n";
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: mem->viewBorrowingHistory(); break;
                case 2: /* pay fines logic */ break;
                case 3: {
                    string keyword;
                    cout << "Enter keyword: ";
                    getline(cin, keyword);
                    mem->searchBook(keyword);
                    break;
                }
                case 0:
                    currentUser = nullptr;
                    return;
                default: cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    void displayLibrarianMenu() {
        int choice;
        while (true) {
            cout << "\n=== LIBRARIAN MENU ===" << endl;
            cout << "1. Manage Books" << endl;
            cout << "2. Manage Members" << endl;
            cout << "3. Manage Borrow/Return" << endl;
            cout << "4. Reports" << endl;
            cout << "0. Logout" << endl;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    displayManageBookMenu();
                    break;
                case 2:
                    displayManageMemberMenu();
                    break;
                case 3:
                    displayManageBorrowMenu();
                    break;
                case 4:
                    displayManageRepotsMenu();
                    break;
                case 0:
                    currentUser = nullptr;
                    return;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    void displayManageBookMenu() {
        int choice;
        while (true) {
            cout << "\n--- MANAGE BOOKS ---" << endl;
            cout << "1. Add book" << endl;
            cout << "2. Remove book" << endl;
            cout << "3. Update book" << endl;
            cout << "0. Back" << endl;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            Librarian* lib = dynamic_cast<Librarian*>(currentUser);
            if (!lib) return;

            switch (choice) {
                case 1: lib->addBook(); break;
                case 2: lib->removeBook(); break;
                case 3: lib->updateBook(); break;
                case 0: return;
                default: cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    void displayManageMemberMenu() {
        int choice;
        while (true) {
            cout << "\n--- MANAGE MEMBERS ---" << endl;
            cout << "1. Delete member" << endl;
            cout << "0. Back" << endl;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            Librarian* lib = dynamic_cast<Librarian*>(currentUser);
            if (!lib) return;

            switch (choice) {
                case 1: lib->removeMember(); break;
                case 0: return;
                default: cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    void displayManageBorrowMenu() {
        int choice;
        while (true) {
            cout << "\n--- MANAGE BORROW/RETURN ---" << endl;
            cout << "1. Borrow/Return book" << endl;
            cout << "0. Back" << endl;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            Librarian* lib = dynamic_cast<Librarian*>(currentUser);
            if (!lib) return;

            switch (choice) {
                case 1: lib->manageBorrowing(); break;
                case 0: return;
                default: cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    void displayManageRepotsMenu() {
        cout << "Reports feature not implemented yet." << endl;
    }
};
