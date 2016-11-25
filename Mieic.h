#pragma once

#include "Uc.h"
#include "Student.h"
#include "Registration.h"
#include "Tutor.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;




class Mieic
{
private:
	vector <Required_Uc> ListofRequiredUcs;
	vector <Optional_Uc> ListofOptionalUcs;
	vector <Optional_Uc> ListofUPortoUcs;
	vector <Tutor> ListofTutors;
	vector <Student> ListofStudents;
	vector <Registration> ListofRegistrations;
	bool StudentsChanged = false;
	bool RegistrationsChanged = false;
	bool TutorsChanged = false;

public:
	Mieic();
	vector <Required_Uc> getListofRequiredUcs() { return ListofRequiredUcs; }
	vector <Optional_Uc> getListofOptionalUcs() { return ListofOptionalUcs; }
	vector <Optional_Uc> getListofUPortoUcs() { return ListofUPortoUcs; }
	void addTutor(string AName);
	void removeTutor(string AName);
	void distributeTutors();
	void addStudent();
	void removeStudent(long TheCode);
	unsigned short int CheckUc(string TheAkaUc, Uc &TheNewUc);
	void StudentPassesUc(long aStudent);
	void StudentDoesntPassUc(long aStudent);
	void addRegistration(Date aDate, string aUc, long aStudent);
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
	void showInfoStudent(long code);
	void showListofRegistrations();
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