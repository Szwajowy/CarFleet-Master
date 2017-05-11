#ifndef operacja_hpp
#define operacja_hpp

#include <string>

using namespace std;

// Wszelkie dane wykonanej operacji i dostêp do akcji z ni¹ zwi¹zanych przechowywane s¹ w klasie "Operacja"
class Operacja {
	private:
		// Dane operacji
		string operacja, wynik;
	 	 
	public:
		// Konstruktor parametrowy
		Operacja(string operacja, string wynik);
		
		// Konstruktor bezparametrowy
		Operacja();
		
		// Zwracanie i ustawianie wartoœci zmiennej "operacja"
		string oddajOperacja();
		void ustawOperacja(string operacja);
		
		// Zwracanie i ustawianie wartoœci zmiennej "wynik"
		string oddajWynik();
		void ustawWynik(string wynik);
};

#endif
