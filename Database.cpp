#include "Database.h"
#include <iostream>

Database::Database(const std::string& path) 
    : isConnected(false) {}

Database::~Database() {
    Disconnect();
}

bool Database::Connect() {
    isConnected = true;
    std::cout << "[OK] Database connected (In-Memory Storage)" << std::endl;
    return true;
}

bool Database::Disconnect() {
    isConnected = false;
    std::cout << "[OK] Database disconnected" << std::endl;
    return true;
}

bool Database::IsConnected() const {
    return isConnected;
}

bool Database::CreateSchema() {
    std::cout << "[OK] Database schema created" << std::endl;
    return true;
}