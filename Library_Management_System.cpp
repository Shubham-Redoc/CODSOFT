#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable;

    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isAvailable(true) {}
};

struct Borrower {
    string name;
    string borrowerID;

    Borrower(string n, string id) : name(n), borrowerID(id) {}
};

struct Transaction {
    string borrowerID;
    string ISBN;
    time_t checkoutDate;
    time_t returnDate;
    bool isReturned;

    Transaction(string bID, string isbn) : borrowerID(bID), ISBN(isbn), isReturned(false) {
        checkoutDate = time(0);
    }
};

vector<Book> books;
vector<Borrower> borrowers;
vector<Transaction> transactions;

void addBook();
void searchBooks();
void checkoutBook();
void returnBook();
void calculateFine(const Transaction& transaction);
void addBorrower();
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();  // Ignore newline character

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBooks();
                break;
            case 3:
                addBorrower();
                break;
            case 4:
                checkoutBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                cout << "Exiting Library Management System.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

void displayMenu() {
    cout << "\nLibrary Management System\n";
    cout << "1. Add Book\n";
    cout << "2. Search Books\n";
    cout << "3. Add Borrower\n";
    cout << "4. Checkout Book\n";
    cout << "5. Return Book\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

void addBook() {
    string title, author, ISBN;
    cout << "Enter book title: ";
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter book ISBN: ";
    getline(cin, ISBN);
    books.push_back(Book(title, author, ISBN));
    cout << "Book added successfully.\n";
}

void searchBooks() {
    int searchChoice;
    string searchTerm;

    cout << "\nSearch by:\n";
    cout << "1. Title\n";
    cout << "2. Author\n";
    cout << "3. ISBN\n";
    cout << "Enter your choice: ";
    cin >> searchChoice;
    cin.ignore();

    cout << "Enter search term: ";
    getline(cin, searchTerm);

    for (const auto& book : books) {
        bool found = false;
        if ((searchChoice == 1 && book.title == searchTerm) ||
            (searchChoice == 2 && book.author == searchTerm) ||
            (searchChoice == 3 && book.ISBN == searchTerm)) {
            cout << "Title: " << book.title << ", Author: " << book.author
                 << ", ISBN: " << book.ISBN
                 << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
            found = true;
        }
        if (!found) {
            cout << "No books found for the search term.\n";
        }
    }
}

void addBorrower() {
    string name, borrowerID;
    cout << "Enter borrower name: ";
    getline(cin, name);
    cout << "Enter borrower ID: ";
    getline(cin, borrowerID);
    borrowers.push_back(Borrower(name, borrowerID));
    cout << "Borrower added successfully.\n";
}

void checkoutBook() {
    string borrowerID, ISBN;
    cout << "Enter borrower ID: ";
    getline(cin, borrowerID);
    cout << "Enter book ISBN: ";
    getline(cin, ISBN);

    for (auto& book : books) {
        if (book.ISBN == ISBN && book.isAvailable) {
            book.isAvailable = false;
            transactions.push_back(Transaction(borrowerID, ISBN));
            cout << "Book checked out successfully.\n";
            return;
        }
    }
    cout << "Book not available or ISBN not found.\n";
}

void returnBook() {
    string borrowerID, ISBN;
    cout << "Enter borrower ID: ";
    getline(cin, borrowerID);
    cout << "Enter book ISBN: ";
    getline(cin, ISBN);

    for (auto& transaction : transactions) {
        if (transaction.borrowerID == borrowerID && transaction.ISBN == ISBN && !transaction.isReturned) {
            transaction.isReturned = true;
            transaction.returnDate = time(0);

            for (auto& book : books) {
                if (book.ISBN == ISBN) {
                    book.isAvailable = true;
                    break;
                }
            }
            calculateFine(transaction);
            cout << "Book returned successfully.\n";
            return;
        }
    }
    cout << "No matching transaction found.\n";
}

void calculateFine(const Transaction& transaction) {
    const double finePerDay = 1.0;  // Fine per day in some currency
    const int maxLoanDays = 14;     // Maximum days without fine
    time_t now = time(0);
    double daysOverdue = difftime(now, transaction.checkoutDate) / (60 * 60 * 24) - maxLoanDays;

    if (daysOverdue > 0) {
        cout << "The book is overdue by " << daysOverdue << " days.\n";
        cout << "Total fine: " << finePerDay * daysOverdue << " units.\n";
    } else {
        cout << "No fine. The book was returned on time.\n";
    }
}
