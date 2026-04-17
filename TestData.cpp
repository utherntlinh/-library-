#include "DatabaseManager.h"
#include "AuthenticationManager.h"
#include <iostream>

// Insert Test Data
void InsertTestData(std::shared_ptr<DatabaseManager> dbManager) {
    std::cout << "\n[*] Inserting test data...\n" << std::endl;

    // ===== Book =====
    Book book1;
    book1.BookID = 1;
    book1.ISBN = "001";
    book1.Title = "Harry Potter";
    book1.Author = "J.K. Rowling";
    book1.Category = "Fantasy";
    book1.Publisher = "Bloomsbury";
    book1.Year = 1997;
    book1.Quantity = 10;
    book1.AvailableQuantity = 10;
    dbManager->AddBook(book1);
    std::cout << "[+] Added book: " << book1.Title << std::endl;

    Book book2;
    book2.BookID = 2;
    book2.ISBN = "002";
    book2.Title = "Clean Code";
    book2.Author = "Robert C. Martin";
    book2.Category = "IT";
    book2.Publisher = "Prentice Hall";
    book2.Year = 2008;
    book2.Quantity = 5;
    book2.AvailableQuantity = 5;
    dbManager->AddBook(book2);
    std::cout << "[+] Added book: " << book2.Title << std::endl;

    Book book3;
    book3.BookID = 3;
    book3.ISBN = "003";
    book3.Title = "The Alchemist";
    book3.Author = "Paulo Coelho";
    book3.Category = "Fiction";
    book3.Publisher = "HarperOne";
    book3.Year = 1988;
    book3.Quantity = 7;
    book3.AvailableQuantity = 7;
    dbManager->AddBook(book3);
    std::cout << "[+] Added book: " << book3.Title << std::endl;

    // ===== THÊM THÀNH VIÊN VỚI TÀI KHOẢN ĐĂNG NHẬP =====
    auto authManager = std::make_shared<AuthenticationManager>(dbManager);
    
    authManager->RegisterNewMember("Huy", "huy@email.com", "0977", "huy123");
    std::cout << "[+] Added member: Huy (huy@email.com)" << std::endl;

    authManager->RegisterNewMember("Hùng", "hung@email.com", "0376", "hung123");
    std::cout << "[+] Added member: Hùng (hung@email.com)" << std::endl;

    authManager->RegisterNewMember("Linh", "linh@email.com", "0473", "linh123");
    std::cout << "[+] Added member: Linh (linh@email.com)" << std::endl;


    // ===== THÊM MỘT SỐ LOAN MẪU =====
    Member huy, hung;
    dbManager->GetMemberByEmail("huy@email.com", huy);
    dbManager->GetMemberByEmail("hung@email.com", hung);
    
    Loan loan1;
    loan1.LoanID = 1001;
    loan1.MemberID = huy.MemberID;
    loan1.BookID = 1;
    loan1.BorrowDate = "2026-04-01";
    loan1.DueDate = "2026-04-15";
    loan1.ReturnDate = "";
    loan1.Status = "Borrowing";
    dbManager->AddLoan(loan1);
    std::cout << "[+] Added loan: Member " << loan1.MemberID << " borrowed book " << loan1.BookID << std::endl;

    Loan loan2;
    loan2.LoanID = 1002;
    loan2.MemberID = hung.MemberID;
    loan2.BookID = 2;
    loan2.BorrowDate = "2026-04-05";
    loan2.DueDate = "2026-04-19";
    loan2.ReturnDate = "";
    loan2.Status = "Borrowing";
    dbManager->AddLoan(loan2);
    std::cout << "[+] Added loan: Member " << loan2.MemberID << " borrowed book " << loan2.BookID << std::endl;

    // ===== THÊM PHÍ MẪU =====
    Fine unpaidFine;
    unpaidFine.FineID = 2001;
    unpaidFine.LoanID = 1001;
    unpaidFine.Amount = 50000;
    unpaidFine.Status = "Unpaid";
    dbManager->AddFine(unpaidFine);
    std::cout << "[+] Added fine: " << unpaidFine.Amount << " VND (Unpaid)" << std::endl;

    // ===== THÊM THÔNG BÁO MẪU =====
    Notification notif1;
    notif1.NotificationID = 3001;
    notif1.MemberID = huy.MemberID;
    notif1.Message = "Your book is due on 2026-04-15. Please return on time!";
    notif1.Date = "2026-04-10";
    notif1.Status = "Sent";
    dbManager->AddNotification(notif1);
    std::cout << "[+] Added notification for member " << notif1.MemberID << std::endl;

    std::cout << "\n[OK] Test data inserted successfully!\n" << std::endl;
    std::cout << "\n[*] Test Accounts for Member Login:" << std::endl;
    std::cout << "  - Email: huy@email.com, Password: huy123" << std::endl;
    std::cout << "  - Email: hung@email.com, Password: hung123" << std::endl;
    std::cout << "  - Email: linh@email.com, Password: linh123" << std::endl;
}