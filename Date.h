#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Date {
private:
	unsigned int Day;			//Dia
	unsigned int Month;			//Mes
	unsigned int Year;			//Ano

public:
	Date() {};				//Construtor por omissao da classe Data
	Date(string TheDate);		//Construtor da classe Data (na forma DD/MM/AAAA)
	unsigned int getDay() const { return Day; }						//Funcao que retorna o Dia
	unsigned int getMonth() const { return Month; }					//Funcao que retorna o Mes
	unsigned int getYear() const { return Year; }					//Funcao que retorna o Ano
	void setDay(unsigned int NewdDay);			//Funcao que permite modificar o Dia
	void setMonth(unsigned int NewMonth);		//Funcao que permite modificar o Mes
	void setYear(unsigned int NewAno);			//Funcao que permite modificar o Ano
	bool operator < (const Date& d1) const;
	bool operator== (const Date& d1) const;
	friend ostream& operator<<(ostream& out, const Date & TheDate);		//Funcao que mostra a Data
};