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
	string Statute;								//"Ordinário", "Trabalhador Estudante", "Dirigente Associativo", "Atleta de alta competição"
	static unsigned int NumberofStudents;
	float AvailableCredits;
	vector <Uc> ApprovedUcs;
	vector <Uc> CurrentUcs;
	Tutor TheTutor;

public:
	Student() {};
	~Student() {};
	Student(string AName, long TheCode, string TheStatute, vector<Uc> TheApprovedUcs, vector<Uc> TheCurrentUcs);
	Student(ifstream & In);
	string getName() const { return Name; }
	long getCode() const { return Code; }
	string getEmail() const { return Email; }
	string getStatute() const { return Statute; }
	static unsigned int getNumberofStudents() { return NumberofStudents; }
	float getAvailableCredits() const { return AvailableCredits; }
	vector<Uc> getApprovedUcs() const { return ApprovedUcs; }
	vector<Uc> getCurrentUcs() const { return CurrentUcs; }
	Tutor getTutor() const { return TheTutor; }
	bool operator < (const Student & s2);
	void setName(string TheName) { Name = TheName; }
	void setCode(long TheCode) { Code = TheCode; }
	void setTutor(string Name);
	void setTutor(Tutor Tutor);
	void setEmail(string TheEmail) { Email = TheEmail; }
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
	friend ostream& operator <<(ostream& out, const Student & TheStudent);
};
