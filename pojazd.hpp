#ifndef pojazd_hpp
#define pojazd_hpp

#include <string>

using namespace std;

// Wszelkie dane pojazdu i dost�p do akcji z nim zwi�zanych przechowywane s� w klasie "Pojazd"
class Pojazd {
	private:
		// Dane pojazdu
		string typ, marka, model, wersja, nadwozie, paliwo, vin, rejestracja, opis, uwagi;
		unsigned int pojSilnika, moc, miejscaSiedz, miejscaOgl, masa, dopMasaCalk, masaPrzyczHam, masaPrzyczBezHam, osie, rozstawOsi, rozstawKol, dopNaciskNaOs, rokProd;
	 
	public:
		// Konstruktor parametrowy dla zmiennych obowi�zkowych 
		Pojazd(string typ,string marka,string model,string wersja,string nadwozie,string paliwo,unsigned int silnik,unsigned int rokProd,string vin,string rejestracja);
		
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

		// Zwracanie i ustawianie warto�ci zmiennej "wersja"
		string oddajWersja();
		void ustawWersja(string wersja);
		
		// Zwracanie i ustawianie warto�ci zmiennej "nadwozie"
		string oddajNadwozie();
		void ustawNadwozie(string nadwozie);

		// Zwracanie i ustawianie warto�ci zmiennej "paliwo"
		string oddajPaliwo();
		void ustawPaliwo(string paliwo);

		// Zwracanie i ustawianie warto�ci zmiennej "pojSilnika"
		unsigned int oddajPojSilnika();
		void ustawPojSilnika(unsigned int pojSilnika);

		// Zwracanie i ustawianie warto�ci zmiennej "moc"
		unsigned int oddajMoc();
		void ustawMoc(unsigned int moc);

		// Zwracanie i ustawianie warto�ci zmiennej "miejscaSiedz"
		unsigned int oddajMiejscaSiedz();
		void ustawMiejscaSiedz(unsigned int miejscaSiedz);

		// Zwracanie i ustawianie warto�ci zmiennej "miejscaOgl"
		unsigned int oddajMiejscaOgl();
		void ustawMiejscaOgl(unsigned int miejscaOgl);
		
		// Zwracanie i ustawianie warto�ci zmiennej "masa"
		unsigned int oddajMasa();
		void ustawMasa(unsigned int masa);
		
		// Zwracanie i ustawianie warto�ci zmiennej "dopMasaCalk"
		unsigned int oddajDopMasaCalk();
		void ustawDopMasaCalk(unsigned int dopMasaCalk);
		
		// Zwracanie i ustawianie warto�ci zmiennej "masaPrzyczHam"
		unsigned int oddajMasaPrzyczHam();
		void ustawMasaPrzyczHam(unsigned int masaPrzyczHam);
		
		// Zwracanie i ustawianie warto�ci zmiennej "masaPrzyczBezHam"
		unsigned int oddajMasaPrzyczBezHam();
		void ustawMasaPrzyczBezHam(unsigned int masaPrzyczBezHam);
		
		// Zwracanie i ustawianie warto�ci zmiennej "osie"
		unsigned int oddajOsie();
		void ustawOsie(unsigned int osie);
		
		// Zwracanie i ustawianie warto�ci zmiennej "rozstawOsi"
		unsigned int oddajRozstawOsi();
		void ustawRozstawOsi(unsigned int rozstawOsi);
		
		// Zwracanie i ustawianie warto�ci zmiennej "rozstawKol"
		unsigned int oddajRozstawKol();
		void ustawRozstawKol(unsigned int rozstawKol);
		
		// Zwracanie i ustawianie warto�ci zmiennej "dopNaciskNaOs"
		unsigned int oddajDopNaciskNaOs();
		void ustawDopNaciskNaOs(unsigned int dopNaciskNaOs);


		// Zwracanie i ustawianie warto�ci zmiennej "rokProd"
		unsigned int oddajRokProd();
		void ustawRokProd(unsigned int rokProd);

		// Zwracanie i ustawianie warto�ci zmiennej "vin"
		string oddajVin();
		void ustawVIN(string vin);
		
		// Zwracanie i ustawianie warto�ci zmiennej "rejestracja"
		string oddajRejestracja();
		void ustawRejestracja(string rejestracja);

		// Zwracanie i ustawianie warto�ci zmiennej "opis"
		string oddajOpis();
		void ustawOpis(string opis);
		
		// Zwracanie i ustawianie warto�ci zmiennej "uwagi"
		string oddajUwagi();
		void ustawUwagi(string uwagi);
};

#endif
