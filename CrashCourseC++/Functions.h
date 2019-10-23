#pragma once

#include <iostream>

int foo1(int x, int y) //Erstelle eine Funktion namens "foo". Die Funktion erstellt eine "int" Variable. 
					  //Die Funktion braucht zwei "int" Variablen und diese werden ins x und y rein copiert.
{
	x += x;
	x *= y;

	return x; //Der Wert x wird zurück gesendet.
}

void foo2() //Funktion der nichts zurück sendet und keine Parameter braucht.
{
	std::cout << "Hello There!\n";
	return; //Optional: es wird am Ende automatisch generiert.
}

void foo3(int x = 3) //Parameter hat einen vorgegeben Wert 3
{
	std::cout << "I am " << x << '\n';
}

void recursion(int x)
{
	std::cout << "Hello " << x << '\n';

	if (x > 1)
		recursion(x - 1); //Die Funktion wird im Funktion wieder aufgerufen aber jetzt mit einen um 1 niedrigeren Wert.

	std::cout << "Bye " << x << '\n';
}