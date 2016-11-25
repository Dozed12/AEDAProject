#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class Uc
{
	string Name;
	string Aka;
	unsigned short int Year;
	unsigned short int Semester;
	float ECTS;
public:
	Uc();
	Uc(string aka);
	string getName() { return Name; }
	string getAka() { return Aka; }
	unsigned short int getYear() { return Year; }
	unsigned short int getSemester() { return Semester; }
	float getECTS() { return ECTS; }
	void setUcEmpty();
	void setName(string NewName) { Name = NewName; }
	void setAka(string TheAka) { Aka = TheAka; }
	void setYear(unsigned short int NewYear) { Year = NewYear; }
	void setSemester(unsigned short int NewSemester) { Semester = NewSemester; }
	void setECTS(float NewECTS) { ECTS = NewECTS; }
};


class Required_Uc : public Uc
{
public:
	Required_Uc(ifstream & In);
};


class Optional_Uc : public Uc
{
private:
	unsigned short int vacancies;
public:
	Optional_Uc(ifstream & In);
	Optional_Uc(ifstream & In, unsigned short int AbsNothing);
	unsigned short int getVacancies() { return vacancies; }
	void setVacancies(unsigned short int TheVacancies) { vacancies = TheVacancies; }
};
