#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class Tutor
{
private:
	string Name;
	static unsigned int NumberofTutors;
	static unsigned int MinStudents;
	unsigned int NStudents;
public:
	Tutor() {};
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
	void Save(ofstream & out) const;
	friend ostream& operator <<(ostream& out, const Tutor & TheStudent);
};