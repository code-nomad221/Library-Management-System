#pragma once
#include <string>
#include "Member.h"
#include "Book.h"
#include "Transaction.h"
#include <queue>
#include <map>
#include <vector>
using namespace std;

class library
{
private:
    vector<Book> books;
    vector<Member *> members; // pointers — key for polymorphism
    vector<Transaction> transactions;
    int nextTransactionid;          // this variable will be used to keep track of the next transaction id that will be assigned to a new transaction when a member borrows a book from the library and it will be incremented by 1 every time a new transaction is created in the library so that we can ensure that each transaction has a unique id and to keep track of the transactions that have been made in the library.
    map<int, queue<int>> waitlists; // bookID → queue of memberIDs
    vector<string> splitLine(const string &line, char delim);
    //  splitLine() is a private helper that breaks one line into fields — used by all three loaders so we don't repeat the same parsing logic three times.

public:
    library();
    void addBook(Book b);
    void registerMember(Member *m); // takes a pointer now
    void issueBook(int memberID, int bookID, string issueDate, string dueDate);
    // creates a Transaction, adds it to transactions vector, marks book as issued, adds bookID to member's borrowed list.
    void returnBook(int memberID, int bookID, string returnDate); // updates Transaction + calculates fine
    void searchBook(string title);
    void searchByAuthor(string author);
    void searchByGenre(string genre);
    void displayAllBooks();
    float checkFine(int memberID);
    void saveToFiles();   // calls File I/O
    void loadFromFiles(); // calls File I/O
    void joinWaitlist(int memberID, int bookID);
    void displayWaitlist(int bookID);
    // map<int, queue<int>> is the key data structure — each book gets its own independent queue of waiting members. bookID is the key, the queue of memberIDs is the value.
    ~library(); // destructor to clean up Member pointers
    // Must use Member* pointers (not Member objects) — this is what enables polymorphism. Without pointers, C++ slices off the subclass part and you lose the override behaviour entirely.
};