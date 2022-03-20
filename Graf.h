#pragma once
#include <iostream>
#include<string>
#include<map>
#include "Pliki.h"

using namespace std;

struct Droga;
/**
 * @brief Stuktura odpowiedzialna za przechowywanie informacji czy dane miasto by³o odwiedzone oraz dystans do danego miasta docelowego.  
*/
struct Wezel
{
	bool czyOdwiedzone;
	vector<Droga> wierzcholki;
};
/**
 * @brief Struktura opowiedzialna za przecowanie informacji o mieœcie docelowym i dystansem do niego z miasta pocz¹tkowego.
*/
struct Droga
{
	string miastoDocelowe;
	double dystans;
};

/**
 * @brief Funkcja buduje graf z przekazanych danych z pliku.
 * @param daneZPliku
 * @return graf
*/
map<string, Wezel> budujGraf(vector<DaneDrog> daneZPliku);
/**Kontener przechowuj¹cy bezpoœrednie po³¹czenia pomiêdzy miastami.
*/
typedef map<string, Wezel> graf;