#pragma once
#include "DatabaseManager.h"
#include <string>
#include <memory>
 
class AuthenticationManager {
private:
    std::shared_ptr<DatabaseManager> dbManager;
    bool isLibrarianLoggedIn;
    bool isMemberLoggedIn;
    Librarian currentLibrarian;
    Member currentMember;
 
public:
    AuthenticationManager(std::shared_ptr<DatabaseManager> db);
    ~AuthenticationManager();
 
    bool LoginAsLibrarian(const std::string& username, const std::string& password);
    bool LoginAsMember(const std::string& email, const std::string& password);
    bool RegisterNewMember(const std::string& name, const std::string& email,
                           const std::string& phone, const std::string& password);
    bool LogoutLibrarian();
    bool LogoutMember();
 
    bool IsLibrarianLoggedIn() const;
    bool IsMemberLoggedIn() const;
 
    Librarian GetCurrentLibrarian() const;
    Member GetCurrentMember() const;
 
    bool AddDefaultLibrarian();
};
 
