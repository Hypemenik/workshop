#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#include <conio.h> 
using namespace std;


bool empty(std::ifstream& pFile) {
	return pFile.peek() == std::ifstream::traits_type::eof();
}

int CoZrobic() {
	int co;
	cout << endl << "Wybierz\n1 jesli naprawa\n2 Jesli Przeglad\n3 Jesli to i to: ";
	cin >> co;
	return co;
}

int getIndx() {
	int nr;
	cout << "NUMER:    ";
	cin >> nr;
	return nr;
}



struct DaneSamochodu {
	string rejestracja;
	string VIN;
	string typNadwozia;
};

struct DaneKlienta {
	int nr;
	string imie;
	string nazwisko;
	int nr_tel;
	DaneSamochodu samochod;
};


class Warsztat {
private:
	vector<DaneKlienta> listaKlientow;
	int liczbaKlientow;

public:
	Warsztat() :  liczbaKlientow(0) {}
	Warsztat(const string file) {;
		liczbaKlientow = 0;
		ifstream plik;
		plik.open(file);
		if (!plik) {
			cerr << "Error in opening the file" << endl;
		}
		DaneKlienta Client;
		while (plik >> Client.nr >> Client.imie >> Client.nazwisko >> Client.nr_tel >> Client.samochod.rejestracja 
			>> Client.samochod.VIN >> Client.samochod.typNadwozia) {
			listaKlientow.push_back(Client);
			liczbaKlientow++;
		}
	}
	DaneKlienta getClient(int idx) {
		DaneKlienta Client = listaKlientow[idx];
		return Client;
	}
	
	/*void usun(int idx) {
		listaKlientow.erase(idx);
	}*/

	~Warsztat() {
	}
	int get_liczbaKlientow() {
		return liczbaKlientow;
	}

	void wypiszKlientow() {
		DaneKlienta Client;
		for (const auto& Client : listaKlientow) {
			cout << endl << endl << "Klient nr: "<<  Client.nr << endl << Client.imie << ' ' << Client.nazwisko << ' ' << Client.nr_tel << endl;
			cout << "Samochod: " << endl;
			cout << Client.samochod.rejestracja << ' ' << Client.samochod.VIN << ' ' << Client.samochod.typNadwozia<<endl<<endl;

		}
	}
	void updateFile() {

		static const char* const file = "clients.txt";
		ofstream fout;
		fout.open(file);
		if (!fout) {
			cerr << "Error in opening the output file" << endl;
		}

		DaneKlienta Client;
		int liczba = 0;
		for (const auto& Client : listaKlientow) {
			fout << liczba << endl << Client.imie << endl << Client.nazwisko << endl << Client.nr_tel << endl << Client.samochod.rejestracja << endl << Client.samochod.VIN << endl << Client.samochod.typNadwozia << endl << endl;
			++liczba;
		}
	}

	void noweZgloszenie() {
		DaneKlienta nowyKlient;

		cout << "Imie: ";
		cin >> nowyKlient.imie;

		cout << "Nazwisko: ";
		cin >> nowyKlient.nazwisko;

		cout << "Nr telefonu: ";
		cin >> nowyKlient.nr_tel;

		cout << "Rejestracja samochodu: ";
		cin >> nowyKlient.samochod.rejestracja;

		cout << "VIN samochodu: ";
		cin >> nowyKlient.samochod.VIN;

		cout << "Typ nadwozia samochodu: ";
		cin >> nowyKlient.samochod.typNadwozia;

		nowyKlient.nr = liczbaKlientow;
		++liczbaKlientow;

		listaKlientow.push_back(nowyKlient);
		cout << "Nowe zgloszenie dodane." << endl;
	}

	void wypiszKlienta(int idx) {
		cout<<endl <<endl << "IMIE NAZWISKO NUMER" << endl << listaKlientow[idx].imie << ' ' << listaKlientow[idx].nazwisko << ' ' << listaKlientow[idx].nr_tel << endl;
		cout << endl<< "Rejestracja nr_VIN Nadwozie" << endl;
		cout << listaKlientow[idx].samochod.rejestracja << ' ' << listaKlientow[idx].samochod.VIN << ' ' << listaKlientow[idx].samochod.typNadwozia << endl <<endl ;
	}

	void serwis() {
		// Tu mo¿na dodaæ logikê obs³ugi serwisu
		cout << "Serwis w toku..." << endl;
	}

	void wystawienieFaktury() {
		// Tu mo¿na dodaæ logikê wystawiania faktury
		cout << "Faktura wystawiona." << endl;
	}
};



struct serwis_info {
	string naprawa;
	string przeglad;
	int nr;
};

class serwis {
	vector<serwis_info> Lista;
	int idx;
public:

	serwis(Warsztat* workship) {
		idx = workship->get_liczbaKlientow();
		ifstream plik("serwis.txt");
		if (!plik)
		{
			cerr << "Error in opening the output file" << endl;
		}

		if (empty(plik)) //plik serwis pusty
		{
			for (int i = 0; i < idx; ++i) {
				serwis_info Client;
				Client.nr = i;
				Client.naprawa = "nie";
				Client.przeglad = "nie";
				Lista.push_back(Client);
			}
			DaneKlienta Client;
			static const char* const file = "serwis.txt";
			ofstream fout;
			for (const auto& Client : Lista) {
				fout << Client.nr << endl << Client.naprawa << endl << Client.przeglad << endl;
			}
		}
		serwis_info Client;
		while (plik >> Client.nr >> Client.naprawa >> Client.przeglad) {
			Lista.push_back(Client);
		}
	}


	void dodaj() {
		serwis_info Client;
		Client.nr = idx;
		Client.naprawa = "nie";
		Client.przeglad = "nie";
		Lista.push_back(Client);
		idx++;

	}
	void update() {
		static const char* const file = "serwis.txt";
		ofstream fout;
		fout.open(file);
		if (!fout) {
			cerr << "Error in opening the output file" << endl;
		}

		DaneKlienta Client;
		for (const auto& Client : Lista) {
			fout << Client.nr << endl << Client.naprawa << endl << Client.przeglad << endl << endl;
		}
	}
	serwis_info getSerwis(int idx) {
		serwis_info Client = Lista[idx];
		return Client;
	}

	void wypiszSerwis(int idx) {
		cout << "Naprawa: " << Lista[idx].naprawa << endl;
		cout << "Przeglad: " << Lista[idx].przeglad << endl;
	}
	
	void aktualizacjaSerwisu(int idx,int co ) {
		if (co == 1) {
			cout << "\nWybrano naprawe ";
			Lista[idx].naprawa = "tak";

		}
		else if (co == 2) {
			cout << "\nWybrano przeglad ";
			Lista[idx].przeglad = "tak";
		}
		else if (co == 3) {
			cout << "\nWybrano przeglad i naprawe ";
			Lista[idx].naprawa = "tak";
			Lista[idx].przeglad = "tak";
		}
	}
};


class Faktury  {
private:
	DaneKlienta Client;
	serwis_info cena;
	int cost;
public:
	Faktury(DaneKlienta Dane,serwis_info Serwis) {
		Client.imie = Dane.imie;
		Client.nazwisko = Dane.nazwisko;
		Client.nr_tel = Dane.nr_tel;
		Client.nr = Dane.nr;
		Client.samochod.rejestracja =  Dane.samochod.rejestracja;
		cena.naprawa = Serwis.naprawa;
		cena.nr = Serwis.nr;
		cena.przeglad = Serwis.przeglad;
		cost = 0;
	}
	void wystawienieFaktury() {
		if (cena.naprawa == "tak" && cena.przeglad == "nie") {
			cout << endl << "Wystawiono fakture za naprawe cena : 500zl ";
			cout << endl << "NR: " << Client.nr;
			cout << endl << Client.imie << ' ' << Client.nazwisko;
			cout << endl << "Nr telefonu: " << Client.nr_tel;
			cout << endl << "Rejestracja: " << Client.samochod.rejestracja;
			cout << endl << "Czy byla naprawa" << cena.naprawa;
			cost = 500;
		}
		if (cena.naprawa == "nie" && cena.przeglad == "tak") {
			cout << endl << "Wystawiono fakture za naprawe przeglad : 200zl ";
			cout << endl << "NR: " << Client.nr;
			cout << endl << Client.imie << ' ' << Client.nazwisko;
			cout << endl << "Nr telefonu: " << Client.nr_tel;
			cout << endl << "Rejestracja: " << Client.samochod.rejestracja;
			cout << endl << "Czy byla przeglad" << cena.przeglad;
			cost = 200;
		}
		if (cena.naprawa == "tak" && cena.przeglad == "tak") {
			cout << endl << "Wystawiono fakture za naprawe i przeglad cena : 700zl ";
			cout << endl << "NR: " << Client.nr;
			cout << endl << Client.imie << ' ' << Client.nazwisko;
			cout << endl << "Nr telefonu: " << Client.nr_tel;
			cout << endl << "Rejestracja: " << Client.samochod.rejestracja;
			cout << endl << "Czy byla naprawa: " << cena.naprawa;
			cout << endl << "Czy byla przeglad: " << cena.przeglad;
			cost = 700;
		}
		if (cena.naprawa == "nie" && cena.przeglad == "nie") {
			cout << "Nie da sie wystawic faktury\n";
		}
	}
	void zapisanie() {
		ofstream fout;
		fout.open("faktury.txt", std::ios_base::app); // append instead of overwrite
		if (!fout) {
			cerr << "Error in opening the output file" << endl;
		}

		fout << endl << "Wystawiono fakture za naprawe i przeglad cena: "<<cost;
		fout << endl << "NR: " << Client.nr;
		fout << endl << Client.imie << ' ' << Client.nazwisko;
		fout << endl << "Nr telefonu: " << Client.nr_tel;
		fout << endl << "Rejestracja: " << Client.samochod.rejestracja;
		fout << endl << "Czy byla naprawa: " << cena.naprawa;
		fout << endl << "Czy byla przeglad: " << cena.przeglad<<endl<<endl;
	}
};



int main() {
	int wybor;
	do {
		Warsztat warsztat("clients.txt");
		serwis Serwis(&warsztat);
		system("CLS");
		cout << "Menu:" << endl;
		cout << "1. Nowe zgloszenie" << endl;
		cout << "2. Serwis" << endl;
		cout << "3. Wystawienie faktury" << endl;
		cout << "4. Wypisz Liste Klientow" << endl;
		cout << "0. Wyjdz" << endl;
		cout << "Wybierz opcje: ";
		cin >> wybor;
		int idx;
		switch (wybor) {
		case 1:
			warsztat.noweZgloszenie();
			Serwis.dodaj();
			system("CLS");
			warsztat.updateFile();
			Serwis.update();
			break;
		case 2:
			system("CLS");
			cout << "Wybierz klienta do ktorego chcesz dodac serwis: "<< endl;
			warsztat.wypiszKlientow();
			cout << endl << endl;
			idx = getIndx();
			system("CLS");
			cout << "Klient nr: " << idx;
			warsztat.wypiszKlienta(idx);
			Serwis.wypiszSerwis(idx);
			int co; 
			co = CoZrobic();
			Serwis.aktualizacjaSerwisu(idx,co);
			Serwis.update();
			_getch();
			break;
		case 3:
		{system("CLS");
		cout << "Wybierz klienta dla ktorego chcesz wystawic fakture: " << endl;
		warsztat.wypiszKlientow();
		cout << endl << endl;
		idx = getIndx();
		system("CLS");
		cout << "Klient nr: " << idx;
		DaneKlienta Uzytkownik = warsztat.getClient(idx);
		serwis_info Ceny = Serwis.getSerwis(idx);
		Faktury faktura(Uzytkownik, Ceny);
		faktura.wystawienieFaktury();
		faktura.zapisanie();
	/*	warsztat.usun(idx);
		Serwis.usun(idx);*/
		warsztat.updateFile();
		Serwis.update();
		_getch(); }
			break;
		case 4:
			system("CLS");
			warsztat.wypiszKlientow();
			_getch();
			system("CLS");
			break;
		case 0:
			cout << "Zakonczono program." << endl;
			break;
		default:
			cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
			_getch();
			
		}

	} while (wybor != 0);

	system("pause");
	return 0;
}