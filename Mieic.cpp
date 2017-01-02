#include "Mieic.h"
#include "Tools.h"
#include <algorithm>

using namespace std;


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
	
	ifstream HashStudentsFile("StudentsHash.txt");
	if (HashStudentsFile.peek() != std::ifstream::traits_type::eof()) 
	{
		Student First_Student(HashStudentsFile);
		HashofStudents.insert(First_Student);
		while (!HashStudentsFile.eof())
		{
			Student Each_Student(HashStudentsFile);
			HashofStudents.insert(Each_Student);
		}
		HashStudentsFile.close();
	}
	else
	{
		HashStudentsFile.close();
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

	ifstream ClassesFile("Classes.txt");
	if (ClassesFile.peek() != std::ifstream::traits_type::eof())
	{
		Class First_Class(ClassesFile);
		ListofClasses.push_back(First_Class);
		while (!ClassesFile.eof())
		{
			Class Each_Class(ClassesFile);
			ListofClasses.push_back(Each_Class);
		}
		ClassesFile.close();
	}
	else
	{
		ClassesFile.close();
	}

	for (unsigned int i = 1; i < 6; i++) {							//Initialization of all the 5 nodes(years) of the tree with its respective ucs
		vector<Uc> aux;

		for (unsigned int j = 0; j < ListofRequiredUcs.size(); j++) {
			if (ListofRequiredUcs[j].getYear() == i)
				aux.push_back(ListofRequiredUcs[j]);
		}

		mieicYears.push_back(Year(i, aux));
		aux.clear();
	}

	// add read students to class
	for (size_t i = 0; i < ListofStudents.size(); i++)
	{
		for (size_t j = 0; j < ListofClasses.size(); j++)
		{
			if (ListofStudents[i].getYear() == ListofClasses[j].getYear() + 1 && ListofStudents[i].getYearClass() == ListofClasses[j].getNumber() + 1) {
				ListofClasses[j].addStudent(ListofStudents[i]);
			}
		}
	}

	for (size_t i = 0; i < ListofClasses.size(); i++)
	{
		int j = ListofClasses[i].getYear();
		mieicYears[j].addNewClass(ListofClasses[i]);
	}
}


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


void Mieic::removeTutor()
{
	string AName;
	cout << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "Remove Tutor" << endl << endl << endl;
	showListofTutors();
	cout << endl << endl << TAB_BIG << TAB_BIG << "Please enter the name of the Tutor you wish to remove:" << TAB;
	getline(cin, AName);
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


void Mieic::addTutorReunion() 
{
	string AName;
	cout << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "New Reunion" << endl;
	showListofTutors();
	cout << endl << endl << TAB_BIG << "Please enter the name of the Tutor you would like to schedule a reunion:" << TAB;
	getline(cin, AName);
	try {
		unsigned int i, flag = 0;
		for (i = 0; i < ListofTutors.size(); i++) {
			if (ListofTutors[i].getName() == AName) {
				ListofTutors[i].addReunion(AName);
				flag = 1;
			}
		}
		if (flag == 0)
			throw TutorNaoExistente(AName);
	}
	catch (TutorNaoExistente& e) {
		cout << endl << endl << "There is no tutor with the name: " << e.nome
			<< ". Please check if you have spelled the tutor's name correctly." << endl << endl;
	}
}


void Mieic::removeTutorReunion() 
{
	string AName;
	cout << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "Cancel Reunion" << endl;
	showListofTutors();
	cout << endl << endl << TAB_BIG << "Please enter the name of the Tutor you would like to cancel the reunion:" << TAB;
	getline(cin, AName);
	try {
		int flag = 0;

		for (unsigned int i = 0; i < ListofTutors.size(); i++) {
			if (ListofTutors[i].getName() == AName) {
				ListofTutors[i].removeReunion(AName);
				flag = 1;
			}
		}
		if (flag == 0)
			throw TutorNaoExistente(AName);
	}
	catch (TutorNaoExistente& e) {
		cout << endl << endl << "There is no tutor with the name: " << e.nome
			<< ". Please check if you have spelled the tutor's name correctly." << endl << endl;
	}
}


void Mieic::changeTutorReunion() 
{
	string AName;
	cout << endl << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "Change Reunion's Description" << endl;
	showListofTutors();
	cout << endl << endl << TAB_BIG << "Please enter the name of the Tutor you would like to change the reunion's description:" << TAB;
	getline(cin, AName);
	try {
		int flag = 0;
		for (unsigned int i = 0; i < ListofTutors.size(); i++) {
			if (ListofTutors[i].getName() == AName) {
				ListofTutors[i].changeReunionDescription(AName);
				flag = 1;
			}
		}
		if (flag == 0)
			throw TutorNaoExistente(AName);
	}
	catch (TutorNaoExistente& e) {
		cout << endl << endl << "There is no tutor with the name: " << e.nome
			<< ". Please check if you have spelled the tutor's name correctly." << endl << endl;
	}
}


void Mieic::distributeTutors() {
	if (ListofTutors.size() == 0)
		return;
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
}


void Mieic::addStudent()
{
	string NewName, NewStatute, NewAdress, NewContact;
	vector<Uc> TheNewApprovedUcs;
	vector<Uc> TheNewCurrentUcs;
	long NewCode;
	unsigned short int TheKindofBool = 0;

	//-----------------------------------
	/*BSTItrIn<Year> it(mieicYears);
	vector<Uc> ucs_aux;

	while (!it.isAtEnd()) {
	if (it.retrieve().getYear() == 2) {
	for (unsigned int j = 0; j < it.retrieve().getYearUcs().size(); j++)
	cout << it.retrieve().getYearUcs()[j].getVacancies() << endl;
	}
	it.advance();
	}*/

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
	cout << "\n Adress: " << TAB;
	getline(cin, NewAdress);
	cout << endl << "\n Contact: " << TAB;
	cin >> NewContact;

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

	int flag;
	int base_year = 1;
	vector<pair<int, int>> aux;

	for (unsigned int i = 0; i < TheNewCurrentUcs.size(); i++) {
		flag = 0;
		for (unsigned int j = 0; j < aux.size(); j++) {
			if (TheNewCurrentUcs[i].getYear() == aux[j].first) {
				flag = 1;
				aux[j].second++;
				break;
			}
		}
		if (flag == 0) {
			pair<int, int> newPair;
			newPair.first = TheNewCurrentUcs[i].getYear();
			newPair.second = 1;
			aux.push_back(newPair);
		}
	}
	pair<int, int> temp;
	temp.first = 0; temp.second = 0;

	for (unsigned int k = 0; k < aux.size(); k++) {
		if (aux[k].second > temp.second) {
			temp.first = aux[k].first;
			temp.second = aux[k].second;
		}
	}
	base_year = temp.first;

	//Choose Year
	int Year;

	if (TheNewCurrentUcs.empty())
	{
		Year = 0;
	}
	else
	{
		Year = TheNewCurrentUcs[0].getYear();
	}

	//Choose Class
	Student NewStudent(NewName, NewCode, Year, mieicYears[Year - 1].getClassesRaw().top().getNumber() + 1, NewStatute, NewAdress, NewContact, TheNewApprovedUcs, TheNewCurrentUcs, TheKindofBool);
	
	mieicYears[Year - 1].addStudentToClass(NewStudent);

	ListofStudents.push_back(NewStudent);
	StudentsChanged = true;
	cout << endl << endl << "Student added successfully" << endl << endl;

	distributeTutors();
}


void Mieic::showFirstYearClassesStudents() 
{

}


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


void Mieic::changeStudentFromList(long TheCode)
{
	try {
		unsigned int i;

		for (i = 0; i < ListofStudents.size(); i++)
		{
			if (ListofStudents[i].getCode() == TheCode)
			{
				string TheCase;
				cout << "What do you want to change regarding this Student? (Input 'A' for Adress or 'C' for Contact)" << endl << endl;
				cin >> TheCase;
				if (TheCase == "A" || TheCase == "a")
				{
					string NewAdress;
					cout << "Please type the new Adress of the Student:" << endl;
					cin.clear();
					cin.ignore(256, '\n');
					getline(cin, NewAdress);
					ListofStudents[i].setAdress(NewAdress);
					cout << "Student's Adress was changed successfully" << endl << endl;
					StudentsChanged = true;
					return;
				}
				else if (TheCase == "C" || TheCase == "c")
				{ 
					string NewContact;
					cout << "Please type the Student's new Contact:" << endl;
					cin >> NewContact;
					ListofStudents[i].setContact(NewContact);
					cout << "Student's Contact was changed successfully" << endl << endl;
					StudentsChanged = true;
					return;
				}
				else
				{
					cout << "The character you inputed was incorrect. Returning to the previous menu." << endl << endl;
					return;
				}
			}
		}
		throw EstudanteNaoExistente(TheCode);
	}
	catch (EstudanteNaoExistente &e) {
		cout << endl << endl << "Sorry! There was no student with the code: " << e.code << ". Please check if you have correctly written the student's code." << endl;
	}
}


void Mieic::changeStudentsFromHash(long TheCode)
{
	try 
	{
		StudentsHashTableIterator it1 = HashofStudents.begin();
		for (; it1 != HashofStudents.end(); ++it1)
		{
			if ((*it1).getCode() == TheCode)
			{
				string TheCase;
				cout << "What do you want to change regarding this Student? (Input 'A' for Adress or 'C' for Contact)" << endl << endl;
				cin >> TheCase;
				if (TheCase == "A" || TheCase == "a")
				{
					string NewAdress;
					cout << "Please type the new Adress of the Student:" << endl;
					cin.clear();
					cin.ignore(256, '\n');
					getline(cin, NewAdress);
					Student NewStudent = (*it1);
					HashofStudents.erase(it1);
					NewStudent.setAdress(NewAdress);
					HashofStudents.insert(NewStudent);
					cout << "Student's Adress was changed successfully" << endl << endl;
					StudentsChanged = true;
					return;
				}
				else if (TheCase == "C" || TheCase == "c")
				{
					string NewContact;
					cout << "Please type the Student's new Contact:" << endl;
					cin >> NewContact;
					Student NewStudent = (*it1);
					HashofStudents.erase(it1);
					NewStudent.setContact(NewContact);
					HashofStudents.insert(NewStudent);
					cout << "Student's Contact was changed successfully" << endl << endl;
					StudentsChanged = true;
					return;
				}
				else
				{
					cout << "The character you inputed was incorrect. Returning to the previous menu." << endl << endl;
					return;
				}
				break;
			}
		}
		throw EstudanteNaoExistente(TheCode);
	}
	catch (EstudanteNaoExistente &e) {
		cout << endl << endl << "Sorry! There was no student with the code: " << e.code << ". Please check if you have correctly written the student's code." << endl;
	}
}


void Mieic::StudentPassesUc(long aStudent)
{
	try {
		int i;
		int ListofStudentsSize = ListofStudents.size();
		for (i = 0; i < ListofStudentsSize; i++)
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

				if (ListofStudents[i].getApprovedUcs().size() == 47)
				{
					ListofStudents[i].setSomeKindofBool(1);
					HashofStudents.insert(ListofStudents[i]);
					ListofStudents.erase(ListofStudents.begin() + i);
					i--;

					distributeTutors();
					StudentsChanged = true;
					cout << "Student passed Uc Successfully!" << endl << "The Student Finished the Course!!" << endl << endl;
					break;
				}
				else
				{
					StudentsChanged = true;
					cout << "Student passed Uc Successfully!" << endl << endl;
					break;
				}
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


void Mieic::StudentInterruptsCourse(long aStudent)
{
	try 
	{
		int i;
		int ListofStudentsSize = ListofStudents.size();
		for (i = 0; i < ListofStudentsSize; i++)
		{
			if (ListofStudents[i].getCode() == aStudent)
			{
				ListofStudents[i].setAvailableCredits(75);
				vector <Uc> EmptyVector;
				ListofStudents[i].setCurrentUcs(EmptyVector);
				ListofStudents[i].setSomeKindofBool(2);
				HashofStudents.insert(ListofStudents[i]);
				ListofStudents.erase(ListofStudents.begin() + i);
				i--;

				mieicYears[ListofStudents[i].getYear()-1].removeStudent(aStudent, ListofStudents[i].getYearClass());

				distributeTutors();
				StudentsChanged = true;
				cout << "Student Interrupted the Course Successfully" << endl << endl;
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

					string TheActualAka;
					for (unsigned int b = 0; b < ListofStudents[i].getApprovedUcs().size(); b++)
					{
						TheActualAka = ListofStudents[i].getApprovedUcs()[b].getAka();
						unsigned int TheYear = GetTheYear(TheActualAka);

						if (MaxUcYear < TheYear)
						{
							MaxUcYear = TheYear;
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
					string TheActualAka;
					for (unsigned int m = 0; m < ListofStudents[i].getApprovedUcs().size(); m++)
					{
						TheActualAka = ListofStudents[i].getApprovedUcs()[m].getAka();
						unsigned int TheYear = GetTheYear(TheActualAka);

						if (MaxUcYear < TheYear)
						{
							MaxUcYear = TheYear;
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
					string TheActualAka;
					for (unsigned int c = 0; c < ListofStudents[TheStudentsIndex].getApprovedUcs().size(); c++)
					{
						TheActualAka = ListofStudents[TheStudentsIndex].getApprovedUcs()[c].getAka();
						unsigned int TheYear = GetTheYear(TheActualAka);

						if (MaxUcYear < TheYear)
						{
							MaxUcYear = TheYear;
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


unsigned int Mieic::GetTheYear(string TheAka)
{
	bool isThereUc = false;
	unsigned int TheYear;

	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		if (ListofRequiredUcs[i].getAka() == TheAka)
		{
			isThereUc = true;
			TheYear = ListofRequiredUcs[i].getYear();
			break;
		}
	}
	if (isThereUc == true)
	{
		return TheYear;
	}

	for (unsigned int j = 0; j < ListofOptionalUcs.size(); j++)
	{
		if (ListofOptionalUcs[j].getAka() == TheAka)
		{
			isThereUc = true;
			TheYear = ListofOptionalUcs[j].getYear();
			break;
		}
	}
	if (isThereUc == true)
	{
		return TheYear;
	}

	for (unsigned int k = 0; k < ListofUPortoUcs.size(); k++)
	{
		if (ListofUPortoUcs[k].getAka() == TheAka)
		{
			isThereUc = true;
			TheYear = ListofUPortoUcs[k].getYear();
			break;
		}
	}
	if (isThereUc == true)
	{
		return TheYear;
	}
	else
	{
		return 0;
	}
}


void Mieic::addHashRegistration(Date aDate, string aUc, long aStudent)
{
	unsigned int MaxUcYear = 0;
	bool isThereStudent = false;
	bool isThereUc = false;
	bool isUcApproved = false;
	bool isThereVacancies = true;
	bool isThereYear = false;

	StudentsHashTableIterator it1 = HashofStudents.begin();
	StudentsHashTableIterator it2 = HashofStudents.begin();

	for (; it1 != HashofStudents.end(); it1++)
	{
		if ((*it1).getCode() == aStudent)
		{
			isThereStudent = true;
			if ((*it1).getSomeKindofBool() == 1)
			{
				cout << "This Student has already finished the Course!" << endl << endl;
				return;
			}
			for (unsigned int j = 0; j < ListofRequiredUcs.size(); j++)
			{
				if (ListofRequiredUcs[j].getAka() == aUc)
				{
					isThereUc = true;
					isThereVacancies = true;

					for (unsigned int t = 0; t < (*it1).getApprovedUcs().size(); t++)
					{
						if ((*it1).getApprovedUcs()[t].getAka() == aUc)
						{
							isUcApproved = true;
							break;
						}
					}
					if (isUcApproved == true)
					{
						break;
					}

					string TheActualAka;
					for (unsigned int b = 0; b < (*it1).getApprovedUcs().size(); b++)
					{
						TheActualAka = (*it1).getApprovedUcs()[b].getAka();
						unsigned int TheYear = GetTheYear(TheActualAka);

						if (MaxUcYear < TheYear)									
						{
							MaxUcYear = TheYear;
						}

					}
					if ((MaxUcYear + 1) >= ListofRequiredUcs[j].getYear())
					{
						isThereYear = true;
						Registration NewRegistration(aDate, aUc, aStudent);
						ListofRegistrations.push_back(NewRegistration);
						Uc NewUc(aUc);
						Student NewStudent = (*it1);
						HashofStudents.erase(it1);
						NewStudent.addCurrentUc(aUc);
						NewStudent.setAvailableCredits(NewStudent.getAvailableCredits() - ListofRequiredUcs[j].getECTS());
						NewStudent.setSomeKindofBool(0);

						mieicYears[NewStudent.getYear() - 1].addStudentToClass(NewStudent);

						ListofStudents.push_back(NewStudent);
						distributeTutors();
						StudentsChanged = true;
						RegistrationsChanged = true;
					}
					else
					{
						break;
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

					for (unsigned int s = 0; s < (*it1).getApprovedUcs().size(); s++)
					{
						if ((*it1).getApprovedUcs()[s].getAka() == aUc)
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
					string TheActualAka;
					for (unsigned int m = 0; m < (*it1).getApprovedUcs().size(); m++)
					{
						TheActualAka = (*it1).getApprovedUcs()[m].getAka();
						unsigned int TheYear = GetTheYear(TheActualAka);

						if (MaxUcYear < TheYear)
						{
							MaxUcYear = TheYear;
						}

					}

					if (ListofOptionalUcs[w].getVacancies() >= 1)
					{
						if ((MaxUcYear + 1) >= ListofOptionalUcs[w].getYear())
						{
							isThereYear = true;
							Registration NewRegistration(aDate, aUc, aStudent);
							ListofRegistrations.push_back(NewRegistration);
							Uc NewUc(aUc);
							Student NewStudent = (*it1);
							HashofStudents.erase(it1);
							NewStudent.addCurrentUc(aUc);
							NewStudent.setAvailableCredits(NewStudent.getAvailableCredits() - ListofRequiredUcs[w].getECTS());
							NewStudent.setSomeKindofBool(0);
							ListofStudents.push_back(NewStudent);
							distributeTutors();
							StudentsChanged = true;
							RegistrationsChanged = true;
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
	else if (isThereStudent == true && isThereUc == true && isUcApproved == true)
	{
		cout << "That Student is already approved to that Uc" << endl;
	}

	else if (isThereStudent == true && isThereUc == true && isUcApproved == false && isThereVacancies == false)
	{
		string answer;
		isThereUc = false;
		cout << "The Uc does not have any more vancancies left" << endl << endl << "Would you like to register to another Uc from UP? (Y for yes, N for no) ";
		cin >> answer;
		while (answer != "Y" && answer != "y" && answer != "n" && answer != "N")
		{
			if (answer == "Y" || answer == "y")
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

						for (unsigned int v = 0; v < (*it1).getApprovedUcs().size(); v++)
						{
							if ((*it1).getApprovedUcs()[v].getAka() == aUc)
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
						string TheActualAka;
						for (unsigned int c = 0; c < (*it1).getApprovedUcs().size(); c++)
						{
							TheActualAka = (*it1).getApprovedUcs()[c].getAka();
							unsigned int TheYear = GetTheYear(TheActualAka);

							if (MaxUcYear < TheYear)
							{
								MaxUcYear = TheYear;
							}

						}

						if ((MaxUcYear + 1) >= ListofUPortoUcs[h].getYear())
						{
							isThereYear = true;
							Registration NewRegistration(aDate, aUc, aStudent);
							ListofRegistrations.push_back(NewRegistration);
							Uc NewUc(aUc);
							Student NewStudent = (*it1);
							HashofStudents.erase(it1);
							NewStudent.addCurrentUc(aUc);
							NewStudent.setAvailableCredits(NewStudent.getAvailableCredits() - ListofRequiredUcs[h].getECTS());
							NewStudent.setSomeKindofBool(0);
							ListofStudents.push_back(NewStudent);
							distributeTutors();
							StudentsChanged = true;
							RegistrationsChanged = true;
						}
					}
				}

				if (isThereStudent == true && isThereUc == false)
				{
					cout << "There isn't such Uc" << endl;
				}
				else if (isThereStudent == true && isThereUc == true && isUcApproved == true)
				{
					cout << "That Student is already approved to that Uc" << endl;
				}
				else if (isThereStudent == true && isThereUc == true && isUcApproved == false && isThereVacancies == true && isThereYear == false)
				{
					cout << "That Uc's year is too advanced for that Student." << endl;
				}
				else if (isThereStudent == true && isThereUc == true && isUcApproved == false && isThereVacancies == true && isThereYear == true)
				{
					cout << "Registration Successfull!" << endl;
				}
			}
			else if (answer == "N" || answer == "n")
			{
				cout << "No Registration made";
			}
			else
			{
				cout << "Incorrect character inputed. Please input 'Y' for Yes or 'N' for No" << endl << endl;
			}
		}
	}

	else if (isThereStudent == true && isThereUc == true && isUcApproved == false && isThereVacancies == true && isThereYear == false)
	{
		cout << "That Uc's year is too advanced for that Student." << endl;
	}
	else if (isThereStudent == true && isThereUc == true && isUcApproved == false && isThereVacancies == true && isThereYear == true)
	{
		cout << "Registration Successfull!" << endl;
	}

}


void Mieic::addClass() {

	int Year;
	int Size;

	cout << TAB_BIG << "New Class:\n";
	cout << endl << " Please Input the New Class's Information: " << endl << endl << "  Year:" << TAB;
	cin >> Year;
	cout << endl << " Size: " << TAB;
	cin >> Size;

	int HighestClassNumber = 0;
	for (size_t i = 0; i < mieicYears[Year - 1].getClasses().size(); i++)
	{
		if (mieicYears[Year - 1].getClasses()[i].getNumber() > HighestClassNumber)
		{
			HighestClassNumber = mieicYears[Year - 1].getClasses()[i].getNumber();
		}
	}

	HighestClassNumber++;

	priority_queue<Student> students;

	vector<Uc> ucs;

	for (unsigned int j = 0; j < ListofRequiredUcs.size(); j++) {
		if (ListofRequiredUcs[j].getYear() == Year)
			ucs.push_back(ListofRequiredUcs[j]);
	}

	Class a(HighestClassNumber, Year, Size, students, ucs);

	mieicYears[Year - 1].addNewClass(a);

	a.setYear(a.getYear() - 1);

	ListofClasses.push_back(a);
	cout << TAB_BIG << TAB_BIG << "Class added successfully! " << endl << endl << endl;

	ClassesChanged = true;

}


void Mieic::removeClass() {

	int Year;
	int Number;

	cout << TAB_BIG << "Class to remove:\n";
	cout << endl << " Please Input the information of the Class you wish to remove: " << endl << endl << "  Year:" << TAB;
	cin >> Year;
	cout << endl << " Number: " << TAB;
	cin >> Number;

	mieicYears[Year - 1].RedistributeAndDelete(Number);

	vector<Student> StudentAux;
	for (size_t i = 0; i < ListofStudents.size(); i++)
	{
		for (size_t j = 0; j < mieicYears[Year - 1].getClasses().size(); j++)
		{
			for (size_t h = 0; h < mieicYears[Year - 1].getClasses()[j].getStudents().size(); h++)
			{
				if (ListofStudents[i].getCode() == mieicYears[Year - 1].getClasses()[j].getStudents()[h].getCode()) {
					ListofStudents[i].setYearClass(mieicYears[Year - 1].getClasses()[j].getNumber() + 1);
				}
			}
		}
	}

	for (size_t i = 0; i < ListofClasses.size(); i++)
	{
		if (ListofClasses[i].getNumber() == Number - 1 && ListofClasses[i].getYear() == Year - 1) {
			ListofClasses.erase(ListofClasses.begin() + i);
			cout << TAB_BIG << TAB_BIG << "Class removed successfully! " << endl << endl << endl;
			break;
		}
	}

	StudentsChanged = true;
	ClassesChanged = true;

}


void Mieic::showListofRUcs()
{
	cout << "List of Required Mieic Ucs:" << endl << endl;
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS()  << endl;
	}
	cout << endl << endl;
}


void Mieic::showListofOUcs()
{
	cout << "List of Optional Mieic Ucs:" << endl << endl;
	for (unsigned int i = 0; i < ListofOptionalUcs.size(); i++)
	{
		cout << ListofOptionalUcs[i].getName() << " (" << ListofOptionalUcs[i].getAka() << "):\n\tYear: " << ListofOptionalUcs[i].getYear() << "\n\tSemester: " << ListofOptionalUcs[i].getSemester() << "\n\tCredits: " << ListofOptionalUcs[i].getECTS() << "\n\tVacancies: " << ListofOptionalUcs[i].getVacancies() <<  endl;
	}
}


void Mieic::showListofUPortoUcs()
{
	cout << "List of other U.Porto Ucs:" << endl << endl;
	for (unsigned int i = 0; i < ListofUPortoUcs.size(); i++)
	{
		cout << ListofUPortoUcs[i].getName() << " (" << ListofUPortoUcs[i].getAka() << "):\n\tYear: " << ListofUPortoUcs[i].getYear() << "\n\tSemester: " << ListofUPortoUcs[i].getSemester() << "\n\tCredits: " << ListofUPortoUcs[i].getECTS() << endl;
	}
}


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


void Mieic::showSearchUC(string AKA) {
	bool found = false;
	cout << "\n";
	for (unsigned int i = 0; i < ListofRequiredUcs.size(); i++)
	{
		if (AKA == ListofRequiredUcs[i].getAka())
		{
			found = true;
			cout << ListofRequiredUcs[i].getName() << " (" << ListofRequiredUcs[i].getAka() << "):\n\tYear: " << ListofRequiredUcs[i].getYear() << "\n\tSemester: " << ListofRequiredUcs[i].getSemester() << "\n\tCredits: " << ListofRequiredUcs[i].getECTS() << endl << endl << endl;
			break;
		}
	}
	for (unsigned int i = 0; i < ListofOptionalUcs.size() && !found; i++)
	{
		if (AKA == ListofOptionalUcs[i].getAka())
		{
			found = true;
			cout << ListofOptionalUcs[i].getName() << " (" << ListofOptionalUcs[i].getAka() << "):\n\tYear: " << ListofOptionalUcs[i].getYear() << "\n\tSemester: " << ListofOptionalUcs[i].getSemester() << "\n\tCredits: " << ListofOptionalUcs[i].getECTS() << "\n\tVacancies: " << ListofOptionalUcs[i].getVacancies() << endl<< endl << endl;
			break;
		}
	}
	for (unsigned int i = 0; i < ListofUPortoUcs.size() && !found; i++)
	{
		if (AKA == ListofUPortoUcs[i].getAka())
		{
			found = true;
			cout << ListofUPortoUcs[i].getName() << " (" << ListofUPortoUcs[i].getAka() << "):\n\tYear: " << ListofUPortoUcs[i].getYear() << "\n\tSemester: " << ListofUPortoUcs[i].getSemester() << "\n\tCredits: " << ListofUPortoUcs[i].getECTS() << endl << endl << endl;
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


void Mieic::showListofTutors()
{
	cout << "List of Tutors:" << endl << endl;

	for (unsigned int i = 0; i < ListofTutors.size(); i++)
	{
		cout << ListofTutors[i].getName() << endl;
	}
}


void Mieic::showListofStudents()
{
	cout << TAB_BIG << "List of Students:" << endl << endl;

	sort(ListofStudents.begin(), ListofStudents.end());			//Ordena os alunos de ordem alfabética

	for (unsigned int i = 0; i < ListofStudents.size(); i++)
	{
		cout << ListofStudents[i].getName() << ", " << ListofStudents[i].getCode() << ", " << ListofStudents[i].getEmail() << "; " << ListofStudents[i].getAdress() << "; " << ListofStudents[i].getContact() << "; " << ListofStudents[i].getStatute() << endl << "Approved Uc's: " << ListofStudents[i].showApprovedUcs() << endl << "Current Uc's: " << ListofStudents[i].showCurrentUcs() << endl << "Tutor : " << ListofStudents[i].getTutor() << endl << endl << endl;
	}
}


void Mieic::showListofIorTStudents()
{
	cout << TAB_BIG << "List of Students of Interrupted or Completed the Course:" << endl << endl;
	StudentsHashTableIterator it1 = HashofStudents.begin();

	for (; it1 != HashofStudents.end(); it1++)
	{
		Student TheStudent = (*it1);
		cout << TheStudent.getName() << ", " << TheStudent.getCode() << ", " << TheStudent.getEmail() << "; " << TheStudent.getAdress() << "; " << TheStudent.getContact() << endl << "Approved Uc's: " << TheStudent.showApprovedUcs() << endl;
		if (TheStudent.getSomeKindofBool() == 1)
		{
			cout << "Estado: Terminou" << endl << endl << endl;
		}
		else if (TheStudent.getSomeKindofBool() == 2)
		{
			cout << "Estado: Interrompeu" << endl << endl << endl;
		}
	}
}


void Mieic::showInfoStudent(long code)
{
	bool isThereStudent = false;
	StudentsHashTableIterator it1 = HashofStudents.begin();
	unsigned int i;
	try {
		for (i = 0; i < ListofStudents.size(); i++)
		{
			if (ListofStudents[i].getCode() == code)
			{
				isThereStudent = true;
				cout << endl << endl << endl << "Name:" << TAB << ListofStudents[i].getName() << "\nCode:" << TAB << ListofStudents[i].getCode() << "\nE-mail:" << TAB <<
					ListofStudents[i].getEmail() << "\nAdress:" << TAB << ListofStudents[i].getAdress() << "\nContact:" << TAB << ListofStudents[i].getContact() << "\nApproved UC's: " <<
					TAB << ListofStudents[i].showApprovedUcs() << endl << "Current Uc's: " << TAB << ListofStudents[i].showCurrentUcs() << endl << 
					"Available Credits: " << TAB << ListofStudents[i].getAvailableCredits() << endl;
				break;
			}
		}
		if (isThereStudent == false)
		{
			for (; it1 != HashofStudents.end(); it1++)
			{
				if ((*it1).getCode() == code)
				{
					isThereStudent = true;
					Student TheStudent = (*it1);
					cout << endl << endl << endl << "Name:" << TAB << TheStudent.getName() << "\nCode:" << TAB << TheStudent.getCode() << "\nE-mail:" << TAB <<
						TheStudent.getEmail() << "\nAdress:" << TAB << TheStudent.getAdress() << "\nContact:" << TAB << TheStudent.getContact() << "\nApproved UC's: " << TAB <<
						TheStudent.showApprovedUcs() << endl << "Current Uc's: " << TAB << TheStudent.showCurrentUcs() << endl << "Available Credits: " << TAB <<
						TheStudent.getAvailableCredits() << endl;
					if (TheStudent.getSomeKindofBool() == 1)
					{
						cout << TAB << "Estado: Terminou" << endl << endl << endl;
					}
					else if (TheStudent.getSomeKindofBool() == 2)
					{
						cout << TAB << "Estado: Interrompeu" << endl << endl << endl;
					}
					break;
				}
			}
		}
		if (i == ListofStudents.size() && it1 == HashofStudents.end())
			throw EstudanteNaoExistente(code);   //cout << "Sorry! There were no matches. Please check if you have correctly written the student's code." << endl;
	}
	catch (EstudanteNaoExistente& e) 
	{
		(void)e;
		cout << endl << endl << 
			"Error! Please check if you have correctly written the student's code." << endl;
	}
}


void Mieic::showListofRegistrations()
{
	cout << "List of Registrations:" << endl << endl;

	for (unsigned int i = 0; i < ListofRegistrations.size(); i++)
	{
		cout << "Student's Code: " << ListofRegistrations[i].getStudentCode() << ", Uc: " << ListofRegistrations[i].getUcAka() << ", Data: " << ListofRegistrations[i].getDate() << endl;
	}
}


void Mieic::showListofClasses() {

	for (size_t i = 0; i < mieicYears.size(); i++)
	{

		cout << TAB_BIG << "Year " << i + 1 << ":\n\n";

		for (size_t j = 0; j < mieicYears[i].getClasses().size(); j++)
		{
			int vacancies = mieicYears[i].getClasses()[j].getnStudents() - mieicYears[i].getClasses()[j].getStudents().size();
			cout << TAB << "- Number: " << mieicYears[i].getClasses()[j].getNumber() + 1 << "  Vacancies: " << vacancies << "/" << mieicYears[i].getClasses()[j].getnStudents() << "\n\tList of Students:\n";
			for (size_t h = 0; h < mieicYears[i].getClasses()[j].getStudents().size(); h++)
			{
				cout << "\t\t- " << mieicYears[i].getClasses()[j].getStudents()[h].getCode() << "\n";
			}
			cout << "\n";
		}
		cout << "\n";

	}

}


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

		stringstream ss2;
		StudentsHashTableIterator it1 = HashofStudents.begin();
		for (; it1 != HashofStudents.end(); ++it1)
		{
			if (it1 != HashofStudents.begin())
				ss2 << endl;
			ss2 << (*it1);
		}
		string newStudentsHash = ss2.str();
		ofstream OStudentsHash("StudentsHash.txt");
		OStudentsHash << newStudentsHash;
		OStudentsHash.close();
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


	if (ClassesChanged == true)		//se ClassesChanged estiver "true" a função passa tudo o que o vector contém para uma string
	{									//e copia a string para o ficheiro original, apagando a informação antiga
		stringstream ss;
		for (size_t i = 0; i < ListofClasses.size(); ++i)
		{
			if (i != 0)
				ss << endl;
			ss << ListofClasses[i];
		}
		string newClasses = ss.str();
		ofstream OClasses("Classes.txt");
		OClasses << newClasses;
		OClasses.close();
	}


}

void Mieic::showTutorReunions() {
	string AName;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "Change Reunion's Description" << endl;
	cout << endl << TAB_BIG << "Please enter the name of the Tutor you would like to see the reunions:" << TAB;
	getline(cin, AName);
	try {
		int flag = 0;
		for (unsigned int i = 0; i < ListofTutors.size(); i++) {
			if (ListofTutors[i].getName() == AName) {
				ListofTutors[i].showReunions(AName);
				flag = 1;
			}
		}
		if (flag == 0)
			throw TutorNaoExistente(AName);
	}
	catch (TutorNaoExistente& e) {
		cout << endl << endl << "There is no tutor with the name: " << e.nome
			<< ". Please check if you have spelled the tutor's name correctly." << endl << endl;
	}
}