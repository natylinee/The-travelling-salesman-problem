#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Pliki.h"

using namespace std;


vector<DaneDrog> odczytajPlikWejsciowy(string& nazwaPliku)
{
	fstream plik;
	plik.open(nazwaPliku); //otwarcie pliku
	string str;

	

	string niedokonczony = ""; //zmienna niedokoñczony zapisuje reszte str, by w calosci odczytac dane

	vector<DaneDrog> daneDrog; //bedzie zawieral informacje zawarte w strukturze DaneDrog
	string trasa = ""; //trasa poczatkowo jest pusta

	while (getline(plik, str)) //pobieram po linijce
	{

		str = niedokonczony + str; //zabezpiecza przed niepelnymi danymi w str
			
		if (str.find(",") == string::npos) //jeœli nie ma przecinka, pobieramy kolejn¹ linijkê i szukamy przecinka
		{
			niedokonczony = str;
		}
		else
		{
				
			for (int i = 0; i < str.length(); i++) //przechodze przez str
			{
				if(str[i] == ',') //gdy napotkam przecinek -> koniec zestawu danych
				{
					trasa = str.substr(0, i); //wydzielam do zmiennej trasa zestaw danych

					if (i < str.length()) //jesli str zawiera jeszcze cos wiecej
					{
						niedokonczony = str.substr(i + 1, str.length() - 1); //dalsza czesc zapisujemy do niedokonczony
					}
					else
						niedokonczony = ""; //w przeciwnym wypadku pusty

					break; //przerwanie funkcji, bo wyznaczyliœmy trasê
				}
			}

			zapisDoDanych(trasa, daneDrog); //wywolanie funkcji
			
		}
		
	}
	
	zapisDoDanych(str, daneDrog); //wyjatek dla ostatniej linijki danych, ktora nie posiada przecinka, gdy funkcja getline sie zakonczy, wywoluje zapisDoDanych dla ostatniego str
	plik.close(); //zamkniecie pliku

	return daneDrog; //zwraca vector z miastami oraz ich polaczeniami, dystansem i info czy dwukierunkowa
}

void zapisDoDanych(string trasa, vector<DaneDrog> &daneDrog)
{
	string rodzajDrogi = "";
	bool czyDwukierunkowa = false;
	string miastoPoczatkowe = "", miastoKoncowe = "";
	double dystans = 0;

	for (int i = 0; i < trasa.length(); i++)
	{
		if (trasa[i] == '(') //usuwamy nawias
			trasa[i] = ' ';
		else if (trasa[i] == ')') //jestemy na koncu naszych danych, sa juz odpowiednio przygotowane do wczytywania
		{
			trasa[i] = ' '; //usuwamy nawias
			stringstream ss(trasa);
			ss >> miastoPoczatkowe; //wczytuje po kolei do zmiennych
			ss >> rodzajDrogi;
			ss >> miastoKoncowe;
			ss >> dystans;
			if (rodzajDrogi == "-") //droga dwukierunkowa
			{
				daneDrog.push_back({ miastoPoczatkowe, true, miastoKoncowe, dystans }); //do vectora dodaje strukturê danych
			}
			else if (rodzajDrogi == "->") //droga jednokierunkowa
			{
				daneDrog.push_back({ miastoPoczatkowe, false, miastoKoncowe, dystans });
			}
		}
		else if (trasa[i] == ':') //usuwamy dwukropek
			trasa[i] = ' ';
	}
}


void zapiszWynikDoPliku(map<vector<string>, double> wynik, string plikWyjsciowyNazwa)
{
	ofstream zapis(plikWyjsciowyNazwa);

	for (map<vector<string>, double>::iterator it = wynik.begin(); it != wynik.end(); ++it) //iteruje po gotowym wyniku
	{
		if (it->second == -1.0) 
		{
			zapis << "Trasa nie istnieje" << endl;
		}
		else
		{
			for (string i : it->first)
			{
				//cout << i << " -> ";
				zapis << i << " "; //zapisuje do pliku kolejne odwiedzane miasta w trasie
			}
			//cout << endl;
			//cout << it->second << endl;
			zapis << endl << it->second; //zapisuje dystans
		}
	}

	zapis.close(); //zamykam strumien
}
