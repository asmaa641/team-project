
#include "User.h"
#include <map>
#include <string>
using namespace std;

class UserManager {
private:
    map<string, User*> usersMap;
    string filePath = "users.txt"; // file of users where saved

public:
    ~UserManager();

    void loadUsersFromFile();
    void saveUsersToFile();
    bool validateUser(const string& username, const string& password);

    bool signupUser(const string& userType, const string& username, const string& password, const string& email);
};
