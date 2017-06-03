#include "pojazd.hpp"

// Konstruktor parametrowy dla zmiennych obowi�zkowych
Pojazd::Pojazd(char typ,string marka,string model,string wersja,char nadwozie,char paliwo,unsigned int pojSilnika,unsigned int rokProd,string vin,string rejestracja, tm przegladOd, tm przegladDo) {
	this->typ = typ;
    this->marka = marka;
	this->model = model;
	this->wersja = wersja;
	this->nadwozie = nadwozie;
    this->paliwo = paliwo;
    this->pojSilnika = pojSilnika;
    this->rokProd = rokProd;
    this->vin = vin;
    this->rejestracja = rejestracja;
    this->przegladOd = przegladOd;
	this->przegladDo = przegladDo;
}
    
// Konstruktor bezparametrowy    
Pojazd::Pojazd() {
    Pojazd('N',"Nieznana","Nieznany","Nieznana",'N','N',0,1981,"AAAAAAAAAAAAA0000","Nieznana", przegladOd, przegladDo);
}      
	
// Zwracanie i ustawianie warto�ci zmiennej "typ"		
char Pojazd::oddajTyp() {
	return typ;	
}
	
void Pojazd::ustawTyp(char typ) {
	this->typ = typ;	
}

// Zwracanie i ustawianie warto�ci zmiennej "marka"
string Pojazd::oddajMarka() {
	return marka;	
}
	
void Pojazd::ustawMarka(string marka) {
	this->marka = marka;	
}

// Zwracanie i ustawianie warto�ci zmiennej "model"
string Pojazd::oddajModel() {
	return model;	
}
	
void Pojazd::ustawModel(string model) {
	this->model = model;	
}  

// Zwracanie i ustawianie warto�ci zmiennej "wersja"
string Pojazd::oddajWersja() {
	return wersja;	
}

void Pojazd::ustawWersja(string wersja) {
	this->wersja = wersja;	
}
		
// Zwracanie i ustawianie warto�ci zmiennej "nadwozie"
char Pojazd::oddajNadwozie() {
	return nadwozie;	
}

void Pojazd::ustawNadwozie(char nadwozie) {
	this->nadwozie = nadwozie;	
}

// Zwracanie i ustawianie warto�ci zmiennej "paliwo"
char Pojazd::oddajPaliwo() {
	return paliwo;	
}
	
void Pojazd::ustawPaliwo(char paliwo) {
	this->paliwo = paliwo;	
}

// Zwracanie i ustawianie warto�ci zmiennej "pojSilnika"
unsigned int Pojazd::oddajPojSilnika() {
	return pojSilnika;	
}
void Pojazd::ustawPojSilnika(unsigned int pojSilnika) {
	this->pojSilnika = pojSilnika;	
}

// Zwracanie i ustawianie warto�ci zmiennej "moc"
unsigned int Pojazd::oddajMoc() {
	return moc;	
}
void Pojazd::ustawMoc(unsigned int moc) {
	this->moc = moc;	
}

// Zwracanie i ustawianie warto�ci zmiennej "miejscaSiedz"
unsigned int Pojazd::oddajMiejscaSiedz() {
	return miejscaSiedz;	
}
void Pojazd::ustawMiejscaSiedz(unsigned int miejscaSiedz) {
	this->miejscaSiedz = miejscaSiedz;	
}

// Zwracanie i ustawianie warto�ci zmiennej "miejscaOgl"
unsigned int Pojazd::oddajMiejscaOgl() {
	return miejscaOgl;	
}
void Pojazd::ustawMiejscaOgl(unsigned int miejscaOgl) {
	this->miejscaOgl = miejscaOgl;	
}
		
// Zwracanie i ustawianie warto�ci zmiennej "masa"
unsigned int Pojazd::oddajMasa() {
	return masa;	
}
void Pojazd::ustawMasa(unsigned int masa) {
	this->masa = masa;	
}
		
// Zwracanie i ustawianie warto�ci zmiennej "dopMasaCalk"
unsigned int Pojazd::oddajDopMasaCalk() {
	return dopMasaCalk;	
}
void Pojazd::ustawDopMasaCalk(unsigned int dopMasaCalk) {
	this->dopMasaCalk = dopMasaCalk;	
}
		
// Zwracanie i ustawianie warto�ci zmiennej "masaPrzyczHam"
unsigned int Pojazd::oddajMasaPrzyczHam() {
	return masaPrzyczHam;	
}
void Pojazd::ustawMasaPrzyczHam(unsigned int masaPrzyczHam) {
	this->masaPrzyczHam = masaPrzyczHam;	
}
		
// Zwracanie i ustawianie warto�ci zmiennej "masaPrzyczBezHam"
unsigned int Pojazd::oddajMasaPrzyczBezHam() {
	return masaPrzyczBezHam;	
}
void Pojazd::ustawMasaPrzyczBezHam(unsigned int masaPrzyczBezHam) {
	this->masaPrzyczBezHam = masaPrzyczBezHam;	
}
		
// Zwracanie i ustawianie warto�ci zmiennej "osie"
unsigned int Pojazd::oddajOsie() {
	return osie;	
}
void Pojazd::ustawOsie(unsigned int osie) {
	this->osie = osie;	
}
		
// Zwracanie i ustawianie warto�ci zmiennej "rozstawOsi"
unsigned int Pojazd::oddajRozstawOsi() {
	return rozstawOsi;	
}
void Pojazd::ustawRozstawOsi(unsigned int rozstawOsi) {
	this->rozstawOsi = rozstawOsi;	
}
		
// Zwracanie i ustawianie warto�ci zmiennej "rozstawKol"
unsigned int Pojazd::oddajRozstawKol() {
	return rozstawKol;	
}
void Pojazd::ustawRozstawKol(unsigned int rozstawKol) {
	this->rozstawKol = rozstawKol;	
}
		
// Zwracanie i ustawianie warto�ci zmiennej "dopNaciskNaOs"
unsigned int Pojazd::oddajDopNaciskNaOs() {
	return dopNaciskNaOs;	
}
void Pojazd::ustawDopNaciskNaOs(unsigned int dopNaciskNaOs) {
	this->dopNaciskNaOs = dopNaciskNaOs;	
}

// Zwracanie i ustawianie warto�ci zmiennej "rokProd"
unsigned int Pojazd::oddajRokProd() {
	return rokProd;	
}
void Pojazd::ustawRokProd(unsigned int rokProd) {
	this->rokProd = rokProd;	
}

// Zwracanie i ustawianie warto�ci zmiennej "vin"
string Pojazd::oddajVin() {
	return vin;	
}
	
void Pojazd::ustawVin(string vin) {
	this->vin = vin;	
}    

// Zwracanie i ustawianie warto�ci zmiennej "rejestracja"
string Pojazd::oddajRejestracja() {
	return rejestracja;	
}

void Pojazd::ustawRejestracja(string rejestracja) {
	this->rejestracja = rejestracja;	
}

// Zwracanie i ustawianie warto�ci zmiennej "opis"
string Pojazd::oddajOpis() {
	return opis;	
}

void Pojazd::ustawOpis(string opis) {
	this->opis = opis;	
}
		
// Zwracanie i ustawianie warto�ci zmiennej "uwagi"
string Pojazd::oddajUwagi() {
	return uwagi;	
}

void Pojazd::ustawUwagi(string uwagi) {
	this->uwagi = uwagi;	
} 

// Zwracanie i ustawianie warto�ci zmiennej "ocOd"
tm Pojazd::oddajOcOd() {
	return ocOd;	
}

void Pojazd::ustawOcOd(tm ocOd) {
	this->ocOd = ocOd;	
} 
		
// Zwracanie i ustawianie warto�ci zmiennej "ocDo"
tm Pojazd::oddajOcDo() {
	return ocDo;	
}

void Pojazd::ustawOcDo(tm ocDo) {
	this->ocDo = ocDo;	
} 
		
// Zwracanie i ustawianie warto�ci zmiennej "przegladOd"
tm Pojazd::oddajPrzegladOd() {
	return przegladOd;	
}

void Pojazd::ustawPrzegladOd(tm przegladOd) {
	this->przegladOd = przegladOd;	
} 
		
// Zwracanie i ustawianie warto�ci zmiennej "przegladDo"
tm Pojazd::oddajPrzegladDo() {
	return przegladDo;	
}

void Pojazd::ustawPrzegladDo(tm przegladDo) {
	this->przegladDo = przegladDo;	
} 
