/**********************************************************************************************//**
 * \file	Mieic.cpp
 *
 * \brief	Implements the mieic class.
 **************************************************************************************************/

#include "Mieic.h"
#include "Tools.h"
#include <algorithm>

using namespace std;

/**********************************************************************************************//**
 * \fn	Mieic::Mieic()
 *
 * \brief	Default constructor.
			
Mieic Constructor, reads information from .txt files

 **************************************************************************************************/

Mieic::Mieic()
{
	ifstream RequiredUcsFile("RequiredUcs.txt");
	Required_Uc FirstR_Uc(RequiredUcsFile);
	ListofRequiredUcs.push_back(FirstR_Uc);
	while (!RequiredUcsFile.eof())
	{
		Required_Uc EachR_Uc(RequiredUcsFile);
		ListofRequiredUcs.push_back(EachR_Uc);
	}
	RequiredUcsFile.close();

	ifstream OptionalUcsFile("OptionalUcs.txt");
	Optional_Uc FirstO_Uc(OptionalUcsFile);
	ListofOptionalUcs.push_back(FirstO_Uc);
	while (!OptionalUcsFile.eof())
	{
		Optional_Uc EachO_Uc(OptionalUcsFile);
		ListofOptionalUcs.push_back(EachO_Uc);
	}
	OptionalUcsFile.close();

	ifstream UPortoUcsFile("UPortoUCs.txt");
	Optional_Uc FirstUPorto_Uc(UPortoUcsFile, 1);
	ListofUPortoUcs.push_back(FirstUPorto_Uc);
	while (!UPortoUcsFile.eof())
	{
		Optional_Uc EachUPorto_Uc(UPortoUcsFile, 1);
		ListofUPortoUcs.push_back(EachUPorto_Uc);
	}
	UPortoUcsFile.close();

	ifstream TutorsFile("Tutors.txt");
	if (TutorsFile.peek() != std::ifstream::traits_type::eof())
	{
		Tutor First_Tutor(TutorsFile);
		ListofTutors.push_back(First_Tutor);
		while (!TutorsFile.eof())
		{
			Tutor Each_Tutor(TutorsFile);
			ListofTutors.push_back(Each_Tutor);
		}
		TutorsFile.close();
	}
	else
	{
		TutorsFile.close();
	}
	
	ifstream StudentsFile("Students.txt");
	if (StudentsFile.peek() != std::ifstream::traits_type::eof()) {
		Student First_Student(StudentsFile);
		ListofStudents.push_back(First_Student);
		while (!StudentsFile.eof())
		{
			Student Each_Student(StudentsFile);
			ListofStudents.push_back(Each_Student);
		}
		StudentsFile.close();
	}
	else
	{
		StudentsFile.close();
	}
	
	ifstream RegistrationsFile("Registrations.txt");
	if (RegistrationsFile.peek() != std::ifstream::traits_type::eof())
	{
		Registration First_Registration(RegistrationsFile);
		ListofRegistrations.push_back(First_Registration);
		while (!RegistrationsFile.eof())
		{
			Registration Each_Registration(RegistrationsFile);
			ListofRegistrations.push_back(Each_Registration);
		}
		RegistrationsFile.close();
	}
	else
	{
		RegistrationsFile.close();
	}

}

/**********************************************************************************************//**
 * \fn	void Mieic::addTutor(string AName)
 *
 * \brief	Adds a tutor.
 *
 Adds Tutor with name provided
 *
 * \param	AName	The name.
 **************************************************************************************************/

void Mieic::addTutor(string AName)
{
	for (unsigned int i = 0; i < ListofTutors.size(); i++)
	{
		if (AName == ListofTutors[i].getName()) {
			cout << "There's a Tutor with that name already\n";
			return;
		}
	}
	Tutor NewTutor(AName);
	ListofTutors.push_back(NewTutor);
	TutorsChanged = true;
	distributeTutors();
	cout << "Tutor added successfully\n";
}

/**********************************************************************************************//**
 * \fn	void Mieic::removeTutor(string AName)
 *
 * \brief	Removes the tutor described by AName.
 *
Removes tutor with provided name
 *
 * \exception	TutorNaoExistente	Thrown when a tutor nao existente error condition occurs.
 *
 * \param	AName	The name.
 **************************************************************************************************/

void Mieic::removeTutor(string AName)
{
	try {
		bool isThereName = false;
		for (unsigned int i = 0; i < ListofTutors.size(); i++)
		{
			if (ListofTutors[i].getName() == AName)
			{
				isThereName = true;
				ListofTutors[i].setNumberofTutors(ListofTutors[i].getNumberofTutors() - 1);
				ListofTutors.erase(ListofTutors.begin() + i);
				TutorsChanged = true;
				distributeTutors();
				cout << "Tutor removed successfully\n";
				return;
			}
		}

		if (isThereName == false)
		{
			throw TutorNaoExistente(AName);
		}
	}
	catch (TutorNaoExistente& e) {
		cout << endl << endl << "There is no tutor with the name: " << e.nome <<". Please check if you have spelled the tutor's name correctly." << endl << endl;
	}
}

/**********************************************************************************************//**
 * \fn	void Mieic::distributeTutors()
 *
 * \brief	Distribute tutors.
 *
 Distributes tutors based on a minimum, when all tutors have the same amount of students assign student to tutor 1 and raise minimum
 **************************************************************************************************/

void Mieic::distributeTutors() {
	bool found = false;
	for (unsigned int i = 0; i < ListofStudents.size(); i++)
	{
		found = false;
		for (unsigned int j = 0; j < ListofTutors.size(); j++)
		{
			if (ListofTutors[j].getNStudents() < ListofTutors[j].getMinStudents())
			{
				ListofStudents[i].setTutor(ListofTutors[j]);
				ListofTutors[j].setNStudents(ListofTutors[j].getNStudents() + 1);
				found = true;
				break;
			}
		}
		if (!found)
		{
			ListofStudents[i].setTutor(ListofTutors[0]);
			ListofTutors[0].setNStudents(ListofTutors[0].getNStudents() + 1);
			ListofTutors[0].setMinStudents(ListofTutors[0].getMinStudents() + 1);
		}
	}
	StudentsChanged = true;
	SaveChanges();
}

/**********************************************************************************************//**
 * \fn	void Mieic::addStudent()
 *
 * \brief	Adds student.
 *
Adds Student with full information
 *
 * \exception	UcNaoExistente	Thrown when a nao existente error condition occurs.
 **************************************************************************************************/

void Mieic::addStudent()
{
	string NewName, NewStatute;
	vector<Uc> TheNewApprovedUcs;
	vector<Uc> TheNewCurrentUcs;
	long NewCode;


	long Max_Code = 0;
	for (unsigned int i = 0; i < ListofStudents.size(); i++)
	{
		if (Max_Code < ListofStudents[i].getCode())
		{
			Max_Code = ListofStudents[i].getCode();
		}
	}
	NewCode = Max_Code + 1;

	cout << TAB_BIG << "New Student:\n";
	cout << endl << " Please Input the New Student's Information: " << endl << endl << "  Name:" << TAB;
	getline(cin, NewName);   
	bool isThereGoodStatute = false;
	while (isThereGoodStatute == false)
	{
		cout << "\n  Statute [Ordinario, Trabalhador Estudante, Dirigente Associativo, Atleta de Alta Competicao]:\n" << endl << "  ";
		cin >> NewStatute;
		if (NewStatute != "Ordinario" && NewStatute != "Trabalhador Estudante" && NewStatute != "Dirigente Associativo" && NewStatute != "Atleta de Alta Competicao" && NewStatute != "ordinario" && NewStatute != "trabalhador estudante" && NewStatute != "dirigente associativo" && NewStatute != "atleta de alta competicao")
		{
			cout << "\nError. Unrecognized Statute. Please input a valid Statute.\n\n" << endl;
		}
		else
		{
			isThereGoodStatute = true;
		}
	}

	cout << "\n  Approved Uc's (Input each one seperately)\n\n\t ***Input <exit> when you are done***\n " << endl;
	string EachUcAka;
	Uc NewUc;
	while (EachUcAka != "exit")
	{
		bool isUcGood = false;
		NewUc.setUcEmpty();

		while (isUcGood == false)
		{
			try {
				cout << "Uc (Initials): " << TAB;
				cin >> EachUcAka;
				if (EachUcAka == "exit")
				{
					break;
				}
				else if (CheckUc(EachUcAka, NewUc) == 0)
				{
					isUcGood = true;
				}
				else if (CheckUc(EachUcAka, NewUc) == 1)
				{
					throw UcNaoExistente();
				}
			}
			catch (UcNaoExistente& e) 
			{
				(void)e;
				cout << endl << "The entered UC is not valid." << endl << endl;
			}
		}

		if (isUcGood == true)
		{
			TheNewApprovedUcs.push_back(NewUc);
		}
	}

	cout << endl << endl << "  Current Uc's (Input each one seperately):\n\n\t ***Input <exit> when you are done***\n " << endl;
	string EachCUcAka;
	Uc NewCUc;
	while (EachCUcAka != "exit")
	{
		bool isUcApproved = false;
		bool isCUcGood = false;
		NewCUc.setUcEmpty();

		while (isCUcGood == false)
		{
			try 
			{
				cout << "Uc (Initials): " << TAB;
				cin >> EachCUcAka;
				if (EachCUcAka == "exit")
				{
					break;
				}
				else if (CheckUc(EachCUcAka, NewCUc) == 0)
				{
					isCUcGood = true;
					for (unsigned int i = 0; i < TheNewApprovedUcs.size(); i++)
					{
						if (TheNewApprovedUcs[i].getAka() == EachCUcAka)
						{
							isUcApproved = true;
							break;
						}
					}
					
				}
				else if (CheckUc(EachCUcAka, NewCUc) == 1)
				{
					throw UcNaoExistente();
				}
			}
			catch (UcNaoExistente& e) 
			{
				(void)e;
				cout << endl << endl << "The entered UC is not valid." << endl << endl;
			}
		}
		if (isCUcGood == true && isUcApproved == true)
		{
			cout << endl << endl << "The entered Uc is already Approved!" << endl << endl;
		}
		else if (isCUcGood == true && isUcApproved == false)
		{
			TheNewCurrentUcs.push_back(NewCUc);
		}
	}

	Student NewStudent(NewName, NewCode, NewStatute, TheNewApprovedUcs, TheNewCurrentUcs);
	ListofStudents.push_back(NewStudent);
	StudentsChanged = true;
	cout << endl << endl << "Student added successfully" << endl << endl;

	distributeTutors();
}

/**********************************************************************************************//**
 * \fn	unsigned short int Mieic::CheckUc(string TheAkaUc, Uc &TheNewUc)
 *
 * \brief	Check uc.
 *
Checks if UC exists
 *
 * \param 		  	TheAkaUc	the aka uc.
 * \param [in,out]	TheNewUc	the new uc.
 *
 * \return	An int.
 **************************************************************************************************/

unsigned short int Mieic::CheckUc(string TheAkaUc, Uc &TheNewUc)
{
	bool isThereUc = false;
	for (unsigned int u = 0; u < ListofRequiredUcs.size(); u++)				
	{																
		if (TheAkaUc == ListofRequiredUcs[u].getAka())						
		{															
			isThereUc = true;
			TheNewUc.setAka(ListofRequiredUcs[u].getAka());
			TheNewUc.setName(ListofRequiredUcs[u].getName());
			TheNewUc.setECTS(ListofRequiredUcs[u].getECTS());
			TheNewUc.setYear(ListofRequiredUcs[u].getYear());
			TheNewUc.setSemester(ListofRequiredUcs[u].getSemester());
			break;
		}
		else;
	}
	if (isThereUc == true)
	{
		return 0;
	}

	for (unsigned int u = 0; u < ListofOptionalUcs.size(); u++)
	{
		if (TheAkaUc == ListofOptionalUcs[u].getAka())
		{
			isThereUc = true;
			TheNewUc.setAka(ListofOptionalUcs[u].getAka());
			TheNewUc.setName(ListofOptionalUcs[u].getName());
			TheNewUc.setECTS(ListofOptionalUcs[u].getECTS());
			TheNewUc.setYear(ListofOptionalUcs[u].getYear());
			TheNewUc.setSemester(ListofOptionalUcs[u].getSemester());
			break;
		}
		else;
	}
	if (isThereUc == true)
	{
		return 0;
	}

	for (unsigned int u = 0; u < ListofUPortoUcs.size(); u++)
	{
		if (TheAkaUc == ListofUPortoUcs[u].getAka())
		{
			isThereUc = true;
			TheNewUc.setAka(ListofUPortoUcs[u].getAka());
			TheNewUc.setName(ListofUPortoUcs[u].getName());
			TheNewUc.setECTS(ListofUPortoUcs[u].getECTS());
			TheNewUc.setYear(ListofUPortoUcs[u].getYear());
			TheNewUc.setSemester(ListofUPortoUcs[u].getSemester());
			break;
		}
		else;
	}
	if (isThereUc == true)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**********************************************************************************************//**
 * \fn	void Mieic::removeStudent(long TheCode)
 *
 * \brief	Removes the student described by TheCode.
 *
Removes student with code provided
 *
 * \exception	EstudanteNaoExistente	Thrown when an estudante nao existente error condition
 * 										occurs.
 *
 * \param	TheCode	the code.
 **************************************************************************************************/

void Mieic::removeStudent(long TheCode)
{
	try {
		unsigned int i;

		for (i = 0; i < ListofStudents.size(); i++)
		{
			if (ListofStudents[i].getCode() == TheCode)
			{
				ListofStudents.erase(ListofStudents.begin() + i);
				StudentsChanged = true;
				cout << "Student Removed Successfully!" << endl << endl;
				distributeTutors();
				return;
			}
		}
		throw EstudanteNaoExistente(TheCode);
	}
	catch (EstudanteNaoExistente &e) {
		cout << endl << endl << "Sorry! There was no student with the code: " << e.code << ". Please check if you have correctly written the student's code." << endl;
	}
	

}

/**********************************************************************************************//**
 * \fn	void Mieic::StudentPassesUc(long aStudent)
 *
 * \brief	Student passes uc.
 *
Approves Student in UC
 *
 * \exception	EstudanteNaoExistente	Thrown when an estudante nao existente error condition
 * 										occurs.
 *
 * \param	aStudent	The student.
 **************************************************************************************************/

void Mieic::StudentPassesUc(long aStudent)
{
	try {
		unsigned int i;

		for (i = 0; i < ListofStudents.size(); i++)
		{
			if (ListofStudents[i].getCode() == aStudent)
			{
				cout << "Here are the Student's Current Ucs: " << endl;
				for (unsigned int j = 0; j < ListofStudents[i].getCurrentUcs().size(); j++)
				{
					cout << ListofStudents[i].getCurrentUcs()[j].getAka() << endl;
				}
				string PassedUc;
				bool isUcCorrect = false;
				unsigned int r = 0;
				while (isUcCorrect == false)
				{
					r = 0;
					cout << endl << endl << "Type the Uc (Initials) that the Student passed: ";
					cin >> PassedUc;
					for (; r < ListofStudents[i].getCurrentUcs().size(); r++)
					{
						if (PassedUc == ListofStudents[i].getCurrentUcs()[r].getAka())
						{
							isUcCorrect = true;
							break;
						}
						else;
					}
					if (isUcCorrect == false)
					{
						cout << "Error. Invalid Uc" << endl;
					}
				}

				float UcsNumberofECTS; // = ListofStudents[i].getCurrentUcs()[r].getECTS();
				bool isThereECTS = false;
				for (unsigned int q = 0; q < ListofRequiredUcs.size(); q++)
				{
					if (ListofRequiredUcs[q].getAka() == ListofStudents[i].getCurrentUcs()[r].getAka())
					{
						isThereECTS = true;
						UcsNumberofECTS = ListofRequiredUcs[q].getECTS();
						break;
					}
				}
				if (isThereECTS == false)
				{
					for (unsigned int w = 0; w < ListofOptionalUcs.size(); w++)
					{
						if (ListofOptionalUcs[w].getAka() == ListofStudents[i].getCurrentUcs()[r].getAka())
						{
							isThereECTS = true;
							UcsNumberofECTS = ListofOptionalUcs[w].getECTS();
							break;
						}
					}
					if (isThereECTS == false)
					{
						for (unsigned int p = 0; p < ListofUPortoUcs.size(); p++)
						{
							if (ListofUPortoUcs[p].getAka() == ListofStudents[i].getCurrentUcs()[r].getAka())
							{
								isThereECTS = true;
								UcsNumberofECTS = ListofUPortoUcs[p].getECTS();
								break;
							}
						}
					}
				}


				Uc ThePassedUc = ListofStudents[i].getCurrentUcs()[r];
				vector <Uc> StudentsApprovedUcs = ListofStudents[i].getApprovedUcs();
				StudentsApprovedUcs.push_back(ThePassedUc);
				ListofStudents[i].setApprovedUcs(StudentsApprovedUcs);

				vector <Uc> StudentsCurrentUcs = ListofStudents[i].getCurrentUcs();
				StudentsCurrentUcs.erase(StudentsCurrentUcs.begin() + r);
				ListofStudents[i].setCurrentUcs(StudentsCurrentUcs);

				ListofStudents[i].setAvailableCredits(ListofStudents[i].getAvailableCredits() + UcsNumberofECTS);

				StudentsChanged = true;
				cout << "Student passed Uc Successfully!" << endl << endl;
				break;
			}
		}
		if (i == ListofStudents.size())
			throw EstudanteNaoExistente(aStudent);
	}
	catch (EstudanteNaoExistente& e) 
	{
		(void)e;
		cout << endl << endl << "Error! Please check if you have correctly written the student's code." << endl << endl;
	}
}

/**********************************************************************************************//**
 * \fn	void Mieic::StudentDoesntPassUc(long aStudent)
 *
 * \brief	Student doesnt pass uc.
 *
Removes UC from students registration without adding to passed UCs
 *
 * \exception	UcNaoExistente		 	Thrown when a nao existente error condition occurs.
 * \exception	EstudanteNaoExistente	Thrown when an estudante nao existente error condition
 * 										occurs.
 *
 * \param	aStudent	The student.
 **************************************************************************************************/

void Mieic::StudentDoesntPassUc(long aStudent)
{
	try {
		unsigned int i;

		for (i = 0; i < ListofStudents.size(); i++)
		{
			if (ListofStudents[i].getCode() == aStudent)
			{
				cout << "Here are the Student's Current Ucs: " << endl;
				for (unsigned int j = 0; j < ListofStudents[i].getCurrentUcs().size(); j++)
				{
					cout << ListofStudents[i].getCurrentUcs()[j].getAka() << endl;
				}
				string NotPassedUc;
				bool isUcCorrect = false;
				unsigned int r = 0;
				while (isUcCorrect == false)
				{
					try {
						r = 0;
						cout << endl << endl << "Type the Uc (initials) that the Student failed: ";
						cin >> NotPassedUc;
						for (; r < ListofStudents[i].getCurrentUcs().size(); r++)
						{
							if (NotPassedUc == ListofStudents[i].getCurrentUcs()[r].getAka())
							{
								isUcCorrect = true;
								break;
							}
							else;
						}
						if (isUcCorrect == false)
						{
							throw UcNaoExistente();
						}
					}
					catch (UcNaoExistente& e) 
					{
						(void)e;
						cout << endl << endl << "The entered UC is not valid." << endl << endl;
					}
				}

				float UcsNumberofECTS; // = ListofStudents[i].getCurrentUcs()[r].getECTS();
				bool isThereECTS = false;
				for (unsigned int q = 0; q < ListofRequiredUcs.size(); q++)
				{
					if (ListofRequiredUcs[q].getAka() == ListofStudents[i].getCurrentUcs()[r].getAka())
					{
						isThereECTS = true;
						UcsNumberofECTS = ListofRequiredUcs[q].getECTS();
						break;
					}
				}
				if (isThereECTS == false)
				{
					for (unsigned int w = 0; w < ListofOptionalUcs.size(); w++)
					{
						if (ListofOptionalUcs[w].getAka() == ListofStudents[i].getCurrentUcs()[r].getAka())
						{
							isThereECTS = true;
							UcsNumberofECTS = ListofOptionalUcs[w].getECTS();
							break;
						}
					}
					if (isThereECTS == false)
					{
						for (unsigned int p = 0; p < ListofUPortoUcs.size(); p++)
						{
							if (ListofUPortoUcs[p].getAka() == ListofStudents[i].getCurrentUcs()[r].getAka())
							{
								isThereECTS = true;
								UcsNumberofECTS = ListofUPortoUcs[p].getECTS();
								break;
							}
						}
					}
				}

				vector <Uc> StudentsCurrentUcs = ListofStudents[i].getCurrentUcs();
				StudentsCurrentUcs.erase(StudentsCurrentUcs.begin() + r);
				ListofStudents[i].setCurrentUcs(StudentsCurrentUcs);

				ListofStudents[i].setAvailableCredits(ListofStudents[i].getAvailableCredits() + UcsNumberofECTS);

				StudentsChanged = true;
				cout << "Student failed to pass Uc  D:" << endl << endl;
				break;
			}
		}
		if (i == ListofStudents.size())
			throw EstudanteNaoExistente(aStudent);//cout << "Sorry! No Student has that code. Please check if you have correctly written the student's code." << endl;
	}
	catch (EstudanteNaoExistente& e) 
	{
		(void)e;
		cout << endl << endl << "Error! Please check if you have correctly written the student's code." << endl << endl;
	}
}

/**********************************************************************************************//**
 * \fn	void Mieic::addRegistration(Date aDate, string aUc, long aStudent)
 *
 * \brief	Adds a registration.
 *
Adds Registration of student in a UC
 *
 * \param	aDate   	The date.
 * \param	aUc			The uc.
 * \param	aStudent	The student.
 **************************************************************************************************/

void Mieic::addRegistration(Date aDate, string aUc, long aStudent)
{
	unsigned int MaxUcYear = 0;
	bool isThereStudent = false;
	bool isThereUc = false;
	bool isUcCurrent = false;
	bool isUcApproved = false;
	bool isThereCredit = false;
	bool isThereVacancies = true;
	bool isThereYear = false;

	unsigned int TheStudentsIndex = 0;
	for (unsigned int i = 0; i < ListofStudents.size(); i++)
	{
		if (ListofStudents[i].getCode() == aStudent)
		{
			isThereStudent = true;
			TheStudentsIndex = i;

			for (unsigned int j = 0; j < ListofRequiredUcs.size(); j++)
			{
				if (ListofRequiredUcs[j].getAka() == aUc)
				{
					isThereUc = true;
					isThereVacancies = true;
					for (unsigned int r = 0; r < ListofStudents[i].getCurrentUcs().size(); r++)
					{
						if (ListofStudents[i].getCurrentUcs()[r].getAka() == aUc)
						{
							isUcCurrent = true;
							break;
						}
					}
					if (isUcCurrent == true)
					{
						break;
					}

					for (unsigned int t = 0; t < ListofStudents[i].getApprovedUcs().size(); t++)
					{
						if (ListofStudents[i].getApprovedUcs()[t].getAka() == aUc)
						{
							isUcApproved = true;
							break;
						}
					}
					if (isUcApproved == true)
					{
						break;
					}

					for (unsigned int b = 0; b < ListofStudents[i].getApprovedUcs().size(); b++)
					{
						if (MaxUcYear < ListofStudents[i].getApprovedUcs()[b].getYear())
						{
							MaxUcYear = ListofStudents[i].getApprovedUcs()[b].getYear();
						}

					}

					if ((ListofStudents[i].getAvailableCredits() - ListofRequiredUcs[j].getECTS()) >= 0)
					{
						isThereCredit = true;

						if ((MaxUcYear+1) >= ListofRequiredUcs[j].getYear())
						{
							isThereYear = true;
							Registration NewRegistration(aDate, aUc, aStudent);
							ListofRegistrations.push_back(NewRegistration);
							Uc NewUc(aUc);
							ListofStudents[i].addCurrentUc(aUc);
							ListofStudents[i].setAvailableCredits(ListofStudents[i].getAvailableCredits() - ListofRequiredUcs[j].getECTS());
							StudentsChanged = true;
							RegistrationsChanged = true;
						}
					}
				}
			}
			
			if (isThereUc == true)
			{
				break;
			}

			for (unsigned int w = 0; w < ListofOptionalUcs.size(); w++)
			{
				if (ListofOptionalUcs[w].getAka() == aUc)
				{
					isThereUc = true;

					for (unsigned int e = 0; e < ListofStudents[i].getCurrentUcs().size(); e++)
					{
						if (ListofStudents[i].getCurrentUcs()[e].getAka() == aUc)
						{
							isUcCurrent = true;
							break;
						}
					}
					if (isUcCurrent == true)
					{
						break;
					}

					for (unsigned int s = 0; s < ListofStudents[i].getApprovedUcs().size(); s++)
					{
						if (ListofStudents[i].getApprovedUcs()[s].getAka() == aUc)
						{
							isUcApproved = true;
							break;
						}
					}
					if (isUcApproved == true)
					{
						break;
					}

					MaxUcYear = 0;
					for (unsigned int m = 0; m < ListofStudents[i].getApprovedUcs().size(); m++)
					{
						if (MaxUcYear < ListofStudents[i].getApprovedUcs()[m].getYear())
						{
							MaxUcYear = ListofStudents[i].getApprovedUcs()[m].getYear();
						}
					}

					if (ListofOptionalUcs[w].getVacancies() >= 1)
					{
						if ((ListofStudents[i].getAvailableCredits() - ListofOptionalUcs[w].getECTS()) >= 0)
						{
							isThereCredit = true;

							if ((MaxUcYear + 1) >= ListofOptionalUcs[w].getYear())
							{
								isThereYear = true;
								Registration NewRegistration(aDate, aUc, aStudent);
								ListofRegistrations.push_back(NewRegistration);
								Uc NewUc(aUc);
								ListofStudents[i].addCurrentUc(aUc);
								ListofStudents[i].setAvailableCredits(ListofStudents[i].getAvailableCredits() - ListofOptionalUcs[w].getECTS());
								StudentsChanged = true;
								RegistrationsChanged = true;
							}
						}
					}
					else
					{
						isThereVacancies = false;
					}
				}
			}
		}
	}

	if (isThereStudent == false)
	{
		cout << "Not possible to make Registration because there is no Student with such code" << endl;
	}
	else if (isThereStudent == true && isThereUc == false)
	{
		cout << "There isn't such Uc" << endl;
	}
	else if (isThereStudent == true && isThereUc == true && isUcCurrent == true)
	{
		cout << "That Student is already registered to that Uc" << endl;
	}
	else if (isThereStudent == true && isThereUc == true && isUcCurrent == false && isUcApproved == true)
	{
		cout << "That Student is already approved to that Uc" << endl;
	}

	else if (isThereStudent == true && isThereUc == true && isUcCurrent == false && isUcApproved == false && isThereVacancies == false && isThereCredit == false)
	{
		char answer;					//Falta checar erros de input aqui
		isThereUc = false;
		cout << "The Uc does not have any more vancancies left" << endl << endl << "Would you like to register to another Uc from UP? (Y for yes, N for no) ";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			showListofUPortoUcs();
			cout << endl << endl << "Which Uc would you like to register to? (Type the Uc's Initials) ";
			cin >> aUc;
			isThereVacancies = true;
			for (unsigned int h = 0; h < ListofUPortoUcs.size(); h++)
			{
				if (ListofUPortoUcs[h].getAka() == aUc)
				{
					isThereUc = true;

					for (unsigned int l = 0; l < ListofStudents[TheStudentsIndex].getCurrentUcs().size(); l++)
					{
						if (ListofStudents[TheStudentsIndex].getCurrentUcs()[l].getAka() == aUc)
						{
							isUcCurrent = true;
							break;
						}
					}
					if (isUcCurrent == true)
					{
						break;
					}

					for (unsigned int v = 0; v < ListofStudents[TheStudentsIndex].getApprovedUcs().size(); v++)
					{
						if (ListofStudents[TheStudentsIndex].getApprovedUcs()[v].getAka() == aUc)
						{
							isUcApproved = true;
							break;
						}
					}
					if (isUcApproved == true)
					{
						break;
					}

					MaxUcYear = 0;
					for (unsigned int c = 0; c < ListofStudents[TheStudentsIndex].getApprovedUcs().size(); c++)
					{
						if (MaxUcYear < ListofStudents[TheStudentsIndex].getApprovedUcs()[c].getYear())
						{
							MaxUcYear = ListofStudents[TheStudentsIndex].getApprovedUcs()[c].getYear();
						}
					}

					if (ListofStudents[TheStudentsIndex].getAvailableCredits() - (ListofUPortoUcs[h].getECTS()) >= 0)
					{
						isThereCredit = true;

						if ((MaxUcYear + 1) >= ListofUPortoUcs[h].getYear())
						{
							isThereYear = true;
							Registration NewRegistration(aDate, aUc, aStudent);
							ListofRegistrations.push_back(NewRegistration);
							Uc NewUc(aUc);
							ListofStudents[TheStudentsIndex].addCurrentUc(aUc);
							ListofStudents[TheStudentsIndex].setAvailableCredits(ListofStudents[TheStudentsIndex].getAvailableCredits() - ListofUPortoUcs[h].getECTS());
							StudentsChanged = true;
							RegistrationsChanged = true;
						}
					}
				}
			}

			if (isThereStudent == true && isThereUc == false)
			{
				cout << "There isn't such Uc" << endl;
			}
			else if (isThereStudent == true && isThereUc == true && isUcCurrent == true)
			{
				cout << "That Student is already registered to that Uc" << endl;
			}
			else if (isThereStudent == true && isThereUc == true && isUcCurrent == false && isUcApproved == true)
			{
				cout << "That Student is already approved to that Uc" << endl;
			}
			else if (isThereStudent == true && isThereUc == true && isUcCurrent == false && isUcApproved == false && isThereVacancies == true && isThereCredit == false)
			{
				cout << "The Student does not have enought credits to make the Registration" << endl;
			}
			else if (isThereStudent == true && isThereUc == true && isUcCurrent == false && isUcApproved == false && isThereVacancies == true && isThereCredit == true && isThereYear == false)
			{
				cout << "That Uc's year is too advanced for that Student." << endl;
			}
			else if (isThereStudent == true && isThereUc == true && isUcCurrent == false && isUcApproved == false && isThereVacancies == true && isThereCredit == true && isThereYear == true)
			{
				cout << "Registration Successfull!" << endl;
			}
		}
		else if (answer == 'N' || answer == 'n')
		{
			cout << "No Registration made";
		}
	}

	else if (isThereStudent == true && isThereUc == true && isUcCurrent == false && isUcApproved == false && isThereVacancies == true && isThereCredit == false)
	{
		cout << "The Student does not have enought credits to make the Registration" << endl;
	}
	else if (isThereStudent == true && isThereUc == true && isUcCurrent == false && isUcApproved == false && isThereVacancies == true && isThereCredit == true && isThereYear == false)
	{
		cout << "That Uc's year is too advanced for that Student." << endl;
	}
	else if (isThereStudent == true && isThereUc == true && isUcCurrent == false && isUcApproved == false && isThereVacancies == true && isThereCredit == true && isThereYear == true)
	{
		cout << "Registration Successfull!" << endl;
	}

	
}

/**********************************************************************************************//**
 * \fn	void Mieic::showListofRUcs()
 *
 * \brief	Shows the listof r ucs.
 *
Display list of Required UCs
 **************************************************************************************************/

void Mieic::showListofRUcs()
{
	cout << "List of Required Mieic Ucs:" << endl << endl;
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS()  << endl;
	}
	cout << endl << endl;
}

/**********************************************************************************************//**
 * \fn	void Mieic::showListofOUcs()
 *
 * \brief	Shows the listof o ucs.
 *
 Display list of Optional UCs
 **************************************************************************************************/

void Mieic::showListofOUcs()
{
	cout << "List of Optional Mieic Ucs:" << endl << endl;
	for (unsigned int i = 0; i < ListofOptionalUcs.size(); i++)
	{
		cout << ListofOptionalUcs[i].getName() << " (" << ListofOptionalUcs[i].getAka() << "):\n\tYear: " << ListofOptionalUcs[i].getYear() << "\n\tSemester: " << ListofOptionalUcs[i].getSemester() << "\n\tCredits: " << ListofOptionalUcs[i].getECTS() << "\n\tVacancies: " << ListofOptionalUcs[i].getVacancies() <<  endl;
	}
}

/**********************************************************************************************//**
 * \fn	void Mieic::showListofUPortoUcs()
 *
 * \brief	Shows the listof u porto ucs.
 *
 Display list of Other UP UCs
 **************************************************************************************************/

void Mieic::showListofUPortoUcs()
{
	cout << "List of other U.Porto Ucs:" << endl << endl;
	for (unsigned int i = 0; i < ListofUPortoUcs.size(); i++)
	{
		cout << ListofUPortoUcs[i].getName() << " (" << ListofUPortoUcs[i].getAka() << "):\n\tYear: " << ListofUPortoUcs[i].getYear() << "\n\tSemester: " << ListofUPortoUcs[i].getSemester() << "\n\tCredits: " << ListofUPortoUcs[i].getECTS() << endl;
	}
}

/**********************************************************************************************//**
 * \fn	void Mieic::showListAllUcs()
 *
 * \brief	Shows the list all ucs.
 *
 Display list of all MIEIC UCs
 **************************************************************************************************/

void Mieic::showListAllUcs()
{
	cout << "List of All Mieic Ucs:" << endl << endl;

	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "   Semester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS() << endl;
	}

	for (unsigned int i = 0; i < ListofOptionalUcs.size(); i++)
	{
		cout << ListofOptionalUcs[i].getName() << " (" << ListofOptionalUcs[i].getAka() << "):\n\tYear: " << ListofOptionalUcs[i].getYear() << "   Semester: " << ListofOptionalUcs[i].getSemester() << "\n\tCredits: " << ListofOptionalUcs[i].getECTS() << "\n\tVacancies: " << ListofOptionalUcs[i].getVacancies() << endl;
	}
}


void Mieic::showListofFirstYearUcs()
{
	cout << TAB << "First Year Uc's:" << endl << endl << endl;
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		if (ListofRequiredUcs[i].getYear() == 1)
		{
			cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS() << endl;
		}
		else
		{
			break;
		}
	}
}


void Mieic::showListofSecondYearUcs()
{
	cout << TAB << "Second Year Uc's:" << endl << endl << endl;
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		if (ListofRequiredUcs[i].getYear() == 2)
		{
			cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS() << endl;
		}
	}
}


void Mieic::showListofThirdYearUcs()
{
	cout << TAB << "Third Year Uc's:" << endl << endl << endl;
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		if (ListofRequiredUcs[i].getYear() == 3)
		{
			cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS() << endl;
		}
	}
}


void Mieic::showListofFourthYearUcs()
{
	cout << TAB << "Fourth Year Uc's:" << endl << endl << endl;
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		if (ListofRequiredUcs[i].getYear() == 4)
		{
			cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS() << endl;
		}
	}
	for (unsigned int j = 0; j < ListofOptionalUcs.size(); j++)
	{
		if (ListofOptionalUcs[j].getYear() == 4)
		{
			cout << ListofOptionalUcs[j].getName() << " (" << ListofOptionalUcs[j].getAka() << "):\n\tYear: " << ListofOptionalUcs[j].getYear() << "\n\tSemester: " << ListofOptionalUcs[j].getSemester() << "\n\tCredits: " << ListofOptionalUcs[j].getECTS() << endl;
		}
	}
}


void Mieic::showListofFifthYearUcs()
{
	cout << TAB << "Fifth Year Uc's:" << endl << endl << endl;
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		if (ListofRequiredUcs[i].getYear() == 5)
		{
			cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS() << endl;
		}
	}
	for (unsigned int j = 0; j < ListofOptionalUcs.size(); j++)
	{
		if (ListofOptionalUcs[j].getYear() == 5)
		{
			cout << ListofOptionalUcs[j].getName() << " (" << ListofOptionalUcs[j].getAka() << "):\n\tYear: " << ListofOptionalUcs[j].getYear() << "\n\tSemester: " << ListofOptionalUcs[j].getSemester() << "\n\tCredits: " << ListofOptionalUcs[j].getECTS() << endl;
		}
	}
}


void Mieic::showListofFirstSemesterUcs()
{
	cout << TAB << "First Semester Uc's:" << endl << endl << endl;	
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		if (ListofRequiredUcs[i].getSemester() == 1)
		{
			cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS() << endl;
		}
	}
	for (unsigned int j = 0; j < ListofOptionalUcs.size(); j++)
	{
		if (ListofOptionalUcs[j].getSemester() == 1)
		{
			cout << ListofOptionalUcs[j].getName() << " (" << ListofOptionalUcs[j].getAka() << "):\n\tYear: " << ListofOptionalUcs[j].getYear() << "\n\tSemester: " << ListofOptionalUcs[j].getSemester() << "\n\tCredits: " << ListofOptionalUcs[j].getECTS() << endl;
		}
	}
}


void Mieic::showListofSecondSemesterUcs()
{
	cout << TAB << "Second Semester Uc's:" << endl << endl << endl;
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		if (ListofRequiredUcs[i].getSemester() == 2)
		{
			cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS() << endl;
		}
	}
	for (unsigned int j = 0; j < ListofOptionalUcs.size(); j++)
	{
		if (ListofOptionalUcs[j].getSemester() == 2)
		{
			cout << ListofOptionalUcs[j].getName() << " (" << ListofOptionalUcs[j].getAka() << "):\n\tYear: " << ListofOptionalUcs[j].getYear() << "\n\tSemester: " << ListofOptionalUcs[j].getSemester() << "\n\tCredits: " << ListofOptionalUcs[j].getECTS() << endl;
		}
	}
}


/**********************************************************************************************//**
 * \fn	void Mieic::showSearchUC(string AKA)
 *
 * \brief	Shows the search uc.
 *
 Display information of searched UC including registred students
 *
 * \param	AKA	The aka.
 **************************************************************************************************/

void Mieic::showSearchUC(string AKA) {
	bool found = false;
	cout << "\n";
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		if (AKA == ListofRequiredUcs[i].getAka())
		{
			found = true;
			cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS() << endl;
			break;
		}
	}
	for (unsigned int i = 0; i < ListofOptionalUcs.size() && !found; i++)
	{
		if (AKA == ListofOptionalUcs[i].getAka())
		{
			found = true;
			cout << ListofOptionalUcs[i].getName() << " (" << ListofOptionalUcs[i].getAka() << "):\n\tYear: " << ListofOptionalUcs[i].getYear() << "\n\tSemester: " << ListofOptionalUcs[i].getSemester() << "\n\tCredits: " << ListofOptionalUcs[i].getECTS() << "\n\tVacancies: " << ListofOptionalUcs[i].getVacancies() << endl;
			break;
		}
	}
	for (unsigned int i = 0; i < ListofUPortoUcs.size() && !found; i++)
	{
		if (AKA == ListofUPortoUcs[i].getAka())
		{
			found = true;
			cout << ListofUPortoUcs[i].getName() << " (" << ListofUPortoUcs[i].getAka() << "):\n\tYear: " << ListofUPortoUcs[i].getYear() << "\n\tSemester: " << ListofUPortoUcs[i].getSemester() << "\n\tCredits: " << ListofUPortoUcs[i].getECTS() << endl;
			break;
		}
	}

	if (!found)
	{
		cout << "No UC " + AKA + " found." << endl << endl << endl;
		return;
	}

	cout << "\tRegistered Students:\n";

	for (unsigned int i = 0; i < ListofStudents.size(); i++)
	{
		for (unsigned int j = 0; j < ListofStudents[i].getCurrentUcs().size(); j++)
		{
			if (ListofStudents[i].getCurrentUcs()[j].getAka() == AKA)
			{
				cout << "\t\t" << ListofStudents[i].getCode() << '\n';
			}
		}
	}

}

/**********************************************************************************************//**
 * \fn	void Mieic::showListofTutors()
 *
 * \brief	Shows the listof tutors.
 *
Display list of Tutors
 **************************************************************************************************/

void Mieic::showListofTutors()
{
	cout << "List of Tutors:" << endl << endl;

	for (unsigned int i = 0; i < ListofTutors.size(); i++)
	{
		cout << ListofTutors[i].getName() << endl;
	}
}

/**********************************************************************************************//**
 * \fn	void Mieic::showListofStudents()
 *
 * \brief	Shows the listof students.
 *
Display list of Students
 **************************************************************************************************/

void Mieic::showListofStudents()
{
	cout << TAB_BIG << "List of Students:" << endl << endl;

	sort(ListofStudents.begin(), ListofStudents.end());			//Ordena os alunos de ordem alfabética

	for (unsigned int i = 0; i < ListofStudents.size(); i++)
	{
		cout << ListofStudents[i].getName() << ", " << ListofStudents[i].getCode() << ", " << ListofStudents[i].getEmail() << "; " << ListofStudents[i].getStatute() << endl << "Approved Uc's: " << ListofStudents[i].showApprovedUcs() << endl << "Current Uc's: " << ListofStudents[i].showCurrentUcs() << endl << "Tutor: " << ListofStudents[i].getTutor() << endl << endl << endl;
	}
}

/**********************************************************************************************//**
 * \fn	void Mieic::showInfoStudent(long code)
 *
 * \brief	Shows the information student.
 *
Display Information of Student
 *
 * \exception	EstudanteNaoExistente	Thrown when an estudante nao existente error condition
 * 										occurs.
 *
 * \param	code	The code.
 **************************************************************************************************/

void Mieic::showInfoStudent(long code)
{

	unsigned int i;
	try {
		for (i = 0; i < ListofStudents.size(); i++)
		{
			if (ListofStudents[i].getCode() == code)
			{
				cout << "Name:" << TAB << ListofStudents[i].getName() << "\nCode:" << TAB << ListofStudents[i].getCode() << "\nE-mail:" << TAB <<
					ListofStudents[i].getEmail() << "\nApproved UC's: " << TAB << ListofStudents[i].showApprovedUcs() << endl << "Current Uc's: " << TAB <<
					ListofStudents[i].showCurrentUcs() << endl << "Available Credits: " << TAB << ListofStudents[i].getAvailableCredits() << endl;
				break;
			}
		}
		if (i == ListofStudents.size())
			throw EstudanteNaoExistente(code);   //cout << "Sorry! There were no matches. Please check if you have correctly written the student's code." << endl;
	}
	catch (EstudanteNaoExistente& e) 
	{
		(void)e;
		cout << endl << endl << 
			"Error! Please check if you have correctly written the student's code." << endl;
	}
	/*
			if (ListofStudents[i].getApprovedUcs().size() == 0)
				cout << "Name:" << TAB << ListofStudents[i].getName() << "\nCode:" << TAB << ListofStudents[i].getCode() << "\nE-mail:" << TAB <<
				ListofStudents[i].getEmail() << "\nApproved UC's: The student does not have any Approved UC.";// << "\nCurrent UC's: " << ListofStudents[i].showCurrentUcs() << endl;
			else
				cout << "Name:" << TAB << ListofStudents[i].getName() << "\nCode:" << TAB << ListofStudents[i].getCode() << "\nE-mail:" << TAB <<
				ListofStudents[i].getEmail() << "\nApproved UC's: " << ListofStudents[i].showApprovedUcs();// << "\nCurrent UC's: " << ListofStudents[i].showCurrentUcs() << endl;
			break;
		}
	*/
}

/**********************************************************************************************//**
 * \fn	void Mieic::showListofRegistrations()
 *
 * \brief	Shows the listof registrations.
 *
Display list of Registrations
 **************************************************************************************************/

void Mieic::showListofRegistrations()
{
	cout << "List of Registrations:" << endl << endl;

	for (unsigned int i = 0; i < ListofRegistrations.size(); i++)
	{
		cout << "Codigo de Aluno: " << ListofRegistrations[i].getStudentCode() << ", Uc: " << ListofRegistrations[i].getUcAka() << ", Data: " << ListofRegistrations[i].getDate() << endl;
	}
}

/**********************************************************************************************//**
 * \fn	void Mieic::SaveChanges() const
 *
 * \brief	Saves the changes.
 *
Saves changes to files if changes occured
 **************************************************************************************************/

void Mieic::SaveChanges() const
{
	if (StudentsChanged == true)		//se StudentsChanged estiver "true" a função passa tudo o que o vector contém para uma string
	{									//e copia a string para o ficheiro original, apagando a informação antiga
		stringstream ss;
		for (size_t i = 0; i < ListofStudents.size(); ++i)
		{
			if (i != 0)
				ss << endl;
			ss << ListofStudents[i];
		}
		string newStudents = ss.str();
		ofstream OStudents("Students.txt");
		OStudents << newStudents;
		OStudents.close();
	}
	if (TutorsChanged == true)			//se TutorsChanged estiver "true" a função passa tudo o que o vector contém para uma string
	{									//e copia a string para o ficheiro original, apagando a informação antiga
		stringstream ss;
		for (size_t i = 0; i < ListofTutors.size(); ++i)
		{
			if (i != 0)
				ss << endl;
			ss << ListofTutors[i];
		}
		string newTutors = ss.str();
		ofstream OTutors("Tutors.txt");
		OTutors << newTutors;
		OTutors.close();
	}
	if (RegistrationsChanged == true)			//se RegistrationsChanged estiver "true" a função passa tudo o que o vector contém para uma string
	{											//e copia a string para o ficheiro original, apagando a informação antiga
		stringstream ss;
		for (size_t i = 0; i < ListofRegistrations.size(); ++i)
		{
			if (i != 0)
				ss << endl;
			ss << ListofRegistrations[i];
		}
		string newRegistrations = ss.str();
		ofstream ORegistrations("Registrations.txt");
		ORegistrations << newRegistrations;
		ORegistrations.close();
	}

}
