#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <string>
using namespace std;

struct BookInfo {
  string isbn;
  string title;
  string author;
  string new_book;
  
};

struct Book {
  BookInfo info{};
  int total_copies;
  int copies_available;
  double rent_price_per_day;
  double sell_price;
};

class BookStore {
      private:
      Book *inventory;
      int size;

      public:
    BookStore();
    BookStore(const string &path_file);
    ~BookStore();


    int getSize() const;
    Book* getInventory() const;
    void setSize(int new_size);
    void setInventory(const string &path_file);


    int findByISBN(const string &isbn);
    int findByAuthor(const string &author); // Prints matches; returns count found
    bool addBook(const Book &b);
    void printBookInfo(const string &isbn);
    bool isAvailable(const string &isbn);
    double rentBook(const string &isbn, int num_days);
    bool returnBook(const string &isbn);
    double sellBook(const string &isbn, double tax_rate);
    double applyDiscount(double base_cost, int num_days);
};

#endif