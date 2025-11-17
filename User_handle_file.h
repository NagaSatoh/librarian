#pragma once
#include "User.h"
#include "Member.h"
#include "Librarian.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class UserRepository {
public:
    // Tải đối tượng Member hoặc Librarian từ file theo email/password
    static User* loadUserByEmail(const string& email, const string& password) {
        ifstream f("pass.txt");
        if (!f.is_open()) {
            cout << "Can't open pass.txt" << endl;
            return nullptr;
        }

        string line;
        while (getline(f, line)) {
            size_t pos1 = line.find(',');
            if (pos1 == string::npos) continue;

            size_t pos2 = line.find(',', pos1 + 1);
            if (pos2 == string::npos) continue;

            string fileEmail = line.substr(0, pos1);
            string filePassword = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string role = line.substr(pos2 + 1);

            if (fileEmail == email && filePassword == password) {
                if (role == "member") {
                    return new Member(email, password);      // cần constructor email/password
                } else if (role == "librarian") {
                    return new Librarian(email, password);  // cũng cần constructor email/password
                }
            }
        }

        return nullptr;
    }
};
