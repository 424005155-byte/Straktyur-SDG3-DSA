#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>

struct User {
    std::string name;
    std::string age;
    std::string password;
};

extern std::unordered_map<std::string, User> userTable;

void loadUsers();
void registerUser();
std::string loginUser();

#endif
