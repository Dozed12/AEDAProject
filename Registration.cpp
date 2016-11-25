/**********************************************************************************************//**
 * \file	Registration.cpp
 *
 * \brief	Implements the registration class.
 **************************************************************************************************/

#include "Registration.h"

using namespace std;

/**********************************************************************************************//**
 * \fn	Registration::Registration(ifstream & In)
 *
 * \brief	Constructor.
 *
 *
 * \param [in,out]	In	The in.
 **************************************************************************************************/

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

/**********************************************************************************************//**
 * \fn	Registration::Registration(Date aDate, string aUc, long aStudent)
 *
 * \brief	Constructor.
 *
 *
 * \param	aDate   	The date.
 * \param	aUc			The uc.
 * \param	aStudent	The student.
 **************************************************************************************************/

Registration::Registration(Date aDate, string aUc, long aStudent)
{
	TheDate = aDate;
	UcAka = aUc;
	StudentCode = aStudent;
}

/**********************************************************************************************//**
 * \fn	void Registration::Save(ofstream & out) const
 *
 * \brief	Saves the given out.
 *
 *
 * \param [in,out]	out	The out to save.
 **************************************************************************************************/

void Registration::Save(ofstream & out) const
{
	out << TheDate;
}

/**********************************************************************************************//**
 * \fn	ostream& operator<<(ostream& out, const Registration & TheRegistration)
 *
 * \brief	Stream insertion operator.
 *
 *
 * \param [in,out]	out			   	The out.
 * \param 		  	TheRegistration	the registration.
 *
 * \return	The shifted result.
 **************************************************************************************************/

ostream& operator <<(ostream& out, const Registration & TheRegistration)
{
	out << TheRegistration.TheDate << "; " << TheRegistration.StudentCode << "; " << TheRegistration.UcAka;
	return out;
}