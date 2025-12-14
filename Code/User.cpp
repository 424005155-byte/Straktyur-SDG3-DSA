#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

unordered_map<string, User> userTable;

void loadUsers() {
    userTable.clear();
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, age, username, password;
        getline(ss, name, '|');
        getline(ss, age, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');

        userTable[username] = {name, age, password};
    }
}

void registerUser() {
    loadUsers();

    string name, age, username, password;
    cout << "\nFull Name: ";
    getline(cin, name);
    cout << "Age: ";
    getline(cin, age);
    cout << "Username: ";
    getline(cin, username);

    if (userTable.count(username)) {
        cout << "❌ Username already exists.\n";
        return;
    }

    cout << "Password: ";
    getline(cin, password);

    ofstream file("users.txt", ios::app);
    file << name << "|" << age << "|" << username << "|" << password << "\n";
    userTable[username] = {name, age, password};

    cout << "✅ Registration successful!\n";
}

string loginUser() {
    loadUsers();

    string username, password;
    cout << "\nUsername: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    if (userTable.count(username) && userTable[username].password == password) {
        cout << "✅ Welcome, " << userTable[username].name << "!\n";
        return username;
    }

    cout << "❌ Invalid username or password.\n";
    return "";
}
