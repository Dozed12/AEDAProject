#pragma once

#include <iostream>
#include <queue>

#include "Student.h"
#include "Uc.h"


using namespace std;

class Class {
private:
	int year;
	int number;
	int n_students;
	priority_queue<Student> students;
	vector<Uc> ucs;
public:
	Class();
	Class(ifstream & In);
	Class(int number, int year, int n_students, priority_queue<Student> students, vector<Uc> ucs);
	int getNumber() const;
	int getnStudents() const;
	int getYear() const;
	vector<Student> getStudents();
	void setYear(int year);
	void setNumber(int number);
	void setNstudents(int n_students);
	void setUcs(vector<Uc>);
	bool checkVacancies(vector<Uc> studentUcs);
	void addStudent(Student newStudent);
	void removeStudent(long code);
	bool operator <(const Class& c1) const;
	friend ostream& operator <<(ostream& out, const Class & TheClass);
};

struct ClassCompare {
	bool operator() (Class &a, Class &b) {
		if (a.getnStudents() - a.getStudents().size() < b.getnStudents() - b.getStudents().size())
		{
			return true;
		}
		return false;
	}
};

class Year {
private:
	int year;
	vector<Uc> yearUcs;
	priority_queue<Class, vector<Class>, ClassCompare> classes;
public:
	Year();
	Year(int year, vector<Uc> ucs);
	int getYear() const;
	void addNewClass(Class a);
	void addStudentToClass(Student a);
	void RedistributeAndDelete(int Number);
	void removeStudent(long code, int classN);
	vector<Uc> getYearUcs() const;
	void addYearsUcs(vector<Uc> ucs);
	vector<Class> getClasses();
	priority_queue<Class, vector<Class>, ClassCompare> getClassesRaw() { return classes; }
	void printStudentsName();
	bool operator<(const Year& y1) const;
	bool operator==(const Year& y1) const;
};

