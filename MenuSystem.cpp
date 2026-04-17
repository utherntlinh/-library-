#include "MenuSystem.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

MenuSystem::MenuSystem(std::shared_ptr<DatabaseManager> db)
    : dbManager(db) {
    authManager = std::make_shared<AuthenticationManager>(db);
    circulationManager = std::make_shared<CirculationManager>(db);
}

MenuSystem::~MenuSystem() {}

void MenuSystem::Start() {
    DisplayMainMenu();
}

void MenuSystem::DisplayMainMenu() {
    int choice = 0;
    
    while (true) {
        cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========" << endl;
        cout << "1. Login as Librarian" << endl;
        cout << "2. Login as Member" << endl;
        cout << "3. Register as New Member" << endl;
        cout << "4. Exit" << endl;
        cout << "=============================================" << endl;
        
        choice = GetInput("Choose an option: ");
        
        if (choice == 4) {
            cout << "Thank you for using Library Management System. Goodbye!" << endl;
            break;
        }
        
        HandleMainMenuChoice(choice);
    }
}

void MenuSystem::HandleMainMenuChoice(int choice) {
    std::string username, password, email, name, phone;
    
    switch (choice) {
    case 1: {
        cout << "\n===== LIBRARIAN LOGIN =====" << endl;
        username = GetStringInput("Username: ");
        password = GetStringInput("Password: ");
        
        if (authManager->LoginAsLibrarian(username, password)) {
            LibrarianMenu();
            authManager->LogoutLibrarian();
        }
        break;
    }
    case 2: {
        cout << "\n===== MEMBER LOGIN =====" << endl;
        email = GetStringInput("Email: ");
        password = GetStringInput("Password: ");
        
        if (authManager->LoginAsMember(email, password)) {
            MemberMenu();
            authManager->LogoutMember();
        }
        break;
    }
    case 3: {
        cout << "\n===== NEW MEMBER REGISTRATION =====" << endl;
        name = GetStringInput("Full Name: ");
        email = GetStringInput("Email: ");
        phone = GetStringInput("Phone: ");
        password = GetStringInput("Password: ");
        
        authManager->RegisterNewMember(name, email, phone, password);
        break;
    }
    default:
        cout << "Invalid choice! Please try again." << endl;
    }
}

void MenuSystem::LibrarianMenu() {
    int choice = 0;
    
    while (true) {
        cout << "\n========== LIBRARIAN DASHBOARD ==========" << endl;
        cout << "Welcome, " << authManager->GetCurrentLibrarian().Name << endl;
        cout << "1. Manage Books" << endl;
        cout << "2. Manage Members" << endl;
        cout << "3. Issue/Return" << endl;
        cout << "4. Fines & Notifications" << endl;
        cout << "5. Logout" << endl;
        cout << "========================================" << endl;
        
        choice = GetInput("Choose an option: ");
        HandleLibrarianMenuChoice(choice);
        
        if (choice == 5) {
            break;
        }
    }
}

void MenuSystem::HandleLibrarianMenuChoice(int choice) {
    switch (choice) {
    case 1:
        ManageBooks();
        break;
    case 2:
        ManageMembers();
        break;
    case 3:
        IssueReturn();
        break;
    case 4:
        FinesAndNotifications();
        break;
    case 5:
        cout << "Logging out..." << endl;
        break;
    default:
        cout << "Invalid choice! Please try again." << endl;
    }
}

// ===== MEMBER MENU =====
void MenuSystem::MemberMenu() {
    int choice = 0;
    
    while (true) {
        cout << "\n========== MEMBER DASHBOARD ==========" << endl;
        cout << "Welcome, " << authManager->GetCurrentMember().Name << endl;
        cout << "1. Search Catalog" << endl;
        cout << "2. View My Loans" << endl;
        cout << "3. View Profile" << endl;
        cout << "4. Update Profile" << endl;
        cout << "5. Logout" << endl;
        cout << "=====================================" << endl;
        
        choice = GetInput("Choose an option: ");
        HandleMemberMenuChoice(choice);
        
        if (choice == 5) {
            break;
        }
    }
}

void MenuSystem::HandleMemberMenuChoice(int choice) {
    switch (choice) {
    case 1:
        SearchCatalog();
        break;
    case 2:
        ViewMyLoans();
        break;
    case 3:
        ViewProfile();
        break;
    case 4:
        UpdateProfile();
        break;
    case 5:
        cout << "Logging out..." << endl;
        break;
    default:
        cout << "Invalid choice! Please try again." << endl;
    }
}

// ===== MANAGE BOOKS =====
void MenuSystem::ManageBooks() {
    int choice = 0;
    
    cout << "\n===== MANAGE BOOKS =====" << endl;
    cout << "1. Add New Book" << endl;
    cout << "2. Update Book" << endl;
    cout << "3. Delete Book" << endl;
    cout << "4. View All Books" << endl;
    cout << "5. Back" << endl;
    
    choice = GetInput("Choose an option: ");
    
    switch (choice) {
    case 1: {
        cout << "\n--- Add New Book ---" << endl;
        Book newBook;
        newBook.BookID = 0; // Auto-assign
        newBook.ISBN = ""; // Auto-assign
        newBook.Title = GetStringInput("Title: ");
        newBook.Author = GetStringInput("Author: ");
        newBook.Category = GetStringInput("Category: ");
        newBook.Publisher = GetStringInput("Publisher: ");
        newBook.Year = GetInput("Year: ");
        newBook.Quantity = GetInput("Quantity: ");
        newBook.AvailableQuantity = newBook.Quantity;
        
        if (dbManager->AddBook(newBook)) {
            cout << "[OK] Book added successfully!" << endl;
        } else {
            cout << "[ERROR] Failed to add book!" << endl;
        }
        break;
    }
    case 2: {
        cout << "\n--- Update Book ---" << endl;
        int bookId = GetInput("Enter Book ID: ");
        Book book;
        if (dbManager->GetBookByID(bookId, book)) {
            cout << "Current Title: " << book.Title << endl;
            book.Title = GetStringInput("New Title (or press Enter to keep): ");
            if (book.Title.empty()) {
                dbManager->GetBookByID(bookId, book); // Reload to get old title
            }
            
            cout << "Current Author: " << book.Author << endl;
            book.Author = GetStringInput("New Author (or press Enter to keep): ");
            if (book.Author.empty()) {
                dbManager->GetBookByID(bookId, book);
            }
            
            cout << "Current Category: " << book.Category << endl;
            book.Category = GetStringInput("New Category (or press Enter to keep): ");
            if (book.Category.empty()) {
                dbManager->GetBookByID(bookId, book);
            }
            
            cout << "Current Quantity: " << book.Quantity << endl;
            int newQty = GetInput("New Quantity (0 to keep): ");
            if (newQty > 0) {
                book.Quantity = newQty;
            }
            
            if (dbManager->UpdateBook(book)) {
                cout << "[OK] Book updated successfully!" << endl;
            } else {
                cout << "[ERROR] Failed to update book!" << endl;
            }
        } else {
            cout << "[ERROR] Book not found!" << endl;
        }
        break;
    }
    case 3: {
        cout << "\n--- Delete Book ---" << endl;
        int bookId = GetInput("Enter Book ID: ");
        Book book;
        if (dbManager->GetBookByID(bookId, book)) {
            cout << "Book Title: " << book.Title << endl;
            cout << "Are you sure you want to delete? (y/n): ";
            char confirm;
            cin >> confirm;
            cin.ignore();
            
            if (confirm == 'y' || confirm == 'Y') {
                if (dbManager->DeleteBook(bookId)) {
                    cout << "[OK] Book deleted successfully!" << endl;
                } else {
                    cout << "[ERROR] Failed to delete book!" << endl;
                }
            } else {
                cout << "Deletion cancelled." << endl;
            }
        } else {
            cout << "[ERROR] Book not found!" << endl;
        }
        break;
    }
    case 4: {
        cout << "\n--- All Books ---" << endl;
        std::vector<Book> books;
        if (dbManager->GetAllBooks(books)) {
            if (books.empty()) {
                cout << "No books in the system." << endl;
            } else {
                DisplayCatalog(books);
            }
        } else {
            cout << "[ERROR] Failed to retrieve books!" << endl;
        }
        break;
    }
    case 5:
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
}

// ===== MANAGE MEMBERS =====
void MenuSystem::ManageMembers() {
    cout << "\n===== MANAGE MEMBERS =====" << endl;
    cout << "1. Add New Member" << endl;
    cout << "2. View All Members" << endl;
    cout << "3. Update Member Status" << endl;
    cout << "4. Back" << endl;
    
    int choice = GetInput("Choose an option: ");
    
    switch (choice) {
    case 1: {
        cout << "\n--- Add New Member ---" << endl;
        string name = GetStringInput("Full Name: ");
        string email = GetStringInput("Email: ");
        string phone = GetStringInput("Phone: ");
        string password = GetStringInput("Password: ");
        
        if (authManager->RegisterNewMember(name, email, phone, password)) {
            cout << "[OK] Member added successfully!" << endl;
        } else {
            cout << "[ERROR] Failed to add member!" << endl;
        }
        break;
    }
    case 2: {
        std::vector<Member> members;
        if (dbManager->GetAllMembers(members)) {
            if (members.empty()) {
                cout << "No members in the system." << endl;
            } else {
                cout << "\n--- All Members ---" << endl;
                cout << setw(5) << "ID" << setw(20) << "Name" << setw(25) << "Email" 
                     << setw(15) << "Status" << setw(12) << "Expiry" << endl;
                cout << string(77, '-') << endl;
                
                for (const auto& member : members) {
                    cout << setw(5) << member.MemberID << setw(20) << member.Name 
                         << setw(25) << member.Email << setw(15) << member.Status 
                         << setw(12) << member.ExpiryDate << endl;
                }
            }
        } else {
            cout << "[ERROR] Failed to retrieve members!" << endl;
        }
        break;
    }
    case 3: {
        int memberId = GetInput("Enter Member ID: ");
        Member member;
        if (dbManager->GetMemberByID(memberId, member)) {
            cout << "Member Name: " << member.Name << endl;
            cout << "Current Status: " << member.Status << endl;
            cout << "\nSelect new status:" << endl;
            cout << "1. Active" << endl;
            cout << "2. Blocked" << endl;
            cout << "3. Expired" << endl;
            int statusChoice = GetInput("Choose: ");
            
            switch (statusChoice) {
            case 1:
                member.Status = "Active";
                break;
            case 2:
                member.Status = "Blocked";
                break;
            case 3:
                member.Status = "Expired";
                break;
            default:
                cout << "Invalid choice!" << endl;
                return;
            }
            
            if (dbManager->UpdateMember(member)) {
                cout << "[OK] Member status updated to: " << member.Status << endl;
            } else {
                cout << "[ERROR] Failed to update member status!" << endl;
            }
        } else {
            cout << "[ERROR] Member not found!" << endl;
        }
        break;
    }
    case 4:
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
}

// ===== ISSUE/RETURN =====
void MenuSystem::IssueReturn() {
    cout << "\n===== ISSUE/RETURN =====" << endl;
    cout << "1. Issue Book to Member" << endl;
    cout << "2. Return Book from Member" << endl;
    cout << "3. Back" << endl;
    
    int choice = GetInput("Choose an option: ");
    
    switch (choice) {
    case 1: {
        cout << "\n--- Issue Book ---" << endl;
        int memberId = GetInput("Enter Member ID: ");
        
        // Check member exists
        Member member;
        if (!dbManager->GetMemberByID(memberId, member)) {
            cout << "[ERROR] Member not found!" << endl;
            break;
        }
        
        cout << "Member: " << member.Name << " (Status: " << member.Status << ")" << endl;
        
        int bookId = GetInput("Enter Book ID: ");
        
        // Check book exists
        Book book;
        if (!dbManager->GetBookByID(bookId, book)) {
            cout << "[ERROR] Book not found!" << endl;
            break;
        }
        
        cout << "Book: " << book.Title << " (Available: " << book.AvailableQuantity << ")" << endl;
        
        string errorMsg;
        if (circulationManager->IssueBook(memberId, bookId, errorMsg)) {
            cout << "[OK] Book issued successfully!" << endl;
        } else {
            cout << "[ERROR] " << errorMsg << endl;
        }
        break;
    }
    case 2: {
        cout << "\n--- Return Book ---" << endl;
        int loanId = GetInput("Enter Loan ID: ");
        
        string errorMsg;
        if (circulationManager->ReturnBook(loanId, errorMsg)) {
            cout << "[OK] Book returned successfully!" << endl;
        } else {
            cout << "[ERROR] " << errorMsg << endl;
        }
        break;
    }
    case 3:
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
}

// ===== FINES & NOTIFICATIONS =====
void MenuSystem::FinesAndNotifications() {
    cout << "\n===== FINES & NOTIFICATIONS =====" << endl;
    cout << "1. View and Process Fines" << endl;
    cout << "2. View Notifications" << endl;
    cout << "3. Back" << endl;
    
    int choice = GetInput("Choose an option: ");
    
    switch (choice) {
    case 1: {
        int memberId = GetInput("Enter Member ID: ");
        
        std::vector<Fine> fines;
        if (dbManager->GetUnpaidFinesByMemberID(memberId, fines)) {
            if (fines.empty()) {
                cout << "[OK] No unpaid fines for this member!" << endl;
                break;
            }
            
            cout << "\n--- Unpaid Fines ---" << endl;
            cout << setw(8) << "Fine ID" << setw(12) << "Amount" << setw(12) << "Status" << endl;
            cout << string(32, '-') << endl;
            
            double totalAmount = 0.0;
            for (const auto& fine : fines) {
                cout << setw(8) << fine.FineID << setw(12) << fine.Amount 
                     << setw(12) << fine.Status << endl;
                totalAmount += fine.Amount;
            }
            
            cout << string(32, '-') << endl;
            cout << "Total: " << totalAmount << " VND" << endl;
            
            int fineId = GetInput("\nEnter Fine ID to mark as paid (0 to cancel): ");
            if (fineId > 0) {
                if (dbManager->UpdateFineStatus(fineId, "Paid")) {
                    cout << "[OK] Fine marked as paid!" << endl;
                } else {
                    cout << "[ERROR] Failed to update fine status!" << endl;
                }
            }
        } else {
            cout << "[ERROR] Member not found!" << endl;
        }
        break;
    }
    case 2: {
        int memberId = GetInput("Enter Member ID: ");
        std::vector<Notification> notifications;
        
        if (dbManager->GetNotificationsByMemberID(memberId, notifications)) {
            if (notifications.empty()) {
                cout << "[OK] No notifications for this member." << endl;
            } else {
                cout << "\n--- Notifications ---" << endl;
                cout << setw(5) << "ID" << setw(12) << "Date" << setw(50) << "Message" 
                     << setw(10) << "Status" << endl;
                cout << string(77, '-') << endl;
                
                for (const auto& notif : notifications) {
                    cout << setw(5) << notif.NotificationID << setw(12) << notif.Date 
                         << setw(50) << notif.Message << setw(10) << notif.Status << endl;
                }
            }
        } else {
            cout << "[ERROR] Member not found!" << endl;
        }
        break;
    }
    case 3:
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
}

void MenuSystem::SearchCatalog() {
    cout << "\n===== SEARCH CATALOG =====" << endl;
    string searchTerm = GetStringInput("Enter search term (Title/Author/Category): ");
    
    std::vector<Book> books;
    if (dbManager->SearchBooks(searchTerm, books)) {
        if (books.empty()) {
            cout << "No books found!" << endl;
            return;
        }
        
        DisplayCatalog(books);
    } else {
        cout << "Search failed!" << endl;
    }
}

void MenuSystem::ViewMyLoans() {
    Member currentMember = authManager->GetCurrentMember();
    std::vector<Loan> loans;
    
    if (circulationManager->GetMemberLoans(currentMember.MemberID, loans)) {
        if (loans.empty()) {
            cout << "You have no loans!" << endl;
            return;
        }
        
        cout << "\n===== MY LOANS =====" << endl;
        cout << setw(8) << "Loan ID" << setw(8) << "Book ID" << setw(12) << "Borrow Date" 
             << setw(12) << "Due Date" << setw(12) << "Status" << endl;
        cout << string(52, '-') << endl;
        
        for (const auto& loan : loans) {
            cout << setw(8) << loan.LoanID << setw(8) << loan.BookID 
                 << setw(12) << loan.BorrowDate << setw(12) << loan.DueDate 
                 << setw(12) << loan.Status << endl;
        }
    } else {
        cout << "Failed to retrieve loans!" << endl;
    }
}

void MenuSystem::ViewProfile() {
    Member currentMember = authManager->GetCurrentMember();
    
    cout << "\n===== MY PROFILE =====" << endl;
    cout << "Member ID: " << currentMember.MemberID << endl;
    cout << "Name: " << currentMember.Name << endl;
    cout << "Email: " << currentMember.Email << endl;
    cout << "Phone: " << currentMember.Phone << endl;
    cout << "Status: " << currentMember.Status << endl;
    cout << "Expiry Date: " << currentMember.ExpiryDate << endl;
}

void MenuSystem::UpdateProfile() {
    Member currentMember = authManager->GetCurrentMember();
    
    cout << "\n===== UPDATE PROFILE =====" << endl;
    currentMember.Name = GetStringInput("Name (current: " + currentMember.Name + "): ");
    currentMember.Phone = GetStringInput("Phone (current: " + currentMember.Phone + "): ");
    
    if (dbManager->UpdateMember(currentMember)) {
        cout << "Profile updated successfully!" << endl;
    } else {
        cout << "Failed to update profile!" << endl;
    }
}

void MenuSystem::DisplayCatalog(const std::vector<Book>& books) {
    // Display book catalog: ISBN, Title, Author, Category, Quantity, Publisher, Year
    cout << "\n--- Book Catalog ---" << endl;
    const int W_ISBN = 6;
    const int W_TITLE = 25;
    const int W_AUTHOR = 18;
    const int W_CAT = 12;
    const int W_QTY = 10;
    const int W_PUB = 18;
    const int W_YEAR = 6;

    cout << left << setw(W_ISBN) << "ISBN"
         << setw(W_TITLE) << "Title"
         << setw(W_AUTHOR) << "Author"
         << setw(W_CAT) << "Category"
         << right << setw(W_QTY) << "Qty"
         << left << setw(W_PUB) << "Publisher"
         << right << setw(W_YEAR) << "Year" << endl;

    cout << string(W_ISBN + W_TITLE + W_AUTHOR + W_CAT + W_QTY + W_PUB + W_YEAR, '-') << endl;

    for (const auto& book : books) {
        auto shorten = [](const std::string& s, size_t max)->std::string{
            if (s.length() <= max) return s;
            if (max <= 3) return s.substr(0, max);
            return s.substr(0, max - 3) + "...";
        };
        std::string title = shorten(book.Title, W_TITLE - 1);
        std::string author = shorten(book.Author, W_AUTHOR - 1);
        std::string category = shorten(book.Category, W_CAT - 1);
        std::string publisher = shorten(book.Publisher, W_PUB - 1);
        std::string year = std::to_string(book.Year);

        cout << left << setw(W_ISBN) << book.BookID
             << setw(W_TITLE) << title
             << setw(W_AUTHOR) << author
             << setw(W_CAT) << category
             << right << setw(W_QTY) << book.Quantity
             << left << setw(W_PUB + 1) << " " + publisher
             << right << setw(W_YEAR) << year << endl;
    }
}

int MenuSystem::GetInput(const std::string& prompt) {
    int input;
    while (true) {
        cout << prompt;
        if (cin >> input) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number." << endl;
    }
}

std::string MenuSystem::GetStringInput(const std::string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

double MenuSystem::GetDoubleInput(const std::string& prompt) {
    double input;
    while (true) {
        cout << prompt;
        if (cin >> input) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number." << endl;
    }
}