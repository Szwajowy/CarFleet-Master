#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Wszelkie dane pojazdu i dostêp do operacji z nim zwi¹zanych przechowywane s¹ w klasie "Pojazd"
/* Mo¿na jeszcze dodaæ podklasy odpowiadaj¹ce typom pojazdów (osobowe,ciê¿arowe,dostawcze) */
class Pojazd {
	private:
	// Dane pojazdu
	/* Sprecyzowaæ dane jakie powinniœmy przechowywaæ */
	string typ, marka, model, silnik;
	unsigned int vin;
	 
	public:     
   	// Konstruktor parametrowy dla zmiennych obowi¹zkowych
	/* Ustaliæ jakie zmienne s¹ obowi¹zkowe przy dodawaniu pojazdu */  
	Pojazd(string typ, string marka, string model, string silnik,unsigned int vin) {
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
	
	// Zwracanie i ustawianie wartoœci zmiennej "Typ"
	string oddajTyp() {
		return typ;	
	}
	
	void ustawTyp(string typ) {
		this->typ = typ;	
	}
	
	// Zwracanie i ustawianie wartoœci zmiennej "Marka"
	string oddajMarka() {
		return marka;	
	}
	
	void ustawMarka(string marka) {
		this->marka = marka;	
	}
	
	// Zwracanie i ustawianie wartoœci zmiennej "Model"
	string oddajModel() {
		return model;	
	}
	
	void ustawModel(string model) {
		this->model = model;	
	}  
	
	// Zwracanie i ustawianie wartoœci zmiennej "Silnik"
	string oddajSilnik() {
		return silnik;	
	}
	
	void ustawSilnik(string silnik) {
		this->silnik = silnik;	
	}
	
	// Zwracanie i ustawianie wartoœci zmiennej "VIN"
	int oddajVin() {
		return vin;	
	}
	
	void ustawVIN(unsigned int vin) {
		this->vin = vin;	
	}     
};

// Definicja wektora obiektow Pojazd
vector <Pojazd> tablicaPojazdow;

// Definicja wektora stringów z historia operacji
//vector <Operacja> historiaOperacji;

/*string dodajDoHistori(string operacja, string wynik) {
	historiaOperacji.push_back(Operacja("Dodaj pojazd"));
}*/

// Metoda dodajaca dane pojazdu dla odpowiedniego indeksu wektora
// (je¿eli dla danego indeksu istnieje ju¿ obiekt to nastêpuje inkrementacja indeksu tego obiektu i ka¿dego nastêpnego, czyli przesuniêcie w prawo i dopiero dodanie naszego obiektu)	
/* Dodaæ sprawdzanie podawanych warto¹ci i porównywanie ich do wzorów, sprecyzowanie obi¹zkowych i nieobowi¹zkowych danych */
string dodajPojazd(unsigned int id) {
	//dodajDoHistori("dodajPojazd");
	
	string typ, marka, model, silnik;
	unsigned int vin;

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

// Metoda edytuj¹ca dane pojazdu o danym ID
/* Dodaæ sprawdzanie podawanych wartoœci i porównywanie ich do wzorów, dodanie mo¿liwoœci edycji tylko zmiennych atrybutów pojazdów */
string edytujPojazd(unsigned int id) {
	// Obs³uga b³êdu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze ¿adnego pojazdu." << endl;
		cout << endl;
		return "x21";	
	}
	
	// Obs³uga b³êdu - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		return "x22";
	}
	
	string typ, marka, model, silnik, atrybut, exit;
	unsigned int vin;
	
	do {
		cout << "Podaj nazwe w³asnoœci pojazdu: ";
		cin >> atrybut;
		cout << endl;
		
		if (atrybut == "Typ" || atrybut == "typ" || atrybut == "TYP") {
			cout << "Podaj typ pojazdu: ";
			cin >> typ;
			cout << endl;
			tablicaPojazdow[id].ustawTyp(typ);
		} else if (atrybut == "Marka" || atrybut == "marka" || atrybut == "MARKA") {
			cout << "Podaj marke pojazdu: ";
			cin >> marka;
			cout << endl;
			tablicaPojazdow[id].ustawMarka(marka);
		} else if (atrybut == "Model" || atrybut == "model" || atrybut == "MODEL") {
			cout << "Podaj model pojazdu: ";
			cin >> model;
			cout << endl;
			tablicaPojazdow[id].ustawModel(model);
		} else if (atrybut == "Typ silnika" || atrybut == "typ silnika" || atrybut == "TYP SILNIKA" || atrybut == "Silnik" || atrybut == "silnik" || atrybut == "SILNIK") {
			cout << "Podaj typ silnika: ";
			cin >> silnik;
			cout << endl;
			tablicaPojazdow[id].ustawSilnik(silnik);
		} else if (atrybut == "Nr.Vin" || atrybut == "nr.vin" || atrybut == "NR.VIN" || atrybut == "Vin" || atrybut == "vin" || atrybut == "VIN" || atrybut == "NrVin" || atrybut == "nrvin" || atrybut == "NRVIN") {
			cout << "Podaj identyfikator VIN pojazdu: ";
			cin >> vin;
			cout << endl;
			tablicaPojazdow[id].ustawVIN(vin);
		}
		cout << "Czy chcesz kontynuowaæ edycjê ?" << endl;
		cin >> exit;
		cout << endl;
	} while (exit == "Tak" || exit == "tak" || exit == "TAK");
	
	return "x20";
}

// Metoda usuwaj¹ca pojazd o danym ID	
// (po usuniêciu obiektu nastêpuje dekrementacja indeksu ka¿dego nastêpnego, czyli przesuniêcie w lewo)	
string usunPojazd(unsigned int id) {
	// Obs³uga b³êdu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze ¿adnego pojazdu." << endl;
		cout << endl;
		return "x31";	
	}
	
	// Obs³uga b³êdu - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		return "x32";
	}
	
	tablicaPojazdow.erase (tablicaPojazdow.begin() + id);
	cout << "Pomyœlnie usuniêto pojazd." << endl;
	cout << endl;
	
	return "x30";
}

// Metoda wyswietlajaca dane pojazdu o danym ID	
/* Dodanie mo¿liwoœci wyœwietlania danych w ró¿ny sposób (tabela, lista) */
string wyswietlDanePojazdu(unsigned int id, string format) {
	// Obs³uga b³êdu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze ¿adnego pojazdu." << endl;
		cout << endl;
		return "x41";	
	}
	
	// Obs³uga b³êdu - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		return "x42";
	}
	
	if (format == "lista") {
		cout << "Typ: " << tablicaPojazdow[id].oddajTyp() << endl;
	    cout << "Marka: " << tablicaPojazdow[id].oddajMarka() << endl;
	    cout << "Model: " << tablicaPojazdow[id].oddajModel() << endl;
	    cout << "Typ silnika: " << tablicaPojazdow[id].oddajSilnik() << endl;
	    cout << "Nr. VIN: " << tablicaPojazdow[id].oddajVin() << endl;
	    cout << endl;
    } else if (format == "tabela") {
    cout.width( 15 );
		cout << left << tablicaPojazdow[id].oddajTyp();
		cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajMarka();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajModel();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajSilnik();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajVin();
	    cout << endl;	
	}
    
    return "x40";	
}

// Metoda filtruj¹ca dane pojazdu
/* Dodanie mo¿liwoœci filtrowania po kilku atrybutach i ich wartoœciach */
string filtrujDanePojazdu() {
	// Obs³uga b³êdu - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze ¿adnego pojazdu." << endl;
		cout << endl;
		return "x51";	
	}
	
	string atrybut, wartosc, format;
	unsigned int znalezionoWyniki = 0;
	
	cout << "Podaj nazwe w³asnoœci pojazdu: ";
	cin >> atrybut;
	cout << "Podaj wartoœc tej w³asnoœci: ";
	cin >> wartosc;
	cout << endl;
	
	cout << "Chcesz wyœwietliæ wyniki jako \"tabela\", czy \"lista\" ?" << endl;
	cin >> format;
	cout << endl;
	
	if (format == "tabela") {
		cout.width( 15 );
		cout << left << "Typ"; 
		cout.width( 15 );
		cout << left << "Marka"; 
		cout.width( 15 );
		cout << left << "Model"; 
		cout.width( 15 );
		cout << left << "Typ silnika"; 
		cout.width( 15 );
		cout << left << "Nr. VIN";
		cout << endl;
	}
	// Przeszukiwanie wszystkich obiektów wektora
	for (int i=0; i<tablicaPojazdow.size();i++) {
		if (atrybut == "Typ" || atrybut == "typ" || atrybut == "TYP") {
			if (tablicaPojazdow[i].oddajTyp()==wartosc) {
				wyswietlDanePojazdu(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (atrybut == "Marka" || atrybut == "marka" || atrybut == "MARKA") {
			if (tablicaPojazdow[i].oddajMarka()==wartosc) {
				wyswietlDanePojazdu(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (atrybut == "Model" || atrybut == "model" || atrybut == "MODEL") {
			if (tablicaPojazdow[i].oddajModel()==wartosc) {
				wyswietlDanePojazdu(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (atrybut == "Typ silnika" || atrybut == "typ silnika" || atrybut == "TYP SILNIKA" || atrybut == "Silnik" || atrybut == "silnik" || atrybut == "SILNIK") {
			if (tablicaPojazdow[i].oddajSilnik()==wartosc) {
				wyswietlDanePojazdu(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (atrybut == "Nr.Vin" || atrybut == "nr.vin" || atrybut == "NR.VIN" || atrybut == "Vin" || atrybut == "vin" || atrybut == "VIN" || atrybut == "NrVin" || atrybut == "nrvin" || atrybut == "NRVIN") {
			if (tablicaPojazdow[i].oddajVin()==stoi(wartosc)) {
				wyswietlDanePojazdu(i,format);
				znalezionoWyniki += 1;	
			}
		// Obs³uga b³êdu - nie istnieje taki atrybut
		} else {
			cout << "Taki atrybut zosta³ nie znaleziony." << endl;
			cout << "SprawdŸ pisownie i spróbuj ponownie." << endl;
			cout << endl;
			return "x52";
		}
	}
	
	if (format == "tabela") {
		cout << endl;
	}
	
	// Obs³uga b³êdu - nie istniej¹ obiekty o takich atrybutach
	if (znalezionoWyniki == 0) {
		cout << "Nie znaleziono elementów odpowiadaj¹cych podanym kryteriom." << endl;
		cout << endl;
		return "x53";	
	} else {
		cout << "Znaleziono " << znalezionoWyniki << " elementów odpowiadaj¹cych podanym kryteriom." << endl;
		cout << endl;
		return "x50";
	}
}

// Metoda zapisuj¹ca wektor do pliku
string zapiszPlik(string nazwaPliku) {
	
	cout << "Rozpoczynam zapis do pliku." << endl;
	cout << endl;
	
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
		}
		plik.close();	
	} else {
		cout << "Wyst¹pi³ problem z plikiem." << endl;
		cout << "Upewnij siê, ¿e wprowadzi³eœ poprawn¹ nazwê i rozszerzenie pliku." << endl;
		cout << endl;
		return "x61";
	}
	
	cout << "Pomyœlnie zakoñczono zapis do pliku." << endl;
	cout << endl;
	return "x60";
}

// Metoda odczytuj¹ca dane pojazdów z pliku i zapisuj¹ca je do wektora
string otworzPlik(string nazwaPliku) {
	string exit;

	cout << "Otwarcie pliku nadpisze wszelkie wprowadzone zmiany." << endl;
	cout << "Przed rozpoczeciem nale¿y zapisaæ swoj¹ prace." << endl;
	cout << "Czy chcesz kontynuowaæ ?" << endl;
	cin >> exit;
	cout << endl;

	if (exit == "Tak" || exit == "tak" || exit == "TAK") {
		cout << "Rozpoczynam odczyt z pliku." << endl;
		cout << endl;

		fstream plik(nazwaPliku,ios::in);
		if( plik.good() ) {
			string wiersz, typ, marka, model, silnik;
			unsigned int id, vin, i = 0;
			while ( !plik.eof() ) {
				getline(plik, wiersz);
				if (wiersz != "") {
					if (i==0) {
						wiersz.erase(0,10);
						id = stoi(wiersz);
						i++;
					} else if (i==1) {
						wiersz.erase(0,5);
						typ = wiersz;
						i++;
					} else if (i==2) {
						wiersz.erase(0,7);
						marka = wiersz;
						i++;
					} else if (i==3) {
						wiersz.erase(0,7);
						model = wiersz;
						i++;
					} else if (i==4) {
						wiersz.erase(0,13);
						silnik = wiersz;
						i++;
					} else if (i==5) {
						wiersz.erase(0,8);
						vin = stoi(wiersz);
						tablicaPojazdow.insert (tablicaPojazdow.begin() + id,Pojazd(typ,marka,model,silnik,vin));
						i=0;
					}
				}
			}
			plik.close();
		} else {
			cout << "Wyst¹pi³ problem z plikiem."<< endl;
			cout << "Upewnij siê, ¿e wprowadzi³eœ poprawn¹ nazwê i rozszerzenie pliku."<< endl;
			cout << endl;
			return "x72";
		}
		cout << "Pomyœlnie zakoñczono odczyt z pliku."<< endl;
		cout << endl;
		return "x70";
	} else {
		cout << "Operacja zosta³a anulowana."<< endl;
		cout << endl;
		return "x71";
	}	
	cout << "Pomyœlnie zakoñczono odczyt z pliku."<< endl;
	cout << endl;
	return "x70";
}

int wyswietlMenu() {
	unsigned int opcja, ile, id;
	string plik, zapisz, format;
	
	cout << "#############################" << endl;
	cout << "1. Plik" << endl;
	cout << "2. Dodaj pojazd" << endl;
	cout << "3. Edytuj pojazd" << endl;
	cout << "4. Usuñ pojazd" << endl;
	cout << "5. Wyswietl pojazd/y" << endl;
	cout << "6. Filtruj pojazdy" << endl;
	cout << "7. Wyjœcie" << endl;
	cout << "#############################" << endl;
	cout << endl;
	
	cout << "Podaj numer opcji: ";
	cin >> opcja;
	cout << endl;
	
	switch (opcja) {
		case 1:
			cout << "1. Otworz" << endl;
			cout << "2. Zapisz" << endl;
			cout << endl;
			
			cout << "Podaj numer opcji: ";
			cin >> opcja;
			cout << endl;
			
			switch(opcja) {
				case 1:
					cout << "Podaj nazwê pliku do otwarcia (np. Pojazdy.txt)." << endl;
					cin >> plik;
					cout << endl;
					
					otworzPlik(plik);
					break;
				case 2:
					cout << "Podaj nazwê pliku do którego chcesz zapisaæ (np. Pojazdy.txt)." << endl;
					cin >> plik;
					cout << endl;
					
					zapiszPlik(plik);
					break;
			}
			break;
		case 2:
			cout << "Ile pojazdów chcesz dodaæ: ";		
			cin >> ile;
			cout << endl;
			
			for (int i=0; i<ile;i++) {
				dodajPojazd();
			}
			break;
		case 3:
			cout << "Podaj ID pojazdu do edycji: ";		
			cin >> id;
			cout << endl;
			
			edytujPojazd(id);
			break;
		case 4:
			cout << "Podaj ID pojazdu do usuniêcia: ";			
			cin >> id;
			cout << endl;
			
			usunPojazd(id);
			break;	
		case 5:
			cout << "1. Wyœwietl jeden pojazd o podanym ID." << endl;
			cout << "2. Wyœwietl wszystkie pojazdy." << endl;
			cout << endl;
			
			cout << "Podaj numer opcji: ";
			cin >> opcja;
			cout << endl;
			
			switch(opcja) {
				case 1:
					cout << "Podaj ID pojazdu do wyœwietlnia: ";
					cin >> id;
					cout << endl;
					
					wyswietlDanePojazdu(id, "lista");
					break;
				case 2:
					cout << "Chcesz wyœwietliæ wyniki jako \"tabela\", czy \"lista\" ?" << endl;
					cin >> format;
					cout << endl;
					
					if (format == "tabela") {
						cout.width( 15 );
						cout << left << "Typ"; 
						cout.width( 15 );
						cout << left << "Marka"; 
						cout.width( 15 );
						cout << left << "Model"; 
						cout.width( 15 );
						cout << left << "Typ silnika"; 
						cout.width( 15 );
						cout << left << "Nr. VIN";
						cout << endl;
					}
					
					for (int i=0; i<tablicaPojazdow.size();i++) {
						wyswietlDanePojazdu(i,format);	
					}
					
					if (format == "tabela") {
						cout << endl;
					}
					
					break;
			}
			break;
		case 6:
			filtrujDanePojazdu();
			break;
		case 7:
			cout << "Czy chcesz zapisaæ pracê przed wyjœciem ?" << endl;
			cin >> zapisz;
			cout << endl;
			
			if (zapisz == "Tak" || zapisz == "tak" || zapisz == "TAK") {
				zapiszPlik("baza.txt");
			}
			return 1;
			break;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	int exit;

	do {
		exit = wyswietlMenu();
	} while (exit != 1);
	
    return EXIT_SUCCESS;
}
