#pragma once

#include "Uc.h"
#include "Student.h"
#include "Registration.h"
#include "Tutor.h"
#include "BST.h"
#include "Year.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>	
#include <unordered_set>

using namespace std;


struct StudentsHash
{
	int operator() (const Student & TheStudent) const
	{
		int Final_Key = 0;
		unsigned long TheCode =TheStudent.getCode();
		string TheCodeasString = to_string(TheCode);
		for (unsigned int i = 0; i < TheCodeasString.size(); i++)
		{
			Final_Key = 37 * Final_Key + TheCodeasString[i];
		}
		return Final_Key;
	}

	bool operator() (const Student & TheStudent1, const Student & TheStudent2) const
	{
		if (TheStudent1.getCode() == TheStudent2.getCode())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

typedef tr1::unordered_set<Student, StudentsHash, StudentsHash> StudentsHashTable;
typedef tr1::unordered_set<Student, StudentsHash, StudentsHash>::iterator StudentsHashTableIterator;
typedef tr1::unordered_set<Student, StudentsHash, StudentsHash>::const_iterator StudentsHashTableConstIterator;


class Mieic
{
private:
	vector <Year> mieicYears;
	vector <Required_Uc> ListofRequiredUcs;
	vector <Optional_Uc> ListofOptionalUcs;
	vector <Optional_Uc> ListofUPortoUcs;
	vector <Tutor> ListofTutors;
	vector <Student> ListofStudents;
	vector <Registration> ListofRegistrations;
	vector <Class> ListofClasses;
	StudentsHashTable HashofStudents;
	bool StudentsChanged = false;
	bool RegistrationsChanged = false;
	bool TutorsChanged = false;
	bool ClassesChanged = false;

public:
	Mieic();
	~Mieic() {};
	vector <Required_Uc> getListofRequiredUcs() { return ListofRequiredUcs; }
	vector <Optional_Uc> getListofOptionalUcs() { return ListofOptionalUcs; }
	vector <Optional_Uc> getListofUPortoUcs() { return ListofUPortoUcs; }
	vector <Student> getListofStudents() { return ListofStudents; }
	void addTutor(string AName);
	void removeTutor();
	void addTutorReunion();
	void removeTutorReunion();
	void changeTutorReunion();
	void distributeTutors();
	void addStudent();
	void changeStudentFromList(long TheCode);
	void changeStudentsFromHash(long TheCode);
	void removeStudent(long TheCode);
	void addClass();
	void removeClass();
	unsigned short int CheckUc(string TheAkaUc, Uc &TheNewUc);
	void StudentPassesUc(long aStudent);
	void StudentDoesntPassUc(long aStudent);
	void StudentInterruptsCourse(long aStudent);
	void addRegistration(Date aDate, string aUc, long aStudent);
	void addHashRegistration(Date aDate, string aUc, long aStudent);
	unsigned int GetTheYear(string TheAka);
	void showListofRUcs();
	void showListofOUcs();
	void showListofUPortoUcs();
	void showListAllUcs();
	void showListofFirstYearUcs();
	void showListofSecondYearUcs();
	void showListofThirdYearUcs();
	void showListofFourthYearUcs();
	void showListofFifthYearUcs();
	void showListofFirstSemesterUcs();
	void showListofSecondSemesterUcs();
	void showSearchUC(string AKA);
	void showListofTutors();
	void showListofStudents();
	void showListofIorTStudents();
	void showInfoStudent(long code);
	void showListofRegistrations();
	void showListofClasses();
	void showFirstYearClassesStudents();
	void showTutorReunions();

	void SaveChanges() const;
};

class EstudanteNaoExistente {
public:
	long code;
	EstudanteNaoExistente() {}
	EstudanteNaoExistente(long code) { this->code = code; };
	long getCode() const { return code; }
};

class TutorNaoExistente {
public:
	string nome;
	TutorNaoExistente(){}
	TutorNaoExistente(string nome) { this->nome = nome; }
};

class UcNaoExistente {
public:
	UcNaoExistente() {}
};