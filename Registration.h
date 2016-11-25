#pragma once

#include "Date.h"
#include "Uc.h"
#include "Student.h"

using namespace std;


class Registration
{
private:
	Date TheDate;
	string UcAka;
	long StudentCode;

public:
	Registration() {}
	Registration(ifstream & In);
	Registration(Date aDate, string aUc, long aStudent);
	Date getDate() { return TheDate; }
	string getUcAka() { return UcAka; }
	long getStudentCode() { return StudentCode; }
	void setDate(Date date) { TheDate = date; }
	void setUcAka(string TheUcAka) { UcAka = TheUcAka; }
	void setStudentCode(long TheStudentCode) { StudentCode = TheStudentCode; }
	void Save(ofstream & out) const;
	friend ostream& operator <<(ostream& out, const Registration & TheRegistration);
	
};