#include "Uc.h"

using namespace std;


Uc::Uc()
{
	Name = "";
	Aka = "";
	Year = 0;
	ECTS = 0;
	Semester = 0;
	vacancies = 2; //30;
}


void Uc::setUcEmpty()
{
	Name = "";
	Aka = "";
	Year = 0;
	ECTS = 0;
	Semester = 0;
	vacancies = 2; //30;
}


Uc::Uc(string aka)
{
	Name = "";
	setAka(aka);
	Year = 0;
	ECTS = 0;
	Semester = 0;
	vacancies = 2; //30;
}


Required_Uc::Required_Uc(ifstream & In)
{
	string line;
	getline(In, line);
	setName(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setAka(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setYear(stoi(line.substr(0, line.find(","))));
	line = line.substr(line.find(",") + 2);
	setSemester(stoi(line.substr(0, line.find(","))));
	line = line.substr(line.find(",") + 2);
	setECTS(stof(line));
}


Optional_Uc::Optional_Uc(ifstream & In)
{
	string line;
	getline(In, line);
	setName(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setAka(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setYear(stoi(line.substr(0, line.find(","))));
	line = line.substr(line.find(",") + 2);
	setSemester(stoi(line.substr(0, line.find(","))));
	line = line.substr(line.find(",") + 2);
	setECTS(stof(line.substr(0, line.find(";"))));
	line = line.substr(line.find(";") + 2);
	setVacancies(stoi(line));
}


Optional_Uc::Optional_Uc(ifstream & In, unsigned short int AbsNothing)
{
	string line;
	getline(In, line);
	setName(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setAka(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setYear(stoi(line.substr(0, line.find(","))));
	line = line.substr(line.find(",") + 2);
	setSemester(stoi(line.substr(0, line.find(","))));
	line = line.substr(line.find(",") + 2);
	setECTS(stof(line));
}