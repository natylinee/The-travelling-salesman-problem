#include <iostream>
#include<string>
#include<vector>
#include "Graf.h"
#include "Pliki.h"
using namespace std;


map<string, Wezel> budujGraf(vector<DaneDrog> daneZPliku)
{
	map<string, Wezel> graf; //tworze zmienna std::map

	for(int i = 0; i < daneZPliku.size(); i++) //czynnosc wykonuje dla kazdego miasta w vectorze
	{
		graf[daneZPliku[i].miastoPoczatkowe];	// key: 1 z danych wyciagam miasto poczatkawe
		graf[daneZPliku[i].miastoKoncowe];		// key: 2 z danych wyciagam miasto koncowe

		if(daneZPliku[i].czyDwukierunkowa)
		{
			graf[daneZPliku[i].miastoPoczatkowe].czyOdwiedzone = false;	//ustawiam status miasta na nieodwiedzone
			
			graf[daneZPliku[i].miastoPoczatkowe].wierzcholki.push_back({daneZPliku[i].miastoKoncowe, daneZPliku[i].dystans}); //dolaczam do grafu miasto docelowe i jego dystans
			
			//to samo w druga strone z powodu dwukierunkowosci
			graf[daneZPliku[i].miastoKoncowe].czyOdwiedzone = false;
			
			graf[daneZPliku[i].miastoKoncowe].wierzcholki.push_back({daneZPliku[i].miastoPoczatkowe, daneZPliku[i].dystans});
		}																		
		else
		{
			graf[daneZPliku[i].miastoPoczatkowe].czyOdwiedzone = false;	// ustawiam status miasta na nieodwiedzone
			
			graf[daneZPliku[i].miastoPoczatkowe].wierzcholki.push_back({daneZPliku[i].miastoKoncowe, daneZPliku[i].dystans}); //dolaczam do grafu miasto docelowe i jego dystans
		}
	}
	



	return graf;
}