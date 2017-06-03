#include "operacja.hpp"

// Konstruktor parametrowy
Operacja::Operacja(string operacja, string wynik) {
	this->operacja = operacja;
	this->wynik = wynik;
}

// Konstruktor bezparametrowy
Operacja::Operacja() {
	Operacja("Operacja nieznana", "brak wyniku");
}
	
// Zwracanie i ustawianie warto�ci zmiennej "operacja"	
string Operacja::oddajOperacja() {
	return operacja;	
}
	
void Operacja::ustawOperacja(string operacja) {
	this->operacja = operacja;	
} 
	
// Zwracanie i ustawianie warto�ci zmiennej "atrybut"
string Operacja::oddajAtrybut() {
	return atrybut;
}

void Operacja::ustawAtrybut(string atrybut) {
	this->atrybut = atrybut;	
} 
		
// Zwracanie i ustawianie warto�ci zmiennej "poprzedniaWartosc"
string Operacja::oddajPoprzedniaWartosc() {
	return poprzedniaWartosc;
}

void Operacja::ustawPoprzedniaWartosc(string poprzedniaWartosc) {
	this->poprzedniaWartosc = poprzedniaWartosc;	
} 		
	
// Zwracanie i ustawianie warto�ci zmiennej "wynik"		
string Operacja::oddajWynik() {
	return wynik;	
}
	
void Operacja::ustawWynik(string wynik) {
	this->wynik = wynik;	
}
