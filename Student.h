#pragma once
#include <string>
using namespace std;
#include "Member.h"

class Student : public Member {
private:
    string studentRollNo;

public:
    Student(string name, string email, int memberid, string rollNo)
        : Member(name, email, memberid) {//The : Member(name, email, memberid) part is called an initializer list. Because Student doesn't own name, email, and memberid — Member does — Student can't set them directly. It has to hand them up to Member's constructor to initialize. Think of it as Student saying "here, you handle your own fields, I'll handle mine." Then studentRollNo = rollNo sets Student's own field normally.
        studentRollNo = rollNo;
    }

    int getBorrowLimit() const override { return 3; }
    string getMemberType() const override { return "Student"; }
    string getRollNo() const { return studentRollNo; }
    string getExtraField() const override { return studentRollNo; }

};
//Student gets a borrow limit of 3. The : Member(name, email, memberid) part calls the parent constructor — this is how you pass data up to the base class.

