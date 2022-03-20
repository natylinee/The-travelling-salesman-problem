
#include <iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include "Przelaczniki.h"
#include "Pliki.h"
#include "Graf.h"
#include "Struktury.h"
#include "Algorytm.h"
#include <map>
using namespace std;

int main(const int argc, char ** argv)
{
    
    string plikWejsciowyNazwa = "";
    string plikWyjsciowyNazwa = "";
    
    if (!odczytajPrzelaczniki(argc, argv, plikWejsciowyNazwa, plikWyjsciowyNazwa))
    {
        help();
    }
    
    vector<DaneDrog> daneZPliku = odczytajPlikWejsciowy(plikWejsciowyNazwa); //odczytuje dane wejsciowe
    
    map<string, Wezel> graf = budujGraf(daneZPliku); //buduje graf
    
    map<vector<string>, double> wynik = komiwojazer(graf, daneZPliku[0].miastoPoczatkowe, plikWyjsciowyNazwa); //caly algorytm
    
    zapiszWynikDoPliku(wynik, plikWyjsciowyNazwa); //zapisuje do pliku wyjsciowego
    
   
}
