#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstdlib>

#include "pojazd.hpp"
#include "operacja.hpp"

using namespace std;

// Definicja wektora stringów z historia operacji
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

// Definicja wektora obiektow Pojazd
vector <Pojazd> tablicaPojazdow;

// Metoda dodajaca dane pojazdu dla odpowiedniego indeksu wektora
// (je¿eli dla danego indeksu istnieje ju¿ obiekt to nastêpuje inkrementacja indeksu tego obiektu i ka¿dego nastêpnego, czyli przesuniêcie w prawo i dopiero dodanie naszego obiektu)	
/* Dodaæ sprawdzanie podawanych warto¹ci i porównywanie ich do wzorów, sprecyzowanie obi¹zkowych i nieobowi¹zkowych danych */
string dodajPojazd(unsigned int id) {
	string typ, marka, model, paliwo, vin;
	char opcja;
	
	cout << "Podaj typ pojazdu: ";
	cin >> typ;
	cout << "Podaj marke pojazdu: ";
	cin >> marka;
	cout << "Podaj model pojazdu: ";
	cin >> model;
	cout << "Wybierz typ silnika: ";
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
	
	string typ, marka, model, paliwo, vin, atrybut, exit;
	
	do {
		cout << "Podaj nazwe w³asnoœci pojazdu: ";
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
		cout << "Czy chcesz kontynuowaæ edycjê ?" << endl;
		cin >> exit;
		cout << endl;
	} while (!stricmp(exit.c_str(), "tak"));
	
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
string wyswietlPojazd(unsigned int id, string format) {
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

// Metoda filtruj¹ca dane pojazdu
string przeszukajPojazdy() {
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
	cout << "Podaj wartoœæ tej w³asnoœci: ";
	cin >> wartosc;
	cout << endl;
	
	cout << "Chcesz wyœwietliæ wyniki jako \"tabela\", czy \"lista\" ?" << endl;
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
	// Przeszukiwanie wszystkich obiektów wektora
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
		// Obs³uga b³êdu - nie istnieje taki atrybut
		} else {
			cout << "Taki atrybut zosta³ nie znaleziony." << endl;
			cout << "SprawdŸ pisownie i spróbuj ponownie." << endl;
			cout << endl;

			return "x52";
		}
	}
	
	if (!stricmp(format.c_str(), "tabela")) {
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
			plik << "Rodzaj paliwa: " << tablicaPojazdow[i].oddajPaliwo() << endl;
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
string otworzPlik(string nazwaPliku, string opcja) {
	string exit;

	if (opcja == "otworz") {
	cout << "Otwarcie pliku nadpisze wszelkie wprowadzone zmiany." << endl;
	cout << "Przed rozpoczeciem nale¿y zapisaæ swoj¹ prace." << endl;
	cout << "Czy chcesz kontynuowaæ ?" << endl;
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
			cout << "Wyst¹pi³ problem z plikiem." << endl;
			cout << "Upewnij siê, ¿e wprowadzi³eœ poprawn¹ nazwê i rozszerzenie pliku." << endl;
			cout << endl;

			return "x72";
		}
		cout << "Pomyœlnie zakoñczono odczyt z pliku." << endl;
		cout << endl;

		return "x70";
	} else {
		cout << "Operacja zosta³a anulowana." << endl;
		cout << endl;

		return "x71";
	}
}

char pasekNarzedzi() {
	unsigned int id, nrOperacji;
	string wynik;
	char opcja;
	
	cout << "[M]enu  ";
	cout << "[D]odaj  ";
	cout << "[E]dytuj  ";
	cout << "[U]suñ  ";
	cout << "[F]iltruj" << endl;
	cout << endl;
	
	cout << "Wybierz opcje: ";
	do {
		opcja = getch();
		if (opcja == 'm' || opcja == 'M' || opcja == 'd' || opcja == 'D' || opcja == 'e' || opcja == 'E' || opcja == 'u' || opcja == 'U' || opcja == 'f' || opcja == 'F') {
			cout << opcja << endl;
		}
	} while (opcja != 'm' && opcja != 'M' && opcja != 'd' && opcja != 'D' && opcja != 'e' && opcja != 'E' && opcja != 'u' && opcja != 'U' && opcja != 'f' && opcja != 'F');
	cout << endl;
	
	switch(opcja) {
		case 'm': case 'M':
			return 'm';
			break;
		
		case 'd' : case 'D':		
			dodajOperacja("Dodanie pojazdu");
			nrOperacji = historiaOperacji.size() - 1;
			
			wynik = dodajPojazd();
			historiaOperacji[nrOperacji].ustawWynik(wynik);
			break;
			
		case 'e': case 'E':
			dodajOperacja("Edycja pojazdu");
			nrOperacji = historiaOperacji.size() - 1;

			cout << "Podaj ID pojazdu do edycji: ";		
			while(!(cin>>id)) {
				cout << "ID pojazdu powinno byæ liczb¹!" << endl;
				cin.clear(); //kasowanie flagi b³êdu strumienia
				cin.sync(); //kasowanie zbêdnych znaków z bufora
				cout << "Podaj ID pojazdu do edycji: ";
			}
			cout << endl;
				
			wynik = edytujPojazd(id);
			historiaOperacji[nrOperacji].ustawWynik(wynik);
			break;
			
		case 'u': case 'U':
			dodajOperacja("Usuniêcie pojazdu");
			nrOperacji = historiaOperacji.size() - 1;
			
			cout << "Podaj ID pojazdu do usuniêcia: ";		
			while(!(cin>>id)) {
				cout << "ID pojazdu powinno byæ liczb¹!" << endl;
				cin.clear(); //kasowanie flagi b³êdu strumienia
				cin.sync(); //kasowanie zbêdnych znaków z bufora
				cout << "Podaj ID pojazdu do usuniêcia: ";
			}
			cout << endl;
				
			wynik = usunPojazd(id);
			historiaOperacji[nrOperacji].ustawWynik(wynik);
			break;
			
		case 'f': case 'F':
			dodajOperacja("Filtrowanie danych pojazdu");
			nrOperacji = historiaOperacji.size() - 1;
			
			wynik = przeszukajPojazdy();
			historiaOperacji[nrOperacji].ustawWynik(wynik);
			break;
			
		default: 
			cout << "Wybrano niew³aœciw¹ opcjê."  << endl;
			cout << endl;
			break;
	}
}

int wyswietlMenu() {
	unsigned int blad, nrOperacji;
	string plik, zapisz, format, wynik;
	char opcja;
	
	cout << "#############################" << endl;
	cout << "1. Plik" << endl;
	cout << "2. Wyœwietl pojazdy" << endl;
	cout << "3. Historia operacji" << endl;
	cout << "4. Wyjœcie" << endl;
	cout << "#############################" << endl;
	cout << endl;
	
	cout << "Podaj numer opcji: ";
	do {
		blad = 0;
		opcja = getch();
		if (opcja == '1' || opcja == '2' || opcja == '3' || opcja == '4') {
			cout << opcja << endl;
		} else {
			blad = 1;
		}
	} while (blad == 1);
	cout << endl;

	switch (opcja) {
		case '1':
			cout << "1. Otwórz jako now¹ bazê" << endl;
			cout << "2. Otwórz jako do³¹czenie do istniej¹cej bazy" << endl;
			cout << "3. Zapisz" << endl;
			cout << endl;
			
			cout << "Podaj numer opcji: ";
			do {
				blad = 0;
				opcja = getch();
				if (opcja == '1' || opcja == '2' || opcja == '3') {
					cout << opcja << endl;
				} else {
					blad = 1;
				}
			} while (blad == 1);
			cout << endl;
			
			switch(opcja) {
				case '1': 
					dodajOperacja("Otwarcie nowej bazy pojazdów");
					nrOperacji = historiaOperacji.size() - 1;
					
					cout << "Podaj nazwê pliku do otwarcia (np. Pojazdy.txt)." << endl;
					cin >> plik;
					cout << endl;
					
					wynik = otworzPlik(plik,"otworz");
					historiaOperacji[nrOperacji].ustawWynik(wynik);
					break;
				case '2':
					dodajOperacja("Dodanie pojazdów z pliku");
					nrOperacji = historiaOperacji.size() - 1;
					
					cout << "Podaj nazwê pliku do otwarcia (np. Pojazdy.txt)." << endl;
					cin >> plik;
					cout << endl;
					
					wynik = otworzPlik(plik,"dolacz");
					historiaOperacji[nrOperacji].ustawWynik(wynik);
					break;
				case '3':
					dodajOperacja("Zapis do pliku");
					nrOperacji = historiaOperacji.size() - 1;
					
					cout << "Podaj nazwê pliku do którego chcesz zapisaæ (np. Pojazdy.txt)." << endl;
					cin >> plik;
					cout << endl;
					
					wynik = zapiszPlik(plik);
					historiaOperacji[nrOperacji].ustawWynik(wynik);
					break;
			}
			break;
		
		case '2':
			char wyjscie;
			do {
				dodajOperacja("Wyœwietlenie bazy pojazdów");
				nrOperacji = historiaOperacji.size() - 1;
	
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
								
				for (int i=0; i<tablicaPojazdow.size();i++) {
					wynik = wyswietlPojazd(i,"tabela");
					historiaOperacji[nrOperacji].ustawWynik(wynik);
					if (wynik != "x40") {
						cout << "Podczas wyœwietlania danych jednego z pojazdów wyst¹pi³ b³¹d!" << endl;
						cout << endl;
						break;	
					}	
				}
				
				cout << endl;
				wyjscie = pasekNarzedzi();
			} while (wyjscie != 'm' && wyjscie != 'M');
			break;

		case '3':
			dodajOperacja("Wyœwietlenie historii operacji");
			nrOperacji = historiaOperacji.size() - 1;

			cout << "Historia wykonywanych operacji:" << endl;
			for(int i = 0; i < historiaOperacji.size();i++) {
				wynik = wyswietlOperacja(i);
				historiaOperacji[nrOperacji].ustawWynik(wynik);
				if (wynik != "x90") {
					cout << "Podczas wyœwietlania jednej z operacji wyst¹pi³ b³¹d!" << endl;
					cout << endl;
					break;	
				}		
			}
			cout << endl;
			break;
			
		case '4':
			dodajOperacja("Zakoñczenie pracy z programem");
			nrOperacji = historiaOperacji.size() - 1;
			
			cout << "Czy chcesz zapisaæ pracê przed wyjœciem ?" << endl;
			cout << "[T]ak  [N]ie" << endl;
			
			do {
				blad = 0;
				opcja = getch();
				if (opcja == 't' || opcja == 'T' || opcja == 'n' || opcja == 'N') {
					cout << opcja << endl;
					zapiszPlik("baza.txt");
				} else {
					blad = 1;
				}
			} while (blad != 0);
			
			cout << endl;
			
			return 1;
			break;
			
		default: 
			cout << "Wybrano niew³aœciw¹ opcjê."  << endl;
			cout << endl;
			break;
	}
	return 0;
}
	
int main(int argc, char *argv[]) {
	setlocale(LC_ALL,"");

	otworzPlik("baza.txt","wymus");
	
	int exit;

	do {
		exit = wyswietlMenu();
	} while (exit != 1);
	
    return EXIT_SUCCESS;
}
