#include "Student.h"

using namespace std;

unsigned int Student::NumberofStudents = 0;



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

	setYear(stoi(line.substr(0, line.find(";"))));
	line = line.substr(line.find(";") + 2);
	setYearClass(stoi(line.substr(0, line.find(";"))));
	line = line.substr(line.find(";") + 2);

	setAdress(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setContact(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setStatute(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setApprovedUcs(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setCurrentUcs(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setAvailableCredits(stof(line.substr(0, line.find(";"))));
	line = line.substr(line.find(";") + 2);
	setTutor(line.substr(0, line.find(";")));
	line = line.substr(line.find(";") + 2);
	setSomeKindofBool(stoi(line));
}


Student::Student(string AName, long TheCode, int Year, int YearClass, string TheStatute, string TheAdress, string TheContact, vector<Uc> TheApprovedUcs, vector<Uc> TheCurrentUcs, unsigned short int TheKindofBool)
{
	Code = TheCode;
	Name = AName;
	Email = "up" + to_string(TheCode) + "@fe.up.pt";
	Statute = TheStatute;
	Adress = TheAdress;
	Contact = TheContact;
	NumberofStudents++;
	ApprovedUcs = TheApprovedUcs;
	CurrentUcs = TheCurrentUcs;
	SomeKindofBool = TheKindofBool;
	AvailableCredits = 75;
	for (unsigned int i = 0; i < CurrentUcs.size(); i++)
	{
		AvailableCredits = AvailableCredits - CurrentUcs[i].getECTS();
	}
	this->Year = Year;
	this->YearClass = YearClass;
}


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


void Student::addCurrentUc(string TheUc)
{
	Uc NewUc(TheUc);
	CurrentUcs.push_back(NewUc);
}


void Student::setTutor(Tutor Tutor) {
	TheTutor = Tutor;
}


void Student::setTutor(string Name) {
	TheTutor = Tutor(Name);
}


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


bool Student::operator < (const Student & s2) const  //Used somewhere.
{
	return this->Name < s2.getName();
}


void Student::Save(ofstream & out) const
{
	out << Name << " ; " << Code << " ; " << Email;// << " ; " << Creditos....etc 	//Not used so far
}


ostream& operator <<(ostream& out, const Student & TheStudent)
{
	out << TheStudent.Name << "; " << TheStudent.Code << "; " << TheStudent.Email << "; " << TheStudent.getYear() << "; " << TheStudent.getYearClass() << "; " << TheStudent.Adress << "; " << TheStudent.Contact << "; " << TheStudent.getStatute() << "; ";
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
	out << "; " << TheStudent.getSomeKindofBool();
	return out;
}


bool operator==(const Student &Student1, const Student &Student2)	// Not used so far
{
	if (Student1.Code == Student2.Code)
	{
		return true;
	}
	else
	{
		return false;
	}
}