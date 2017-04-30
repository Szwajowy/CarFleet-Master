#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Wszelkie dane pojazdu i dostęp do operacji z nim związanych przechowywane są w klasie "Pojazd"
class Pojazd {
	// Dane pojazdu
	string typ, marka, model, silnik;
    int vin;
	 
	public:     
    // Konstruktor parametrowy dla zmiennych obowiązkowych  
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
	
	// Zwracanie i ustawianie wartości zmiennej "Typ"
	string oddajTyp() {
		return typ;	
	}
	
	void ustawTyp(string typ) {
		this->typ = typ;	
	}
	
	// Zwracanie i ustawianie wartości zmiennej "Marka"
	string oddajMarka() {
		return marka;	
	}
	
	void ustawMarka(string marka) {
		this->marka = marka;	
	}
	
	// Zwracanie i ustawianie wartości zmiennej "Model"
	string oddajModel() {
		return model;	
	}
	
	void ustawModel(string model) {
		this->model = model;	
	}  
	
	// Zwracanie i ustawianie wartości zmiennej "Silnik"
	string oddajSilnik() {
		return silnik;	
	}
	
	void ustawSilnik(string silnik) {
		this->silnik = silnik;	
	}
	
	// Zwracanie i ustawianie wartości zmiennej "VIN"
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
// (jeżeli dla danego indeksu istnieje już obiekt to następuje inkrementacja indeksu tego obiektu i każdego następnego, czyli przesunięcie w prawo i dopiero dodanie naszego obiektu)	
string dodajPojazd(unsigned int id) {
	
	string typ, marka, model, silnik;
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
	
	return "x10";
}

// Metoda dodajaca dane pojazdu na koniec wektora
string dodajPojazd() {
	return dodajPojazd(tablicaPojazdow.size());
}

// Metoda edytująca dane pojazdu o danym ID
string edytujPojazd(unsigned int id) {
	// Obsługa błędu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
			cout << "Nie dodano jeszcze żadnego pojazdu." << endl;
			cout << endl;
			return "x21";	
	}
	
	// Obsługa błędu - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		return "x22";
	}
	
	string typ, marka, model, silnik, atrybut, exit;
	int vin;
	
	do {
		cout << "Podaj nazwe własności pojazdu: " << endl;
		cin >> atrybut;
		
		if (atrybut == "Typ" || atrybut == "typ" || atrybut == "TYP") {
			cout << "Podaj typ pojazdu: ";
			cin >> typ;
			tablicaPojazdow[id].ustawTyp(typ);
		} else if (atrybut == "Marka" || atrybut == "marka" || atrybut == "MARKA") {
			cout << "Podaj marke pojazdu: ";
			cin >> marka;
			tablicaPojazdow[id].ustawMarka(marka);
		} else if (atrybut == "Model" || atrybut == "model" || atrybut == "MODEL") {
			cout << "Podaj model pojazdu: ";
			cin >> model;
			tablicaPojazdow[id].ustawModel(model);
		} else if (atrybut == "Typ silnika" || atrybut == "typ silnika" || atrybut == "TYP SILNIKA" || atrybut == "Silnik" || atrybut == "silnik" || atrybut == "SILNIK") {
			cout << "Podaj typ silnika: ";
			cin >> silnik;
			tablicaPojazdow[id].ustawSilnik(silnik);
		} else if (atrybut == "Nr.Vin" || atrybut == "nr.vin" || atrybut == "NR.VIN" || atrybut == "Vin" || atrybut == "vin" || atrybut == "VIN" || atrybut == "NrVin" || atrybut == "nrvin" || atrybut == "NRVIN") {
			cout << "Podaj identyfikator VIN pojazdu: ";
			cin >> vin;
			tablicaPojazdow[id].ustawVIN(vin);
		}
		cout << "Czy chcesz kontynuować edycję ?" << endl;
		cin >> exit;
	} while (exit != "tak");
	
	return "x20";
}

// Metoda usuwająca pojazd o danym ID	
// (po usunięciu obiektu następuje dekrementacja indeksu każdego następnego, czyli przesunięcie w lewo)	
string usunPojazd(unsigned int id) {
	// Obsługa błędu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
			cout << "Nie dodano jeszcze żadnego pojazdu." << endl;
			cout << endl;
			return "x31";	
	}
	
	// Obsługa błędu - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		return "x32";
	}
	
	tablicaPojazdow.erase (tablicaPojazdow.begin() + id);
	
	return "x30";
}

// Metoda wyswietlajaca dane pojazdu o danym ID	
string wyswietlDanePojazdu(unsigned int id) {
	// Obsługa błędu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
			cout << "Nie dodano jeszcze żadnego pojazdu." << endl;
			cout << endl;
			return "x41";	
	}
	
	// Obsługa błędu - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		return "x42";
	}
	
	cout << "Typ: " << tablicaPojazdow[id].oddajTyp() << endl;
    cout << "Marka: " << tablicaPojazdow[id].oddajMarka() << endl;
    cout << "Model: " << tablicaPojazdow[id].oddajModel() << endl;
    cout << "Typ silnika: " << tablicaPojazdow[id].oddajSilnik() << endl;
    cout << "Nr. VIN: " << tablicaPojazdow[id].oddajVin() << endl;
    cout << endl;
    
    return "x40";	
}

// Metoda filtrująca dane pojazdu
string filtrujDanePojazdu() {
	// Obsługa błędu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
			cout << "Nie dodano jeszcze żadnego pojazdu." << endl;
			cout << endl;
			return "x51";	
	}
	
	unsigned int znalezionoWyniki = 0;
	string atrybut, wartosc;
	
	cout << "Podaj nazwe własności pojazdu: ";
	cin >> atrybut;
	cout << "Podaj wartośc tej własności: ";
	cin >> wartosc;
	
	// Przeszukiwanie wszystkich obiektów wektora
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
		} else if (atrybut == "Nr.Vin" || atrybut == "nr.vin" || atrybut == "NR.VIN" || atrybut == "Vin" || atrybut == "vin" || atrybut == "VIN" || atrybut == "NrVin" || atrybut == "nrvin" || atrybut == "NRVIN") {
			if (tablicaPojazdow[i].oddajVin()==stoi(wartosc)) {
				wyswietlDanePojazdu(i);
				znalezionoWyniki = 1;	
			}
		// Obsługa błędu - nie istnieje taki atrybut
		} else {
			cout << "Taki atrybut został nie znaleziony." << endl;
			cout << "Sprawdź pisownie i spróbuj ponownie." << endl;
			cout << endl;
			return "x52";
		}
	}
	
	// Obsługa błędu - nie istnieją obiekty o takich atrybutach
	if (znalezionoWyniki == 0) {
		cout << "Nie znaleziono elementów odpowiadających podanym kryteriom." << endl;
		cout << endl;
		return "x53";	
	}
				
	return "x50";
}

string zapiszPlik() {
	
	cout << "Rozpoczynam zapis do pliku.";
	
	fstream plik("Pojazdy.txt",ios::out);
	if( plik.good() ) {
		for (int i=0; i<tablicaPojazdow.size();i++) {
			plik << "Pojazd nr." << i << endl;
			plik << "Typ: " << tablicaPojazdow[i].oddajTyp() << endl;
			plik << "Marka: " << tablicaPojazdow[i].oddajMarka() << endl;
			plik << "Model: " << tablicaPojazdow[i].oddajModel() << endl;
			plik << "Typ silnika: " << tablicaPojazdow[i].oddajSilnik() << endl;
			plik << "Nr.VIN: " << tablicaPojazdow[i].oddajVin() << endl;
			plik << endl;
			plik.flush();
		}	
	}
	plik.close();
	
	cout << "Pomyślnie zakończono zapis do pliku.";
	return "x60";
}

string otworzPlik() {
	string wiersz, typ, marka, model, silnik;
	int id, i, vin;
	
	cout << "Rozpoczynam odczyt z pliku.";
	
	fstream plik("Pojazdy.txt",ios::in);
	if( plik.good() ) {
		while (getline(plik, wiersz) != 0) {
			if (wiersz != "") {
				if (i==0) {
					cout << wiersz << endl;
					wiersz.erase(0,10);
					id = stoi(wiersz);
					i++;
				} else if (i==1) {
					cout << wiersz << endl;
					wiersz.erase(0,5);
					typ = wiersz;
					i++;
				} else if (i==2) {
					cout << wiersz << endl;
					wiersz.erase(0,7);
					marka = wiersz;
					i++;
				} else if (i==3) {
					cout << wiersz << endl;
					wiersz.erase(0,7);
					model = wiersz;
					i++;
				} else if (i==4) {
					cout << wiersz << endl;
					wiersz.erase(0,13);
					silnik = wiersz;
					i++;
				} else if (i==5) {
					cout << wiersz << endl;
					cout << endl;
					wiersz.erase(0,8);
					vin = stoi(wiersz);
					tablicaPojazdow.insert (tablicaPojazdow.begin() + id,Pojazd(typ,marka,model,silnik,vin));
					i=0;
				}
			}
		}	
	}
	plik.close();
	
	cout << "Pomyślnie zakończono odczyt z pliku.";
	return "x70";
}

int main(int argc, char *argv[]) {
	
    return EXIT_SUCCESS;
}
