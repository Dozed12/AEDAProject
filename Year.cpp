#include "Year.h"
#include "Mieic.h"



Class::Class() {}


Class::Class(ifstream & In)
{
	string line;		
	getline(In, line);
	setYear(stoi(line.substr(0, line.find(";"))) - 1);
	line = line.substr(line.find(";") + 2);
	setNumber(stoi(line.substr(0, line.find(";"))) - 1);
	line = line.substr(line.find(";") + 2);
	setNstudents(stoi(line));	//setNstudents(stoi(line.substr(0, line.find(";"))))
}


Class::Class(int number, int year, int n_students, priority_queue<Student> students, vector<Uc> ucs) :
	number(number), year(year), n_students(n_students), students(students), ucs(ucs) {}


int Class::getNumber() const { return number; }


int Class::getnStudents() const { return n_students; }


int Class::getYear() const { return year; }


void Class::setYear(int year) { this->year = year; }


void Class::setNumber(int number) { this->number = number; }


void Class::setNstudents(int n_students) { this->n_students = n_students; }


void Class::addStudent(Student newStudent) {

	students.push(newStudent);

}


vector<Student> Class::getStudents() {
	vector<Student> students_aux;

	while (!students.empty()) {
		students_aux.push_back(students.top());
		students.pop();
	}

	for (unsigned int i = 0; i < students_aux.size(); i++) {
		students.push(students_aux[i]);
	}

	return students_aux;
}


void Class::setUcs(vector<Uc> ucs_year) {
	for (unsigned int i = 0; i < ucs_year.size(); i++) {
		ucs.push_back(ucs_year[i]);
	}
}


bool Class::operator<(const Class& c1) const {
	if (this->year == c1.getYear()) {
		return this->number < c1.getNumber();
	}
	return this->year < c1.getYear();
}


ostream& operator <<(ostream& out, const Class & TheClass)
{
	out << TheClass.year + 1 << "; " << TheClass.number + 1 << "; " << TheClass.n_students;
	return out;
}


void Class::removeStudent(long code) {

	vector <Student> auxStudent;

	auxStudent = this->getStudents();

	for (size_t i = 0; i < auxStudent.size(); i++)
	{
		if (auxStudent[i].getCode() == code) {
			auxStudent.erase(auxStudent.begin() + i);
			break;
		}
	}

	while (!students.empty())
	{
		students.pop();
	}

	for (size_t i = 0; i < auxStudent.size(); i++)
	{
		students.push(auxStudent[i]);
	}

}

//---------------------YEAR()


Year::Year() {}


Year::Year(int year, vector<Uc> ucs) {
	this->year = year;
	this->yearUcs = ucs;
}


void Year::addNewClass(Class a) {
	classes.push(a);
}


int Year::getYear() const { return year; }


vector<Uc> Year::getYearUcs() const { return yearUcs; }


void Year::addYearsUcs(vector<Uc> ucs) { this->yearUcs = ucs; }


void Year::printStudentsName() {

	vector<Class> classes_aux;

	while (!classes.empty()) {
		classes_aux.push_back(classes.top());
		classes.pop();
	}

	for (unsigned int i = 0; i < classes_aux.size(); i++) {
		vector<Student> students_aux = classes_aux[i].getStudents();

		cout << endl << endl << "\t\tClass " << i + 1 << endl;

		for (unsigned int j = 0; j < students_aux.size(); j++) {
			cout << "\t" << students_aux[j].getName() << "\t\t" << students_aux[j].getCode() << endl;
		}

	}
}


vector<Class> Year::getClasses() {

	vector<Class> classes_return;

	while (!classes.empty()) {
		classes_return.push_back(classes.top());
		classes.pop();
	}

	for (unsigned int i = 0; i < classes_return.size(); i++) {
		classes.push(classes_return[i]);
	}

	return classes_return;
}


bool Class::checkVacancies(vector<Uc> studentUcs) {

	for (unsigned int i = 0; i < studentUcs.size(); i++) {
		for (unsigned int j = 0; j < ucs.size(); j++) {
			if (studentUcs[i].getName() == ucs[j].getName()) {
				if (ucs[j].getVacancies() == 0)
					return false;
			}
		}
	}
	return true;
}


bool Year::operator<(const Year& y1) const {
	return this->year < y1.getYear();
}


bool Year::operator==(const Year& y1) const {
	return this->year == y1.getYear();
}


void Year::addStudentToClass(Student a) {
	Class b = classes.top();
	classes.pop();
	b.addStudent(a);
	classes.push(b);
}


void Year::RedistributeAndDelete(int Number) {
	vector<Class> auxClasses;
	while (!classes.empty())
	{
		auxClasses.push_back(classes.top());
		classes.pop();
	}

	int Index = 0;
	for (size_t i = 0; i < auxClasses.size(); i++)
	{
		if (auxClasses[i].getNumber() == Number - 1)
		{
			Index = i;
		}
	}

	vector<Student> StudentsToRedistribute;

	StudentsToRedistribute = auxClasses[Index].getStudents();

	for (size_t i = 0; i < auxClasses.size(); i++)
	{
		if (i != Index)
		{
			classes.push(auxClasses[i]);
		}
	}

	for (size_t i = 0; i < StudentsToRedistribute.size(); i++)
	{
		Class a = classes.top();
		classes.pop();
		a.addStudent(StudentsToRedistribute[i]);
		classes.push(a);
	}

}

void Year::removeStudent(long code, int classN) {

	vector<Class> auxClass;
	while (!classes.empty())
	{
		auxClass.push_back(classes.top());
		classes.pop();
	}

	for (size_t i = 0; i < auxClass.size(); i++)
	{
		if (classN == auxClass[i].getNumber())
		{
			auxClass[i].removeStudent(code);
		}
	}

	for (size_t i = 0; i < auxClass.size(); i++)
	{
		classes.push(auxClass[i]);
	}

}