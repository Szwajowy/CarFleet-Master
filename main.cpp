#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "pojazd.hpp"
#include "operacja.hpp"

using namespace std;

// Definicja wektora obiektow Pojazd
vector <Pojazd> tablicaPojazdow;

// Definicja wektora string�w z historia operacji
vector <Operacja> historiaOperacji;

string dodajOperacja(string operacja) {
	if (historiaOperacji.size() > 198) {
		for (int i=0; i < 20; i++) {
			historiaOperacji.erase (historiaOperacji.begin());			
		}
	}
	historiaOperacji.push_back(Operacja(operacja,"wynik nieznany"));
	return "x80";
}

string wyswietlOperacja(int id) {
	cout << historiaOperacji[id].oddajOperacja() << " - " << historiaOperacji[id].oddajWynik() << endl;
	return "x90";
}

// Metoda dodajaca dane pojazdu dla odpowiedniego indeksu wektora
// (je�eli dla danego indeksu istnieje ju� obiekt to nast�puje inkrementacja indeksu tego obiektu i ka�dego nast�pnego, czyli przesuni�cie w prawo i dopiero dodanie naszego obiektu)	
/* Doda� sprawdzanie podawanych warto�ci i por�wnywanie ich do wzor�w, sprecyzowanie obi�zkowych i nieobowi�zkowych danych */
string dodajPojazd(unsigned int id) {
	string typ, marka, model, paliwo, vin;

	cout << "Podaj typ pojazdu: ";
	cin >> typ;
	cout << "Podaj marke pojazdu: ";
	cin >> marka;
	cout << "Podaj model pojazdu: ";
	cin >> model;
	cout << "Podaj rodzaj paliwa: ";
	cin >> paliwo;
	cout << "Podaj identyfikator VIN pojazdu: ";
	cin >> vin;
	
	tablicaPojazdow.insert (tablicaPojazdow.begin() + id,Pojazd(typ,marka,model,paliwo,vin));
	cout << endl;

	return "x10";
}

// Metoda dodajaca dane pojazdu na koniec wektora
string dodajPojazd() {
	return dodajPojazd(tablicaPojazdow.size());
}

// Metoda edytuj�ca dane pojazdu o danym ID
/* Doda� sprawdzanie podawanych warto�ci i por�wnywanie ich do wzor�w, dodanie mo�liwo�ci edycji tylko zmiennych atrybut�w pojazd�w */
string edytujPojazd(unsigned int id) {
	// Obs�uga b��du - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze �adnego pojazdu." << endl;
		cout << endl;
		
		return "x21";	
	}
	
	// Obs�uga b��du - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		
		return "x22";
	}
	
	string typ, marka, model, paliwo, vin, atrybut, exit;
	
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
		} else if (!stricmp(atrybut.c_str(), "rodzaj paliwa") || !stricmp(atrybut.c_str(), "paliwo")) {
			cout << "Podaj rodzaj paliwa: ";
			cin >> paliwo;
			cout << endl;
			tablicaPojazdow[id].ustawPaliwo(paliwo);
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
	
	return "x20";
}

// Metoda usuwaj�ca pojazd o danym ID	
// (po usuni�ciu obiektu nast�puje dekrementacja indeksu ka�dego nast�pnego, czyli przesuni�cie w lewo)	
string usunPojazd(unsigned int id) {
	// Obs�uga b��du - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze �adnego pojazdu." << endl;
		cout << endl;

		return "x31";	
	}
	
	// Obs�uga b��du - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;

		return "x32";
	}
	
	tablicaPojazdow.erase (tablicaPojazdow.begin() + id);
	cout << "Pomy�lnie usuni�to pojazd." << endl;
	cout << endl;

	return "x30";
}

// Metoda wyswietlajaca dane pojazdu o danym ID	
/* Dodanie mo�liwo�ci wy�wietlania danych w r�ny spos�b (tabela, lista) */
string wyswietlPojazd(unsigned int id, string format) {
	// Obs�uga b��du - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze �adnego pojazdu." << endl;
		cout << endl;
		
		return "x41";	
	}
	
	// Obs�uga b��du - nie istnieje taki element
	if (id >=tablicaPojazdow.size()) {
		cout << "Nie istnieje pojazd o podanym ID." << endl;
		cout << endl;
		
		return "x42";
	}
	
	if (!stricmp(format.c_str(), "lista")) {
		cout << "ID: " << id << endl;
		cout << "Typ: " << tablicaPojazdow[id].oddajTyp() << endl;
	    cout << "Marka: " << tablicaPojazdow[id].oddajMarka() << endl;
	    cout << "Model: " << tablicaPojazdow[id].oddajModel() << endl;
	    cout << "Rodzaj paliwa: " << tablicaPojazdow[id].oddajPaliwo() << endl;
	    cout << "Nr. VIN: " << tablicaPojazdow[id].oddajVin() << endl;
	    cout << endl;
    } else if (!stricmp(format.c_str(), "tabela")) {
		cout.width( 5 );
		cout << left << id;
		cout.width( 15 );
		cout << left << tablicaPojazdow[id].oddajTyp();
		cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajMarka();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajModel();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajPaliwo();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajVin();
	    cout << endl;	
	}

    return "x40";	
}

// Metoda filtruj�ca dane pojazdu
string przeszukajPojazdy() {
	// Obs�uga b��du - wektor jest pusty
	if (tablicaPojazdow.size()<=0){
		cout << "Nie dodano jeszcze �adnego pojazdu." << endl;
		cout << endl;
		
		return "x51";	
	}
	
	string atrybut, wartosc, format;
	unsigned int znalezionoWyniki = 0;
	
	cout << "Podaj nazwe w�asno�ci pojazdu: ";
	cin >> atrybut;
	cout << "Podaj warto�� tej w�asno�ci: ";
	cin >> wartosc;
	cout << endl;
	
	cout << "Chcesz wy�wietli� wyniki jako \"tabela\", czy \"lista\" ?" << endl;
	cin >> format;
	cout << endl;
	
	if (!stricmp(format.c_str(), "tabela")) {
		cout.width( 5 );
		cout << left << "ID"; 
		cout.width( 15 );
		cout << left << "Typ"; 
		cout.width( 15 );
		cout << left << "Marka"; 
		cout.width( 15 );
		cout << left << "Model"; 
		cout.width( 15 );
		cout << left << "Rodzaj paliwa"; 
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
		} else if (!stricmp(atrybut.c_str(), "rodzaj paliwa") || !stricmp(atrybut.c_str(), "paliwo")) {
			if (tablicaPojazdow[i].oddajPaliwo()==wartosc) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (atrybut == "Nr.Vin" || atrybut == "nr.vin" || atrybut == "NR.VIN" || atrybut == "Vin" || atrybut == "vin" || atrybut == "VIN" || atrybut == "NrVin" || atrybut == "nrvin" || atrybut == "NRVIN") {
			if (tablicaPojazdow[i].oddajVin()==wartosc) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		// Obs�uga b��du - nie istnieje taki atrybut
		} else {
			cout << "Taki atrybut zosta� nie znaleziony." << endl;
			cout << "Sprawd� pisownie i spr�buj ponownie." << endl;
			cout << endl;

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
		
		return "x53";	
	} else {
		cout << "Znaleziono " << znalezionoWyniki << " element�w odpowiadaj�cych podanym kryteriom." << endl;
		cout << endl;

		return "x50";
	}
}

// Metoda zapisuj�ca wektor do pliku
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
			plik << "Rodzaj paliwa: " << tablicaPojazdow[i].oddajPaliwo() << endl;
			plik << "Nr.VIN: " << tablicaPojazdow[i].oddajVin() << endl;
			plik << endl;
			plik.flush();
		}
		plik.close();	
	} else {
		cout << "Wyst�pi� problem z plikiem." << endl;
		cout << "Upewnij si�, �e wprowadzi�e� poprawn� nazw� i rozszerzenie pliku." << endl;
		cout << endl;
		
		return "x61";
	}
	
	cout << "Pomy�lnie zako�czono zapis do pliku." << endl;
	cout << endl;
	
	return "x60";
}

// Metoda odczytuj�ca dane pojazd�w z pliku i zapisuj�ca je do wektora
string otworzPlik(string nazwaPliku, string opcja) {
	string exit;

	if (opcja == "otworz") {
	cout << "Otwarcie pliku nadpisze wszelkie wprowadzone zmiany." << endl;
	cout << "Przed rozpoczeciem nale�y zapisa� swoj� prace." << endl;
	cout << "Czy chcesz kontynuowa� ?" << endl;
	cin >> exit;
	cout << endl;
	}	

	if (!stricmp(exit.c_str(), "tak") || opcja == "dolacz" || opcja == "wymus") {
		if (opcja == "otworz") {
			cout << "Usuwanie poprzednich danych." << endl;	
			for(int i=tablicaPojazdow.size(); i >= 0; i--) {
				usunPojazd(i);
			}
		}
		
		cout << "Rozpoczynam odczyt z pliku." << endl;

		fstream plik(nazwaPliku,ios::in);
		if( plik.good() ) {
			string wiersz, typ, marka, model, paliwo, vin;
			unsigned int id, i = 0;
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
						paliwo = wiersz;
						i++;
					} else if (i==5) {
						wiersz.erase(0,8);
						vin = stoi(wiersz);
						if (opcja == "otworz" || opcja == "wymus") {
							tablicaPojazdow.insert (tablicaPojazdow.begin() + id,Pojazd(typ,marka,model,paliwo,vin));
						} else if (opcja == "dolacz") {
							tablicaPojazdow.push_back (Pojazd(typ,marka,model,paliwo,vin));
						}
						i=0;
					}
				}
			}
			plik.close();
		} else {
			cout << "Wyst�pi� problem z plikiem." << endl;
			cout << "Upewnij si�, �e wprowadzi�e� poprawn� nazw� i rozszerzenie pliku." << endl;
			cout << endl;

			return "x72";
		}
		cout << "Pomy�lnie zako�czono odczyt z pliku." << endl;
		cout << endl;

		return "x70";
	} else {
		cout << "Operacja zosta�a anulowana." << endl;
		cout << endl;

		return "x71";
	}
}

int wyswietlMenu() {
	unsigned int ile, id, blad, nrOperacji;
	string plik, zapisz, format, wynik;
	char opcja, pre_id;
	blad = 0;
	
	cout << "#############################" << endl;
	cout << "1. Plik" << endl;
	cout << "2. Dodaj pojazd" << endl;
	cout << "3. Edytuj pojazd" << endl;
	cout << "4. Usu� pojazd" << endl;
	cout << "5. Wy�wietl pojazd/y" << endl;
	cout << "6. Filtruj pojazdy" << endl;
	cout << "7. Wy�wietl histori� operacji" << endl;
	cout << "8. Wyj�cie" << endl;
	cout << "#############################" << endl;
	cout << endl;
	
	do {
		cout << "Podaj numer opcji: ";
		cin >> opcja;
		cout << endl;
		
		if (opcja != '1' && opcja != '2' && opcja != '3' && opcja != '4' && opcja != '5' && opcja != '6' && opcja != '7' && opcja != '8') {
			cout << "Prosz� wybra� opcj� z zakresu od 1 do 7!" << endl;
			cout << endl;
		}
	} while (opcja != '1' && opcja != '2' && opcja != '3' && opcja != '4' && opcja != '5' && opcja != '6' && opcja != '7' && opcja != '8');
	
	switch (opcja) {
		case '1':
			cout << "1. Otw�rz jako now� baz�" << endl;
			cout << "2. Otw�rz jako do��czenie do istniej�cej bazy" << endl;
			cout << "3. Zapisz" << endl;
			cout << endl;
			
			do {
				cout << "Podaj numer opcji: ";
				cin >> opcja;
				cout << endl;
				
				if (opcja != '1' && opcja != '2' && opcja != '3') {
					cout << "Prosz� wybra� opcj� od 1 do 3!" << endl;
					cout << endl;
				}
			} while (opcja != '1' && opcja != '2' && opcja != '3');
			
			switch(opcja) {
				case '1':
					dodajOperacja("Otwarcie nowej bazy pojazd�w");
					nrOperacji = historiaOperacji.size() - 1;
					
					cout << "Podaj nazw� pliku do otwarcia (np. Pojazdy.txt)." << endl;
					cin >> plik;
					cout << endl;
					
					wynik = otworzPlik(plik,"otworz");
					historiaOperacji[nrOperacji].ustawWynik(wynik);
					break;
				case '2':
					dodajOperacja("Dodanie pojazd�w z pliku");
					nrOperacji = historiaOperacji.size() - 1;
					
					cout << "Podaj nazw� pliku do otwarcia (np. Pojazdy.txt)." << endl;
					cin >> plik;
					cout << endl;
					
					wynik = otworzPlik(plik,"dolacz");
					historiaOperacji[nrOperacji].ustawWynik(wynik);
					break;
				case '3':
					dodajOperacja("Zapis do pliku");
					nrOperacji = historiaOperacji.size() - 1;
					
					cout << "Podaj nazw� pliku do kt�rego chcesz zapisa� (np. Pojazdy.txt)." << endl;
					cin >> plik;
					cout << endl;
					
					wynik = zapiszPlik(plik);
					historiaOperacji[nrOperacji].ustawWynik(wynik);
					break;
			}
			break;
		case '2':		
			dodajOperacja("Dodanie pojazdu");
			nrOperacji = historiaOperacji.size() - 1;
			
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
				wynik = dodajPojazd();
				historiaOperacji[nrOperacji].ustawWynik(wynik);
				if (wynik != "x10") {
					cout << "Podczas dodawanie jednego z pojazd�w wyst�pi� b��d!" << endl;
					cout << endl;
					break;	
				}
			}
			break;
		case '3':
			dodajOperacja("Edycja pojazdu");
			nrOperacji = historiaOperacji.size() - 1;
			
			do {
				blad = 0;
				cout << "Podaj ID pojazdu do edycji: ";		
				cin >> pre_id;
				cout << endl;
				
				if((isdigit(pre_id))==1){		//isdigit zwraca 1 dla prawdy, 0 dla fa�szu
					id = (unsigned int)pre_id - 48;		//Je�li pre_id jest warto�ci� liczbow� to przypisuje j� do id, a -48 jest dlatego, �e po konwersji zwraca warto�� decymaln� ascii http://www.asciitable.com/index/asciifull.gif
					wynik = edytujPojazd(id);
					historiaOperacji[nrOperacji].ustawWynik(wynik);
					break;
				} else {
					cout << "ID musi by� liczb�!" << endl;
					blad = 1;
				}
			} while (blad = 1);
		case '4':
			dodajOperacja("Usuni�cie pojazdu");
			nrOperacji = historiaOperacji.size() - 1;
			
			do {
				blad = 0;
				cout << "Podaj ID pojazdu do usuni�cia: ";		
				cin >> pre_id;
				cout << endl;
				
				if((isdigit(pre_id))==1){		//isdigit zwraca 1 dla prawdy, 0 dla fa�szu
					id = (unsigned int)pre_id - 48;		//Je�li pre_id jest warto�ci� liczbow� to przypisuje j� do id, a -48 jest dlatego, �e po konwersji zwraca warto�� decymaln� ascii http://www.asciitable.com/index/asciifull.gif
					wynik = usunPojazd(id);
					historiaOperacji[nrOperacji].ustawWynik(wynik);
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
					dodajOperacja("Wy�wietlenie danych pojazdu");
					nrOperacji = historiaOperacji.size() - 1;
					
					do {
						blad = 0;
						cout << "Podaj ID pojazdu do wy�wietlenia: ";		
						cin >> pre_id;
						cout << endl;
						
						if((isdigit(pre_id))==1){		//isdigit zwraca 1 dla prawdy, 0 dla fa�szu
							id = (unsigned int)pre_id - 48;		//Je�li pre_id jest warto�ci� liczbow� to przypisuje j� do id, a -48 jest dlatego, �e po konwersji zwraca warto�� decymaln� ascii http://www.asciitable.com/index/asciifull.gif
							if (id < 0){
								cout << "ID nie mo�e by� ujemne!" << endl;
								blad = 1;	
							} else {
								wynik = wyswietlPojazd(id, "lista");
								historiaOperacji[nrOperacji].ustawWynik(wynik);
								break;
							}
						} else {
							cout << "ID musi by� liczb�!" << endl;
							blad = 1;
						}
					} while (blad = 1);
					break;
				case '2':
					dodajOperacja("Wy�wietlenie danych wszystkich pojazd�w");
					nrOperacji = historiaOperacji.size() - 1;
					
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
								cout.width( 5 );
								cout << left << "ID"; 
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
								wynik = wyswietlPojazd(i,format);
								historiaOperacji[nrOperacji].ustawWynik(wynik);
								if (wynik != "x40") {
									cout << "Podczas wy�wietlania danych jednego z pojazd�w wyst�pi� b��d!" << endl;
									cout << endl;
									break;	
								}	
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
			dodajOperacja("Przeszukiwanie danych pojazdu");
			nrOperacji = historiaOperacji.size() - 1;
			
			wynik = przeszukajPojazdy();
			historiaOperacji[nrOperacji].ustawWynik(wynik);
			break;
		case '7':
			dodajOperacja("Wy�wietlenie historii operacji");
			nrOperacji = historiaOperacji.size() - 1;

			cout << "Historia wykonywanych operacji:" << endl;
			for(int i = 0; i < historiaOperacji.size();i++) {
				wynik = wyswietlOperacja(i);
				historiaOperacji[nrOperacji].ustawWynik(wynik);
				if (wynik != "x90") {
					cout << "Podczas wy�wietlania jednej z operacji wyst�pi� b��d!" << endl;
					cout << endl;
					break;	
				}		
			}
			cout << endl;
			break;
		case '8':
			dodajOperacja("Zako�czenie pracy z programem");
			nrOperacji = historiaOperacji.size() - 1;
			
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
	
	cout << "Automatyczne otwieranie bazy Pojazd�w." << endl;
	cout << endl;
	otworzPlik("baza.txt","wymus");
	
	int exit;

	do {
		exit = wyswietlMenu();
	} while (exit != 1);
	
    return EXIT_SUCCESS;
}
