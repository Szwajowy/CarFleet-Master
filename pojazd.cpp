#include "pojazd.hpp"

// Konstruktor parametrowy dla zmiennych obowi¹zkowych
Pojazd::Pojazd(string typ, string marka, string model, string paliwo, string vin) {
	this->typ = typ;
    this->marka = marka;
	this->model = model;
    this->paliwo = paliwo;
    this->vin = vin;
}
    
// Konstruktor bezparametrowy    
Pojazd::Pojazd() {
    Pojazd("Nieznany","Nieznana","Nieznany","Nieznany",0);
}      
	
// Zwracanie i ustawianie wartoœci zmiennej "typ"		
string Pojazd::oddajTyp() {
	return typ;	
}
	
void Pojazd::ustawTyp(string typ) {
	this->typ = typ;	
}

// Zwracanie i ustawianie wartoœci zmiennej "marka"
string Pojazd::oddajMarka() {
	return marka;	
}
	
void Pojazd::ustawMarka(string marka) {
	this->marka = marka;	
}

// Zwracanie i ustawianie wartoœci zmiennej "model"
string Pojazd::oddajModel() {
	return model;	
}
	
void Pojazd::ustawModel(string model) {
	this->model = model;	
}  

// Zwracanie i ustawianie wartoœci zmiennej "paliwo"
string Pojazd::oddajPaliwo() {
	return paliwo;	
}
	
void Pojazd::ustawPaliwo(string paliwo) {
	this->paliwo = paliwo;	
}

// Zwracanie i ustawianie wartoœci zmiennej "vin"
string Pojazd::oddajVin() {
	return vin;	
}
	
void Pojazd::ustawVIN(string vin) {
	this->vin = vin;	
}     
