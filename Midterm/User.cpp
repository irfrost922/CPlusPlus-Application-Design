#include "User.h"

using namespace std;

User::User(const string& name) : username(name) {
}

string User::getUsername() const {
    return username;
}

Admin::Admin(const string& name) : User(name) {
}

string Admin::getRoleName() const {
    return "Admin";
}

bool Admin::canModifyRecords() const {
    return true;
}

RegularUser::RegularUser(const string& name) : User(name) {
}

string RegularUser::getRoleName() const {
    return "Regular User";
}

bool RegularUser::canModifyRecords() const {
    return false;
}
