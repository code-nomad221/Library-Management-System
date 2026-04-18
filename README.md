A console-based Library Management System built in C++ using Object-Oriented Programming principles. It supports book management, member registration, book issuing and returning, fine calculation, waitlist management, and persistent file-based storage.

--------------------------------------------------------------------------------------------------------------------------

**Features**

- Add books to the library with ID, title, author, and genre
- Register students and teachers as library members
- Issue books to members with duplicate and waitlist checks
- Return books and automatically calculate overdue fines
- Join and display a waitlist for unavailable books
- Search books by title, author, or genre
- Display all books with their availability status
- Check outstanding fines for any member
- Save all data (books, members, transactions) to .txt files
- Reload all saved data automatically on startup

--------------------------------------------------------------------------------------------------------------------------

**Project Structure**

```
lib-mang-sys/
│
├── src/
│   ├── Main.cpp          # Entry point
│   ├── Library.cpp       # Core logic
│   ├── Book.cpp          # Book class
│   ├── Member.cpp        # Member class
│   └── Transaction.cpp   # Transaction logic
│
├── Book.h
├── Member.h
├── Student.h
├── Teacher.h
├── Library.h
├── Transaction.h
│
├── books.txt
├── member.txt
└── transactions.txt
```
--------------------------------------------------------------------------------------------------------------------------

**OOP Concepts Used**

Inheritance
- Student and Teacher both inherit from the abstract base class Member. They share common fields like name, email, and member ID through the base class, while each adds its own unique field (rollNo for students, department for teachers).
Polymorphism
- The library class stores all members as vector<Member*> — a vector of base class pointers. When methods like getMemberType() or getExtraField() are called, C++ automatically dispatches to the correct Student or Teacher version at runtime. This is runtime polymorphism through virtual functions.
Encapsulation
- Every class exposes only what it needs to through public getter and setter methods. Internal data fields (title, isAvailable, fines, etc.) are all private, preventing direct external modification.
Abstraction
- Member is an abstract base class. It defines the interface that all member types must follow, without exposing the implementation details of any specific type.

--------------------------------------------------------------------------------------------------------------------------

**How to Compile & Run**
Prerequisites
- g++ compiler (MinGW on Windows, g++ on Linux/Mac)
- C++11 or later
**Compile**
g++ -I. src/Main.cpp src/Library.cpp src/Member.cpp src/Transaction.cpp src/Book.cpp -o lms

**Run**
# Windows
.\lms.exe

# Linux / Mac
./lms
The program will automatically load any previously saved data from books.txt, member.txt, and transactions.txt if they exist.

--------------------------------------------------------------------------------------------------------------------------

**Usage Walkthrough**
Below is an example session showing the core flow from start to finish.

- Add Book
Enter choice: 1
Enter Book ID: 101
Enter Book Title: Clean Code
Enter Book Author: Robert C. Martin
Enter Book Genre: Programming
 **Book with id 101 and title Clean Code has been added to the library.**

- Register a student
Enter choice: 2
Enter Student ID: 1
Enter Student Name: Ali Hassan
Enter Student Email: ali@uni.edu
Enter Student Roll No: CS-2021-01
**Member with id 1 and name Ali Hassan has been registered to the library.**

- Issue the book
Enter choice: 4
Enter Member ID: 101
Enter Book ID: 1
Enter Issue Date (YYYY-MM-DD): 2024-06-01
Enter Due Date (YYYY-MM-DD): 2024-06-15
**Book 1 issued to member 101.**

- Return the book with a fine
Enter choice: 5
Enter Member ID: 101
Enter Book ID: 1
Enter Return Date (YYYY-MM-DD): 2024-06-20
**Book overdue by 5 day(s). Fine: Rs25**

- Reload on next startup
Loaded 1 book(s).
Loaded 1 member(s).
Loaded 2 transaction(s).
All data loaded successfully.

--------------------------------------------------------------------------------------------------------------------------
**Screenshots**
- Main menu

![image alt](https://github.com/code-nomad221/Library-Management-System/blob/da01295a95e27e2453c634b34386fc5ddf3011cd/main%20menu.png)

- Issuing a book
  ![image alt](https://github.com/code-nomad221/Library-Management-System/blob/fce6098bf91da33673facf3ee212feb3134ddb96/issuing-book.png)




- Returning a book with a fine


- Waitlist flow


- Saved data files


- Data reload on startup

--------------------------------------------------------------------------------------------------------------------------

Challenges & How I Solved Them

- Transactions not loading on startup
Symptom: Every restart printed Loaded 0 transaction(s) even though transactions.txt had data in it.
Root cause: When a book has not been returned yet, returnDate is empty, so the saved line ends with a trailing | and nothing after it. The stringstream split did not reliably produce a sixth empty token for that trailing delimiter, so f.size() came back as 5. The guard if (f.size() < 6) continue; then silently skipped every unreturned transaction.

// Before — skips all unreturned transactions
if (f.size() < 6) continue;

// After — handles missing returnDate safely
if (f.size() < 5) continue;
string returnDate = (f.size() > 5) ? f[5] : "";

- Member type and extra field getting glued together in the save file
Symptom: Members were written to member.txt as StudentCS101 instead of Student|CS101, causing them to be unrecognised and silently skipped on reload.
Root cause: A | delimiter was missing between getMemberType() and getExtraField() in saveToFiles(). The two values were concatenated directly.

// Before — no separator between type and extra field
<< members[i]->getMemberType() <<
members[i]->getExtraField() << endl;

// After — pipe added between the two fields
<< members[i]->getMemberType() << "|"
<< members[i]->getExtraField() << endl;

- checkFine() using the wrong vector index
Symptom: Fine checks either returned the wrong member's data or crashed with an out-of-bounds error.
Root cause: The loop was iterating over transactions with index i, but using i to index into members — two completely separate vectors. 

// Before — i is a transaction index, not a member index
for (int i = 0; i < transactions.size(); i++) {
    if (transactions[i].getMemberid() == memberID) {
        float fine = members[i]->getFines(); // wrong member!
        cout << totalFine;
    }
}

// After — search members directly
for (int i = 0; i < members.size(); i++) {
    if (members[i]->getMemberid() == memberID) {
        float fine = members[i]->getFines();
        cout << "Total fine: Rs" << fine << endl;
        return totalfine;
    }
}

--------------------------------------------------------------------------------------------------------------------------

What I Learned

- How stringstream with getline handles (or fails to handle) trailing delimiters — boundary conditions in parsing are easy to get wrong and produce silent failures with no error message.

- Why designing a custom file format (like pipe-delimited text) requires strict discipline — one missing character breaks the entire load cycle.

- The importance of keeping loop variables and collection indices clearly separated — using the same index i across two unrelated vectors is a reliable way to introduce hard-to-spot bugs.

- How polymorphism through base class pointers (vector<Member*>) works in practice, and why heap allocation with new is necessary to preserve derived class behaviour.

- The habit of always calling cin.ignore() after cin >> when getline() will be called next — a C++ input buffering rule that does not announce itself when broken.

--------------------------------------------------------------------------------------------------------------------------

Future Improvements

 - Add a proper date library (e.g. <chrono>) to calculate fines based on the real system date instead of hardcoded strings.
 - Replace .txt file storage with an SQLite database for more robust persistence.
 - Add a graphical user interface using Qt or a web-based front end.
 - Implement a fine payment system that clears a member's balance.
 - Add member login with password authentication.
 - Support exporting reports (issued books, overdue books, total fines) to CSV.




