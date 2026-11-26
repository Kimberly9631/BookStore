#include "BookStore.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

BookStore::BookStore(){
  inventory = nullptr;
  size = 0;
}

BookStore::BookStore(const string &path_file)
{
  inventory = nullptr;
  size = 0;

  ifstream read_file;
  read_file.open(path_file);

 if(!read_file){
  cout << "File does not exist. " << endl;
  return;
 }

 string line;

 while(getline(read_file, line)){
  if(!line.empty()){
    size++;
  }
 }

 read_file.clear();
 read_file.seekg(0, ios::beg);

 inventory = new Book[size];

  for(int i=0;i<size;i++){
  read_file >> inventory[i].info.isbn 
  >> inventory[i].info.title 
  >> inventory[i].info.author 
  >> inventory[i].total_copies 
  >> inventory[i].copies_available 
  >> inventory[i].rent_price_per_day 
  >> inventory[i].sell_price;
  }

  read_file.close();
 
}

BookStore::~BookStore()
{
  delete[] inventory;
}

int BookStore::getSize() const
{
  return size;
}

Book *BookStore::getInventory() const
{
  return inventory;
}

void BookStore::setSize(int new_size)
{
  if(new_size<=0){
    return;
  }

Book *new_inventory = new Book[new_size];

int new_count;
if(new_size<size){
  new_count = new_size;
}
else{
  new_count = size;
}

for(int i=0;i<new_count;i++){
  new_inventory[i] = inventory[i];
}
delete[] inventory;

inventory = new_inventory;
size = new_size;
}

void BookStore::setInventory(const string &path_file)
{

 ifstream read_file;
 read_file.open(path_file);
 if(!read_file){
  cout << "File does not exist" << endl;
  return;
 }
 
 delete[] inventory;
 inventory = nullptr;
 size = 0;

 string line;
 while(getline(read_file, line)){
  if(!line.empty()){
    size++;
  }
 }

 read_file.clear();
 read_file.seekg(0, ios::beg);

 inventory = new Book[size];

 for (int i=0;i<size;i++){
  if(!(read_file >> inventory[i].info.isbn 
  >> inventory[i].info.title 
  >> inventory[i].info.author 
  >> inventory[i].total_copies 
  >> inventory[i].copies_available 
  >> inventory[i].rent_price_per_day 
  >> inventory[i].sell_price))
  break;
 }
 read_file.close();
}


int BookStore::findByISBN(const string &isbn)
{
  
 for(int i=0;i<size;i++){
  if(inventory[i].info.isbn == isbn){
    return i;
  }
 }
  return -1;
}

int BookStore::findByAuthor(const string &author)
{
  int books_found =0;
  for(int i=0;i<size;i++){
    if(inventory[i].info.author == author){
      printBookInfo(inventory[i].info.isbn);
      books_found++;
    }
  }
  return books_found;
}

bool BookStore::addBook(const Book &b)
{

  if(findByISBN(b.info.isbn) != -1){
    cout << "Error! A book with this ISBN already exists." << endl;
    return false;
  }
 Book *new_inventory = new Book[size +1];
 
 for(int i =0;i<size;i++){
  new_inventory[i] = inventory[i];
 }
 
 new_inventory[size] = b;

 delete[] inventory;

 inventory = new_inventory;
 size +=1;

 return true;
}

void BookStore::printBookInfo(const string &isbn)
{
      int index = findByISBN(isbn);

      const Book& b = inventory[index];
      cout << "ISBN: " << b.info.isbn
         << " | Title: " << b.info.title
         << " | Author: " << b.info.author
         << " | Total: " << b.total_copies
         << " | Available: " << b.copies_available
         << " | Rent/Day: $" << fixed << setprecision(2) << b.rent_price_per_day
         << " | Sell: $" << fixed << setprecision(2) << b.sell_price
         << "\n";
}

bool BookStore::isAvailable(const string &isbn) {
   for(int i=0;i<size;i++){
    if(inventory[i].info.isbn == isbn && inventory[i].copies_available > 0){
      return true;
   }
   }
   return false;
}

double BookStore::rentBook(const string &isbn, int num_days){

int index = findByISBN(isbn);

if(index == -1 || !isAvailable(isbn)){
  return -1;
}
if (num_days <=0){
  return -1;
}

 inventory[index].copies_available -= 1;
 double rental_cost = inventory[index].rent_price_per_day * num_days;

    return applyDiscount(rental_cost, num_days);
}

bool BookStore::returnBook(const string &isbn)
{
  int index = findByISBN(isbn);

if(index == -1){
  cout << "Error! Book does not exist" << endl;
  return false;
}

if(inventory[index].copies_available >= inventory[index].total_copies){
  cout << "Error! Cannot return beyond total book copies." << endl;
  return false;
}

else{
  inventory[index].copies_available += 1;
}

return true;
}

double BookStore::sellBook(const string& isbn, double tax_rate)
{
  int index = findByISBN(isbn);
  if(index == -1 || !isAvailable(isbn)){
    cout << "Error! Book does not exist or there are no available books to be purchased." << endl;
    return -1;
  }
 
    inventory[index].total_copies -=1;
    inventory[index].copies_available -=1;

    double sale_cost = (inventory[index].sell_price * tax_rate) + inventory[index].sell_price;

    return sale_cost;
}

double BookStore::applyDiscount(double base_cost, int num_days){

double total_rent_cost = base_cost;

  if(num_days>30){
    total_rent_cost = base_cost - (base_cost * .4);
  }
  else if(num_days>10){
    total_rent_cost = base_cost - (base_cost * .25);
  }
  return total_rent_cost;
}
