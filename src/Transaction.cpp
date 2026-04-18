#include "../Transaction.h"
#include <iostream>
#include <sstream> // for stringstream

using namespace std;

Transaction::Transaction(int t, int mid, int bid, string r, string i, string d)
{
    transactionid = t;
    memberid = mid;
    bookid = bid;
    returnDate = r;
    issueDate = i;
    dueDate = d;
    fineamount = 0.0;
}

int Transaction::getTransactionid() const
{
    return transactionid;
}
int Transaction::getMemberid() const
{
    return memberid;
}
int Transaction::getBookid() const
{
    return bookid;
}
string Transaction::getreturnDate() const
{
    return returnDate;
}
void Transaction::recordReturn(string r)
{
    returnDate = r;
}
string Transaction::getissueDate() const {
    return issueDate;
}

string Transaction::getDueDate() const {
    return dueDate;
}
const float Transaction::FINE_PER_DAY = 5.0;

int Transaction::dateToDays(const string &date)
{
    // date format expected: "YYYY-MM-DD"
    int year, month, day;
    char dash;
    stringstream ss(date);
    ss >> year >> dash >> month >> dash >> day;

    // convert to a total day count using a standard formula
    // this gives each date a unique integer we can subtract
    month = (month + 9) % 12;
    year = year - month / 10;
    return 365 * year + year / 4 - year / 100 + year / 400 + (month * 306 + 5) / 10 + day - 1;
}
void Transaction::calculateFine()
{
    if (returnDate == "")
    {
        fineamount = 0.0;
        return;
    }
    int due = dateToDays(dueDate);
    int ret = dateToDays(returnDate);
    int daysOverdue = ret - due;

    if (daysOverdue > 0)
    {
        fineamount = daysOverdue * FINE_PER_DAY;
        cout << "Book overdue by " << daysOverdue
             << " day(s). Fine: Rs" << fineamount << endl;
    }
    else
    {
        fineamount = 0.0;
        cout << "Returned on time. No fine." << endl;
    }
}

bool Transaction::Isoverdue() const
{
    if (returnDate == "")
        return false;
    return dateToDays(returnDate) > dateToDays(dueDate);
}
// The core idea is that dates are not numbers — "2024-06-20" is just text, and C++ compares text character by character from left to right. It works accidentally when dates are in YYYY-MM-DD format and stay in the same month, but the moment you cross a month or year boundary it silently gives wrong answers.
//  dateToDays() solves this by converting any date into a single integer representing the total number of days since a fixed reference point. Once both dates are plain integers, you can just subtract them:
//  returnDay - dueDay = daysOverdue
//  If the result is positive, the book is late by that many days. Multiply by FINE_PER_DAY and you have a realistic per-day fine instead of a flat fee.
//  Also notice Isoverdue() was updated to use the same dateToDays() function — previously it had its own duplicate string comparison. Now both functions use the same logic consistently.

float Transaction::getFineAmount() const
{
    return fineamount;
}

string Transaction::getsummary() const
{

    string status;

    // determine current status of this transaction
    if (returnDate == "")
    {
        status = "Not Returned Yet";
    }
    else
    {
        status = "Returned on " + returnDate;
    }

    // you can join strings together using the + operator

    // to_string() is a function that converts a number to a string so that we can concatenate it with other strings to create a summary of the transaction that includes all the details of the transaction in a readable format for the user to see when they return a book to the library and to keep track of the transactions that have been made in the library.

    // So to_string() is used to convert the non string variables like transactionid, memberid, bookid and fineamount to string so that we can concatenate them with other strings to create a summary of the transaction.
    return "Transaction ID : " + to_string(transactionid) +
           " | Member ID    : " + to_string(memberid) +
           " | Book ID      : " + to_string(bookid) +
           " | Issued On    : " + issueDate +
           " | Due Date     : " + dueDate +
           " | Status       : " + status +
           " | Fine         : " + to_string(fineamount);
}
