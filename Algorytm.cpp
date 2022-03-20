#include <iostream>
#include <string>
#include <map>
#include "Algorytm.h"
#include <algorithm>
#include <fstream>


using namespace std;

map<vector<string>, vector<double>> permutuj(string miastoPoczatkowe, string miastoWezla, map<string, Wezel>& graf, vector<double>& aktualnyDystans, vector<string>& aktualnaTrasa, bool czyPermutacjaMozliwa); //, vector<string>& minimalnaTrasa, double& minimalnyDystans);


//tu mamy funckje
map<vector<string>, double> komiwojazer(map<string, Wezel> graf, string miastoPoczatkowe, string plikWyjsciowyNazwa)
{

    double minimalnyDystans = INT_MAX; //ustalam minDystans na max

    vector<string> minimalnaTrasa;
    vector<double> aktualnyDystans;
    vector<string> aktualnaTrasa;
    vector<string> pustaTrasa;
    aktualnaTrasa.push_back(miastoPoczatkowe); //dodaje do trasy miasto poczatkowe, czyli 1

    //wywoluje funkcje permutuj, wynik jest map¹, której klucz przyjmuje vector stringów (zawiera trasy), jako wartoœæ mapy przyjmujemy vector double'i (zawiera dystanse)
    map<vector<string>, vector<double>> wynik = permutuj(miastoPoczatkowe, miastoPoczatkowe, graf, aktualnyDystans, aktualnaTrasa, false); 

    
    for (map<vector<string>, vector<double>>::iterator it = wynik.begin(); it != wynik.end(); ++it) //iteruje po wyniku
    {
        double suma = 0;
        for (double i : it->second)
        {
            suma += i; //dodaje pojedyncze odleglosci
        }
        

        if (suma > -1.0 && suma < minimalnyDystans) //if true uaktualniam trase i dystans
        {
            minimalnyDystans = suma;
            minimalnaTrasa.erase(minimalnaTrasa.begin(), minimalnaTrasa.end()); //czyszcze trase do pewnosci, gdyby zawierala smieci

            for (string j : it->first) //przechodze przez pierwszy element mapy (klucz) i pushuje trase
            {
                minimalnaTrasa.push_back(j);
            }
                
        }
        
    }
    if (minimalnyDystans == INT_MAX)
    {
        minimalnyDystans = -1.0;
    }

    

    map<vector<string>, double> w;
    w[minimalnaTrasa] = minimalnyDystans; 
    
    return w; //przekazuje wlasciwy wynik
}

//zalozenia
//miastoPoczatkowe jest stale i przekazywane na poczatku
//czyPermMozliwa jest domyslnie falszywa
//minimalny dystans sprawdzam na koncu

map<vector<string>, vector<double>> permutuj(string miastoPoczatkowe, string miastoWezla, map<string, Wezel> &graf, vector<double>& aktualnyDystans, vector<string>& aktualnaTrasa, bool czyPermutacjaMozliwa)//, vector<string> &minimalnaTrasa, double &minimalnyDystans)
{    
    vector<Droga> wierzcholki = graf[miastoWezla].wierzcholki; // miasta docelowe i dystans aktualnie przerabianego miasta
    map<vector<string>, vector<double>> wynik;


    if (wierzcholki.size() > 0)//gdy sa jakies polaczenia
    {
        for (int i = 0; i < wierzcholki.size(); i++)
        {

            if(wierzcholki[i].miastoDocelowe == miastoPoczatkowe) // gdy miasto docelowe jest 1
            {
                
                if(aktualnaTrasa.size() == graf.size()) //czy przeszlismy juz przez wszystkie miasta?
                {
                        //mamy wszystkie miasta
                    
                        aktualnyDystans.push_back(graf[miastoWezla].wierzcholki[i].dystans); //dodaje jeszcze droge powrotna
                    
                        graf[miastoWezla].czyOdwiedzone = true; //przedostatnie miasto tak¿e odwiedzone
                    
                        
                        aktualnaTrasa.push_back(miastoPoczatkowe); //dodaje takze 1 dla pelnej trasy
                                      
                        
                        wynik[aktualnaTrasa] = aktualnyDystans; //zapisuje do wyniku
                        
                        //skoro znalezlismy pelna trase, to usuwamy 1 i dystans z aktualnej trasy, poniewaz nie jest juz nam dalej potrzebna
                        aktualnyDystans.pop_back();
                        aktualnaTrasa.pop_back();
                        //usuwamy tez miasto, w ktorym znajdujemy sie aktualnie i jego dystans z aktualnej trasy, zeby wyszukac inna droge
                        aktualnaTrasa.pop_back();
                        aktualnyDystans.pop_back();

                        return wynik; 
               
                }
            }
            
            if (graf[wierzcholki[i].miastoDocelowe].czyOdwiedzone == false) //jesli miasto nie bylo odwiedzone
            {
                czyPermutacjaMozliwa = true;
                aktualnyDystans.push_back(graf[miastoWezla].wierzcholki[i].dystans); //dodaje dystans
                
                graf[miastoWezla].czyOdwiedzone = true; //ustalam na juz odwiedzone
                aktualnaTrasa.push_back(wierzcholki[i].miastoDocelowe); //dodaje do trasy
                
                map<vector<string>, vector<double>> w = permutuj(miastoPoczatkowe, wierzcholki[i].miastoDocelowe, graf, aktualnyDystans, aktualnaTrasa, false); 
                //rekurencyjnie wywoluje f permutuj dla miasta docelowego, ktore staje sie miastem wezla
                wynik.insert(w.begin(), w.end()); //wkladam do wyniku znalezion¹ trasê w permutuj 

                graf[wierzcholki[i].miastoDocelowe].czyOdwiedzone = false; //ustalam miasto docelowe na nieodwiedzone

            }
        }    
    }

    

    if(!czyPermutacjaMozliwa) //gdy dane wierzcho³ki nie s¹ 1 i by³y ju¿ odwiedzone to dalsza permutacja nie jest mo¿liwa, musimy siê wróciæ- ta trasa nie jest mo¿liwa
    {
        if(aktualnaTrasa.size() > 0) //zabezpieczenie dla sytuacji, kiedy w grafie znajduje sie miasto poczatkowe, ktore nie ma zadnych drog
        {
            wynik[aktualnaTrasa] = vector<double>{ -1.0 }; //ustalam umownie dystans na -1.0 interpretuje go jako brak wyznaczonej trasy
            aktualnaTrasa.pop_back();
        }
        else
        {
            aktualnaTrasa.push_back(miastoWezla);
            wynik[aktualnaTrasa] = vector<double>{ -1.0 };
            aktualnaTrasa.pop_back();
        }
        
        if(aktualnyDystans.size() > 0)
            aktualnyDystans.pop_back();

        return wynik;
    }

    aktualnaTrasa.pop_back(); //w ramach cofania sie z aktualnego miasta, gdy nie ma ju¿ innych wêz³ów do odwiedzenia(sprawdzenia) to usuwamy z aktualne miasto z trasy
    if(aktualnyDystans.size() > 0) //wracajac do miasta poczatkowego nie ma w nim dystansu do zadnego miasta
        aktualnyDystans.pop_back();
    
    return wynik;
    
}