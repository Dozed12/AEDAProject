#pragma once

#include "Mieic.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


unsigned short int InicialMenu();					//Funcao que apresenta o Menu inicial

void InicialOptions(Mieic & TheCourse);				//Funcao que direciona a escolha do utilizador para a funcionalidade de Menu respetiva

unsigned short int StudentManagmentMenu();

void StudentManagmentOptions(Mieic & TheCourse);

unsigned short int UcManagmentMenu();

void UcManagmentOptions(Mieic & TheCourse);

unsigned short int TutorManagmentMenu();

void TutorManagmentOptions(Mieic & TheCourse);

unsigned short int RegistrationManagmentMenu();

void RegistrationManagmentOptions(Mieic & TheCourse);

unsigned short int ClassManagmentMenu();

void ClassManagmentOptions(Mieic & TheCourse);