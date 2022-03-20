#include<iostream>
using namespace std;
/**
 * @brief 
 * @param argc 
 * @param argv 
 * @param plikWejsciowy 
 * @param plikWyjsciowy 
 * @return 
*/
bool odczytajPrzelaczniki(int argc, char** argv, string& plikWejsciowy, string& plikWyjsciowy)
{
	for (int i = 0; i < argc; i++)
	{
		if (argc > 1)
		{
			if (strcmp(argv[i], "-i") == 0)
			{
				plikWejsciowy = argv[i + 1];
			}
			if (strcmp(argv[i], "-d") == 0)
			{
				plikWyjsciowy = argv[i + 1];
			}
		}
		else return false;
	} 
	return true;
}

void help()
{
	cout << "Aby poprawnie skorzystac z przelacznikow wpisz w konsole \n kurier.exe -i wejsciowy.txt -d wyjsciowy.txt" << endl;
}