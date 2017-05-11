#ifndef operacja_hpp
#define operacja_hpp

#include <string>

using namespace std;

// Wszelkie dane wykonanej operacji i dost�p do akcji z ni� zwi�zanych przechowywane s� w klasie "Operacja"
class Operacja {
	private:
		// Dane operacji
		string operacja, wynik;
	 	 
	public:
		// Konstruktor parametrowy
		Operacja(string operacja, string wynik);
		
		// Konstruktor bezparametrowy
		Operacja();
		
		// Zwracanie i ustawianie warto�ci zmiennej "operacja"
		string oddajOperacja();
		void ustawOperacja(string operacja);
		
		// Zwracanie i ustawianie warto�ci zmiennej "wynik"
		string oddajWynik();
		void ustawWynik(string wynik);
};

#endif
