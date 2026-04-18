#pragma once
#include <string>
#include <vector>
using namespace std;

class Member
{
protected:
    string name;
    string email;
    int memberid;
    vector<int> borrowedbooksids; // this vector will store the ids of the books that the member has borrowed from the library and it will be used to keep track of the books that the member has borrowed and to check if the member has already borrowed a book or not when they try to borrow a new book from the library.
    float totalFines;

public:
    Member(string name, string emails, int memberid);
    void borrowBook(int bookid);              // this function will be used to add the id of the book that the member has borrowed to the vector of borrowed books ids and it will be called when the member borrows a book from the library and it will take the id of the book as a parameter and it will add it to the vector of borrowed books ids.
    virtual int getBorrowLimit() const = 0;   // pure virtual
    virtual string getMemberType() const = 0; // pure virtual
    virtual string getExtraField() const = 0; // pure virtual

    virtual ~Member() {}
    void returnBook(int bookid);
    string getName() const;
    string getEmail() const;
    int getMemberid() const;
     void addFine(float amount);
    void clearFines();
    float getFines() const;
    vector<int> getBorrowedbooksids() const;
    //totalFines lives in protected so subclasses can access it directly if needed. Three new methods: addFine() to accumulate, getFines() to read, clearFines() for when a member pays up.
};