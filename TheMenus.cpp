/**********************************************************************************************//**
 * \file	TheMenus.cpp
 *
 * \brief	Implements the menus class.
 **************************************************************************************************/

#include "TheMenus.h"
#include "Tools.h"
#include "Date.h"

/**********************************************************************************************//**
 * \fn	unsigned short int InicialMenu()
 *
 * \brief	*****			Menu Inicial		 ******.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \return	An int.
 **************************************************************************************************/

unsigned short int InicialMenu()
{
	unsigned short int TheOption;

	cout << endl << TAB_BIG << "Inicial Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Student Managment" << endl;
	cout << TAB << "2 - Uc Managment" << endl;
	cout << TAB << "3 - Tutor Managment" << endl;
	cout << TAB << "4 - Registration Managment" << endl;
	cout << TAB << "5 - Exit Program" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	TheOption = ReadUnsignedShortInt(1, 5);		//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 5

	clearScreen();

	if (TheOption == 5)
		return 0;

	return TheOption;
}

/**********************************************************************************************//**
 * \fn	void InicialOptions(Mieic & TheCourse)
 *
 * \brief	Inicial options.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param [in,out]	TheCourse	the course.
 **************************************************************************************************/

void InicialOptions(Mieic & TheCourse)
{
	unsigned int Option;

	while ((Option = InicialMenu()))
		switch (Option)
		{
		case 1: StudentManagmentOptions(TheCourse);
			break;
		case 2: UcManagmentOptions(TheCourse);
			break;
		case 3: TutorManagmentOptions(TheCourse);
			break;
		case 4: RegistrationManagmentOptions(TheCourse);
			break;
		}
}

/**********************************************************************************************//**
 * \fn	unsigned short int StudentManagmentMenu()
 *
 * \brief	*****		Student Managment		 ******.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \return	An int.
 **************************************************************************************************/

unsigned short int StudentManagmentMenu()
{
	unsigned short int Option;

	cout << endl << TAB_BIG << "Student Managment Menu" << endl;
	cout << endl;
	cout << TAB << "1 - List All Students" << endl;
	cout << TAB << "2 - See Information About a Single Student" << endl;
	cout << TAB << "3 - Add Student" << endl;
	cout << TAB << "4 - Remove Student" << endl;
	cout << TAB << "5 - Studant Passes Uc" << endl;
	cout << TAB << "6 - Studant Doesn't Pass Uc" << endl;
	cout << TAB << "7 - Go Back to Inicial Menu" << endl << endl;
	cout << TAB << "Input your Option: ";
	Option = ReadUnsignedShortInt(1, 7);			//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 6
	clearScreen();

	if (Option == 7)
	{
		return 0;
	}

	return Option;
}

/**********************************************************************************************//**
 * \fn	void StudentManagmentOptions(Mieic & TheCourse)
 *
 * \brief	Student managment options.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param [in,out]	TheCourse	the course.
 **************************************************************************************************/

void StudentManagmentOptions(Mieic & TheCourse)
{
	unsigned int Option;

	while ((Option = StudentManagmentMenu()))
		switch (Option)
		{
		case 1:
			TheCourse.showListofStudents();
			break;
		case 2: 
		{
			long code;
			cout << TAB_BIG << "Student Info:" << endl;
			cout << endl <<  "Please insert the code of the student (no up prefix needed):\n\nCode:   ";
			cin >> code;
			TheCourse.showInfoStudent(code);
		}
			break;
		case 3: 
			TheCourse.addStudent();
			break;
		case 4: 
		{
			long TheRcode;
			cout << TAB_BIG << "Remove Student:" << endl;
			cout << endl << "Please insert the code of the student you want to remove (no up prefix needed):\n\nCode:" << TAB;
			cin >> TheRcode;
			TheCourse.removeStudent(TheRcode);
		}
			break;
		case 5:
		{
			long code;
			cout << TAB_BIG << "Student's Passed UC's Register:" << endl;
			cout << endl << "Please insert the code of the student (no up prefix needed):\n\nCode:" << TAB;
			cin >> code;
			TheCourse.StudentPassesUc(code);
		}
			break;
		case 6:
		{
			long code;
			cout << TAB_BIG << "Student's Failed UC's Register:" << endl;
			cout << endl << "Please insert the code of the student (no up prefix needed)\n\nCode:" << TAB;
			cin >> code;
			TheCourse.StudentDoesntPassUc(code);
		}
			break;
		}
}

/**********************************************************************************************//**
 * \fn	unsigned short int UcManagmentMenu()
 *
 * \brief	***			Uc Managment			****.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \return	An int.
 **************************************************************************************************/

unsigned short int UcManagmentMenu()
{
	unsigned short int Option;

	cout << endl << TAB_BIG << "Uc Managment Menu" << endl << endl;
	cout << endl;
	cout << TAB << "1 - List Required Uc's" << endl;
	cout << TAB << "2 - List Optional Uc's" << endl;
	cout << TAB << "3 - List All Uc's" << endl;
	cout << TAB << "4 - Search UC" << endl;
	cout << endl << TAB << "Uc Costumized Search:" << endl << endl;
	cout << TAB << TAB << "5 - List all 1st Year Uc's" << endl;
	cout << TAB << TAB << "6 - List all 2nd Year Uc's" << endl;
	cout << TAB << TAB << "7 - List all 3rd Year Uc's" << endl;
	cout << TAB << TAB << "8 - List all 4th Year Uc's" << endl;
	cout << TAB << TAB << "9 - List all 5th Year Uc's" << endl;
	cout << TAB << TAB << "10 - List all 1st Semester Uc's" << endl;
	cout << TAB << TAB << "11 - List all 2nd Semester Uc's" << endl << endl;
	cout << TAB << "12 - Go Back to Inicial Menu" << endl << endl;
	cout << TAB << "Input your Option: ";
	Option = ReadUnsignedShortInt(1, 12);		//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 12
	clearScreen();

	if (Option == 12)
		return 0;

	return Option;
}

/**********************************************************************************************//**
 * \fn	void UcManagmentOptions(Mieic & TheCourse)
 *
 * \brief	Managment options.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param [in,out]	TheCourse	the course.
 **************************************************************************************************/

void UcManagmentOptions(Mieic & TheCourse)
{
	unsigned int Option;

	while ((Option = UcManagmentMenu()))
		switch (Option) {
		case 1:	TheCourse.showListofRUcs();
			break;
		case 2:	TheCourse.showListofOUcs();
			break;
		case 3:	TheCourse.showListAllUcs();
			break;
		case 4:	
		{
			cout << TAB_BIG << "UCs Search:" << endl;
			cout << endl << "Please insert the AKA of the UC you want to search:" << TAB;
			string AKA;
			cin >> AKA;
			TheCourse.showSearchUC(AKA);
			break;
		}
		case 5: TheCourse.showListofFirstYearUcs();
			break;
		case 6: TheCourse.showListofSecondYearUcs();
			break;
		case 7: TheCourse.showListofThirdYearUcs();
			break;
		case 8: TheCourse.showListofFourthYearUcs();
			break;
		case 9: TheCourse.showListofFifthYearUcs();
			break;
		case 10: TheCourse.showListofFirstSemesterUcs();
			break;
		case 11: TheCourse.showListofSecondSemesterUcs();
			break;

		}		
}

/**********************************************************************************************//**
 * \fn	unsigned short int TutorManagmentMenu()
 *
 * \brief	*****		 Tutor Managment		******.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \return	An int.
 **************************************************************************************************/

unsigned short int TutorManagmentMenu()
{
	unsigned short int Option;

	cout << endl << endl << TAB_BIG << "Tutor Managment Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Add Tutor" << endl;
	cout << TAB << "2 - Remove Tutor" << endl;
	cout << TAB << "3 - List all Tutors" << endl;
	cout << TAB << "4 - Go Back to Inicial Menu" << endl << endl;
	cout << TAB << "Input your Option: ";
	Option = ReadUnsignedShortInt(1, 4);		//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 4
	clearScreen();

	if (Option == 4)
		return 0;

	return Option;
}

/**********************************************************************************************//**
 * \fn	void TutorManagmentOptions(Mieic & TheCourse)
 *
 * \brief	Tutor managment options.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param [in,out]	TheCourse	the course.
 **************************************************************************************************/

void TutorManagmentOptions(Mieic & TheCourse) {
	unsigned int Option;

	while ((Option = TutorManagmentMenu()))
		switch (Option) {
		case 1:
		{
			string name;
			cout << TAB_BIG << "New Tutor" << endl;
			cout << endl << "Please enter the name of the new Tutor:" << TAB;
			getline(cin, name);
			TheCourse.addTutor(name);
			break;
		}
		case 2: 
		{
			string name;
			cout << TAB_BIG << "Remove Tutor" << endl;
			cout << endl << "Please enter the name of the Tutor you wish to remove:" << TAB;
			getline(cin, name);
			TheCourse.removeTutor(name);
			break;
		}
			break;
		case 3: TheCourse.showListofTutors();
			break;
		}
}

/**********************************************************************************************//**
 * \fn	unsigned short int RegistrationManagmentMenu()
 *
 * \brief	***		Registration Managment		****.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \return	An int.
 **************************************************************************************************/

unsigned short int RegistrationManagmentMenu()
{
	unsigned short int Option;

	cout << endl << endl << TAB_BIG << "Registration Managment Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Make Registration" << endl;
	cout << TAB << "2 - List all Registrations" << endl;
	cout << TAB << "3 - Go Back to Inicial Menu" << endl << endl;
	cout << TAB << "Input your Option: ";
	Option = ReadUnsignedShortInt(1, 3);		//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 5
	clearScreen();

	if (Option == 3)
		return 0;

	return Option;
}

/**********************************************************************************************//**
 * \fn	void RegistrationManagmentOptions(Mieic & TheCourse)
 *
 * \brief	Registration managment options.
 *
 * \author	Francisco Moreira
 * \date	20/11/2016
 *
 * \param [in,out]	TheCourse	the course.
 **************************************************************************************************/

void RegistrationManagmentOptions(Mieic & TheCourse) {
	unsigned int Option;

	while ((Option = RegistrationManagmentMenu()))
		switch (Option) {
		case 1:
		{
			long aStudent;
			cout << TAB_BIG << "New Registration" << endl;

			cout << endl << "Please insert the code of the student (no up prefix needed):\n\nCode:" << TAB;
			cin >> aStudent;
			while (cin.fail()) 
			{														
				cout << "Error. Please input a vavlid Code." << endl;		//Se o input for invalido volta a pedir um novo Code
				cin.clear();
				cin.ignore(256, '\n');
				cin >> aStudent;
			}

			string aUc;
			cout << "\nPlease insert the initials of the Uc" << TAB;
			cin >> aUc;
			string TheDate;
			cout << "\nPlease insert the date of the Registration [in the format DD/MM/YYYY]: " << endl;
			cin >> TheDate;
			Date aDate(TheDate);
			TheCourse.addRegistration(aDate, aUc, aStudent);
		}
		break;
		case 2: TheCourse.showListofRegistrations();
			break;
		}

}