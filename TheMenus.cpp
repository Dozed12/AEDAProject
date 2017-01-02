#include "TheMenus.h"
#include "Tools.h"
#include "Date.h"


unsigned short int InicialMenu()
{
	unsigned short int TheOption;

	cout << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "Main Menu:\n" << endl;
	cout << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "1 - Student Managment\n" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "2 - Uc Managment\n" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "3 - Tutor Managment\n" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "4 - Registration Managment\n" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "5 - Class Managment\n" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "6 - Exit Program\n" << endl << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "Please select an option: ";
	TheOption = ReadUnsignedShortInt(1, 6);		//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 6

	clearScreen();

	if (TheOption == 6)
		return 0;

	return TheOption;
}


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
		case 5: ClassManagmentOptions(TheCourse);
			break;
		}
}


unsigned short int StudentManagmentMenu()
{
	unsigned short int Option;

	cout << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "Student Managment Menu" << endl;
	cout << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "1 - List Students" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "2 - List of Students Who Have Finished or Interrupted the Course" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "3 - See Information About a Single Student" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "4 - Add Student" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "5 - Makes Changes to a Student" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "6 - Remove Student" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "7 - Studant Passes Uc" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "8 - Studant Doesn't Pass Uc" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "9 - Student Interrupts Course" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "10 - Go Back to Inicial Menu" << endl << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "Input your Option: ";
	Option = ReadUnsignedShortInt(1, 10);			//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 10
	clearScreen();

	if (Option == 10)
	{
		return 0;
	}

	return Option;
}


void StudentManagmentOptions(Mieic & TheCourse)
{
	unsigned int Option;

	while ((Option = StudentManagmentMenu()))
		switch (Option)
		{
		case 1:TheCourse.showListofStudents();
			break;
		case 2:TheCourse.showListofIorTStudents();
			break;
		case 3: 
		{
			long code;
			cout << TAB_BIG << "Student Info:" << endl;
			cout << endl <<  "Please insert the code of the student (no up prefix needed):\n\nCode:   ";
			cin >> code;
			while (cin.fail())
			{
				cout << "Error. Please input a valid Code." << endl;		//Se o input for invalido volta a pedir um novo Code
				cin.clear();
				cin.ignore(256, '\n');
				cin >> code;
			}
			TheCourse.showInfoStudent(code);
		}
			break;
		case 4: TheCourse.addStudent();
			break;
		case 5:
		{
			long TheCcode;
			cout << TAB_BIG << "Make Changes to a Student:" << endl;
			cout << endl << "Please insert the code of the student you want to make changes to (no up prefix needed):\n\nCode:" << TAB;
			cin >> TheCcode;
			while (cin.fail())
			{
				cout << "Error. Please input a valid Code." << endl;		//Se o input for invalido volta a pedir um novo Code
				cin.clear();
				cin.ignore(256, '\n');
				cin >> TheCcode;
			}
			bool isThereStudent = false;
			vector <Student> TheListofStudents = TheCourse.getListofStudents();
			for (unsigned int i = 0; i < TheListofStudents.size(); i++)
			{
				if (TheListofStudents[i].getCode() == TheCcode)
				{
					isThereStudent = true;
					break;
				}
			}
			if (isThereStudent == false)
			{
				TheCourse.changeStudentsFromHash(TheCcode);
			}
			else
			{
				TheCourse.changeStudentFromList(TheCcode);
			}
		}
		break;
		case 6: 
		{
			long TheRcode;
			cout << TAB_BIG << "Remove Student:" << endl;
			cout << endl << "Please insert the code of the student you want to remove (no up prefix needed):\n\nCode:" << TAB;
			cin >> TheRcode;
			while (cin.fail())
			{
				cout << "Error. Please input a valid Code." << endl;		//Se o input for invalido volta a pedir um novo Code
				cin.clear();
				cin.ignore(256, '\n');
				cin >> TheRcode;
			}
			TheCourse.removeStudent(TheRcode);
		}
			break;
		case 7:
		{
			long code;
			cout << TAB_BIG << "Student's Passed UC's Register:" << endl;
			cout << endl << "Please insert the code of the student (no up prefix needed):\n\nCode:" << TAB;
			cin >> code;
			while (cin.fail())
			{
				cout << "Error. Please input a valid Code." << endl;		//Se o input for invalido volta a pedir um novo Code
				cin.clear();
				cin.ignore(256, '\n');
				cin >> code;
			}
			TheCourse.StudentPassesUc(code);
		}
			break;
		case 8:
		{
			long code;
			cout << TAB_BIG << "Student's Failed UC's Register:" << endl;
			cout << endl << "Please insert the code of the student (no up prefix needed)\n\nCode:" << TAB;
			cin >> code;
			while (cin.fail())
			{
				cout << "Error. Please input a valid Code." << endl;		//Se o input for invalido volta a pedir um novo Code
				cin.clear();
				cin.ignore(256, '\n');
				cin >> code;
			}
			TheCourse.StudentDoesntPassUc(code);
		}
		break;
		case 9:
		{
			long code;
			cout << endl << "Please insert the code of the student (no up prefix needed)\n\nCode:" << TAB;
			cin >> code;
			while (cin.fail())
			{
				cout << "Error. Please input a valid Code." << endl;		//Se o input for invalido volta a pedir um novo Code
				cin.clear();
				cin.ignore(256, '\n');
				cin >> code;
			}
			TheCourse.StudentInterruptsCourse(code);
		}
		break;
		}
}


unsigned short int UcManagmentMenu()
{
	unsigned short int Option;

	cout << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "Uc Managment Menu" << endl << endl;
	cout << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "1 - List Required Uc's" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "2 - List Optional Uc's" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "3 - List All Uc's" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "4 - Search UC" << endl;
	cout << endl << TAB  << TAB_BIG << TAB_BIG << "Uc Costumized Search:" << endl << endl;
	cout << TAB << TAB << TinyTAB << TAB_BIG << TAB_BIG << TAB_BIG << "5 - List all 1st Year Uc's" << endl;
	cout << TAB << TAB << TinyTAB << TAB_BIG << TAB_BIG << TAB_BIG << "6 - List all 2nd Year Uc's" << endl;
	cout << TAB << TAB << TinyTAB << TAB_BIG << TAB_BIG << TAB_BIG << "7 - List all 3rd Year Uc's" << endl;
	cout << TAB << TAB << TinyTAB << TAB_BIG << TAB_BIG << TAB_BIG << "8 - List all 4th Year Uc's" << endl;
	cout << TAB << TAB << TinyTAB << TAB_BIG << TAB_BIG << TAB_BIG << "9 - List all 5th Year Uc's" << endl;
	cout << TAB << TAB << TinyTAB << TAB_BIG << TAB_BIG << TAB_BIG << "10 - List all 1st Semester Uc's" << endl;
	cout << TAB << TAB << TinyTAB << TAB_BIG << TAB_BIG << TAB_BIG << "11 - List all 2nd Semester Uc's" << endl << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "12 - Go Back to Inicial Menu" << endl << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "Input your Option: ";
	Option = ReadUnsignedShortInt(1, 12);		//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 12
	clearScreen();

	if (Option == 12)
		return 0;

	return Option;
}


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
			cout << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "UCs Search:" << endl;
			cout << endl << TAB_BIG << "Please insert the AKA of the UC you want to search:" << TAB;
			string AKA;
			cin >> AKA;
			TheCourse.showSearchUC(AKA);
		}
		break;
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


unsigned short int TutorManagmentMenu()
{
	unsigned short int Option;

	cout << endl << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "Tutor Managment Menu" << endl;
	cout << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "1 - Add Tutor" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "2 - Remove Tutor" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "3 - List all Tutors" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "4 - Schedule a Reunion" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "5 - Cancel a Reunion" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "6 - Change Reunion's Topics" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "7 - Show Tutor's Reunions" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "8 - Go Back to Inicial Menu" << endl << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "Input your Option: ";
	Option = ReadUnsignedShortInt(1, 8);		//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 7
	clearScreen();

	if (Option == 8)
		return 0;

	return Option;
}


void TutorManagmentOptions(Mieic & TheCourse) {
	unsigned int Option;

	while ((Option = TutorManagmentMenu()))
		switch (Option) {
		case 1:
		{
			string name;
			cout << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "New Tutor" << endl;
			cout << endl << TAB_BIG << TAB_BIG << "Please enter the name of the new Tutor:" << TAB;
			getline(cin, name);
			TheCourse.addTutor(name);
		}
		break;
		case 2: TheCourse.removeTutor();
			break;
		case 3: TheCourse.showListofTutors();
			break;
		case 4:	TheCourse.addTutorReunion();
			break;
		case 5:TheCourse.removeTutorReunion();
			break;
		case 6: TheCourse.changeTutorReunion();
			break;
		case 7: TheCourse.showTutorReunions();
			break;
		}
}


unsigned short int RegistrationManagmentMenu()
{
	unsigned short int Option;

	cout << endl << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "Registration Managment Menu" << endl;
	cout << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "1 - Make Registration" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "2 - List all Registrations" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "3 - Go Back to Inicial Menu" << endl << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "Input your Option: ";
	Option = ReadUnsignedShortInt(1, 3);		//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 5
	clearScreen();

	if (Option == 3)
		return 0;

	return Option;
}


void RegistrationManagmentOptions(Mieic & TheCourse) {
	unsigned int Option;

	while ((Option = RegistrationManagmentMenu()))
		switch (Option) {
		case 1:
		{
			long aStudent;
			cout << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "New Registration" << endl;
			cout << endl << TAB_BIG << "Please insert the code of the student (no up prefix needed):\n\nCode:" << TAB;
			cin >> aStudent;
			while (cin.fail()) 
			{														
				cout << "Error. Please input a valid Code." << endl;		//Se o input for invalido volta a pedir um novo Code
				cin.clear();
				cin.ignore(256, '\n');
				cin >> aStudent;
			}

			bool isThereStudent = false;
			vector <Student> TheListofStudents = TheCourse.getListofStudents();
			for (unsigned int i = 0; i < TheListofStudents.size(); i++)
			{
				if (TheListofStudents[i].getCode() == aStudent)
				{
					isThereStudent = true;
					break;
				}
			}
			if (isThereStudent == true)
			{
				string aUc;
				cout << TAB_BIG << "\nPlease insert the initials of the Uc" << TAB;
				cin >> aUc;
				string TheDate;
				cout << "\nPlease insert the date of the Registration [in the format DD/MM/YYYY]: " << TAB;
				cin >> TheDate;
				Date aDate(TheDate);
				TheCourse.addRegistration(aDate, aUc, aStudent);
			}
			else
			{
				string aUc;
				cout << TAB_BIG << "\nPlease insert the initials of the Uc" << TAB;
				cin >> aUc;
				string TheDate;
				cout << "\nPlease insert the date of the Registration [in the format DD/MM/YYYY]: " << TAB;
				cin >> TheDate;
				Date aDate(TheDate);
				TheCourse.addHashRegistration(aDate, aUc, aStudent);
			}
		}
		break;
		case 2: TheCourse.showListofRegistrations();
			break;
		}
}


unsigned short int ClassManagmentMenu()
{
	unsigned short int Option;

	cout << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "Class Managment Menu" << endl;
	cout << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "1 - View Classes" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "2 - Add Class" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "3 - Remove Class" << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "4 - Go Back to Inicial Menu" << endl << endl;
	cout << TAB << TAB_BIG << TAB_BIG << TAB_BIG << "Input your Option: ";
	Option = ReadUnsignedShortInt(1, 4);		//Chamada da funcao ReadUnsignedShortInt que verifica se opcao se encontrar entre 1 e 5
	clearScreen();

	if (Option == 4)
		return 0;

	return Option;
}


void ClassManagmentOptions(Mieic & TheCourse) {
	unsigned int Option;

	while ((Option = ClassManagmentMenu()))
		switch (Option) 
		{
		case 1: TheCourse.showListofClasses();
			break;
		case 2: TheCourse.addClass();
			break;
		case 3: TheCourse.removeClass();
			break;
		}
}