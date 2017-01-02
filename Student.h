#pragma once

#include "Uc.h"
#include "Tutor.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


class Student
{
private:
	long Code;
	string Name;
	string Email;
	string Adress;
	string Contact;
	string Statute;								//"Ordinário", "Trabalhador Estudante", "Dirigente Associativo", "Atleta de alta competição"
	static unsigned int NumberofStudents;
	float AvailableCredits;
	vector <Uc> ApprovedUcs;
	vector <Uc> CurrentUcs;
	Tutor TheTutor;
	int Year;
	int YearClass;
	unsigned short int SomeKindofBool;			// 0 -> Estudante Normal;  1 -> Estudante Terminou o Curso;  2 -> Estudante Interrompeu o Curso

public:
	Student() {};
	~Student() {};
	Student(string AName, long TheCode, int Year, int YearClass, string TheStatute, string TheAdress, string TheContact, vector<Uc> TheApprovedUcs, vector<Uc> TheCurrentUcs, unsigned short int TheKindofBool);
	Student(ifstream & In);
	string getName() const { return Name; }
	long getCode() const { return Code; }
	string getEmail() const { return Email; }
	string getAdress() const { return Adress; }
	string getContact() const { return Contact; }
	string getStatute() const { return Statute; }
	static unsigned int getNumberofStudents() { return NumberofStudents; }
	float getAvailableCredits() const { return AvailableCredits; }
	vector<Uc> getApprovedUcs() const { return ApprovedUcs; }
	vector<Uc> getCurrentUcs() const { return CurrentUcs; }
	Tutor getTutor() const { return TheTutor; }
	int getYear() const { return Year; }
	int getYearClass() const { return YearClass; }
	unsigned short int getSomeKindofBool() const { return SomeKindofBool; }
	bool operator < (const Student & s2) const;
	void setYear(int year) { Year = year; }
	void setYearClass(int Class) { YearClass = Class; }
	void setName(string TheName) { Name = TheName; }
	void setCode(long TheCode) { Code = TheCode; }
	void setTutor(string Name);
	void setTutor(Tutor Tutor);
	void setSomeKindofBool (unsigned short int TheSomewhatBool) { SomeKindofBool = TheSomewhatBool; }
	void setEmail(string TheEmail) { Email = TheEmail; }
	void setAdress(string TheAdress) { Adress = TheAdress; }
	void setContact(string TheContact) { Contact = TheContact; }
	void setStatute(string AStatute) { Statute = AStatute; }
	void setAvailableCredits(float TheAvailableCredits) { AvailableCredits = TheAvailableCredits; }
	void setApprovedUcs(string TheUcs);				// *** Esta funcao mete no vetor Approved Ucs as Ucs do estudante, mas os objetos da class Uc no vetor apenas terao o atributo Aka (nao vi maneira de fazer melhor)
	void setCurrentUcs(string TheUcs);
	void setApprovedUcs(vector <Uc> TheApprovedUcs) { ApprovedUcs = TheApprovedUcs; }
	void setCurrentUcs(vector <Uc> TheCurrentUcs) { CurrentUcs = TheCurrentUcs; }
	void addCurrentUc(string TheUc);
	string showApprovedUcs();
	string showCurrentUcs();
	void Save(ofstream & out) const;
	friend bool operator==(const Student &Student1, const Student &Student2);
	friend ostream& operator <<(ostream& out, const Student & TheStudent);
};
