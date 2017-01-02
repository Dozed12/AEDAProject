#include "Registration.h"

using namespace std;


Registration::Registration(ifstream & In)
{
	string line;
	getline(In, line);
	setDate(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setStudentCode(stol(line.substr(0, line.find(";"))));
	line = line.substr(line.find(";") + 2);
	setUcAka(line);
}


Registration::Registration(Date aDate, string aUc, long aStudent)
{
	TheDate = aDate;
	UcAka = aUc;
	StudentCode = aStudent;
}


void Registration::Save(ofstream & out) const
{
	out << TheDate;
}


ostream& operator <<(ostream& out, const Registration & TheRegistration)
{
	out << TheRegistration.TheDate << "; " << TheRegistration.StudentCode << "; " << TheRegistration.UcAka;
	return out;
}