#ifndef pojazd_hpp
#define pojazd_hpp

#include <string>
#include <time.h>

using namespace std;

// Wszelkie dane pojazdu i dostêp do akcji z nim zwi¹zanych przechowywane s¹ w klasie "Pojazd"
class Pojazd {
	private:
		// Dane pojazdu
		char typ;
		string marka, model, wersja, nadwozie, paliwo, vin, rejestracja, opis, uwagi;
		unsigned int pojSilnika, moc, miejscaSiedz, miejscaOgl, masa, dopMasaCalk, masaPrzyczHam, masaPrzyczBezHam, osie, rozstawOsi, rozstawKol, dopNaciskNaOs, rokProd;
		
		struct tm * ocOd, * ocDo, * przegladOd, * przegladDo;
		
	public:
		// Konstruktor parametrowy dla zmiennych obowi¹zkowych 
		Pojazd(char typ,string marka,string model,string wersja,string nadwozie,string paliwo,unsigned int silnik,unsigned int rokProd,string vin,string rejestracja, tm * przegladOd, tm * przegladDo);
		
		// Konstruktor bezparametrowy
		Pojazd();
		
		// Zwracanie i ustawianie wartoœci zmiennej "typ"
		char oddajTyp();
		void ustawTyp(char typ);
		
		// Zwracanie i ustawianie wartoœci zmiennej "marka"
		string oddajMarka();
		void ustawMarka(string marka);

		// Zwracanie i ustawianie wartoœci zmiennej "model"
		string oddajModel();
		void ustawModel(string model);

		// Zwracanie i ustawianie wartoœci zmiennej "wersja"
		string oddajWersja();
		void ustawWersja(string wersja);
		
		// Zwracanie i ustawianie wartoœci zmiennej "nadwozie"
		string oddajNadwozie();
		void ustawNadwozie(string nadwozie);

		// Zwracanie i ustawianie wartoœci zmiennej "paliwo"
		string oddajPaliwo();
		void ustawPaliwo(string paliwo);

		// Zwracanie i ustawianie wartoœci zmiennej "pojSilnika"
		unsigned int oddajPojSilnika();
		void ustawPojSilnika(unsigned int pojSilnika);

		// Zwracanie i ustawianie wartoœci zmiennej "moc"
		unsigned int oddajMoc();
		void ustawMoc(unsigned int moc);

		// Zwracanie i ustawianie wartoœci zmiennej "miejscaSiedz"
		unsigned int oddajMiejscaSiedz();
		void ustawMiejscaSiedz(unsigned int miejscaSiedz);

		// Zwracanie i ustawianie wartoœci zmiennej "miejscaOgl"
		unsigned int oddajMiejscaOgl();
		void ustawMiejscaOgl(unsigned int miejscaOgl);
		
		// Zwracanie i ustawianie wartoœci zmiennej "masa"
		unsigned int oddajMasa();
		void ustawMasa(unsigned int masa);
		
		// Zwracanie i ustawianie wartoœci zmiennej "dopMasaCalk"
		unsigned int oddajDopMasaCalk();
		void ustawDopMasaCalk(unsigned int dopMasaCalk);
		
		// Zwracanie i ustawianie wartoœci zmiennej "masaPrzyczHam"
		unsigned int oddajMasaPrzyczHam();
		void ustawMasaPrzyczHam(unsigned int masaPrzyczHam);
		
		// Zwracanie i ustawianie wartoœci zmiennej "masaPrzyczBezHam"
		unsigned int oddajMasaPrzyczBezHam();
		void ustawMasaPrzyczBezHam(unsigned int masaPrzyczBezHam);
		
		// Zwracanie i ustawianie wartoœci zmiennej "osie"
		unsigned int oddajOsie();
		void ustawOsie(unsigned int osie);
		
		// Zwracanie i ustawianie wartoœci zmiennej "rozstawOsi"
		unsigned int oddajRozstawOsi();
		void ustawRozstawOsi(unsigned int rozstawOsi);
		
		// Zwracanie i ustawianie wartoœci zmiennej "rozstawKol"
		unsigned int oddajRozstawKol();
		void ustawRozstawKol(unsigned int rozstawKol);
		
		// Zwracanie i ustawianie wartoœci zmiennej "dopNaciskNaOs"
		unsigned int oddajDopNaciskNaOs();
		void ustawDopNaciskNaOs(unsigned int dopNaciskNaOs);


		// Zwracanie i ustawianie wartoœci zmiennej "rokProd"
		unsigned int oddajRokProd();
		void ustawRokProd(unsigned int rokProd);

		// Zwracanie i ustawianie wartoœci zmiennej "vin"
		string oddajVin();
		void ustawVin(string vin);
		
		// Zwracanie i ustawianie wartoœci zmiennej "rejestracja"
		string oddajRejestracja();
		void ustawRejestracja(string rejestracja);

		// Zwracanie i ustawianie wartoœci zmiennej "opis"
		string oddajOpis();
		void ustawOpis(string opis);
		
		// Zwracanie i ustawianie wartoœci zmiennej "uwagi"
		string oddajUwagi();
		void ustawUwagi(string uwagi);
		
		// Zwracanie i ustawianie wartoœci zmiennej "ocOd"
		tm oddajOcOd();
		void ustawOcOd(tm * ocOd);
		
		// Zwracanie i ustawianie wartoœci zmiennej "ocDo"
		tm oddajOcDo();
		void ustawOcDo(tm * ocDo);
		
		// Zwracanie i ustawianie wartoœci zmiennej "przegladOd"
		tm oddajPrzegladOd();
		void ustawPrzegladOd(tm * przegladOd);
		
		// Zwracanie i ustawianie wartoœci zmiennej "przegladDo"
		tm oddajPrzegladDo();
		void ustawPrzegladDo(tm * przegladDo);
};

// Odpowiadaj¹ce klasy dla pojazdów ró¿nego typu: Jednoœlad, Osobowy, Autobus, Ciê¿arowy, Specjalny, Przyczepa, Naczepa

/* class Jednoslad : private Pojazd {
	
};

class Osobowy : private Pojazd {
	
};

class Autobus : private Pojazd {
	
};

class Ciezarowy : private Pojazd {
	
};

class Specjalny : private Pojazd {
	
};

class Przyczepa : private Pojazd {
	
};

class Naczepa : private Pojazd {
	
}; */

#endif
