#include "Tutor.h"

using namespace std;


unsigned int Tutor::NumberofTutors = 0;
unsigned int Tutor::MinStudents = 0;

Tutor::Tutor(ifstream & In)
{
	string line;
	getline(In, line);
	setName(line);
	NStudents = 0;
	NumberofTutors++;
}


Tutor::Tutor(string TheName)
{
	Name = TheName;
	NStudents = 0;
	NumberofTutors++;
}


void Tutor::Save(ofstream & out) const
{
	out << Name;
}


ostream& operator <<(ostream& out, const Tutor & TheTutor)
{
	out << TheTutor.Name; //"Enviar" para out (Visualizar) um Tutor na forma (Name)
	return out;
}


