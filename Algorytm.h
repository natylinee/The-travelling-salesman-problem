#pragma once
#include <iostream>
#include<string>
#include<map>
#include<fstream>
#include "Graf.h" 

using namespace std;
/**
 * @brief Funkcja analizuje zwrócony wynik i zwraca najoptymalniejsz¹ trasê.
 * @param graf 
 * @param miastoPoczatkowe 
 * @param plikWyjsciowyNazwa 
 * @return w
*/
map<vector<string>, double> komiwojazer(map<string, Wezel> graf, string miastoPoczatkowe, string plikWyjsciowyNazwa);

/**
 * @brief Funkcja wylicza permutacje wszystkich mo¿liwych œcie¿ek wraz z ich wag¹.
 * @param miastoPoczatkowe 
 * @param miastoWezla 
 * @param graf 
 * @param aktualnyDystans 
 * @param aktualnaTrasa 
 * @param czyPermutacjaMozliwa 
 * @return wynik
*/
map<vector<string>, vector<double>> permutuj(string miastoPoczatkowe, string miastoWezla, map<string, Wezel>& graf, vector<double>& aktualnyDystans, vector<string>& aktualnaTrasa, bool czyPermutacjaMozliwa);

/**Kontener przechowuj¹cy wszystkie wyszukane œcie¿ki wraz z ich wag¹.
*/
typedef map<vector<string>, vector<double>> wynik;
/**Kontener przechowuj¹cy najkrótsz¹ œcie¿kê spe³niaj¹c¹ warunki zadania i jej dystans.
*/
typedef map<vector<string>, double> w;