#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string username;

public:
    User(const std::string& name);
    virtual ~User() = default;

    std::string getUsername() const;
    virtual std::string getRoleName() const = 0;
    virtual bool canModifyRecords() const = 0;
};

class Admin : public User {
public:
    Admin(const std::string& name);
    std::string getRoleName() const override;
    bool canModifyRecords() const override;
};

class RegularUser : public User {
public:
    RegularUser(const std::string& name);
    std::string getRoleName() const override;
    bool canModifyRecords() const override;
};

#endif
