#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <regex>
#include <time.h>
#include <algorithm>
#include <windows.h>

#include "pojazd.hpp"
#include "operacja.hpp"

using namespace std;
namespace kolor {
  enum {
	DEFAULT           = 7,
    BLACK             = 0,
    DARKBLUE          = FOREGROUND_BLUE,
    DARKGREEN         = FOREGROUND_GREEN,
    DARKCYAN          = FOREGROUND_GREEN | FOREGROUND_BLUE,
    DARKRED           = FOREGROUND_RED,
    DARKMAGENTA       = FOREGROUND_RED | FOREGROUND_BLUE,
    DARKYELLOW        = FOREGROUND_RED | FOREGROUND_GREEN,
    DARKGRAY          = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    GRAY              = FOREGROUND_INTENSITY,
    BLUE              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    GREEN             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    CYAN              = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    RED               = FOREGROUND_INTENSITY | FOREGROUND_RED,
    MAGENTA           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    YELLOW            = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    WHITE             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
  };
}
static HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

struct tm * aktualnyCzas;

bool sprawdzRokProd(unsigned int rokProd) {
	if( rokProd < 1981 || rokProd > aktualnyCzas->tm_year) {
		cout << "B³¹d! Rocznij mo¿e byæ tylko z przedzia³u od 1981 do " << aktualnyCzas->tm_year << "." << endl;
		return true;
	}	else {
		return false;
	}
}

bool sprawdzVin(string vin) {
	// VIN - 1-13 cyfry/litery, 14-17 cyfry np. W0L0SDL68B4352330
	regex wzorzecVin("([0-9]|[A-H]|[K-N]|P|[R-Z]){13}[0-9]{4}");
	smatch sprawdzonyVin;
	
	if( !regex_search(vin,sprawdzonyVin,wzorzecVin)) {
		cout << "B³¹d! Wprowadzono niepoprawny VIN." << endl;
		return true;
	} else {
		return false;
	}
}

bool sprawdzRejestracja(string rejestracja) {
	// Rejestracja - 2-3 litery, 4-5 cyfry/liter np. SBE G083
	regex wzorzecRejestracja("([A-Z]{2,3}[\x20]?[0-9A-Z]{4,5})|([A-Z]{1}[0-9]{1}[\x20]?[0-9A-Z]{3,5})");
	smatch sprawdzonyRejestracja;
	
	if( !regex_search(rejestracja,sprawdzonyRejestracja,wzorzecRejestracja)) {
		cout << rejestracja << endl;
		cout << "B³¹d! Wprowadzono niepoprawn¹ rejestracjê." << endl;
		return true;
	} else {
		return false;
	}
}

bool sprawdzCzyLiczba(string liczba) {
	if(liczba.empty() || ((!isdigit(liczba[0])) && (liczba[0] != '-') && (liczba[0] != '+'))) {
		cout << "B³¹d! Podana wartoœæ nie jest liczb¹." << endl;
		return true;
	} else {
		return false;
	}
}

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
string dodajPojazd(unsigned int id) {
	string typ, marka, model, wersja, nadwozie, paliwo, vin, rejestracja, opis, uwagi, smoc, spojSilnika, smiejscaSiedz, smiejscaOgl, smasa, sdopMasaCalk, smasaPrzyczHam, smasaPrzyczBezHam, sosie, srozstawOsi, srozstawKol, sdopNaciskNaOs;
	unsigned int moc, pojSilnika, miejscaSiedz, miejscaOgl, masa, dopMasaCalk, masaPrzyczHam, masaPrzyczBezHam, osie, rozstawOsi, rozstawKol, dopNaciskNaOs, rokProd;
	unsigned int blad;
	
	cout << "Dane wymagane do dodania pojazdu s¹ oznaczone gwiazdk¹, wszelkie inne dane mo¿na pomin¹æ wciskaj¹c ENTER." << endl;
	
	cout << "* Podaj typ pojazdu: ";
	cin.sync();
	getline( cin, typ );
	
	cout << "* Podaj marke pojazdu: ";
	cin.sync();
	getline( cin, marka );
	
	cout << "* Podaj model pojazdu: ";
	cin.sync();
	getline( cin, model );
	
	cout << "* Podaj wersjê pojazdu: ";
	cin.sync();
	getline( cin, wersja );
	
	cout << "* Podaj typ nadwozia pojazdu: ";
	cin.sync();
	getline( cin, nadwozie );
	
	cout << "* Podaj rodzaj paliwa: ";
	cin.sync();
	getline( cin, paliwo );
	
	// Pojemnoœc powinno siê móc dodaæ zarówno jako "1.2" "1200"
	cout << "* Podaj pojemnoœæ silnika: ";
	while(!(cin>>pojSilnika)) {
		cout << "Pojemnoœæ silnika powinna byæ liczb¹!" << endl;
		cin.clear();
		cin.sync(); 
		cout << "* Podaj pojemnoœæ silnika: ";
	}
	
	do {
		cout << "* Podaj rok produkcji: ";
		cin >> rokProd;
		blad = sprawdzRokProd(rokProd);
	} while (blad != false);
	
	do {
		cout << "* Podaj identyfikator VIN pojazdu: ";
		cin >> vin;
		transform(vin.begin(), vin.end(),vin.begin(), ::toupper);
		blad = sprawdzVin(vin);
	} while (blad != false);
	
	do {
		cout << "* Podaj numer rejestracji: ";
		cin.sync();
		getline( cin, rejestracja );
		transform(rejestracja.begin(), rejestracja.end(),rejestracja.begin(), ::toupper);
		blad = sprawdzRejestracja(rejestracja);
	} while (blad != false);
	
	tablicaPojazdow.insert (tablicaPojazdow.begin() + id,Pojazd(typ,marka,model,wersja,nadwozie,paliwo,pojSilnika,rokProd,vin,rejestracja));
	
	do {
		blad = false;
		cout << "Podaj moc silnika: ";
		cin.sync();
		getline( cin, smoc );
		if (smoc != "") {
			blad = sprawdzCzyLiczba(smoc);
			if (blad == false) moc = stoi(smoc);;
		}
	} while (blad != false);
	
	do {
		blad = false;
		cout << "Podaj liczbê miejsc siedz¹cych: ";
		cin.sync();
		getline( cin, smiejscaSiedz );
		if (smiejscaSiedz != "") {
			blad = sprawdzCzyLiczba(smiejscaSiedz);
			if (blad == false) miejscaSiedz = stoi(smiejscaSiedz);
		}
	} while (blad != false);
	
	do {
		blad = false;
		cout << "Podaj liczbê miejsc ogó³em: ";
		cin.sync();
		getline( cin, smiejscaOgl );
		if (smiejscaOgl != "") {
			blad = sprawdzCzyLiczba(smiejscaOgl);
			if (blad == false) miejscaOgl = stoi(smiejscaOgl);
		}
	} while (blad != false);
	
	do {
		blad = false;
		cout << "Podaj masê pojazdu: ";
		cin.sync();
		getline( cin, smasa );
		if (smasa != "") {
			blad = sprawdzCzyLiczba(smasa);
			if (blad == false) masa = stoi(smasa);
		}
	} while (blad != false);
	
	do {
		blad = false;
		cout << "Podaj dopuszczaln¹ masê ca³kowit¹ pojazdu: ";
		cin.sync();
		getline( cin, sdopMasaCalk );
		if (sdopMasaCalk != "") {
			blad = sprawdzCzyLiczba(sdopMasaCalk);
			if (blad == false) dopMasaCalk = stoi(sdopMasaCalk);
		}
	} while (blad != false);
	
	do {
		blad = false;
		cout << "Podaj maksymaln¹ dopuszczaln¹ masê przyczepy z hamulcem: ";
		cin.sync();
		getline( cin, smasaPrzyczHam );
		if (smasaPrzyczHam != "") {
			blad = sprawdzCzyLiczba(smasaPrzyczHam);
			if (blad == false) masaPrzyczHam = stoi(smasaPrzyczHam);
		}
	} while (blad != false);

	do {
		blad = false;
		cout << "Podaj maksymaln¹ dopuszczaln¹ masê przyczepy bez hamulca: ";
		cin.sync();
		getline( cin, smasaPrzyczBezHam );
		if (smasaPrzyczBezHam != "") {
			blad = sprawdzCzyLiczba(smasaPrzyczBezHam);
			if (blad == false) masaPrzyczBezHam = stoi(smasaPrzyczBezHam);
		}
	} while (blad != false);	

	do {
		blad = false;
		cout << "Podaj liczbê osi pojazdu: ";
		cin.sync();
		getline( cin, sosie );
		if (sosie != "") {
			blad = sprawdzCzyLiczba(sosie);
			if (blad == false) osie = stoi(sosie);
		}
	} while (blad != false);
	
	do {
		blad = false;
		cout << "Podaj rozstaw osi pojazdu: ";
		cin.sync();
		getline( cin, srozstawOsi );
		if (srozstawOsi != "") {
			blad = sprawdzCzyLiczba(srozstawOsi);
			if (blad == false) rozstawOsi = stoi(srozstawOsi);
		}
	} while (blad != false);
	
	do {
		blad = false;
		cout << "Podaj rozstaw kó³ pojazdu: ";
		cin.sync();
		getline( cin, srozstawKol );
		if (srozstawKol != "") {
			blad = sprawdzCzyLiczba(srozstawKol);
			if (blad == false) rozstawKol = stoi(srozstawKol);
		}
	} while (blad != false);
	
	do {
		blad = false;
		cout << "Podaj maksymalny dopuszczalny nacisk na oœ pojazdu: ";
		cin.sync();
		getline( cin, sdopNaciskNaOs );
		if (sdopNaciskNaOs != "") {
			blad = sprawdzCzyLiczba(sdopNaciskNaOs);
			if (blad == false) dopNaciskNaOs = stoi(sdopNaciskNaOs);
		}
	} while (blad != false);
	
	cout << endl;	
	return "x10";
}

// Metoda dodajaca dane pojazdu na koniec wektora
string dodajPojazd() {
	return dodajPojazd(tablicaPojazdow.size());
}

// Metoda edytuj¹ca dane pojazdu o danym ID
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
	
	string atrybut, typ, marka, model, wersja, nadwozie, paliwo, vin, rejestracja, opis, uwagi, smoc, spojSilnika, smiejscaSiedz, smiejscaOgl, smasa, sdopMasaCalk, smasaPrzyczHam, smasaPrzyczBezHam, sosie, srozstawOsi, srozstawKol, sdopNaciskNaOs;
	unsigned int moc, pojSilnika, miejscaSiedz, miejscaOgl, masa, dopMasaCalk, masaPrzyczHam, masaPrzyczBezHam, osie, rozstawOsi, rozstawKol, dopNaciskNaOs, rokProd;
	unsigned int blad;
	char opcja;

	do {
		cout << "Podaj nazwe w³asnoœci pojazdu: ";
		cin.sync();
		getline(cin, atrybut);
		cout << endl;
		
		if (!stricmp(atrybut.c_str(), "typ")) {
			cout << "* Podaj typ pojazdu: ";
			cin.sync();
			getline( cin, typ );
			tablicaPojazdow[id].ustawTyp(typ);
		} else if (!stricmp(atrybut.c_str(), "marka")) {
			cout << "* Podaj marke pojazdu: ";
			cin.sync();
			getline( cin, marka );
			tablicaPojazdow[id].ustawMarka(marka);
		} else if (!stricmp(atrybut.c_str(), "model")) {
			cout << "* Podaj model pojazdu: ";
			cin.sync();
			getline( cin, model );
			tablicaPojazdow[id].ustawModel(model);
		} else if (!stricmp(atrybut.c_str(), "wersja")) {
			cout << "* Podaj wersjê pojazdu: ";
			cin.sync();
			getline( cin, wersja );
			tablicaPojazdow[id].ustawWersja(wersja);
		} else if (!stricmp(atrybut.c_str(), "typ nadwozia") || !stricmp(atrybut.c_str(), "nadwozie")) {
			cout << "* Podaj typ nadwozia pojazdu: ";
			cin.sync();
			getline( cin, nadwozie );
			tablicaPojazdow[id].ustawNadwozie(nadwozie);
		} else if (!stricmp(atrybut.c_str(), "pojemnosc silnika") || !stricmp(atrybut.c_str(), "pojemnosc")) {
			cout << "* Podaj pojemnoœæ silnika: ";
			while(!(cin>>pojSilnika)) {
				cout << "Pojemnoœæ silnika powinna byæ liczb¹!" << endl;
				cin.clear();
				cin.sync();
				cout << "* Podaj pojemnoœæ silnika: ";
			}
			tablicaPojazdow[id].ustawPojSilnika(pojSilnika);
		} else if (!stricmp(atrybut.c_str(), "rok produkcji") || !stricmp(atrybut.c_str(), "rocznik")) {
			cout << "B³¹d! Nie mo¿na dokonaæ edycji atrybutu \"rok produkcji\", poniewa¿ jest on sta³y." << endl;
		} else if (!stricmp(atrybut.c_str(), "rodzaj paliwa") || !stricmp(atrybut.c_str(), "paliwo")) {
			cout << "* Podaj rodzaj paliwa: ";
			cin.sync();
			getline( cin, paliwo );
			tablicaPojazdow[id].ustawPaliwo(paliwo);
		} else if (!stricmp(atrybut.c_str(), "nr.vin") || !stricmp(atrybut.c_str(), "nr vin") || !stricmp(atrybut.c_str(), "numer vin")) {
			cout << "B³¹d! Nie mo¿na dokonaæ edycji atrybutu \"VIN\", poniewa¿ jest on sta³y." << endl;
		} else if (!stricmp(atrybut.c_str(), "rejestracja")) {
			do {
				cout << "* Podaj numer rejestracji: ";
				cin.sync();
				getline( cin, rejestracja );
				transform(rejestracja.begin(), rejestracja.end(),rejestracja.begin(), ::toupper);
				blad = sprawdzRejestracja(rejestracja);
			} while (blad != true);	
			tablicaPojazdow[id].ustawRejestracja(rejestracja);
		} else if (!stricmp(atrybut.c_str(), "moc silnika") || !stricmp(atrybut.c_str(), "moc")) {
			do {
				blad = false;
				cout << "Podaj moc silnika: ";
				cin.sync();
				getline( cin, smoc );
				if (smoc != "") {
					blad = sprawdzCzyLiczba(smoc);
					if (blad == false) moc = stoi(smoc);;
				}
			} while (blad != false);
		}  else if (!stricmp(atrybut.c_str(), "liczba miejsc siedz¹cych") || !stricmp(atrybut.c_str(), "miejsca siedz¹ce") || !stricmp(atrybut.c_str(), "siedz¹ce")) {
			do {
				blad = false;
				cout << "Podaj liczbê miejsc siedz¹cych: ";
				cin.sync();
				getline( cin, smiejscaSiedz );
				if (smiejscaSiedz != "") {
					blad = sprawdzCzyLiczba(smiejscaSiedz);
					if (blad == false) miejscaSiedz = stoi(smiejscaSiedz);
				}
			} while (blad != false);
			tablicaPojazdow[id].ustawMiejscaSiedz(miejscaSiedz);
		}  else if (!stricmp(atrybut.c_str(), "liczba miejsc ogó³em") || !stricmp(atrybut.c_str(), "miejsca ogó³em") || !stricmp(atrybut.c_str(), "ogó³em")) {
			do {
				blad = false;
				cout << "Podaj liczbê miejsc ogó³em: ";
				cin.sync();
				getline( cin, smiejscaOgl );
				if (smiejscaOgl != "") {
					blad = sprawdzCzyLiczba(smiejscaOgl);
					if (blad == false) miejscaOgl = stoi(smiejscaOgl);
				}
			} while (blad != false);
			tablicaPojazdow[id].ustawMiejscaOgl(miejscaOgl);
		} else if (!stricmp(atrybut.c_str(), "masa pojazdu") || !stricmp(atrybut.c_str(), "masa")) {
			do {
				blad = false;
				cout << "Podaj masê pojazdu: ";
				cin.sync();
				getline( cin, smasa );
				if (smasa != "") {
					blad = sprawdzCzyLiczba(smasa);
					if (blad == false) masa = stoi(smasa);
				}
			} while (blad != false);
			tablicaPojazdow[id].ustawMasa(masa);
		} else if (!stricmp(atrybut.c_str(), "dopuszczalna masa ca³kowita") || !stricmp(atrybut.c_str(), "masa ca³kowita")) {
			do {
				blad = false;
				cout << "Podaj dopuszczaln¹ masê ca³kowit¹ pojazdu: ";
				cin.sync();
				getline( cin, sdopMasaCalk );
				if (sdopMasaCalk != "") {
					blad = sprawdzCzyLiczba(sdopMasaCalk);
					if (blad == false) dopMasaCalk = stoi(sdopMasaCalk);
				}
			} while (blad != false);
			tablicaPojazdow[id].ustawDopMasaCalk(dopMasaCalk);
		} else if (!stricmp(atrybut.c_str(), "dopuszczalna masa przyczepy z hamulcem") || !stricmp(atrybut.c_str(), "masa przyczepy z hamulcem")) {
			do {
				blad = false;
				cout << "Podaj maksymaln¹ dopuszczaln¹ masê przyczepy z hamulcem: ";
				cin.sync();
				getline( cin, smasaPrzyczHam );
				if (smasaPrzyczHam != "") {
					blad = sprawdzCzyLiczba(smasaPrzyczHam);
					if (blad == false) masaPrzyczHam = stoi(smasaPrzyczHam);
				}
			} while (blad != false);
			tablicaPojazdow[id].ustawMasaPrzyczHam(masaPrzyczHam);
		} else if (!stricmp(atrybut.c_str(), "dopuszczalna masa przyczepy bez hamulca") || !stricmp(atrybut.c_str(), "masa przyczepy bez hamulca")) {
			do {
				blad = false;
				cout << "Podaj maksymaln¹ dopuszczaln¹ masê przyczepy bez hamulca: ";
				cin.sync();
				getline( cin, smasaPrzyczBezHam );
				if (smasaPrzyczBezHam != "") {
					blad = sprawdzCzyLiczba(smasaPrzyczBezHam);
					if (blad == false) masaPrzyczBezHam = stoi(smasaPrzyczBezHam);
				}
			} while (blad != false);
			tablicaPojazdow[id].ustawMasaPrzyczBezHam(masaPrzyczBezHam);	
		} else if (!stricmp(atrybut.c_str(), "liczba osi") || !stricmp(atrybut.c_str(), "osie")) {
			do {
				blad = false;
				cout << "Podaj liczbê osi pojazdu: ";
				cin.sync();
				getline( cin, sosie );
				if (sosie != "") {
					blad = sprawdzCzyLiczba(sosie);
					if (blad == false) osie = stoi(sosie);
				}
			} while (blad != false);
			tablicaPojazdow[id].ustawOsie(osie);
		} else if (!stricmp(atrybut.c_str(), "rozstaw osi")) {
			do {
				blad = false;
				cout << "Podaj rozstaw osi pojazdu: ";
				cin.sync();
				getline( cin, srozstawOsi );
				if (srozstawOsi != "") {
					blad = sprawdzCzyLiczba(srozstawOsi);
					if (blad == false) rozstawOsi = stoi(srozstawOsi);
				}
			} while (blad != false);
			tablicaPojazdow[id].ustawRozstawOsi(rozstawOsi);
		} else if (!stricmp(atrybut.c_str(), "rozstaw kó³")) {	
			do {
				blad = false;
				cout << "Podaj rozstaw kó³ pojazdu: ";
				cin.sync();
				getline( cin, srozstawKol );
				if (srozstawKol != "") {
					blad = sprawdzCzyLiczba(srozstawKol);
					if (blad == false) rozstawKol = stoi(srozstawKol);
				}
			} while (blad != false);
			tablicaPojazdow[id].ustawRozstawKol(rozstawKol);
		} else if (!stricmp(atrybut.c_str(), "maksymalny dopuszczalny nacisk na oœ") || !stricmp(atrybut.c_str(), "dopuszczalny nacisk na oœ") || !stricmp(atrybut.c_str(), "maksymalny nacisk na oœ")) {	
			do {
				blad = false;
				cout << "Podaj maksymalny dopuszczalny nacisk na oœ pojazdu: ";
				cin.sync();
				getline( cin, sdopNaciskNaOs );
				if (sdopNaciskNaOs != "") {
					blad = sprawdzCzyLiczba(sdopNaciskNaOs);
					if (blad == false) dopNaciskNaOs = stoi(sdopNaciskNaOs);
				}
			} while (blad != false);
			tablicaPojazdow[id].ustawDopNaciskNaOs(dopNaciskNaOs);
		} else {
			cout << "Taki atrybut zosta³ nie znaleziony." << endl;
			cout << "SprawdŸ pisownie i spróbuj ponownie." << endl;
			cout << endl;

			return "x23";
		}
		
		cout << endl;
		cout << "Czy chcesz kontynuowaæ edycjê ?" << endl;
		cout << "[T]ak  [N]ie" << endl;
		opcja = getch();	

		cout << endl;
	} while (opcja == 't' || opcja == 'T');
	
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
	    cout << "Wersja: " << tablicaPojazdow[id].oddajWersja() << endl;
	    cout << "Nadwozie: " << tablicaPojazdow[id].oddajNadwozie() << endl;
	    cout << "Rodzaj paliwa: " << tablicaPojazdow[id].oddajPaliwo() << endl;
	    cout << "Pojemnoœæ silnika: " << tablicaPojazdow[id].oddajPojSilnika() << endl;
	    cout << "Rok produkcji: " << tablicaPojazdow[id].oddajRokProd() << endl;
	    cout << "Nr. VIN: " << tablicaPojazdow[id].oddajVin() << endl;
	    cout << "Rejestracja: " << tablicaPojazdow[id].oddajRejestracja() << endl;
	    cout << endl;
    } else if (!stricmp(format.c_str(), "tabela")) {
		cout.width( 4 );
		cout << left << id;
		cout.width( 15 );
		cout << left << tablicaPojazdow[id].oddajTyp();
		cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajMarka();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajModel();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajWersja();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajNadwozie();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajPaliwo();
	    cout.width( 20 );
	    cout << left << tablicaPojazdow[id].oddajPojSilnika();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajRokProd();
	    cout.width( 18 );
	    cout << left << tablicaPojazdow[id].oddajVin();
	    cout.width( 15 );
	    cout << left << tablicaPojazdow[id].oddajRejestracja();
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
	cin.sync();
	getline(cin, atrybut);
	cout << "Podaj wartoœæ tej w³asnoœci: ";
	cin.sync();
	getline(cin, wartosc);
	cout << endl;
	
	cout << "Chcesz wyœwietliæ wyniki jako \"tabela\", czy \"lista\" ?" << endl;
	cin >> format;
	cout << endl;
	
	if (!stricmp(format.c_str(), "tabela")) {
		cout.width( 4 );
		cout << left << "ID"; 
		cout.width( 15 );
		cout << left << "Typ"; 
		cout.width( 15 );
		cout << left << "Marka"; 
		cout.width( 15 );
		cout << left << "Wersja";
		cout.width( 15 );
		cout << left << "Nadwozie"; 
		cout.width( 15 );
		cout << left << "Model"; 
		cout.width( 15 );
		cout << left << "Rodzaj paliwa"; 
		cout.width( 20 );
		cout << left << "Pojemnoœæ silnika"; 
		cout.width( 15 );
		cout << left << "Rok produkcji"; 
		cout.width( 18 );
		cout << left << "Nr. VIN";
		cout.width( 15 );
		cout << left << "Rejestracja"; 
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
		} else if (!stricmp(atrybut.c_str(), "wersja")) {
			if (tablicaPojazdow[i].oddajWersja()==wartosc) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (!stricmp(atrybut.c_str(), "nadwozie")) {
			if (tablicaPojazdow[i].oddajNadwozie()==wartosc) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (!stricmp(atrybut.c_str(), "rodzaj paliwa") || !stricmp(atrybut.c_str(), "paliwo")) {
			if (tablicaPojazdow[i].oddajPaliwo()==wartosc) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (!stricmp(atrybut.c_str(), "pojemnoœæ silnika") || !stricmp(atrybut.c_str(), "pojemnoœæ") || !stricmp(atrybut.c_str(), "pojemnosc")) {
			if (tablicaPojazdow[i].oddajPojSilnika()==stoi(wartosc)) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (!stricmp(atrybut.c_str(), "rok produkcji") || !stricmp(atrybut.c_str(), "rocznik")) {
			if (tablicaPojazdow[i].oddajRokProd()==stoi(wartosc)) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (atrybut == "Nr.Vin" || atrybut == "nr.vin" || atrybut == "NR.VIN" || atrybut == "Vin" || atrybut == "vin" || atrybut == "VIN" || atrybut == "NrVin" || atrybut == "nrvin" || atrybut == "NRVIN") {
			if (tablicaPojazdow[i].oddajVin()==wartosc) {
				wyswietlPojazd(i,format);
				znalezionoWyniki += 1;	
			}
		} else if (!stricmp(atrybut.c_str(), "rejestracja")) {
			if (tablicaPojazdow[i].oddajRejestracja()==wartosc) {
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
			plik << "Wersja: " << tablicaPojazdow[i].oddajWersja() << endl;
			plik << "Nadwozie: " << tablicaPojazdow[i].oddajNadwozie() << endl;
			plik << "Rodzaj paliwa: " << tablicaPojazdow[i].oddajPaliwo() << endl;
			plik << "Pojemnoœæ silnika: " << tablicaPojazdow[i].oddajPojSilnika() << endl;
			plik << "Rok produkcji: " << tablicaPojazdow[i].oddajRokProd() << endl;
			plik << "Nr.VIN: " << tablicaPojazdow[i].oddajVin() << endl;
			plik << "Rejestracja: " << tablicaPojazdow[i].oddajRejestracja() << endl;
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
	cout << "[T]ak  [N]ie" << endl;
		
	exit = getche();
	cout << endl;
	}	

	if (!stricmp(exit.c_str(), "t") || !stricmp(exit.c_str(), "T") || opcja == "dolacz" || opcja == "wymus") {
		if (opcja == "otworz") {
			cout << "Usuwanie poprzednich danych." << endl;	
			for(int i=tablicaPojazdow.size(); i >= 0; i--) {
				usunPojazd(i);
			}
		}
		
		cout << "Rozpoczynam odczyt z pliku." << endl;

		fstream plik(nazwaPliku,ios::in);
		if( plik.good() ) {
			string wiersz, typ, marka, model, wersja, nadwozie, paliwo, vin, rejestracja;
			unsigned int id, i = 0, pojSilnika, rokProd;
			
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
						wiersz.erase(0,8);
						wersja = wiersz;
						i++;
					} else if (i==5) {
						wiersz.erase(0,10);
						nadwozie = wiersz;
						i++;	
					} else if (i==6) {
						wiersz.erase(0,15);
						paliwo = wiersz;
						i++;
					} else if (i==7) {
						wiersz.erase(0,19);
						pojSilnika = stoi(wiersz);
						i++;
					} else if (i==8) {
						wiersz.erase(0,15);
						rokProd = stoi(wiersz);
						i++;
					} else if (i==9) {
						wiersz.erase(0,8);
						vin = wiersz;
						i++;
					} else if (i==10) {
						wiersz.erase(0,13);
						rejestracja = wiersz;
						if (opcja == "otworz" || opcja == "wymus") {
							tablicaPojazdow.insert (tablicaPojazdow.begin() + id,Pojazd(typ,marka,model,wersja,nadwozie,paliwo,pojSilnika,rokProd,vin,rejestracja));
						} else if (opcja == "dolacz") {
							tablicaPojazdow.push_back (Pojazd(typ,marka,model,wersja,nadwozie,paliwo,pojSilnika,rokProd,vin,rejestracja));
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
	unsigned int id, nrOperacji, blad;
	string wynik;
	char opcja;
	
	SetConsoleTextAttribute(h, kolor::GREEN);
	cout << "[M]";
	SetConsoleTextAttribute(h, kolor::DEFAULT);
	cout << "enu  "; 
	SetConsoleTextAttribute(h, kolor::GREEN);
	cout << "[D]";
	SetConsoleTextAttribute(h, kolor::DEFAULT);
	cout << "odaj  ";
	SetConsoleTextAttribute(h, kolor::GREEN);
	cout << "[E]";
	SetConsoleTextAttribute(h, kolor::DEFAULT);
	cout << "dytuj  ";
	SetConsoleTextAttribute(h, kolor::GREEN);
	cout << "[U]";
	SetConsoleTextAttribute(h, kolor::DEFAULT);
	cout <<"suñ  ";
	SetConsoleTextAttribute(h, kolor::GREEN);
	cout << "[F]";
	SetConsoleTextAttribute(h, kolor::DEFAULT);
	cout << "iltruj" << endl;
	cout << endl;
	
	cout << "Wybierz opcje: ";
	do {
		blad = 0;
		opcja = getch();
		if (opcja == 'm' || opcja == 'M' || opcja == 'd' || opcja == 'D' || opcja == 'e' || opcja == 'E' || opcja == 'u' || opcja == 'U' || opcja == 'f' || opcja == 'F') {
			cout << opcja << endl;
		} else {
			blad = 1;
		}
	} while (blad != 0);
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
	SetConsoleTextAttribute(h, kolor::WHITE);
	cout << "#############################" << endl;
	SetConsoleTextAttribute(h, kolor::GREEN);
	cout << "1. "; 
	SetConsoleTextAttribute(h, kolor::DEFAULT);
	cout << "Plik" << endl;
	SetConsoleTextAttribute(h, kolor::GREEN);
	cout << "2. ";
	SetConsoleTextAttribute(h, kolor::DEFAULT);
	cout << "Wyœwietl pojazdy" << endl;
	SetConsoleTextAttribute(h, kolor::GREEN);
	cout << "3. ";
	SetConsoleTextAttribute(h, kolor::DEFAULT);
	cout <<"Historia operacji" << endl;
	SetConsoleTextAttribute(h, kolor::GREEN);
	cout << "4. ";
	SetConsoleTextAttribute(h, kolor::DEFAULT);
	cout << "Wyjœcie" << endl;
	SetConsoleTextAttribute(h, kolor::WHITE);
	cout << "#############################" << endl;
	SetConsoleTextAttribute(h, kolor::DEFAULT);
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
			SetConsoleTextAttribute(h, kolor::GREEN);
			cout << "1. ";
			SetConsoleTextAttribute(h, kolor::DEFAULT);
			cout << "Otwórz jako now¹ bazê" << endl;
			SetConsoleTextAttribute(h, kolor::GREEN);
			cout << "2. ";
			SetConsoleTextAttribute(h, kolor::DEFAULT);
			cout << "Otwórz jako do³¹czenie do istniej¹cej bazy" << endl;
			SetConsoleTextAttribute(h, kolor::GREEN);
			cout << "3. ";
			SetConsoleTextAttribute(h, kolor::DEFAULT);
			cout << "Zapisz" << endl;
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
					cin.sync();
					getline( cin, plik );
					cout << endl;
					
					wynik = otworzPlik(plik,"otworz");
					historiaOperacji[nrOperacji].ustawWynik(wynik);
					break;
				case '2':
					dodajOperacja("Dodanie pojazdów z pliku");
					nrOperacji = historiaOperacji.size() - 1;
					
					cout << "Podaj nazwê pliku do otwarcia (np. Pojazdy.txt)." << endl;
					cin.sync();
					getline( cin, plik );
					cout << endl;
					
					wynik = otworzPlik(plik,"dolacz");
					historiaOperacji[nrOperacji].ustawWynik(wynik);
					break;
				case '3':
					dodajOperacja("Zapis do pliku");
					nrOperacji = historiaOperacji.size() - 1;
					
					cout << "Podaj nazwê pliku do którego chcesz zapisaæ (np. Pojazdy.txt)." << endl;
					cin.sync();
					getline( cin, plik );
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
				SetConsoleTextAttribute(h, kolor::RED | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				
				cout.width( 4 );
				cout << left << "ID"; 
				cout.width( 15 );
				cout << left << "Typ"; 
				cout.width( 15 );
				cout << left << "Marka"; 
				cout.width( 15 );
				cout << left << "Model"; 
				cout.width( 15 );
				cout << left << "Wersja";
				cout.width( 15 );
				cout << left << "Nadwozie"; 
				cout.width( 15 );
				cout << left << "Rodzaj paliwa"; 
				cout.width( 20 );
				cout << left << "Pojemnoœæ silnika"; 
				cout.width( 15 );
				cout << left << "Rok produkcji"; 
				cout.width( 18 );
				cout << left << "Nr. VIN";
				cout.width( 15 );
				cout << left << "Rejestracja"; 
				cout << endl;
				SetConsoleTextAttribute(h, kolor::DEFAULT);	
							
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
			SetConsoleTextAttribute(h, kolor::GREEN);
			cout << "[T]";
			SetConsoleTextAttribute(h, kolor::DEFAULT);
			cout <<"ak  ";
			SetConsoleTextAttribute(h, kolor::GREEN);
			cout <<"[N]";
			SetConsoleTextAttribute(h, kolor::DEFAULT);
			cout << "ie" << endl;
			
			opcja = getch();
			if (opcja == 't' || opcja == 'T') {
				cout << opcja << endl;
				zapiszPlik("baza.txt");
			}

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
	
	time_t czas;
	time( & czas );
	aktualnyCzas = localtime( & czas );
	aktualnyCzas->tm_year += 1900;
	aktualnyCzas->tm_mon += 1;

	otworzPlik("baza.txt","wymus");
	
	int exit;

	do {
		exit = wyswietlMenu();
	} while (exit != 1);

    return EXIT_SUCCESS;
}
