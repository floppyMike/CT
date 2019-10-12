#include "Functions.h"
#include "Structures.h"
#include <limits>
#include <array>

//----------------------------------------------
//Basics
//----------------------------------------------

// <- Um linie zu kommentieren (wird nicht kompaliert).

/*
Hier wird nicht kompaliert.
*/

#include <iostream> //Pre-prozessor befehl um inhalt einer file (hier: "iostream") hier zu setzen.

int main() //Hier fängt das von dir geschriebene programm an.
{
	//----------------------------------------------
	//Basics
	//----------------------------------------------

	{ //Alles drinnen ist unsichtbar draußen.
		int x = 0; //Alle Befehle müssen ein ";" am Ende haben.
	}
	//x = 5; <- Wird nicht kompalieren.


	//--- Variablen Teil 1
	{
		int x; //definiert eine variable namens "x" mit typ "int".
		x = 5; //variable "x" hält jetzt den Wert 5.
		int y = 5; //definiert eine variable namens "y" mit typ "int" und es hält den Wert 5.
		int z(5); //definiert eine variable namens "z" mit typ "int" und es hält den Wert 5.
		int j{ 5 }; //definiert eine variable namens "j" mit typ "int" und es hält den Wert 5.

		bool bo = true; //Typ "bool" hält entweder 1 oder 0. Die größe vom Typ ist aber 8-bit. Max ist 1.
		char ch = 'a'; //Typ "char" hält eine 8-bit Zahl. Gemacht für ascii charaktere. Max ist 127.
		short sh = 10; //Hält eine 16-bit Zahl. Gemacht für kleine Zahlen. Max ist 32767.
		int in = 10; //Hält eine 32-bit Zahl. Gemacht für mittel große Zahlen. Wird am meisten verwendet. Max ist 2147483647.
		long lo = 10; //Hält eine 32-bit oder 64-bit Zahl. Es ist gleich wie "int" oder "long long".
		long long lolo = 10; //Hält eine 64-bit Zahl. Gemacht für große Zahlen. Max ist 9223372036854775807.

		int size = sizeof(long); //Typ größen hängen vom System ab. D.h. "long" könnte 64-bit haben statt 32-bit. 
								 //Mit "sizeof" kann man die Bytes einer Typ bestimmen.
	
		int8_t in8; //Typ muss insgesamt 8-bit haben.
		int16_t in16; //Typ muss insgesamt 16-bit haben.
		int32_t in32; //Typ muss insgesamt 32-bit haben.
		int64_t in64; //Typ muss insgesamt 64-bit haben. Nicht überall erhältlich.

		signed int sin; //Typ "int" ist jetzt "signed". Das bedeutet es kann jetzt negative Zahlen halten, aber nur 7-bit werden verwendet.
						//Der letzte bit wird verwendet um zu bestimmen ob die Zahl negativ oder positiv ist. 
						//Alle Typen ohne "signed" oder "unsigned" sind "signed".

		unsigned int uin; //Typ "int" ist jetzt "unsigned". Das bedeutet es hält die vollständige 32-bit Zahl. Sie kann nichts negatives halten.
						  //Max wird zu 4294967295 oder 0xFFFFFFFF.

		const int cint = 4; //Typ "int" ist jetzt constant. D.h. die Variable kann nicht verändert werden.
		//cint = 10; <- Wird nicht kompalieren.
	}


	//--- Output
	{
		std::cout << 5; //Die Zahl 5 wird in die Console geschieben.

		std::cout << '\n' << 12 << 'e' << ' ' << 2 << '\n'; //'\n' druckt eine neue Zeile. Dann wird 12 geschrieben. 
															//Dann wird die Buchstabe e geschrieben.
															//Dann wird leertaste geschrieben. Dann wird 2 geschrieben. 
															//Zu letzt kommt eine neue Zeile.

		std::cout << "Hello World!\n"; //Schreibt "Hello World!" zur Console.

		const int x = 10;
		std::cout << x << '\n'; //Schreibt den Inhalt der Variable "x". Hier wird 10 geschrieben.

		std::cout << "\"long\" has " << sizeof(long) << " bytes.\n"; //Druckt die größe vom "long" zur Console.

		std::cout << "üöäÜÖÄß\n"; //Es wird normalerweise in ASCII gedruckt. D.h. hier werden seltsame Buchstaben rauskommen.
	}


	//--- Input
	{
		std::cout << "Enter a number:\n";
		int x;
		std::cin >> x; //Erwartet eine Zahl als input durch die Console.
		std::cout << "You entered: " << x << '\n';

		std::cout << "Enter two numbers:\n";
		int y;
		int z;
		std::cin >> y >> z; //Erwartet zwei Zahlen als input durch die Console. Input wird mit enter oder leertaste seperiert.
		std::cout << "You entered: " << y << " and " << z << '\n';
	}


	//--- Variablen Teil 2
	{
		float fl; //Hält eine 32-bit comma Zahl. Die Precision ist 7 decimale. D.h. es kann 10.1234567 halten. Max ist 1.79769e+308
		double dou; //Hält eine 64-bit comma Zahl. Die Precision ist 15 decimale. D.h. es kann 10.123456789012345 halten. Max ist 3.40282e+38
		//Beide können nicht "unsigned" werden und sie können precisions Fehler haben. Bsp. 4.0 wird als 3.9999999... gespeichert.

		auto au1 = 10; //Hier wird der Typ automatisch definiert. Hier wird der Typ zum "int".
		auto au2 = false; //Hier wird der Typ zum "bool".
		auto au3 = (short)10; //Hier wird der Typ zum "short".
		auto au4 = 10l; //Hier wird der Typ zum "long".
		auto au5 = 10ll; //Hier wird der Typ zum "long long".

		auto au6 = 10u; //Hier wird der Typ zum "unsigned int".
		auto au7 = 10ul; //Hier wird der Typ zum "unsigned long".

		auto au8 = 10.f; //Hier wird der Typ zum "float".
		auto au9 = 10.; //Hier wird der Typ zum "double".

		const auto hex = 0xFF; //Hexadecimal schreibweise für den Wert 255.
		const auto bin = 0b1111'1111; //Binäre schreibweise für den Wert 255.
		const auto oct = 0377; //Octal schreibweise für den Wert 255.
	}


	//--- Mathe
	{
		std::cout << "Loesung vom (3 + 5) * 5 ist: " << (3 + 5) * 5 << '\n'; //Mathe wird wie normal in korrekter reihenfolge ausgeführt.

		std::cout << "Loesung vom 5 / 3 + 5 * 5 ist: " << 5. / 3 + 5. * 5 << '\n'; //Der größte Typ in der Formel, ist der Typ was rauskommt.

		std::cout << "50 % 6 = " << 50 % 6 << '\n'; //Hier gibt es noch den Modulus als operator. Es schaut zu erst wie oft die 6 
													//in die 50 passt und dann druckt es die verbiebenen Zahlen die nicht reingepasst haben.
													//In anderen Worten, es druck den Rest der Division aus.

		int x = 3 + 1;
		std::cout << "3 + 50 % 6 = " << x + 50 % 6 << '\n'; //Der Modulus hat den gleichen Rang wie Multiplikation oder Division.

		const auto y = ++x; //++ heißt die Variable soll um 1 hoch gehen. y ist 5;
		x += 56; //ist gleich wie x = x + 56
		x -= 56; //ist gleich wie x = x - 56
		x *= 56; //ist gleich wie x = x * 56
		x /= 56; //ist gleich wie x = x / 56
		x %= 56; //ist gleich wie x = x % 56
	}


	//--- Logik
	{
		std::cout << "Is 3 equal 4? " << (3 == 4) << '\n'; //3 und 4 werden vergliechen ob sie gleich sind und als "bool" ausgedruckt.
		std::cout << std::boolalpha << "Is 3 equal 3? " << (3 == 3) << '\n'; //Das Ergebniss wird jetzt als "true" oder "false" gedruckt.

		std::cout.setf(std::ios::boolalpha); //Alle "bool" ergebnisse werden als "true" oder "false" gedruckt.

		const auto x = 5;
		std::cout << "5 < 6 " << (x < 6) << '\n' //Ist 5 kleiner als 6?
			<< "5 <= 6 " << (x <= 6) << '\n' //Ist 5 kleiner oder gleich wie 6?
			<< "5 > 6 " << (x > 6) << '\n' //Ist 5 größer als 6?
			<< "5 >= 6 " << (x >= 6) << '\n' //Ist 5 größer oder gleich wie 6?
			<< "5 != 6 " << (x != 6) << '\n'; //Ist 5 nicht 6?

		std::cout.unsetf(std::ios::boolalpha); //Alle "bool" ergebnisse werden wieder als 1 oder 0 gedruckt.

		const auto b1 = 5 < 6 || 5 > 6; //Wenn 5 kleiner als 6 ist oder 5 größer als 6 ist
		const auto b2 = 5 < 6 && 5 > 6; //Wenn 5 kleiner als 6 ist und 5 größer als 6 ist

		const auto y1 = 5 << 1; //Die bits werden nach links um 1 verschoben.
		//0101 -> 1010
		const auto y2 = 5 >> 1; //Die bits werden nach rechts um 1 verschoben.
		//0101 -> 0010
		const auto y3 = ~5; //Die bits werden invertiert. D.h. 0 wird 1 und 1 wird 0
		//0101 -> 1010
		const auto y4 = 5 & 3; //Die bits von 5 und 3 werden zusammen mit AND gerechnet
		//  0101
		//& 0011
		//= 0001
		const auto y5 = 5 | 3; //Die bits von 5 und 3 werden zusammen mit OR gerechnet
		//  0101
		//| 0011
		//= 0111
		const auto y6 = 5 ^ 3; //Die bits von 5 und 3 werden zusammen mit XOR gerechnet
		//  0101
		//^ 0011
		//= 0110
	}


	//--- Kontroll Fluss
	{
		if (5 < 3) //Wenn 5 kleiner als 3 ist wird das im {} ausgeführt
		{
			std::cout << "5 is smaller than 3\n"; //Wird nie ausgeführt
		}

		if (5 < 3) //Gleich wie oben nur kürzer. Es geht nur wenn es danach nur ein Befehl zum ausführen gibt.
			std::cout << "5 is smaller than 3\n";

		if (5 < 3); //Semicolon führt dazu, dass nichts ausgeführt wird wenn es richtig ist.
		else //Wenn obere if nicht richtig ist.
			std::cout << "5 is larger than 3\n";

		if (6 < 7);
		else if (5 > 3) //Wenn oberes falsch ist, wird hier noch mal if gemacht. Wenn oben aber richtig ist, wird hier alles übersprungen.
			std::cout << "5 is larger than 3\n";
		else;

		const int x = 6;
		switch (x) //Wert zum evaluieren wird hier eingesteckt
		{
		case 1: //Wenn der Wert 1 ist
			std::cout << "x is 1\n";
			break; //Breche ab und gehe raus aus der "switch". Sonst wird der Programm weiter zur Befehlen von 6 gehen

		case 6: //Wenn der Wert 6 ist
			std::cout << "x is 6\n";
			//Hier gibt es kein "break". Der Programm geht weiter zur Befehlen von 3

		case 3:
			std::cout << "x is 3?\n";
			break;

		default:
			break;
		}

		while (5 > 3) //Hier ist ein loop. Wenn es richtig ist werden die Befehle ausgeführt und dann wird es nochmal gecheckt usw..
		{
			break; //Breche aus der loop heraus ohne zu checken oder das Untere auszuführen.
		}

		do
		{
			std::cout << "I will be displayed once!\n";
		} while (3 > 5); //Gleich wie "while" nur es wird erst nach den Befehlen gecheckt.

		for (int i = 0; i < 5; ++i) //Deklariere eine "int" Variable mit dem Wert 0. Checke nach jedem loop ob i kleiner ist als 5. 
									//Wenn ja, dann loope weiter. Wenn nein, dann breche ab. Nach jedem loop wird i um 1 erhöht.
		{
			std::cout << "I am increasing! " << i << '\n';
		}
	}


	//--- Funktionen
	{
		const auto x = foo1(2, 3); //Die Variable x wird mit der Funktion "foo" und den Parametern 2 und 3 erstellt. 
								   //"foo" ist im "Functions.h" file definiert. Gehe dahin
		const auto y = foo1(3, 4); //Gleich wie oben nur mit anderen Parametern

		foo2(); //Funktion "foo2" wird ausgeführt ohne Parametern

		foo3(); //Funktion mit optionalen Parameter
		foo3(5);

		recursion(5); //Recursiver Funktion aufrufen

		auto lambda1 = [] //Variable für ein Lambda Funktion der hier definiert ist
		{
			std::cout << "ABC\n";
		};
		lambda1(); //Variable wie eine Funktion ausführen

		auto lambda2 = [x] //Variable x wird rein copiert und wird bei jeder anwendung der lambda benutzt.
		{
			std::cout << "x == " << x << '\n';
		};
		lambda2();

		[] //Lambda kann auf Variablenloss sein
		{
			std::cout << "Nameless\n";
		}();
	}


	//--- Variablen Teil 3
	{
		std::array<int, 5> arr1; //5 "int" Variable werden erstellt
		arr1[0] = 5; //Die erste Variable hat jetzt den Wert 5
		arr1[4] = 9; //Die letzte Variable hat jetzt den Wert 9
		arr1.front() = 5; //Gleich wie oben
		arr1.back() = 9; //Gleich wie oben

		std::array<int, 3> arr2 = { 1, 2, 3 }; //Die Variablen haben die Werte 1, 2 und 3 in der Reihenfolge

		const auto s = arr1.size(); //Gibt die größe des Arrays an

		arr1.fill(10); //Alle Variablen im Array halten den Wert 10
		std::cout << arr1[2] << '\n';

		const auto a = static_cast<double>(3); //"static_cast" convertiert einen Wert zu einen anderen Typ
	}


	//--- User Typen
	{
		Struct1 s1; //User gemachte Typ wird declariert. Gehe zu "Structures.h".
		s1.x = 10; //x Variable vom Struct1 bekommt den Wert 10.
		s1.y = 20; //y Variable vom Struct1 bekommt den Wert 20.

		std::cout << "Struct1 has x = " << s1.x << " and y = " << s1.y << '\n';

		Struct2 s2; //Variablen müssen nicht geändert werden, weil sie schon einen Wert bekommen haben
		std::cout << "Struct2 has x = " << s2.x << " and y = " << s2.y << '\n';


	}


	return 0;
}