#include <string>
#include "../Library.h"
#include "../Member.h"
#include "../Book.h"
#include "../Transaction.h"
#include "../Student.h"
#include "../Teacher.h"
#include <fstream> // for file I/O
#include <sstream> // for stringstream
#include <iostream>
using namespace std;

library::library()
{
    nextTransactionid = 1;
}

void library::addBook(Book b)
{
    books.push_back(b);
    cout << "Book with id " << b.getid() << " and title " << b.getTitle() << " has been added to the library." << endl;
}

void library::registerMember(Member *m)
{
    members.push_back(m);
    cout << "Member with id " << m->getMemberid() << " and name " << m->getName() << " has been registered to the library." << endl;
}
void library::issueBook(int memberID, int bookID, string issueDate, string dueDate)
{
    // check if this member is skipping the waitlist
    if (!waitlists[bookID].empty())
    {
        if (waitlists[bookID].front() != memberID)
        {
            cout << "ERROR: Book " << bookID
                 << " has a waitlist. Member "
                 << waitlists[bookID].front()
                 << " is next in line." << endl;
            return;
        }
        // this member is first in line — remove them from queue
        waitlists[bookID].pop();
        cout << "Member " << memberID
             << " removed from waitlist for book "
             << bookID << "." << endl;
    }
    // Find the book and member in the library
    Book *found = nullptr;
    Member *foundmember = nullptr;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getid() == bookID)
        {
            found = &books[i];
            break;
        }
    }
    // Check if the book is found in the library or not if it is not found we will print an error message and return from the function without doing anything else because we cannot issue a book that it is not in the library.
    if (found == nullptr)
    {
        cout << "ERROR: Book with id" << bookID << " not found in the library." << endl;
        return;
    }
    // Check if the book is available for borrowing or not if it is not available we will print an error message and return from the function without doing anything else because we cannot issue a book that is not available for borrowing.
    if (!found->getisAvailability())
    {
        cout << "ERROR: Book with id " << bookID << " is already issued to someone else" << endl;
        return;
    }
    for (int i = 0; i < members.size(); i++)
    {
        if (members[i]->getMemberid() == memberID)
        {
            foundmember = members[i];
            break;
        }
    }

    if (foundmember == nullptr)
    {
        cout << "ERROR: Member with id " << memberID << "not found in the library." << endl;
        return;
    }
    // If the book is found and it is available for borrowing and the member is found in the library we will issue the book to the member by creating a new transaction and adding it to the transactions vector in the library and we will also mark the book as issued and we will also add the id of the book to the vector of borrowed books ids in the member class so that we can keep track of the books that the member has borrowed from the library.

    found->markAsissued();
    foundmember->borrowBook(bookID);
    // we will create a new transaction and add it to the transactions vector in the library and we will also mark the book as issued and we will also add the id of the book to the vector of borrowed books ids in the member class so that we can keep track of the books that the member has borrowed from the library.

    Transaction t(nextTransactionid++, memberID, bookID, "", issueDate, dueDate); //
    // This line creates a new `Transaction` object named `t` by calling the `Transaction` constructor with six arguments.

    // The first argument is `nextTransactionid++`, which uses post-increment: the current value of `nextTransactionid` is passed into the constructor as the transaction id, and then `nextTransactionid` is incremented afterward. The next two arguments are `memberID` and `bookID`, linking the transaction to the member and book involved.

    // The fourth argument is an empty string `""`, which is used for `returnDate` because the book is just being issued and has not been returned yet. The final two arguments are `issueDate` and `dueDate`, so the transaction stores when the book was borrowed and when it must be returned.
    transactions.push_back(t);
    cout << " Book with ID " << bookID << " has been issued to member with ID " << memberID << " successfully. " << endl;
}
void library::returnBook(int memberID, int bookID, string returnDate)
{
    Book *found = nullptr;
    Member *foundmember = nullptr;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getid() == bookID)
        {
            found = &books[i];
            break;
        }
    }
    // Check if the book is found in the library or not if it is not found we will print an error message and return from the function without doing anything else because we cannot issue a book that it is not in the library.
    if (found == nullptr)
    {
        cout << "ERROR: Book with id" << bookID << " not found in the library." << endl;
        return;
    }

    if (found->getisAvailability())
    {
        cout << "ERROR: Book is already on the shelf." << endl;

        return;
    }
    for (int i = 0; i < members.size(); i++)
    {
        if (members[i]->getMemberid() == memberID)
        {
            foundmember = members[i];
            break;
        }
    }

    if (foundmember == nullptr)
    {
        cout << "ERROR: Member with id " << memberID << "not found in the library." << endl;
        return;
    }
    Transaction *foundtransaction = nullptr;
    for (int i = 0; i < transactions.size(); i++)
    {
        if (transactions[i].getMemberid() == memberID && transactions[i].getBookid() == bookID && transactions[i].getreturnDate() == "")
        {
            foundtransaction = &transactions[i];
            break;
        }
    }
    if (foundtransaction == nullptr)
    {
        cout << "ERROR: NO active transaction found for member with id " << memberID << " and book with id " << bookID << " " << endl;
        return;
    }
    foundtransaction->recordReturn(returnDate);
    foundtransaction->calculateFine();
    found->markAsreturned();
    foundmember->returnBook(bookID);
    cout << "Book with id " << bookID << " has been returned successfully by member with id " << memberID << "." << endl;
    // notify next member on waitlist if one exists
    if (!waitlists[bookID].empty())
    {
        int nextMemberID = waitlists[bookID].front();
        cout << "--- WAITLIST NOTIFICATION ---" << endl;
        cout << "Book " << bookID << " is now available." << endl;
        cout << "Member " << nextMemberID
             << " — you are next in line. Please collect your book." << endl;
        cout << "Remaining in waitlist: "
             << waitlists[bookID].size() << endl;
    }

    float fine = foundtransaction->getFineAmount();
    if (fine > 0)
    {
        foundmember->addFine(fine);
        cout << "Fine of Rs" << fine << " applied to "
             << foundmember->getName() << "'s account." << endl;
    }
    else
    {
        cout << "Returned on time. No fine." << endl;
    }
}

void library::displayWaitlist(int bookID)
{
    if (waitlists[bookID].empty())
    {
        cout << "No waitlist for book " << bookID << "." << endl;
        return;
    }

    cout << "Waitlist for book " << bookID << ":" << endl;
    queue<int> temp = waitlists[bookID]; // copy — never modify original
    int position = 1;
    while (!temp.empty())
    {
        cout << "  " << position << ". Member " << temp.front() << endl;
        temp.pop();
        position++;
    }
}

void library::searchBook(string title)
{
    bool found = false;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getTitle().find(title) != string::npos)
        {
            cout << "Book with id " << books[i].getid()
                 << "Title: " << books[i].getTitle()
                 << "Author: " << books[i].getAuthor() << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No books found with title: " << title << endl;
    }
}
void library::searchByAuthor(string author)
{
    bool found = false;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getAuthor().find(author) != string::npos)
        {
            cout << "ID: " << books[i].getid()
                 << " | Title: " << books[i].getTitle()
                 << " | Author: " << books[i].getAuthor()
                 << " | Status: " << (books[i].getisAvailability() ? "Available" : "Issued")
                 << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No books found by author: " << author << endl;
}
void library::searchByGenre(string genre)
{
    bool found = false;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getGenre().find(genre) != string::npos)
        {
            cout << "ID: " << books[i].getid()
                 << " | Title: " << books[i].getTitle()
                 << " | Genre: " << books[i].getGenre()
                 << " | Status: " << (books[i].getisAvailability() ? "Available" : "Issued")
                 << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No books found in genre: " << genre << endl;
}

void library::displayAllBooks()
{
    if (books.empty())
    {
        cout << "No books in library." << endl;
        return;
    }

    cout << "===== ALL BOOKS =====" << endl;
    for (int i = 0; i < books.size(); i++)
    {
        cout << "[" << i + 1 << "] "
             << "ID: " << books[i].getid()
             << " | Title: " << books[i].getTitle()
             << " | Author: " << books[i].getAuthor()
             << " | Genre: " << books[i].getGenre()
             << " | Status: " << (books[i].getisAvailability() ? "Available" : "Issued")
             << endl;
    }
}
float library::checkFine(int memberID)
{
    float totalFine = 0.0;
    for (int i = 0; i < members.size(); i++)
    {
        if (members[i]->getMemberid() == memberID)
        {
            float fine = members[i]->getFines();
            cout << "Total fine for a member" << memberID << "is: Rs" << fine << endl;
            // cout << "Rs" << totalFine;
            return fine;
        }
    }
    cout << "ERROR: Member not found." << endl;
    return 0.0;
} // it just reads directly from the member's own totalFines field — simpler and always up to date.

void library::saveToFiles()
{
    ofstream Bookfile("books.txt");
    for (int i = 0; i < books.size(); i++)
    {
        Bookfile << books[i].getid() << "|"
                 << books[i].getTitle() << "|"
                 << books[i].getAuthor() << "|"
                 << books[i].getGenre() << "|"
                 << books[i].getisAvailability() << endl;
    }
    Bookfile.close();

    ofstream Memberfile("member.txt");
    for (int i = 0; i < members.size(); i++)
    {
        Memberfile << members[i]->getMemberid() << "|"
                   << members[i]->getName() << "|"
                   << members[i]->getEmail() << "|"
                   << members[i]->getMemberType() << "|"
                   << members[i]->getExtraField() << endl;
        // if members[i] points to a Student → returns rollNo
        // if members[i] points to a Teacher → returns department"\n";
    }
    Memberfile.close();

    ofstream transFile("transactions.txt");
    for (int i = 0; i < transactions.size(); i++)
    {
        transFile << transactions[i].getTransactionid() << "|"
                  << transactions[i].getMemberid() << "|"
                  << transactions[i].getBookid() << "|"
                  << transactions[i].getissueDate() << "|"
                  << transactions[i].getDueDate() << "|"
                  << transactions[i].getreturnDate() << endl;
    }
    transFile.close();

    std::cout << "All data saved." << std::endl;
}
void library::loadFromFiles()
{
    books.clear();
    members.clear();
    transactions.clear();
    nextTransactionid = 1;

    // ── load books ──────────────────────────────
    ifstream bookFile("books.txt");
    if (!bookFile.is_open())
    {
        cout << "WARNING: books.txt not found. Starting fresh." << endl;
    }
    else
    {
        string line;
        while (getline(bookFile, line))
        {
            if (line.empty())
                continue;
            vector<string> f = splitLine(line, '|');
            if (f.size() < 5)
                continue; // skip malformed lines
            int id = stoi(f[0]);
            string title = f[1];
            string author = f[2];
            string genre = f[3];
            bool isAvail = (f[4] == "1");
            books.push_back(Book(title, genre, author, id, isAvail));
        }
        bookFile.close();
        cout << "Loaded " << books.size() << " book(s)." << endl;
    }

    // ── load members ────────────────────────────
    ifstream memberFile("member.txt");
    if (!memberFile.is_open())
    {
        cout << "WARNING: member.txt not found. Starting fresh." << endl;
    }
    else
    {
        string line;
        while (getline(memberFile, line))
        {
            if (line.empty())
                continue;
            vector<string> f = splitLine(line, '|');
            if (f.size() < 4)
                continue;
            int id = stoi(f[0]);
            string name = f[1];
            string email = f[2];
            string type = f[3];
            string extra = (f.size() > 4) ? f[4] : ""; // rollNo or department
            // string extra= " ";
            if (type == "Student")
            {
                members.push_back(new Student(name, email, id, extra));
            }
            else if (type == "Teacher")
            {
                members.push_back(new Teacher(name, email, id, extra));
            }
        }
        memberFile.close();
        cout << "Loaded " << members.size() << " member(s)." << endl;
    }

    // ── load transactions ───────────────────────
    ifstream transFile("transactions.txt");
    if (!transFile.is_open())
    {
        cout << "WARNING: transactions.txt not found. Starting fresh." << endl;
    }
    else
    {
        string line;
        while (getline(transFile, line))
        {
            if (line.empty())
                continue;
            vector<string> f = splitLine(line, '|');
            if (f.size() < 5)
                continue;
            int tid = stoi(f[0]);
            int memberid = stoi(f[1]);
            int bookid = stoi(f[2]);
            string issueDate = f[3];
            string dueDate = f[4];
            string returnDate = (f.size() > 5) ? f[5] : ""; // add this line

            Transaction t(tid, memberid, bookid, returnDate, issueDate, dueDate);
            t.calculateFine();
            transactions.push_back(t);
            if (tid >= nextTransactionid)
                nextTransactionid = tid + 1;
        }
        transFile.close();
        cout << "Loaded " << transactions.size() << " transaction(s)." << endl;
    }

    cout << "All data loaded successfully." << endl;
}
void library::joinWaitlist(int memberID, int bookID)
{
    // check book exists
    bool bookExists = false;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getid() == bookID)
        {
            bookExists = true;
            break;
        }
    }
    if (!bookExists)
    {
        cout << "ERROR: Book " << bookID << " not found." << endl;
        return;
    }

    // check member exists
    bool memberExists = false;
    for (int i = 0; i < members.size(); i++)
    {
        if (members[i]->getMemberid() == memberID)
        {
            memberExists = true;
            break;
        }
    }
    if (!memberExists)
    {
        cout << "ERROR: Member " << memberID << " not found." << endl;
        return;
    }

    // check member isn't already in this waitlist
    queue<int> temp = waitlists[bookID]; // copy to scan
    while (!temp.empty())
    {
        if (temp.front() == memberID)
        {
            cout << "ERROR: Member " << memberID
                 << " is already on the waitlist for book "
                 << bookID << "." << endl;
            return;
        }
        temp.pop();
    }

    waitlists[bookID].push(memberID);
    cout << "Member " << memberID
         << " added to waitlist for book " << bookID
         << ". Position: " << waitlists[bookID].size()
         << "." << endl;
}
vector<string> library::splitLine(const string &line, char delim)
{
    vector<string> fields;
    stringstream ss(line);
    string field;
    while (getline(ss, field, delim))
    { // The third argument lets you change what character it stops at.Instead of stopping at \n, it now stops at |. Every call reads from the current cursor position up to the next |, stores whatever it found into field, and moves the cursor past that | for the next call.
        fields.push_back(field);
    }
    return fields;
}
library::~library()
{
    for (int i = 0; i < members.size(); i++)
    {
        delete members[i];
    }
}
