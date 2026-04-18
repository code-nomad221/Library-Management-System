#include <iostream>
#include "../Member.h"
using namespace std;
Member::Member(string n, string e, int m)
{
    name = n;
    email = e;
    memberid = m;
        totalFines = 0.0;  // always start at zero

};

void Member::borrowBook(int bookid)
{
    if ((int)borrowedbooksids.size() >= getBorrowLimit())
    //The reason (int) cast is there before borrowedbooksids.size() is because size() returns an unsigned int in C++. Comparing an unsigned int with a regular int from getBorrowLimit() can cause subtle bugs — the cast keeps both sides the same type.
    {
        cout << "ERROR: Borrow limit of " << getBorrowLimit()
             << " reached for " << getMemberType() << "." << endl;
        return;
    } // getBorrowLimit() is called polymorphically — when a Student calls this, it returns 3. When a Teacher calls it, it returns 7. Same function, different behaviour depending on the object type.

    // The limit check is the very first thing that runs — before even checking for duplicates. So the order of checks is:

    // 1.Has this member hit their limit? → stop if yes
    // 2.Have they already borrowed this exact book? → stop if yes
    // 3.All clear → add the book

    for (int val : borrowedbooksids)
    {
        if (val == bookid)
        {
            cout << "ERROR: You have already borrowed this book." << endl;

            return;
        }
    }
    borrowedbooksids.push_back(bookid);
    cout << "Book " << bookid << " added to your borrowed list." << endl;
}

void Member::returnBook(int bookid)
{

    for (auto i = borrowedbooksids.begin(); i != borrowedbooksids.end(); i++)
    {
        if (*i == bookid)
        {
            borrowedbooksids.erase(i);
            cout << "Book with id " << bookid << "has been returned successfully." << endl;
            return;
        }
    };
    cout << "ERROR: This member did not  borrow this book." << endl;
}
string Member::getName() const
{
    return name;
}

string Member::getEmail() const
{
    return email;
}
int Member::getMemberid() const
{
    return memberid;
}
void Member::addFine(float amount){
     if (amount < 0) {
        cout << "ERROR: Fine amount cannot be negative." << endl;
        return;
    }
    totalFines += amount;
    cout << "Fine of Rs" << amount << " added to "
         << name << ". Total: Rs" << totalFines << endl;
}
float Member::getFines() const {
    return totalFines;
}
void Member::clearFines(){
    totalFines=0.0;
    cout<<"All fines cleared for "<<name<<". Total fines now: Rs" << totalFines <<endl;
}
//The negative check in addFine() guards against accidental bad calls. clearFines() is useful when a member pays their dues at the front desk.
vector<int> Member::getBorrowedbooksids() const
{
    return borrowedbooksids;
}