#ifndef AUTHENTICATION_MANAGER_H
#define AUTHENTICATION_MANAGER_H

#include "DatabaseManager.h"
#include "Models.h"
#include <memory>
#include <string>

class AuthenticationManager {
private:
    std::shared_ptr<DatabaseManager> dbManager;
    Librarian currentLibrarian;
    Member currentMember;
    bool isLibrarianLoggedIn;
    bool isMemberLoggedIn;

public:
    AuthenticationManager(std::shared_ptr<DatabaseManager> db);
    ~AuthenticationManager();

    // Login methods
    bool LoginAsLibrarian(const std::string& username, const std::string& password);
    bool LoginAsMember(const std::string& email, const std::string& password);
    bool RegisterNewMember(const std::string& name, const std::string& email, 
                          const std::string& phone, const std::string& password);

    // Logout methods
    bool LogoutLibrarian();
    bool LogoutMember();

    // Session check
    bool IsLibrarianLoggedIn() const;
    bool IsMemberLoggedIn() const;

    // Get current user
    Librarian GetCurrentLibrarian() const;
    Member GetCurrentMember() const;

    // Add default librarian
    bool AddDefaultLibrarian();
};

#endif // AUTHENTICATION_MANAGER_H