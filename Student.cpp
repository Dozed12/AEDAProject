/**********************************************************************************************//**
 * \file	Student.cpp
 *
 * \brief	Implements the student class.
 **************************************************************************************************/

#include "Student.h"

using namespace std;


unsigned int Student::NumberofStudents = 0;

/**********************************************************************************************//**
 * \fn	Student::Student(ifstream & In)
 *
 * \brief	Constructor.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param [in,out]	In	The in.
 **************************************************************************************************/

Student::Student(ifstream & In)
{
	string line;
	getline(In, line);
	setName(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setCode(stol(line.substr(0, line.find(";"))));
	line = line.substr(line.find(";") + 2);
	setEmail(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setStatute(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setApprovedUcs(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setCurrentUcs(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setAvailableCredits(stof(line.substr(0, line.find(";"))));
	line = line.substr(line.find(";") + 2);
	setTutor(line);
}

/**********************************************************************************************//**
 * \fn	Student::Student(string AName, long TheCode, string TheStatute, vector<Uc> TheApprovedUcs, vector<Uc> TheCurrentUcs)
 *
 * \brief	Constructor.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param	AName		  	The name.
 * \param	TheCode		  	the code.
 * \param	TheStatute	  	the statute.
 * \param	TheApprovedUcs	the approved ucs.
 * \param	TheCurrentUcs 	the current ucs.
 **************************************************************************************************/

Student::Student(string AName, long TheCode, string TheStatute, vector<Uc> TheApprovedUcs, vector<Uc> TheCurrentUcs)
{
	Code = TheCode;
	Name = AName;
	Email = "up" + to_string(TheCode) + "@fe.up.pt";
	Statute = TheStatute;
	NumberofStudents++;
	ApprovedUcs = TheApprovedUcs;
	CurrentUcs = TheCurrentUcs;
	AvailableCredits = 75;
	for (unsigned int i = 0; i < CurrentUcs.size(); i++)
	{
		AvailableCredits = AvailableCredits - CurrentUcs[i].getECTS();
	}
}

/**********************************************************************************************//**
 * \fn	void Student::setApprovedUcs(string TheUcs)
 *
 * \brief	Sets approved ucs.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param	TheUcs	the ucs.
 **************************************************************************************************/

void Student::setApprovedUcs(string TheUcs)
{
	string line = TheUcs;
	while (line.size() > 5)
	{
		string OneUc = line.substr(0, line.find(","));
		Uc Each_Uc(OneUc);
		ApprovedUcs.push_back(Each_Uc);
		line = line.substr(line.find(",") + 2);
	}
	Uc Each_Uc(line);
	ApprovedUcs.push_back(Each_Uc);
}

/**********************************************************************************************//**
 * \fn	void Student::setCurrentUcs(string TheUcs)
 *
 * \brief	Sets current ucs.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param	TheUcs	the ucs.
 **************************************************************************************************/

void Student::setCurrentUcs(string TheUcs)
{
	string line = TheUcs;
	while (line.size() > 5)
	{
		string OneUc = line.substr(0, line.find(","));
		Uc Each_Uc(OneUc);
		CurrentUcs.push_back(Each_Uc);
		line = line.substr(line.find(",") + 2);
	}
	Uc Each_Uc(line);
	CurrentUcs.push_back(Each_Uc);
}

/**********************************************************************************************//**
 * \fn	void Student::addCurrentUc(string TheUc)
 *
 * \brief	Adds a current uc.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param	TheUc	the uc.
 **************************************************************************************************/

void Student::addCurrentUc(string TheUc)
{
	Uc NewUc(TheUc);
	CurrentUcs.push_back(NewUc);
}

/**********************************************************************************************//**
 * \fn	void Student::setTutor(Tutor Tutor)
 *
 * \brief	Sets a tutor.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param	Tutor	The tutor.
 **************************************************************************************************/

void Student::setTutor(Tutor Tutor) {
	TheTutor = Tutor;
}

/**********************************************************************************************//**
 * \fn	void Student::setTutor(string Name)
 *
 * \brief	Sets a tutor.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param	Name	The name.
 **************************************************************************************************/

void Student::setTutor(string Name) {
	TheTutor = Tutor(Name);
}

/**********************************************************************************************//**
 * \fn	string Student::showApprovedUcs()
 *
 * \brief	Shows the approved ucs.
 *
Display Approved UCs
 *
 * \return	A string.
 **************************************************************************************************/

string Student::showApprovedUcs()
{
	string FinalOutput;
	if (ApprovedUcs.size() == 0)
	{
		return FinalOutput;
	}
	else
	{
		FinalOutput = ApprovedUcs[0].getAka();
		for (unsigned int i = 1; i < ApprovedUcs.size(); i++)
		{
			FinalOutput = FinalOutput + ", " + ApprovedUcs[i].getAka();
		}
		return FinalOutput;
	}
}

/**********************************************************************************************//**
 * \fn	string Student::showCurrentUcs()
 *
 * \brief	Shows the current ucs.
 *
Display Current UCs
 *
 * \return	A string.
 **************************************************************************************************/

string Student::showCurrentUcs()
{
	string FinalOutput;
	if (CurrentUcs.size() == 0)
	{
		return FinalOutput;
	}
	FinalOutput = CurrentUcs[0].getAka();
	for (unsigned int i = 1; i < CurrentUcs.size(); i++)
	{
		FinalOutput = FinalOutput + ", " + CurrentUcs[i].getAka();
	}
	return FinalOutput;
}

/**********************************************************************************************//**
 * \fn	bool Student::operator< (const Student & s2)
 *
 * \brief	Less-than comparison operator.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param	s2	The second Student.
 *
 * \return	True if the first parameter is less than the second.
 **************************************************************************************************/

bool Student::operator < (const Student & s2)
{
	return this->Name < s2.getName();
}

//Not Used so far

/**********************************************************************************************//**
 * \fn	void Student::Save(ofstream & out) const
 *
 * \brief	Saves the given out.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param [in,out]	out	The out to save.
 **************************************************************************************************/

void Student::Save(ofstream & out) const
{
	out << Name << " ; " << Code << " ; " << Email;// << " ; " << Creditos....etc 	//"Enviar" para out (guardar) um Cliente na forma (id ; nome ; Data de adesao ; quantia gasta)
}

/**********************************************************************************************//**
 * \fn	ostream& operator<<(ostream& out, const Student & TheStudent)
 *
 * \brief	Stream insertion operator.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param [in,out]	out		  	The out.
 * \param 		  	TheStudent	the student.
 *
 * \return	The shifted result.
 **************************************************************************************************/

ostream& operator <<(ostream& out, const Student & TheStudent)
{
	out << TheStudent.Name << "; " << TheStudent.Code << "; " << TheStudent.Email << "; " << TheStudent.getStatute() << "; ";
	for (unsigned int i = 0; i < TheStudent.getApprovedUcs().size(); i++)
	{
		if (i < TheStudent.getApprovedUcs().size()-1)
		{
			out << TheStudent.getApprovedUcs()[i].getAka() << ", ";
		}
		else
		{
			out << TheStudent.getApprovedUcs()[i].getAka();
		}
	}
	out << "; ";
	for (unsigned int i = 0; i < TheStudent.getCurrentUcs().size(); i++)
	{
		if (i < TheStudent.getCurrentUcs().size() - 1)
		{
			out << TheStudent.getCurrentUcs()[i].getAka() << ", ";
		}
		else
		{
			out << TheStudent.getCurrentUcs()[i].getAka();
		}
	}
	out << "; " << TheStudent.getAvailableCredits();
	out << "; " << TheStudent.getTutor().getName();
	return out;
}