#include "Tutor.h"

using namespace std;


unsigned int Tutor::NumberofTutors = 0;
unsigned int Tutor::MinStudents = 0;

Reunion::Reunion(Date date, long id, string topics, string description) :  
reunionDate(date), studentCode(id), reunionTopics(topics), reunionDescription(description) { }

bool Reunion::operator <(const Reunion& r1) const {
	if (this->reunionDate == r1.getReunionDate())
		return this->studentCode < r1.getStudentCode();
	return this->reunionDate < r1.getReunionDate();
}

bool Reunion::operator ==(const Reunion&r1) const {
	return this->reunionDate == r1.getReunionDate();
}

Tutor::Tutor(ifstream & In) : tutorReunions(Reunion())
{
	string line;
	getline(In, line);
	setName(line);
	NStudents = 0;
	NumberofTutors++;
}


Tutor::Tutor(string TheName) : tutorReunions(Reunion())
{
	Name = TheName;
	NStudents = 0;
	NumberofTutors++;
}

void Tutor::addReunion(string tutorName) {
	long code;
	//vector<string> topics;  topic1 -- topics[0] , topic2 -- topics[1] etc
	string date, topics, description;
	
	cout << endl << "Date of the reunion:  ";
	cin >> date;
	cout << endl << "Student's ID code:   ";								//VERIFICAR O ID DO STUDENT??
	cin >> code;
	cout << endl << "Reunion's description:   ";
	cin >> description;
	cout << endl << "Reunion's topics:   ";
	cin >> topics;

	Reunion r(Date(date), code, topics, description);
	tutorReunions.insert(r);

	BSTItrIn<Reunion> it(tutorReunions);

/*	while (!it.isAtEnd()) {										//PARA TESTAR A VER SE A ARVORE ESTA A FUNCIONAR BEM
		cout << it.retrieve().getStudentCode();
		it.advance();
	}*/
}

void Tutor::removeReunion(string tutorName) {
	int option;
	long studentID;
	BSTItrIn<Reunion> it(tutorReunions);
	BSTItrIn<Reunion> it2(tutorReunions);
	vector<Reunion> student_reunions;
	
	cout << "\nEnter the student's code you would like to cancel the reunion:   ";
	cin >> studentID;																	//VERIFICAR!!

	while (!it.isAtEnd()) {
		if (it.retrieve().getStudentCode() == studentID) {
			student_reunions.push_back(it.retrieve());
			//tutorReunions.remove(it.retrieve());
		}
		it.advance();
	}

	if (student_reunions.size() == 0)
		cout << "The student " << studentID << " does not have any schedule reunion with the tutor." << endl;
	else {
		cout << endl << "The student " << studentID <<
			" has " << student_reunions.size() << " reunions.\n\n\tPlease choose the one you would like to remove:\n";

		for (unsigned int j = 0; j < student_reunions.size(); j++) {
			cout << "\t\t" << j + 1 << ". Date: " << student_reunions[j].getReunionDate() << endl;
		}
		cout << "\t\t>>>>\t";
		cin >> option;

		if (option >= 1 && option <= student_reunions.size()) {
			BSTItrIn<Reunion> iterador(tutorReunions);

			while (!iterador.isAtEnd()) {
				if (iterador.retrieve().getStudentCode() == student_reunions[option - 1].getStudentCode() &&
					iterador.retrieve().getReunionDate() == student_reunions[option-1].getReunionDate()) {
					tutorReunions.remove(iterador.retrieve());
					break;
				}
				iterador.advance();
			}
		}
		else
			cout << "Your input was not recognized." << endl;
	}


	BSTItrIn<Reunion> iter(tutorReunions);					//this is just to test if the bst is working properly
	while (!iter.isAtEnd()) {
		cout << iter.retrieve().getReunionDate() << endl;
		iter.advance();
	}

	student_reunions.clear();

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

