#pragma once
#include <string>
using namespace std;

class Book
{
private:
    string title;
    string author;
    string genre;
    int id;
    bool isAvailability;

public:
    Book(string title, string genre, string author, int id, bool isAvailabilty);

    void markAsissued();   // when isAvailability == false it means that the book is issued to someone
    void markAsreturned(); // when isAvailability ==true it means that the book is returned or avaialable on the shelfs for the users to borrow
    string getTitle() const;
    string getAuthor() const;
    string getGenre() const;
    int getid() const;
    bool getisAvailability() const;
};
