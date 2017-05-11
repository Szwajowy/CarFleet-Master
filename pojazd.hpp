#ifndef pojazd_hpp
#define pojazd_hpp

#include <string>

using namespace std;

// Wszelkie dane pojazdu i dost�p do akcji z nim zwi�zanych przechowywane s� w klasie "Pojazd"
class Pojazd {
	private:
		// Dane pojazdu
		string typ, marka, model, wersja, nadwozie, paliwo, vin, rejestracja, opis, uwagi;
		unsigned int moc, silnik, miejscaSiedz, miejscaOgl, masa, dopMasaCalk, masaPrzyczHam, masaPrzyczBezHam, osie, rozstawOsi, rozstawKol, dopNaciskNaOs;
	 
	public:
		// Konstruktor parametrowy dla zmiennych obowi�zkowych 
		Pojazd(string typ, string marka, string model, string silnik,string vin);
		
		// Konstruktor bezparametrowy
		Pojazd();
		
		// Zwracanie i ustawianie warto�ci zmiennej "typ"
		string oddajTyp();
		void ustawTyp(string typ);
		
		// Zwracanie i ustawianie warto�ci zmiennej "marka"
		string oddajMarka();
		void ustawMarka(string marka);

		// Zwracanie i ustawianie warto�ci zmiennej "model"
		string oddajModel();
		void ustawModel(string model);

		// Zwracanie i ustawianie warto�ci zmiennej "paliwo"
		string oddajPaliwo();
		void ustawPaliwo(string paliwo);

		// Zwracanie i ustawianie warto�ci zmiennej "vin"
		string oddajVin();
		void ustawVIN(string vin);
};

#endif
