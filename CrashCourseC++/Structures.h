#pragma once

struct Struct1 //Hier ist eine Declarierung vom struct Struct1
{
	int x; //Es h�lt zwei int Variablen namens x und y
	int y;
}; //sizeof(Struct1) == 2 * sizeof(int)

struct Struct2
{
	double x = 4.5; //Variablen k�nnen vorgegebene Werte haben
	int y = 50;
}; //sizeof(Struct1) == sizeof(double) + sizeof(int)