#pragma once
#include <string>
using namespace std;

class Transaction
{
private:
    int transactionid;
    int memberid;
    int bookid;
    string returnDate;
    string issueDate;
    string dueDate;
    float fineamount;
    static const float FINE_PER_DAY;           // rate declared here
    static int dateToDays(const string &date); // helper declared here
    // dateToDays() is a static helper — it belongs to the class but doesn't need any object's data. FINE_PER_DAY is static const so the rate is defined once and shared across all transactions.

public:
    Transaction(int t, int mid, int bid, string r, string i, string d);
    int getTransactionid() const;
    int getMemberid() const;
    int getBookid() const;
    string getreturnDate() const;
    string getissueDate() const;
    string getDueDate() const;
    void recordReturn(string returnDate);
    void calculateFine();   // compares duedate vs returndate
    bool Isoverdue() const; // compares duedate vs returndate and return true if the book is overdue false if not.
    float getFineAmount() const;

    string getsummary() const; // this function will return a string that contains the summary of the transaction which includes the transaction id, member id, book id, issue date, due date, return date and fine amount if there is any fine amount to be paid by the member. this function will be called when the member returns a book to the library and it will be used to generate a summary of the transaction for the member to see and to keep track of the transactions that have been made in the library.
};