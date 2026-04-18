#include "../Book.h"
#include <iostream>
using namespace std;

Book::Book(string t, string g, string a, int i, bool isA)
{
    title = t;
    genre = g;
    author = a;
    id = i;
    isAvailability = true;
}
void Book::markAsissued()
{
    if (!isAvailability)
    {
        cout << "ERROR: Book is already issued to someone else." << endl;
    }
    isAvailability = false;//Now the flag actually flips to false, so the book correctly shows as unavailable after issuing.


    return;
    
}
void Book::markAsreturned(){
    if(isAvailability){
        cout<<"ERROR: Book is already avalaible on the shelfs."<<endl;
}
// else{
//     // isAvailability=false;//Sets the flag to false on return — the book becomes "issued" again instead of going back to the shelf.



// }
 isAvailability = true;
    cout << "Book '" << title << "' is back on the shelf." << endl;

}
int Book::getid() const{
return id; // it returns the id of the book and that id is in the private section of the class which is initialized in the parameterized constructor of the class so thats why we can access it here in the getid function and return it to the user when they call this function in the main function or any other function that uses this class.
}
string Book::getTitle() const{
    return title;
}
string Book::getAuthor() const{
    return author;
}
string Book::getGenre() const{
    return genre;
}
bool Book::getisAvailability() const {
    return isAvailability;
}