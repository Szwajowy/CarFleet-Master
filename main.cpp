#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// Wszelkie dane pojazdu i dost�p do operacji z nim zwi�zanych przechowywane s� w klasie "Pojazd"
class Pojazd {
	// Dane pojazdu
	string typ, marka, model, silnik;
    int vin;
	 
	public:     
    // Konstruktor parametrowy dla zmiennych obowi�zkowych  
	Pojazd(string typ, string marka, string model, string silnik, int vin) {
    	this->typ = typ;
        this->marka = marka;
        this->model = model;
        this->silnik = silnik;
        this->vin = vin;
    }
    
	// Konstruktor bezparametrowy  
	Pojazd() {
    	Pojazd("Nieznany","Nieznana","Nieznany","Nieznany",0);
    }    
	
	// Zwracanie i ustawianie warto�ci zmiennej "Typ"
	string oddajTyp() {
		return typ;	
	}
	
	void ustawTyp(string typ) {
		this->typ = typ;	
	}
	
	// Zwracanie i ustawianie warto�ci zmiennej "Marka"
	string oddajMarka() {
		return marka;	
	}
	
	void ustawMarka(string marka) {
		this->marka = marka;	
	}
	
	// Zwracanie i ustawianie warto�ci zmiennej "Model"
	string oddajModel() {
		return model;	
	}
	
	void ustawModel(string model) {
		this->model = model;	
	}  
	
	// Zwracanie i ustawianie warto�ci zmiennej "Silnik"
	string oddajSilnik() {
		return silnik;	
	}
	
	void ustawSilnik(string silnik) {
		this->silnik = silnik;	
	}
	
	// Zwracanie i ustawianie warto�ci zmiennej "VIN"
	int oddajVin() {
		return vin;	
	}
	
	void ustawVIN(int vin) {
		this->vin = vin;	
	}     
};

// Definicja wektora obiektow Pojazd
vector <Pojazd> tablicaPojazdow;

// Metoda dodajaca dane pojazdu dla odpowiedniego indeksu wektora
// (je�eli dla danego indeksu istnieje ju� obiekt to nast�puje inkrementacja indeksu tego obiektu i ka�dego nast�pnego i dopiero dodanie naszego obiektu)	
string dodajPojazd(unsigned int id) {
	
	string typ,marka,model,silnik;
	int vin;

	cout << "Podaj typ pojazdu: ";
	cin >> typ;
	cout << "Podaj marke pojazdu: ";
	cin >> marka;
	cout << "Podaj model pojazdu: ";
	cin >> model;
	cout << "Podaj typ silnika: ";
	cin >> silnik;
	cout << "Podaj identyfikator VIN pojazdu: ";
	cin >> vin;
	
	tablicaPojazdow.insert (tablicaPojazdow.begin() + id,Pojazd(typ,marka,model,silnik,vin));
	cout << endl;
	
	return "Operacja wykonana pomy�lnie!";
}

// Metoda dodajaca dane pojazdu na koniec wektora
string dodajPojazd() {
	return dodajPojazd(tablicaPojazdow.size());
}

// Metoda wyswietlajaca dane pojazdu o danym ID	
string wyswietlDanePojazdu(unsigned int id) {
	if (id >=tablicaPojazdow.size()) {
		cout << "B��d x11" << endl;
		cout << endl;
		return "x11";
	} else {
		cout << "Typ: " << tablicaPojazdow[id].oddajTyp() << endl;
       	cout << "Marka: " << tablicaPojazdow[id].oddajMarka() << endl;
      	cout << "Model: " << tablicaPojazdow[id].oddajModel() << endl;
        cout << "Typ silnika: " << tablicaPojazdow[id].oddajSilnik() << endl;
        cout << "Nr. VIN: " << tablicaPojazdow[id].oddajVin() << endl;
        cout << endl;
        return "x10";	
	}
}

// Metoda filtruj�ca dane pojazdu
string filtrujDanePojazdu() {
	unsigned int znalezionoWyniki = 0;
	string atrybut, wartosc;
	
	cout << "Podaj nazwe w�asno�ci pojazdu: ";
	cin >> atrybut;
	cout << "Podaj warto�c tej w�asno�ci: ";
	cin >> wartosc;

	// Obs�uga b��du - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
			cout << "Nie dodano jeszcze �adnego pojazdu." << endl;
			cout << endl;
			return "x23";	
	}
	
	// Przeszukiwanie wszystkich obiekt�w wektora
	for (int i=0; i<tablicaPojazdow.size();i++) {
		if (atrybut == "Typ" || atrybut == "typ" || atrybut == "TYP") {
			if (tablicaPojazdow[i].oddajTyp()==wartosc) {
				wyswietlDanePojazdu(i);
				znalezionoWyniki = 1;	
			}
		} else if (atrybut == "Marka" || atrybut == "marka" || atrybut == "MARKA") {
			if (tablicaPojazdow[i].oddajMarka()==wartosc) {
				wyswietlDanePojazdu(i);
				znalezionoWyniki = 1;	
			}
		} else if (atrybut == "Model" || atrybut == "model" || atrybut == "MODEL") {
			if (tablicaPojazdow[i].oddajModel()==wartosc) {
				wyswietlDanePojazdu(i);
				znalezionoWyniki = 1;	
			}
		} else if (atrybut == "Typ silnika" || atrybut == "typ silnika" || atrybut == "TYP SILNIKA" || atrybut == "Silnik" || atrybut == "silnik" || atrybut == "SILNIK") {
			if (tablicaPojazdow[i].oddajSilnik()==wartosc) {
				wyswietlDanePojazdu(i);
				znalezionoWyniki = 1;	
			}
		// Filtrowanie po VIN nie dzia�a z powodu niedzia�aj�cego parsowania zmiennej "wartosc"
		} else if (atrybut == "Nr.Vin" || atrybut == "nr.vin" || atrybut == "NR.VIN" || atrybut == "Vin" || atrybut == "vin" || atrybut == "VIN" || atrybut == "NrVin" || atrybut == "nrvin" || atrybut == "NRVIN") {
			if (tablicaPojazdow[i].oddajVin()==stoi(wartosc)) {
				wyswietlDanePojazdu(i);
				znalezionoWyniki = 1;	
			}
		// Obs�uga b��du - nie istnieje taki atrybut
		} else {
			cout << "Taki atrybut zosta� nie znaleziony." << endl;
			cout << "Sprawd� pisownie i spr�buj ponownie." << endl;
			cout << endl;
			return "x22";
		}
	}
	
	// Obs�uga b��du - nie istniej� obiekty o takich atrybutach
	if (znalezionoWyniki == 0) {
		cout << "Nie znaleziono element�w odpowiadaj�cych podanym kryteriom." << endl;
		cout << endl;
		return "x21";	
	}
				
	return "x20";
}

int main(int argc, char *argv[]) {
	
	dodajPojazd(0);
	cout << filtrujDanePojazdu();
	
    return EXIT_SUCCESS;
}
