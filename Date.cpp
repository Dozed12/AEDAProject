/**********************************************************************************************//**
 * \file	Date.cpp
 *
 * \brief	Implements the date class.
 **************************************************************************************************/

#include "Date.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/**********************************************************************************************//**
 * \fn	Date::Date(string TheDate)
 *
 * \brief	Constructor.
 *
Constructs new Date while checking for invalid dates
 *
 * \param	TheDate	the date.
 **************************************************************************************************/

Date::Date(string TheDate)
{
	Day = stoi(TheDate.substr(0, TheDate.find("/")));		//Mover para dia o Dia do existente na string
	while (Day > 31)								//Teste que avalia a variavel dia e, se esta for maior que 31, envia uma mensagem de erro e pede um novo Dia
	{
		Day = NULL;
		cout << "Dia introduzido invalido (Maior que 31). Por favor introduza um dia valido." << endl;
		cout << "Dia: ";
		cin >> Day;
	}

	TheDate = TheDate.substr(TheDate.find("/") + 1);			//"Atualizar" a string data (de modo a que seja retirada da string a informacao que ja foi assimilada)
	Month = stoi(TheDate.substr(0, TheDate.find("/")));		//Mover para mes o Mes existente na string

	while (Month > 12)								//Teste que avalia a variavel mes e, se esta for maior que 12, envia uma mensagem de erro e pede um novo Mes
	{
		Month = NULL;
		cout << "Mes introduzido invalido (Maior que 12). Por favor introduza um mes valido." << endl;
		cout << "Mes: ";
		cin >> Month;
	}
	while ((Day > 29) && (Month == 2))				//Teste que avalia a variavel mes e a variavel dia e, se o dia for maior que 29 e o mes maior igual a 2, 
	{												//envia uma mensagem de erro e pede um novo Mes
		Month = NULL;
		cout << "Mes introduzido invalido (O mes 2 nao tem o dia especificado). Por favor introduza um mes valido." << endl;
		cout << "Mes: ";
		cin >> Month;
	}
	while ((Day > 30) && (Month == 4 || Month == 6 || Month == 9 || Month == 11))	//Teste que avalia as variaveis mes e dia e, se o dia for maior que 30, e se se tratarem de
	{																		//meses que so devem ter, no maximo, 30 dias, envia um mesagem de erro e pede um novo Mes
		Month = NULL;
		cout << "Mes introduzido invalido (O mes especificado nao tem 31 dias). Por favor introduza um mes valido." << endl;
		cout << "Mes: ";
		cin >> Month;
	}

	TheDate = TheDate.substr(TheDate.find("/") + 1);				//"Atualizar" a string data
	Year = stoi(TheDate);									//Mover para ano o Ano existente na string
	while (Year < 1926)									//Assumir um limite inferior para as datas; neste caso pode-se considerar 01/01/2000 como a Data da inauguracao
	{													//Teste que avalia a variavel ano e, se esta for menor que 2000, envia uma mensagem de erro e pede um novo Ano
		Year = NULL;
		cout << "Ano introduzido invalido (A FEUP apenas foi inaugurada em 1926). Por favor introduza um Ano valido." << endl;
		cout << "Ano: ";
		cin >> Year;
	}
}

/**********************************************************************************************//**
 * \fn	int Date::getDia() const
 *
 * \brief	Gets the dia.
 *
 *
 * \return	The dia.
 **************************************************************************************************/

int Date::getDia() const { return Day; }

/**********************************************************************************************//**
 * \fn	int Date::getMes() const
 *
 * \brief	Gets the mes.
 *
 *
 * \return	The mes.
 **************************************************************************************************/

int Date::getMes() const { return Month; }

/**********************************************************************************************//**
 * \fn	int Date::getAno() const
 *
 * \brief	Gets the ano.
 *
 *
 * \return	The ano.
 **************************************************************************************************/

int Date::getAno() const { return Year; }

/**********************************************************************************************//**
 * \fn	void Date::setDia(unsigned int NewDay)
 *
 * \brief	Sets a dia.
 *
 *
 * \param	NewDay	The new day.
 **************************************************************************************************/

void Date::setDia(unsigned int NewDay)
{
	Day = NewDay;
	while (Day > 31)			//Teste que avalia a variavel dia e, se esta for maior que 31, envia uma mensagem de erro e pede um novo Dia
	{
		Day = NULL;
		cout << "Dia introduzido invalido. Por favor introduza um dia valido." << endl;
		cout << "Dia: ";
		cin >> Day;
	}
}

/**********************************************************************************************//**
 * \fn	void Date::setMes(unsigned int NewMonth)
 *
 * \brief	Sets the mes.
 *
 *
 * \param	NewMonth	The new month.
 **************************************************************************************************/

void Date::setMes(unsigned int NewMonth)
{
	Month = NewMonth;
	while (NewMonth > 12)		//Teste que avalia a variavel mes e, se esta for maior que 12, envia uma mensagem de erro e pede um novo Mes
	{
		Month = NULL;
		cout << "Mes introduzido invalido (Maior que 12). Por favor introduza um mes valido." << endl;
		cout << "Mes: ";
		cin >> Month;
	}
	while ((Day > 29) && (Month == 2))		//Teste que avalia a variavel mes e a variavel dia e, se o dia for maior que 29 e o mes maior igual a 2, 
	{										//envia uma mensagem de erro e pede um novo Mes
		Month = NULL;
		cout << "Mes introduzido invalido (O mes 2 nao tem o dia especificado). Por favor introduza um mes valido." << endl;
		cout << "Mes: ";
		cin >> Month;
	}
	while ((Day > 30) && (Month == 4 || Month == 6 || Month == 9 || Month == 11))		//Teste que avalia as variaveis mes e dia e, se o dia for maior que 30, e se se tratarem de																	//meses que so devem ter, no maximo, 30 dias, envia um mesagem de erro e pede um novo Mes
	{																			//meses que so devem ter, no maximo, 30 dias, envia um mesagem de erro e pede um novo Mes
		Month = NULL;
		cout << "Mes introduzido invalido (O mes especificado nao tem 31 dias). Por favor introduza um mes valido." << endl;
		cout << "Mes: ";
		cin >> Month;
	}
}

/**********************************************************************************************//**
 * \fn	void Date::setAno(unsigned int NewYear)
 *
 * \brief	Sets an ano.
 *
 *
 * \param	NewYear	The new year.
 **************************************************************************************************/

void Date::setAno(unsigned int NewYear)
{
	Year = NewYear;
	while (Year < 1926)				//Assumir um limite inferior para as datas; neste caso pode-se considerar 01/01/2000 como a Data da inauguracao
	{								//Teste que avalia a variavel ano e, se esta for menor que 2000, envia uma mensagem de erro e pede um novo Ano
		Year = NULL;
		cout << "Ano introduzido invalido (A FEUP apenas foi inaugurada em 1926). Por favor introduza um Ano valido." << endl;
		cout << "Ano: ";
		cin >> Year;
	}
}

/**********************************************************************************************//**
 * \fn	ostream& operator<<(ostream& out, const Date & TheDate)
 *
 * \brief	Stream insertion operator.
 *
 * 
 *
 * \param [in,out]	out	   	The out.
 * \param 		  	TheDate	the date.
 *
 * \return	The shifted result.
 **************************************************************************************************/

ostream& operator<<(ostream& out, const Date & TheDate)
{
	string dayD;
	string monthD;
	string yearD;
	string FinalDate;
	dayD = to_string(TheDate.Day);						 //Converter o Dia num objeto do tipo string (diaD)
	monthD = to_string(TheDate.Month);					 //Converter o Mes num objeto do tipo string (mesD)
	yearD = to_string(TheDate.Year);					 //Converter o Ano num objeto do tipo string (anoD)
	FinalDate = dayD + '/' + monthD + '/' + yearD;		 //Colocar no objeto datafinal a data (em string) na forma (Dia/Mes/Ano)
	out << FinalDate;									 //"Enviar" para out (Visualizacao) o objeto datafinal
	return out;
}