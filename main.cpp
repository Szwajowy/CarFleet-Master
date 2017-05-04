#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

// Wszelkie dane pojazdu i dost�p do operacji z nim zwi�zanych przechowywane s� w klasie "Pojazd"
/* Mo�na jeszcze doda� podklasy odpowiadaj�ce typom pojazd�w (osobowe,ci�arowe,dostawcze) */
class Pojazd {
	private:
	// Dane pojazdu
	/* Sprecyzowa� dane jakie powinni�my przechowywa� */
	string typ, marka, model, silnik;
	unsigned int vin;
	 
	public:     
   	// Konstruktor parametrowy dla zmiennych obowi�zkowych
	/* Ustali� jakie zmienne s� obowi�zkowe przy dodawaniu pojazdu */  
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
	
	void ustawVIN(unsigned int vin) {
		this->vin = vin;	
	}     
};

// Definicja wektora obiektow Pojazd
vector <Pojazd> tablicaPojazdow;

class Operacja {
	private:
	// Dane operacji
	string operacja, wynik;
	 
	public:
	Operacja(string operacja, string wynik) {
		this->operacja = operacja;
		this->wynik = wynik;
	}
	
	Operacja() {
		Operacja("Operacja nieznana", "brak wyniku");
	}
	
	// Zwracanie i ustawianie warto�ci zmiennej "operacja"
	string oddajOperacja() {
		return operacja;	
	}
	
	void ustawOperacja(string operacja) {
		this->operacja = operacja;	
	} 
	
	// Zwracanie i ustawianie warto�ci zmiennej "wynik"
	string oddajWynik() {
		return wynik;	
	}
	
	void ustawWynik(string wynik) {
		this->wynik = wynik;	
	} 	
};

// Definicja wektora string�w z historia operacji
vector <Operacja> historiaOperacji;

string dodajOperacja(string operacja) {
	historiaOperacji.push_back(Operacja(operacja,"wynik nieznany"));
	return "udalo sie";
}

string wyswietlOperacja(int id) {
	cout << historiaOperacji[id].oddajOperacja() << " - " << historiaOperacji[id].oddajWynik() << endl;
	cout << endl;
	return "udalo sie";
}

// Metoda dodajaca dane pojazdu dla odpowiedniego indeksu wektora
// (je�eli dla danego indeksu istnieje ju� obiekt to nast�puje inkrementacja indeksu tego obiektu i ka�dego nast�pnego, czyli przesuni�cie w prawo i dopiero dodanie naszego obiektu)	
/* Doda� sprawdzanie podawanych warto�ci i por�wnywanie ich do wzor�w, sprecyzowanie obi�zkowych i nieobowi�zkowych danych */
string dodajPojazd(unsigned int id) {
	dodajOperacja("Dodanie pojazdu");
	int nrOperacji = historiaOperacji.size() - 1;
	
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
	
	historiaOperacji[nrOperacji].ustawWynik("udane");
	return "x10";
}

// Metoda dodajaca dane pojazdu na koniec wektora
string dodajPojazd() {
	return dodajPojazd(tablicaPojazdow.size());
}

// Metoda edytuj�ca dane pojazdu o danym ID
/* Doda� sprawdzanie podawanych warto�ci i por�wnywanie ich do wzor�w, dodanie mo�liwo�ci edycji tylko zmiennych atrybut�w pojazd�w */
string edytujPojazd(unsigned int id) {
	dodajOperacja("Edycja pojazdu");
	int nrOperacji = historiaOperacji.size() - 1;
	
	// Obs�uga b��du - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze �adnego pojazdu." << endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("nie udana");
		return "x21";	
	}
	
	// Obs�uga b��du - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("nie udana");
		return "x22";
	}
	
	string typ, marka, model, silnik, atrybut, exit;
	unsigned int vin;
	
	do {
		cout << "Podaj nazwe w�asno�ci pojazdu: ";
		cin >> atrybut;
		cout << endl;
		
		if (!stricmp(atrybut.c_str(), "typ")) {
			cout << "Podaj typ pojazdu: ";
			cin >> typ;
			cout << endl;
			tablicaPojazdow[id].ustawTyp(typ);
		} else if (!stricmp(atrybut.c_str(), "marka")) {
			cout << "Podaj marke pojazdu: ";
			cin >> marka;
			cout << endl;
			tablicaPojazdow[id].ustawMarka(marka);
		} else if (!stricmp(atrybut.c_str(), "model")) {
			cout << "Podaj model pojazdu: ";
			cin >> model;
			cout << endl;
			tablicaPojazdow[id].ustawModel(model);
		} else if (!stricmp(atrybut.c_str(), "typ silnika") || !stricmp(atrybut.c_str(), "silnik")) {
			cout << "Podaj typ silnika: ";
			cin >> silnik;
			cout << endl;
			tablicaPojazdow[id].ustawSilnik(silnik);
		} else if (!stricmp(atrybut.c_str(), "nr.vin") || !stricmp(atrybut.c_str(), "nr vin") || !stricmp(atrybut.c_str(), "numer vin")) {
			cout << "Podaj identyfikator VIN pojazdu: ";
			cin >> vin;
			cout << endl;
			tablicaPojazdow[id].ustawVIN(vin);
		}
		cout << "Czy chcesz kontynuowa� edycj� ?" << endl;
		cin >> exit;
		cout << endl;
	} while (!stricmp(exit.c_str(), "tak"));
	
	historiaOperacji[nrOperacji].ustawWynik("udana");
	return "x20";
}

// Metoda usuwaj�ca pojazd o danym ID	
// (po usuni�ciu obiektu nast�puje dekrementacja indeksu ka�dego nast�pnego, czyli przesuni�cie w lewo)	
string usunPojazd(unsigned int id) {
	dodajOperacja("Usuni�cie pojazdu");
	int nrOperacji = historiaOperacji.size() - 1;
	
	// Obs�uga b��du - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze �adnego pojazdu." << endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("nie udane");
		return "x31";	
	}
	
	// Obs�uga b��du - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("nie udane");
		return "x32";
	}
	
	tablicaPojazdow.erase (tablicaPojazdow.begin() + id);
	cout << "Pomy�lnie usuni�to pojazd." << endl;
	cout << endl;
	
	historiaOperacji[nrOperacji].ustawWynik("udane");
	return "x30";
}

// Metoda wyswietlajaca dane pojazdu o danym ID	
/* Dodanie mo�liwo�ci wy�wietlania danych w r�ny spos�b (tabela, lista) */
string wyswietlPojazd(unsigned int id, string format) {
	dodajOperacja("Wy�wietlanie danych pojazdu");
	int nrOperacji = historiaOperacji.size() - 1;
	
	// Obs�uga b��du - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze �adnego pojazdu." << endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("nie udane");
		return "x41";	
	}
	
	// Obs�uga b��du - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("nie udane");
		return "x42";
	}
	
	if (!stricmp(format.c_str(), "lista")) {
		cout << "Typ: " << tablicaPojazdow[id].oddajTyp() << endl;
	    cout << "Marka: " << tablicaPojazdow[id].oddajMarka() << endl;
	    cout << "Model: " << tablicaPojazdow[id].oddajModel() << endl;
	    cout << "Typ silnika: " << tablicaPojazdow[id].oddajSilnik() << endl;
	    cout << "Nr. VIN: " << tablicaPojazdow[id].oddajVin() << endl;
	    cout << endl;
    } else if (!stricmp(format.c_str(), "tabela")) {
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
    
    historiaOperacji[nrOperacji].ustawWynik("udane");
    return "x40";	
}

// Metoda filtruj�ca dane pojazdu
/* Dodanie mo�liwo�ci filtrowania po kilku atrybutach i ich warto�ciach */
string przeszukajPojazdy() {
	dodajOperacja("Przeszukanie danych pojazd�w");
	int nrOperacji = historiaOperacji.size() - 1;
	
	// Obs�uga b��du - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze �adnego pojazdu." << endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("nie udane");
		return "x51";	
	}
	
	string atrybut, wartosc, format;
	unsigned int znalezionoWyniki = 0;
	
	cout << "Podaj nazwe w�asno�ci pojazdu: ";
	cin >> atrybut;
	cout << "Podaj warto�c tej w�asno�ci: ";
	cin >> wartosc;
	cout << endl;
	
	cout << "Chcesz wy�wietli� wyniki jako \"tabela\", czy \"lista\" ?" << endl;
	cin >> format;
	cout << endl;
	
	if (!stricmp(format.c_str(), "tabela")) {
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
	// Przeszukiwanie wszystkich obiekt�w wektora
	for (int i=0; i<tablicaPojazdow.size();i++) {
		if (!stricmp(atrybut.c_str(), "typ")) {
			if (tablicaPojazdow[i].oddajTyp()==wartosc) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (!stricmp(atrybut.c_str(), "marka")) {
			if (tablicaPojazdow[i].oddajMarka()==wartosc) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (!stricmp(atrybut.c_str(), "model")) {
			if (tablicaPojazdow[i].oddajModel()==wartosc) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (!stricmp(atrybut.c_str(), "typ silnika") || !stricmp(atrybut.c_str(), "silnik")) {
			if (tablicaPojazdow[i].oddajSilnik()==wartosc) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (atrybut == "Nr.Vin" || atrybut == "nr.vin" || atrybut == "NR.VIN" || atrybut == "Vin" || atrybut == "vin" || atrybut == "VIN" || atrybut == "NrVin" || atrybut == "nrvin" || atrybut == "NRVIN") {
			if (tablicaPojazdow[i].oddajVin()==stoi(wartosc)) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		// Obs�uga b��du - nie istnieje taki atrybut
		} else {
			cout << "Taki atrybut zosta� nie znaleziony." << endl;
			cout << "Sprawd� pisownie i spr�buj ponownie." << endl;
			cout << endl;
			
			historiaOperacji[nrOperacji].ustawWynik("nie udane");
			return "x52";
		}
	}
	
	if (!stricmp(format.c_str(), "tabela")) {
		cout << endl;
	}
	
	// Obs�uga b��du - nie istniej� obiekty o takich atrybutach
	if (znalezionoWyniki == 0) {
		cout << "Nie znaleziono element�w odpowiadaj�cych podanym kryteriom." << endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("nie udane");
		return "x53";	
	} else {
		cout << "Znaleziono " << znalezionoWyniki << " element�w odpowiadaj�cych podanym kryteriom." << endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("udane");
		return "x50";
	}
}

// Metoda zapisuj�ca wektor do pliku
string zapiszPlik(string nazwaPliku) {
	dodajOperacja("Zapisanie danych do pliku");
	int nrOperacji = historiaOperacji.size() - 1;
	
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
		cout << "Wyst�pi� problem z plikiem." << endl;
		cout << "Upewnij si�, �e wprowadzi�e� poprawn� nazw� i rozszerzenie pliku." << endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("nie udane");
		return "x61";
	}
	
	cout << "Pomy�lnie zako�czono zapis do pliku." << endl;
	cout << endl;
	
	historiaOperacji[nrOperacji].ustawWynik("udana");
	return "x60";
}

// Metoda odczytuj�ca dane pojazd�w z pliku i zapisuj�ca je do wektora
string otworzPlik(string nazwaPliku) {
	dodajOperacja("Otwarcie pliku z danymi");
	int nrOperacji = historiaOperacji.size() - 1;
	
	string exit;

	cout << "Otwarcie pliku nadpisze wszelkie wprowadzone zmiany." << endl;
	cout << "Przed rozpoczeciem nale�y zapisa� swoj� prace." << endl;
	cout << "Czy chcesz kontynuowa� ?" << endl;
	cin >> exit;
	cout << endl;

	if (!stricmp(exit.c_str(), "tak")) {
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
			cout << "Wyst�pi� problem z plikiem."<< endl;
			cout << "Upewnij si�, �e wprowadzi�e� poprawn� nazw� i rozszerzenie pliku."<< endl;
			cout << endl;
			
			historiaOperacji[nrOperacji].ustawWynik("nie udane");
			return "x72";
		}
		cout << "Pomy�lnie zako�czono odczyt z pliku."<< endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("udana");
		return "x70";
	} else {
		cout << "Operacja zosta�a anulowana."<< endl;
		cout << endl;
		
		historiaOperacji[nrOperacji].ustawWynik("nie udane");
		return "x71";
	}
}

int wyswietlMenu() {
	unsigned int ile, id, blad;
	string plik, zapisz, format;
	char opcja, pre_id;
	blad = 0;
	
	cout << "#############################" << endl;
	cout << "1. Plik" << endl;
	cout << "2. Dodaj pojazd" << endl;
	cout << "3. Edytuj pojazd" << endl;
	cout << "4. Usu� pojazd" << endl;
	cout << "5. Wy�wietl pojazd/y" << endl;
	cout << "6. Filtruj pojazdy" << endl;
	cout << "7. Wyj�cie" << endl;
	cout << "#############################" << endl;
	cout << endl;
	
	do {
		cout << "Podaj numer opcji: ";
		cin >> opcja;
		cout << endl;
		
		if (opcja != '1' && opcja != '2' && opcja != '3' && opcja != '4' && opcja != '5' && opcja != '6' && opcja != '7') {
			cout << "Prosz� wybra� opcj� z zakresu od 1 do 7!" << endl;
			cout << endl;
		}
	} while (opcja != '1' && opcja != '2' && opcja != '3' && opcja != '4' && opcja != '5' && opcja != '6' && opcja != '7');
	
	switch (opcja) {
		case '1':
			cout << "1. Otw�rz" << endl;
			cout << "2. Zapisz" << endl;
			cout << endl;
			
			do {
				cout << "Podaj numer opcji: ";
				cin >> opcja;
				cout << endl;
				
				if (opcja != '1' && opcja != '2') {
					cout << "Prosz� wybra� opcj� 1 lub 2!" << endl;
					cout << endl;
				}
			} while (opcja != '1' && opcja != '2');
			
			switch(opcja) {
				case '1':
					cout << "Podaj nazw� pliku do otwarcia (np. Pojazdy.txt)." << endl;
					cin >> plik;
					cout << endl;
					
					otworzPlik(plik);
					break;
				case '2':
					cout << "Podaj nazw� pliku do kt�rego chcesz zapisa� (np. Pojazdy.txt)." << endl;
					cin >> plik;
					cout << endl;
					
					zapiszPlik(plik);
					break;
			}
			break;
		case '2':		
			do {
				cout << "Ile pojazd�w chcesz doda�: ";		
				cin >> ile;
				cout << endl;
				
				if (ile <= 0) {
					cout << "Prosz� poda� warto�� wi�ksz� od zera!" << endl;
					cout << endl;
				}
			} while (opcja != '1' && opcja != '2');
						
			for (int i=0; i<ile;i++) {
				dodajPojazd();
			}
			break;
		case '3':
			do {
				blad = 0;
				cout << "Podaj ID pojazdu do edycji: ";		
				cin >> pre_id;
				cout << endl;
				
				if((isdigit(pre_id))==1){		//isdigit zwraca 1 dla prawdy, 0 dla fa�szu
					id = (unsigned int)pre_id - 48;		//Je�li pre_id jest warto�ci� liczbow� to przypisuje j� do id, a -48 jest dlatego, �e po konwersji zwraca warto�� decymaln� ascii http://www.asciitable.com/index/asciifull.gif
					edytujPojazd(id);
					break;
				} else {
					cout << "ID musi by� liczb�!" << endl;
					blad = 1;
				}
			} while (blad = 1);
		case '4':
			do {
				blad = 0;
				cout << "Podaj ID pojazdu do edycji: ";		
				cin >> pre_id;
				cout << endl;
				
				if((isdigit(pre_id))==1){		//isdigit zwraca 1 dla prawdy, 0 dla fa�szu
					id = (unsigned int)pre_id - 48;		//Je�li pre_id jest warto�ci� liczbow� to przypisuje j� do id, a -48 jest dlatego, �e po konwersji zwraca warto�� decymaln� ascii http://www.asciitable.com/index/asciifull.gif
					usunPojazd(id);
					break;
				} else {
					cout << "ID musi by� liczb�!" << endl;
					blad = 1;
				}
			} while (blad = 1);
			break;	
		case '5':
			cout << "1. Wy�wietl jeden pojazd o podanym ID." << endl;
			cout << "2. Wy�wietl wszystkie pojazdy." << endl;
			cout << endl;

			do {
				cout << "Podaj numer opcji: ";
				cin >> opcja;
				cout << endl;
				
				if (opcja != '1' && opcja != '2') {
					cout << "Prosz� wybra� opcj� 1 lub 2 !" << endl;
					cout << endl;
				}
			} while (opcja != '1' && opcja != '2');
			
			switch(opcja) {
				case '1':
					do {
						blad = 0;
						cout << "Podaj ID pojazdu do edycji: ";		
						cin >> pre_id;
						cout << endl;
						
						if((isdigit(pre_id))==1){		//isdigit zwraca 1 dla prawdy, 0 dla fa�szu
							id = (unsigned int)pre_id - 48;		//Je�li pre_id jest warto�ci� liczbow� to przypisuje j� do id, a -48 jest dlatego, �e po konwersji zwraca warto�� decymaln� ascii http://www.asciitable.com/index/asciifull.gif
							if (id < 0){
								cout << "ID nie mo�e by� ujemne!" << endl;
								blad = 1;	
							} else {
								wyswietlPojazd(id, "lista");
								break;
							}
						} else {
							cout << "ID musi by� liczb�!" << endl;
							blad = 1;
						}
					} while (blad = 1);
					break;
				case '2':
					do {
						blad = 0;
						cout << "Chcesz wy�wietli� wyniki jako \"lista\", czy \"tabela\" ?" << endl;
						cin >> format;
						cout << endl;
						
						if (stricmp(format.c_str(), "lista") && stricmp(format.c_str(), "tabela")) {
							cout << "B��d! Prosz� wybra� format \"lista\" lub \"tabela\"" << endl;
							cout << endl;
							blad = 1;
						} else {
							if (!stricmp(format.c_str(), "tabela")) {
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
								wyswietlPojazd(i,format);	
							}
							
							if (!stricmp(format.c_str(), "tabela")) {
								cout << endl;
							}
							
							break;
						}
					} while (blad = 1);
			}
			break;
		case '6':
			przeszukajPojazdy();
			break;
		case '7':
			cout << "Czy chcesz zapisa� prac� przed wyj�ciem ?" << endl;
			cin >> zapisz;
			cout << endl;
			
			if (!stricmp(zapisz.c_str(), "tak")) {
				zapiszPlik("baza.txt");
			}
			return 1;
			break;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL,"");
	int exit;

	do {
		exit = wyswietlMenu();
	} while (exit != 1);
	
    return EXIT_SUCCESS;
}
