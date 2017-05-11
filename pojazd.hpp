#ifndef pojazd_hpp
#define pojazd_hpp

#include <string>

using namespace std;

// Wszelkie dane pojazdu i dostêp do akcji z nim zwi¹zanych przechowywane s¹ w klasie "Pojazd"
class Pojazd {
	private:
		// Dane pojazdu
		string typ, marka, model, wersja, nadwozie, paliwo, vin, rejestracja, opis, uwagi;
		unsigned int moc, silnik, miejscaSiedz, miejscaOgl, masa, dopMasaCalk, masaPrzyczHam, masaPrzyczBezHam, osie, rozstawOsi, rozstawKol, dopNaciskNaOs;
	 
	public:
		// Konstruktor parametrowy dla zmiennych obowi¹zkowych 
		Pojazd(string typ, string marka, string model, string silnik,string vin);
		
		// Konstruktor bezparametrowy
		Pojazd();
		
		// Zwracanie i ustawianie wartoœci zmiennej "typ"
		string oddajTyp();
		void ustawTyp(string typ);
		
		// Zwracanie i ustawianie wartoœci zmiennej "marka"
		string oddajMarka();
		void ustawMarka(string marka);

		// Zwracanie i ustawianie wartoœci zmiennej "model"
		string oddajModel();
		void ustawModel(string model);

		// Zwracanie i ustawianie wartoœci zmiennej "paliwo"
		string oddajPaliwo();
		void ustawPaliwo(string paliwo);

		// Zwracanie i ustawianie wartoœci zmiennej "vin"
		string oddajVin();
		void ustawVIN(string vin);
};

#endif
