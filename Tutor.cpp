#include "Tutor.h"

using namespace std;


unsigned int Tutor::NumberofTutors = 0;
unsigned int Tutor::MinStudents = 0;


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


Reunion::Reunion(Date date, long id, vector<string> topics, string description) :
	reunionDate(date), studentCode(id), reunionTopics(topics), reunionDescription(description) { }


bool Reunion::operator <(const Reunion& r1) const {
	if (this->reunionDate == r1.getReunionDate())
		return this->studentCode < r1.getStudentCode();
	return this->reunionDate < r1.getReunionDate();
}


bool Reunion::operator ==(const Reunion&r1) const {
	return this->reunionDate == r1.getReunionDate();
}


void Tutor::addReunion(string tutorName) {
	long code;
	vector<string> topics;  //topic1 -- topics[0] , topic2 -- topics[1] etc
	string date, topics_aux, description;

	cout << endl << "Date of the reunion:  ";
	cin >> date;
	cout << endl << "Student's ID code:   ";								//VERIFICAR O ID DO STUDENT??
	cin >> code;
	cout << endl << "Reunion's description:   ";
	cin >> description;
	cout << endl << "Reunion's topics:(enter <done> to exit)  ";

	for (unsigned int i = 1;; i++) {
		cout << "\t" << i << ". ";
		cin >> topics_aux;
		cout << endl << "\t\t";
		if (topics_aux == "done")
			break;
		else {
			topics.push_back(topics_aux);
		}

	}

	Reunion r(Date(date), code, topics, description);			//constructor vector<string>
	tutorReunions.insert(r);

	/*BSTItrIn<Reunion> it(tutorReunions);

	while (!it.isAtEnd()) {
	for (unsigned int j = 0; j < it.retrieve().getReunionTopics().size(); j++)
	cout << it.retrieve().getReunionTopics()[j] << endl;					//PARA TESTAR A VER SE A ARVORE ESTA A FUNCIONAR BEM
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

		int StudentReuniousSize = student_reunions.size();

		if (option >= 1 && option <= StudentReuniousSize) {
			BSTItrIn<Reunion> iterador(tutorReunions);

			while (!iterador.isAtEnd()) {
				if (iterador.retrieve().getStudentCode() == student_reunions[option - 1].getStudentCode() &&
					iterador.retrieve().getReunionDate() == student_reunions[option - 1].getReunionDate()) {
					tutorReunions.remove(iterador.retrieve());
					break;
				}
				iterador.advance();
			}
		}
		else
			cout << "Your input was not recognized." << endl;
	}


	/*BSTItrIn<Reunion> iter(tutorReunions);					//this is just to test if the bst is working properly
	while (!iter.isAtEnd()) {
	cout << iter.retrieve().getReunionDate() << endl;
	iter.advance();
	}*/

	student_reunions.clear();
}


void Tutor::changeReunionDescription(string tutorName) {
	int option;
	long studentID;
	BSTItrIn<Reunion> it(tutorReunions);
	vector<Reunion> student_reunions;

	cout << "\nEnter the student's code of wich you would like to change the reunion's description:   ";
	cin >> studentID;

	while (!it.isAtEnd()) {
		if (it.retrieve().getStudentCode() == studentID)
			student_reunions.push_back(it.retrieve());
		it.advance();
	}

	if (student_reunions.size() == 0)
		cout << "The student " << studentID << " does not have any schedule reunion with the tutor." << endl;
	else {
		cout << endl << "The student " << studentID <<
			" has " << student_reunions.size() << " reunions.\n\n\tPlease choose the one you would like to change the description:\n";

		for (unsigned int j = 0; j < student_reunions.size(); j++) {
			cout << "\t\t" << j + 1 << ". Date: " << student_reunions[j].getReunionDate() << endl << endl;
		}
		cout << "\t\t>>>>\t";
		cin >> option;

		int StudentReunionsSize = student_reunions.size();

		if (option >= 1 && option <= StudentReunionsSize) {
			BSTItrIn<Reunion> it(tutorReunions);
			string new_description;

			cout << "\n\tReunion's Description:\t" << student_reunions[option - 1].getReunionDescription() << endl;

			cout << "\n\tThis reunion's topics are:\n";
			for (unsigned int j = 0; j < student_reunions[option - 1].getReunionTopics().size(); j++) {
				cout << "\t\t\t" << j + 1 << ". " << student_reunions[option - 1].getReunionTopics()[j] << endl;
			}

			cout << "\nNew Reunion Description:\t";
			cin >> new_description;

			student_reunions[option - 1].setReunionDescription(new_description);

			while (!it.isAtEnd()) {
				if (it.retrieve().getReunionDate() == student_reunions[option - 1].getReunionDate()) {
					tutorReunions.remove(it.retrieve());
					break;
				}
				it.advance();
			}
			tutorReunions.insert(student_reunions[option - 1]);

		}
		else
			cout << "Your input was not recognized." << endl;
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

void Tutor::showReunions(string tutorName) {
	BSTItrIn<Reunion> it(tutorReunions);
	int n = 1;

	cout << "\t\tThe Tutor " << tutorName << " reunions are:\n" << endl << endl;

	if (it.isAtEnd())
		cout << "\t\t" << tutorName << " has no reunions." << endl;
	else {
		while (!it.isAtEnd()) {
			cout << "\t\t\t" << n << ". " << it.retrieve().getStudentCode() << "\t" << it.retrieve().getReunionDate() << " " << it.retrieve().getReunionDescription() << endl;
			it.advance();
			n++;
		}
	}
}