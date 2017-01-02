#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "BST.h"
#include "Date.h"

using namespace std;

class Reunion {
private:
	Date reunionDate;
	long studentCode;
	vector<string> reunionTopics;
	string reunionDescription;
public:
	Reunion() { };
	Reunion(Date date, long id, vector<string> topics, string description);
	bool operator <(const Reunion& r1) const;
	bool operator ==(const Reunion&r1) const;
	Date getReunionDate() const { return reunionDate; }
	long getStudentCode() const { return studentCode; }
	vector<string> getReunionTopics() const { return reunionTopics; }		//CONST NÃO PODE SER ALTERADO
	string getReunionDescription() const { return reunionDescription; }
	void setReunionDescription(string newDescription) { this->reunionDescription = newDescription; }
};

class Tutor
{
private:
	string Name;
	BST<Reunion> tutorReunions;
	static unsigned int NumberofTutors;
	static unsigned int MinStudents;
	unsigned int NStudents;
public:
	Tutor() : tutorReunions(Reunion()) {};
	~Tutor() {};
	Tutor(string TheName);
	Tutor(ifstream & In);
	static unsigned int getMinStudents() { return MinStudents; }
	unsigned int getNStudents() { return NStudents; }
	string getName() { return Name; }
	static unsigned int getNumberofTutors() { return NumberofTutors; }
	void setName(string TheName) { Name = TheName; }
	static void setNumberofTutors(unsigned int TheNumberofTutors) { NumberofTutors = TheNumberofTutors; }
	static void setMinStudents(unsigned int TheMinStudents) { MinStudents = TheMinStudents; }
	void setNStudents(int TheNStudents) { NStudents = TheNStudents; }
	void addReunion(string tutorName);
	void removeReunion(string tutorName);
	void changeReunionDescription(string tutorName);
	void Save(ofstream & out) const;
	void showReunions(string tutorName);
	friend ostream& operator <<(ostream& out, const Tutor & TheStudent);
};