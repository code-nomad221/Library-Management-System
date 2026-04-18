#include <iostream>
#include "Library.h"
#include "Student.h"
#include "Teacher.h"
using namespace std;
void showMenu()
{
    cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====" << endl;
    cout << "1.  Add Book" << endl;
    cout << "2.  Register Student" << endl;
    cout << "3.  Register Teacher" << endl;
    cout << "4.  Issue Book" << endl;
    cout << "5.  Return Book" << endl;
    cout << "6.  Search by Title" << endl;
    cout << "7.  Search by Author" << endl;
    cout << "8.  Search by Genre" << endl;
    cout << "9.  Display All Books" << endl;
    cout << "10. Check Member Fines" << endl;
    cout << "11. Join Waitlist" << endl;
    cout << "12. Display Waitlist" << endl;
    cout << "13. Save Data" << endl;
    cout << "0.  Exit" << endl;
    cout << "=====================================" << endl;
    cout << "Enter choice: "<<endl;
}
int main()
{
     library lib;
     // load saved data on startup
    lib.loadFromFiles();
    cout << flush;
    // cout << "DEBUG: Books loaded successfully" << endl;


    

    int choice;
    do
    {
        showMenu();
        cin >> choice;
        cin.ignore(); // Clear the input buffer
        if (choice == 0)
        {
            cout << "Exiting the system. Goodbye!" << endl;
        }
        else if (choice == 1)
        {
            string title, author, genre;
            int id;
            cout << "Enter Book ID: " << endl;
            cin >> id;
            cin.ignore();
            cout << "Enter Book Title: " << endl;
            getline(cin, title);
            cout << "Enter Book Author: " << endl;
            getline(cin, author);
            cout << "Enter Book Genre: " << endl;
            getline(cin, genre);
            lib.addBook(Book(title, genre, author, id, true));
        }
        else if (choice == 2)
        {
            string name, email, rollno;
            int id;
            cout << "Enter Student ID: " << endl;
            cin >> id;
            cin.ignore();
            cout << "Enter Student Name: " << endl;
            getline(cin, name);
            cout << "Enter Student Email: ";
            getline(cin, email);
            cout << "Enter Student Roll No: ";
            getline(cin, rollno);
            lib.registerMember(new Student(name, email, id, rollno)); // we use new to create a Student object on the heap and pass its pointer to registerMember. This is crucial for polymorphism — if we created a Student object on the stack and passed it by value, we'd lose the Student-specific behaviour when we store it in the library's vector of Member pointers.
            //              ->   creates a Student on the heap
            //              ->   returns its memory address (a pointer)
            //              ->   that pointer is passed to registerMember()
            //              ->   which pushes it into vector<Member*>
            //              ->   the Student stays alive for the program's lifetime
        }

        else if (choice == 3)
        {
            string email, name, dept;
            int id;
            cout << "Enter Teacher ID: " << endl;
            cin >> id;
            cin.ignore();
            cout << "Enter Teacher Name: " << endl;
            getline(cin, name);
            cout << "Enter Teacher Email: " << endl;
            getline(cin, email);
            cout << "Enter Teacher Department: " << endl;
            getline(cin, dept);
            lib.registerMember(new Teacher(name, email, id, dept));
        }
       else if (choice == 4) {
    int memberID, bookID;
    string issueDate, dueDate;

    cout << "Enter Member ID: ";
    cin >> memberID;
    cin.ignore();

    cout << "Enter Book ID: ";
    cin >> bookID;
    cin.ignore();

    cout << "Enter Issue Date (YYYY-MM-DD): ";
    getline(cin, issueDate);

    cout << "Enter Due Date (YYYY-MM-DD): ";
    getline(cin, dueDate);

    lib.issueBook(memberID, bookID, issueDate, dueDate);
}
       else if (choice == 5) {
    int memberID, bookID;
    string returnDate;

    cout << "Enter Member ID: ";
    cin >> memberID;
    cin.ignore();

    cout << "Enter Book ID: ";
    cin >> bookID;
    cin.ignore();

    cout << "Enter Return Date (YYYY-MM-DD): ";
    getline(cin, returnDate);

    lib.returnBook(memberID, bookID, returnDate);
}
        else if(choice==6){
            string title;
            cout<<"Enter title to search: "<<endl;
            getline(cin, title);
            lib.searchBook(title);
        }
        else if(choice==7){
            string author;
            cout<<"Enter author to search: "<<endl;
            getline(cin, author);
            lib.searchByAuthor(author);
        }
        else if(choice==8){
            string genre;
            cout<<"Enter genre to search: "<<endl;
            getline(cin, genre);
            lib.searchByGenre(genre);
        }
        else if(choice==9){
            lib.displayAllBooks();
        }
        else if(choice==10){
            int memberID;
            cout<<"Enter Member ID: "<<endl;
            cin>>memberID;
            lib.checkFine(memberID);
        }
        else if(choice==11){
            int memberID, bookID;
            cout<<"Enter Member ID: "<<endl;
            cin>>memberID;
            cout<<"Enter Book ID: "<<endl;
            cin>>bookID;
            lib.joinWaitlist(memberID, bookID);
   }
   else if(choice==12){
    int bookID;
    cout<<"Enter Book ID: "<<endl;
    cin>>bookID;
    lib.displayWaitlist(bookID);
   }
   else if(choice==13){
        lib.saveToFiles();
    }
    else if(choice !=0){
        cout<<"Invalid choice. Please try again."<<endl;
    }
    } while (choice != 0);
    // save everything before exiting
    lib.saveToFiles();
    cout << "Data saved. Goodbye." << endl;

    return 0;
}