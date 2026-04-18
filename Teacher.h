#pragma once
#include <string>
using namespace std;
#include "Member.h"

class Teacher : public Member {
private:
    string department;

public:
    Teacher(string name, string email, int memberid, string dept)
        : Member(name, email, memberid) {
        department = dept;
    }

    int getBorrowLimit() const override { return 7; }
    string getMemberType() const override { return "Teacher"; }
    string getDepartment() const { return department; }
    string getExtraField() const override { return department; }

};
//Teacher gets a borrow limit of 7 and an extra department field. Same pattern as Student — override the two pure virtuals, add your own unique data.

