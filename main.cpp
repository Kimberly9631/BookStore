
#include <iostream>
#include <iomanip>
#include <limits>
#include "BookStore.h"

using namespace std;

// --------- Menu display ----------
static void clearBadInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static string readString(const string& prompt) {
    string s;
    cout << prompt;
    cin >> s;
    return s;
}

static int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        cout << "Invalid input. Try again.\n";
        clearBadInput();
    }
}

static double readDouble(const string& prompt) {
    double x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        cout << "Invalid input. Try again.\n";
        clearBadInput();
    }
}

static void printMenu() {
    cout << "\n==============================\n";
    cout << "        BOOKSTORE MENU        \n";
    cout << "==============================\n";
    cout << "1) Print inventory size\n";
    cout << "2) Search book by ISBN\n";
    cout << "3) Search books by Author\n";
    cout << "4) Print book info (by ISBN)\n";
    cout << "5) Check availability (by ISBN)\n";
    cout << "6) Rent a book (by ISBN)\n";
    cout << "7) Return a book (by ISBN)\n";
    cout << "8) Sell a book (by ISBN)\n";
    cout << "9) Add a new book\n";
    cout << "0) Exit\n";
    cout << "------------------------------\n";
}
// FREEZE CODE BEGIN
int main() {

    string path_file = "bookInventory.txt";
    BookStore store(path_file);
    cout << "Inventory loaded. Current size: " << store.getSize() << "\n";
    int choice = -1;
    while (choice != 0) {
        printMenu();
        choice = readInt("Choose an option: ");

        if (choice == 1) {
            cout << "Inventory size: " << store.getSize() << "\n";
        }
        else if (choice == 2) {
            string isbn = readString("Enter ISBN: ");
            int idx = store.findByISBN(isbn);
            if (idx == -1) cout << "Book not found.\n";
            else cout << "Book found at index: " << idx << "\n";
        }
        else if (choice == 3) {
            string author = readString("Enter Author (use underscores if needed): ");
            int found = store.findByAuthor(author);
            if (found == 0) cout << "No books found for author: " << author << "\n";
            else cout << "Total matches: " << found << "\n";
        }
        else if (choice == 4) {
        
            string isbn = readString("Enter ISBN: ");
            store.printBookInfo(isbn);
        }
        else if (choice == 5) {
            string isbn = readString("Enter ISBN: ");
            bool ok = store.isAvailable(isbn);
            cout << (ok ? "Available.\n" : "Not available.\n");
        }
        else if (choice == 6) {
            string isbn = readString("Enter ISBN: ");
            int num_days = readInt("Enter number of rental days: ");
            double cost = store.rentBook(isbn, num_days);

            if (cost < 0) {
                cout << "Rent failed (not found / unavailable / invalid input).\n";
            } else {
                cout << "Rental cost: $" << fixed << setprecision(2) << cost << "\n";
            }
        }
        else if (choice == 7) {
            string isbn = readString("Enter ISBN: ");
            bool ok = store.returnBook(isbn);
            cout << (ok ? "Return successful.\n" : "Return failed.\n");
        }
        else if (choice == 8) {
            string isbn = readString("Enter ISBN: ");
            double tax_rate = readDouble("Enter tax rate (e.g., 0.07): ");

            double total = store.sellBook(isbn, tax_rate);
            if (total < 0) {
                cout << "Sell failed (not found / no available copies).\n";
            } else {
                cout << "Final total (with tax): $" << fixed << setprecision(2) << total << "\n";
            }
        }
        else if (choice == 9) {
            Book b;

            b.info.isbn = readString("Enter ISBN: ");
            b.info.title = readString("Enter Title (no spaces, use underscores): ");
            b.info.author = readString("Enter Author (no spaces, use underscores): ");
            b.total_copies = readInt("Enter total copies: ");
            b.copies_available = readInt("Enter copies available: ");
            b.rent_price_per_day = readDouble("Enter rent price per day: ");
            b.sell_price = readDouble("Enter sell price: ");

            bool ok = store.addBook(b);
            cout << (ok ? "Book added.\n" : "Add failed (duplicate ISBN).\n");
        }
        else if (choice == 0) {
            cout << "Goodbye.\n";
        }
        else {
            cout << "Invalid option.\n";
            choice = 0;
        }
    }

    return 0;
}