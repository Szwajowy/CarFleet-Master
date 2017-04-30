#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Wszelkie dane pojazdu i dostêp do operacji z nim zwi±zanych przechowywane s± w klasie "Pojazd"
/* Mo¿na jeszcze dodaæ podklasy odpowiadaj±ce typom pojazdów (osobowe,ciê¿arowe,dostawcze) */
class Pojazd {
		private:
		// Dane pojazdu
		/* Sprecyzowaæ dane jakie powinni¶my przechowywaæ */
		string typ, marka, model, silnik;
  	int vin;

		public:
    // Konstruktor parametrowy dla zmiennych obowi±zkowych
		/* Ustaliæ jakie zmienne s± obowi±zkowe przy dodawaniu pojazdu */
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

		// Zwracanie i ustawianie warto¶ci zmiennej "Typ"
		string oddajTyp() {
				return typ;
		}

		void ustawTyp(string typ) {
				this->typ = typ;
		}

		// Zwracanie i ustawianie warto¶ci zmiennej "Marka"
		string oddajMarka() {
				return marka;
		}

		void ustawMarka(string marka) {
				this->marka = marka;
		}

		// Zwracanie i ustawianie warto¶ci zmiennej "Model"
		string oddajModel() {
				return model;
		}

		void ustawModel(string model) {
				this->model = model;
		}

		// Zwracanie i ustawianie warto¶ci zmiennej "Silnik"
		string oddajSilnik() {
				return silnik;
		}

	void ustawSilnik(string silnik) {
		this->silnik = silnik;
	}

	// Zwracanie i ustawianie warto¶ci zmiennej "VIN"
	int oddajVin() {
		return vin;
	}

	void ustawVIN(int vin) {
		this->vin = vin;
	}
};

// Definicja wektora obiektów "Pojazd"
vector <Pojazd> tablicaPojazdow;

// Metoda dodaj±ca dane pojazdu dla odpowiedniego indeksu wektora
// (je¿eli dla danego indeksu istnieje ju¿ obiekt to nastêpuje inkrementacja indeksu tego obiektu i ka¿dego nastêpnego, czyli przesuniêcie w prawo i dopiero dodanie naszego obiektu)
/* Dodaæ sprawdzanie podawanych warto¶ci i porównywanie ich do wzorów, sprecyzowanie obi±zkowych i nieobowi±zkowych danych */
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

// Metoda dodaj±ca dane pojazdu na koniec wektora
string dodajPojazd() {
	return dodajPojazd(tablicaPojazdow.size());
}

// Metoda edytuj±ca dane pojazdu o danym ID
/* Dodaæ sprawdzanie podawanych warto¶ci i porównywanie ich do wzorów, dodanie mo¿liwo¶ci edycji tylko zmiennych atrybutów pojazdów */
string edytujPojazd(unsigned int id) {
	// Obs³uga b³êdu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
			cout << "Nie dodano jeszcze zadnego pojazdu." << endl;
			cout << endl;
			return "x21";
	}

	// Obs³uga b³êdu - id pojazdu spoza zakresu wektora
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		return "x22";
	}

	string typ, marka, model, silnik, atrybut, exit;
	int vin;

	do {
		cout << "Podaj nazwe w³asno¶ci pojazdu: " << endl;
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
		cout << "Czy chcesz kontynuowaæ edycje ?" << endl;
		cin >> exit;
	} while (exit != "tak");

	return "x20";
}

// Metoda usuwaj±ca pojazd o danym ID
// (po usuniêciu obiektu nastêpuje dekrementacja indeksu ka¿dego nastêpnego, czyli przesuniêcie w lewo)
string usunPojazd(unsigned int id) {
	// Obs³uga b³êdu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
			cout << "Nie dodano jeszcze ¿adnego pojazdu." << endl;
			cout << endl;
			return "x31";
	}

	// Obs³uga b³êdu - id pojazdu spoza zakresu wektora
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		return "x32";
	}

	tablicaPojazdow.erase (tablicaPojazdow.begin() + id);

	return "x30";
}

// Metoda wy¶wietlaj±ca dane pojazdu o danym ID
/* Dodanie mo¿liwo¶ci wy¶wietlania danych w ró¿ny sposób (tabela, lista) */
string wyswietlDanePojazdu(unsigned int id) {
	// Obs³uga b³êdu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
			cout << "Nie dodano jeszcze zadnego pojazdu." << endl;
			cout << endl;
			return "x41";
	}

	// Obs³uga b³êdu - id pojazdu spoza zakresu wektora
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

// Metoda filtruj±ca dane pojazdu
/* Dodanie mo¿liwo¶ci filtrowania po kilku atrybutach i ich warto¶ciach */
string filtrujDanePojazdu() {
	// Obs³uga b³êdu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
			cout << "Nie dodano jeszcze ¿adnego pojazdu." << endl;
			cout << endl;
			return "x51";
	}

	unsigned int znalezionoWyniki = 0;
	string atrybut, wartosc;

	cout << "Podaj nazwê w³asno¶ci pojazdu: ";
	cin >> atrybut;
	cout << "Podaj warto¶æ tej w³asno¶ci: ";
	cin >> wartosc;

	// Przeszukiwanie wszystkich obiektow wektora
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
		// Obs³uga b³êdu - taki atrybut nie istnieje
		} else {
			cout << "Podany atrybut nie zosta³ znaleziony." << endl;
			cout << "Sprawd¼ pisownie i spróbuj ponownie." << endl;
			cout << endl;
			return "x52";
		}
	}

	// Obs³uga b³êdu - ¿aden obiekt nie odpowiada takim kryteriom
	if (znalezionoWyniki == 0) {
		cout << "Nie znaleziono elementów odpowiadaj±cych podanym kryteriom." << endl;
		cout << endl;
		return "x53";
	}

	return "x50";
}

// Metoda zapisuj±ca wektor do pliku
string zapiszPlik(string nazwaPliku) {

	cout << "Rozpoczynam zapis do pliku.";

	fstream plik(nazwaPliku,ios::out);
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
			plik.close();
		}
	} else {
			cout << "Wyst±pi³ problem z plikiem.";
			cout << "Upewnij siê, ¿e wprowadzi³e¶ poprawn± nazwê i rozszerzenie pliku.";
			return "x61";
		}

	cout << "Pomy¶lnie zakoñczono zapis do pliku.";
	return "x60";
}

// Metoda odczytuj±ca dane pojazdów z pliku i zapisuj±ca je do wektora
string otworzPlik(string nazwaPliku) {
	string wiersz, typ, marka, model, silnik;
	int id, i, vin;

	cout << "Otwarcie pliku nadpisze wszelkie wprowadzone zmiany." << endl;
	cout << "Przed rozpoczeciem nale¿y zapisaæ swoj± prace." << endl;
	cout << "Czy chcesz kontynuowaæ ?" << endl;
	cin >> exit;

	if (exit=="tak") {
		cout << "Rozpoczynam odczyt z pliku.";

		fstream plik(nazwaPliku,ios::in);
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
			plik.close();
		} else {
			cout << "Wyst±pi³ problem z plikiem.";
			cout << "Upewnij siê, ¿e wprowadzi³e¶ poprawn± nazwê i rozszerzenie pliku.";
			return "x72";
		}

		cout << "Pomy¶lnie zakoñczono odczyt z pliku.";
		return "x70";
	} else {
		cout << "Operacja zosta³a anulowana.";
		return "x71";
	}
}

int main(int argc, char *argv[]) {

    return EXIT_SUCCESS;
}
