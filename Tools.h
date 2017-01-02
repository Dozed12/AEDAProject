#pragma once



#include <iostream>
#include <vector>
#include <cstdlib>


using namespace std;


#define ALTURA_ECRA 24

#define TAB_BIG "          "
#define TAB    "   "
#define TinyTAB " "


void resize();			//Funcao que fixa a janela da consola num tamanho preferível para uma melhor visualizacao do programa

void clearScreen();		//Funcao que limpa o ecra

unsigned short int ReadUnsignedShortInt(unsigned short int min, unsigned short int max);	//Funcao que avalia se o inteiro (opcao) introduzido pelo utilizador e valido (esta dentro de determinado intervalo)
