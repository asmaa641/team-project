// UserManager.cpp
#include "UserManager.h"
#include "Admin.h"
#include "RegularUser.h"
#include <fstream>
#include <iostream>
using namespace std;

UserManager::~UserManager() {
    for (auto& pair : usersMap) { //for each
        delete pair.second;
    }
}

void UserManager::loadUsersFromFile() {
    ifstream file(filePath); //read from  users file
    if (!file.is_open()) {
        cout << "Not Open";
        return;
    }

    string userType, username, password, email;
    while (file >> userType >> username >> password >> email) {
        if (userType == "Admin") {
            usersMap[username] = new Admin(username, password, email);
        } else if (userType == "RegularUser") {
            usersMap[username] = new RegularUser(username, password, email);
        }
    }

    file.close();
}

void UserManager::saveUsersToFile() {
    ofstream file(filePath); //write and save manually users
    if (!file.is_open()) {
        cout << "Not Open";
        return;
    }

    for (auto& pair : usersMap) {
        file << pair.second->getUserType() << " "
             << pair.second->getUsername() << " "
             << pair.second->getPassword() << " "
             << pair.second->getEmail() << "\n";
    }

    file.close();
}

bool UserManager::validateUser(const string& username, const string& password) { //copy information
    if (usersMap.count(username) && usersMap.at(username)->checkPassword(password)) { // checks if the user exists and pointer to values by usename, check password
        return true;
    }
    return false; //otherwise
}

bool UserManager::signupUser(const string& userType, const string& username, const string& password, const string& email) {
    if (usersMap.count(username)) { // Check if user already exists
        return false; // signup fails if user exists, no dublicated usernames
    }    

    if (userType == "Admin") {
        usersMap[username] = new Admin(username, password, email);
    } else if (userType == "RegularUser") {
        usersMap[username] = new RegularUser(username, password, email);
    } else {
        return false; // Unknown type
    }

    saveUsersToFile(); //save all
    return true; // singnup success 
}
