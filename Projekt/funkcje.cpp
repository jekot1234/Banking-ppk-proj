#include <string>
#include <iostream> 
#include <cstdlib>
#include <fstream>    
#include <sstream>
//#include <vld.h>

#include "struktury.h"
#include "funkcje.h"

uzytkownik* wczytaj(std::string nazwa) {

	std::ifstream wejscie(nazwa);	//otwarcie pliku

	if (wejscie)
	{

		uzytkownik *head = nullptr;
		uzytkownik *poprz = nullptr;	//wskaznik pomocniczy

		while (!wejscie.eof())
		{

			if (!head)
			{
				head = new uzytkownik;

				wejscie >> head->imie;
				wejscie >> head->nazwisko;
				wejscie >> head->konto;
				wejscie >> head->limit;
				head->transhead = nullptr;

				if (wejscie.fail())	// sprawdzenie poprawnosci
				{
					std::cout << "Blad pliku!";
					wejscie.close();	// zamkniecie pliku
					usun(head);
					return nullptr;		// powrot po niepowodzeniu
				}

				while (!wejscie.eof() && wejscie.get() != 10) // dopoki nie pojawi sie nowa linia lub koniec pliku
				{
					if (!head->transhead)
					{
						trans *nowa = new trans;

						int r;	//zmienne pomocnicze
						int m;
						int d;

						wejscie >> r;
						wejscie >> m;
						wejscie >> d;

						nowa->termin = date{ d, m, r };

						wejscie >> nowa->kwota;
						nowa->konto = head->konto;

						nowa->next = nullptr;
						head->transhead = nowa;

						if (wejscie.fail())	// sprawdzenie poprawnosci
						{
							std::cout << "Blad pliku!";
							wejscie.close();	// zamkniêcie pliku
							usun(head);
							return nullptr;		// powrot po niepowodzeniu
						}
					}
					else
					{
						trans *nowa = new trans;

						int r;	//zmienne pomocnicze
						int m;
						int d;

						wejscie >> r;
						wejscie >> m;
						wejscie >> d;

						nowa->termin = date{ d, m, r };

						wejscie >> nowa->kwota;
						nowa->konto = head->konto;

						nowa->next = head->transhead;
						head->transhead = nowa;

						if (wejscie.fail())	// sprawdzenie poprawnosci
						{
							std::cout << "Blad pliku!";
							wejscie.close();	// zamkniecie pliku
							usun(head);
							return nullptr;		// powrot po niepowodzeniu
						}
					}
				}

				head->next = nullptr;	//zabezpiecznie przed wyjatkiem
				poprz = head;
			}
			else
			{
				uzytkownik * nowy = new uzytkownik;

				wejscie >> nowy->imie;
				wejscie >> nowy->nazwisko;
				wejscie >> nowy->konto;
				wejscie >> nowy->limit;
				nowy->transhead = nullptr;

				if (wejscie.fail())	// sprawdzenie poprawnosci
				{
					std::cout << "Blad pliku!";
					poprz->next = nullptr;	//zabezpiecznie przed wyjatkiem
					wejscie.close();		// zamyka plik
					usun(head);
					return nullptr;			//powrot po porazce
				}

				while (!wejscie.eof() && wejscie.get() != 10) // dopoki nie pojawi sie nowa linia lub koniec pliku
				{
					if (!nowy->transhead)
					{
						trans *nowa = new trans;

						int r;	//zmienne pomocnicze
						int m;
						int d;

						wejscie >> r;
						wejscie >> m;
						wejscie >> d;

						nowa->termin = date{ d, m, r };

						wejscie >> nowa->kwota;
						nowa->konto = nowy->konto;

						nowa->next = nullptr;
						nowy->transhead = nowa;

						if (wejscie.fail())	// sprawdzenie poprawnosci
						{
							std::cout << "Blad pliku!";
							wejscie.close();	// zamkniecie pliku
							usun(head);
							return nullptr;		// powrot po niepowodzeniu
						}
					}
					else
					{
						trans *nowa = new trans;

						int r;	//zmienne pomocnicze
						int m;
						int d;

						wejscie >> r;
						wejscie >> m;
						wejscie >> d;

						nowa->termin = date{ d, m, r };

						wejscie >> nowa->kwota;
						nowa->konto = nowy->konto;

						nowa->next = nowy->transhead;
						nowy->transhead = nowa;

						if (wejscie.fail())	// sprawdzenie poprawnosci
						{
							std::cout << "Blad pliku!";
							wejscie.close();	// zamkniecie pliku
							usun(head);
							return nullptr;		// powrot po niepowodzeniu
						}
					}
				}

				poprz->next = nowy;
				poprz = nowy;
				poprz->next = nullptr;
			}
		}
		wejscie.close();	// zamyka plik
		std::cout << "Wczytywanie uzytkownikow zakonczone pomyslnie." << std::endl;
		return head;		//sukces zwraca wskaznik na poczatek listy
	}
	else
	{
		std::cout << "Nie udalo sie wczytac wskazanego pliku!" << std::endl;
		return nullptr;	//powrot po niepowodzeniu
	}
}

void wyplata(uzytkownik * &head, int kwota, date termin, int konto)
{
	uzytkownik *szukany = szukajkonto(head, konto);

	if (szukany == nullptr)
		return;

	szukany->limit -= kwota;

	trans *nowa = new trans;
	nowa->kwota = kwota * (-1);
	nowa->termin = termin;
	nowa->konto = konto;

	if (szukany->transhead == nullptr)
		nowa->next = nullptr;
	else
		nowa->next = szukany->transhead;
	szukany->transhead = nowa;
}

void wplata(uzytkownik * &head, int kwota, date termin, int konto)
{
	uzytkownik *szukany = szukajkonto(head, konto);

	if (szukany == nullptr)
		return;

	szukany->limit += kwota;

	trans *nowa = new trans;
	nowa->kwota = kwota;
	nowa->termin = termin;
	nowa->konto = konto;

	if (szukany->transhead == nullptr)
		nowa->next = nullptr;
	else
		nowa->next = szukany->transhead;

	szukany->transhead = nowa;
}

void undo(uzytkownik *head, int kwota, date termin, int konto)
{
	head = szukajkonto(head, konto);

	if (!head)
	{
		std::cout << "Nie znaleziono uzytkownika" << std::endl;
		return;
	}

	trans *transhead = head->transhead;

	if (transhead == nullptr)
		return;
	trans *usuwana = transhead;
	trans *poprz = nullptr;
	bool usunieto = false;

	while (transhead)
	{
		if (transhead->konto == konto && transhead->kwota == kwota && rownadate(termin, transhead->termin))
		{
			if (!poprz)											//jezeli pierwsza z listy transakcja do usuniecia
			{
				if (!head->transhead->next)						// i jednoczesnie ostatnia
				{
					head->transhead = nullptr;
					delete(transhead);
					usunieto = true;
					break;
				}
				else
				{
					head->transhead = head->transhead->next;
					usuwana = transhead;
					transhead = transhead->next;
					delete(usuwana);
					usunieto = true;
					break;
				}
			}
			else
			{
				poprz->next = transhead->next;
				usuwana = transhead;
				transhead = transhead->next;
				delete(usuwana);
				usunieto = true;
				break;
			}
		}
		poprz = transhead;
		transhead = transhead->next;
	}
	if (!usunieto)
		std::cout << "Nie udalo sie znalesc transakcji do usuniecia" << std::endl;
}

void wywe(uzytkownik *head, int kwota, int kontoA, int kontoB, date termin)
{
	uzytkownik *nadawca = szukajkonto(head, kontoA);
	uzytkownik *odbiorca = szukajkonto(head, kontoB);

	if (!nadawca || !odbiorca)
	{
		std::cout << " Nie znaleziono nadawcy/odbiorcy!" << std::endl;
		return;
	}

	wyplata(nadawca, kwota, termin, kontoA);
	wplata(odbiorca, kwota, termin, kontoB);

}


void wypisz(uzytkownik *head, bool kontynuuj)
{
	while (head)
	{

		std::cout << head->imie << " ";
		std::cout << head->nazwisko << " ";
		std::cout << head->konto << " ";
		std::cout << head->limit << std::endl;

		trans *transhead = head->transhead;

		while (transhead)
		{
			trans *temp = transhead;
			date DATA = temp->termin;

			std::cout << DATA.rok << " ";
			std::cout << DATA.miesiac << " ";
			std::cout << DATA.dzien << " ";

			std::cout << temp->kwota << "PLN ";

			std::cout << temp->konto << std::endl;
			transhead = temp->next;

		}

		head = head->next;

		if (!kontynuuj)
			head = nullptr;

	}
}

uzytkownik* szukajkonto(uzytkownik *head, int szukane) {

	bool znalezione = false;

	while (!znalezione && head)
	{
		if (head->konto == szukane)
		{
			znalezione = true;
			return head;
		}
		head = head->next;
	}
	if (!znalezione)
	{
		return nullptr;
	}
}

void raport(uzytkownik *head, date a, date b, std::string arg)
{

	trans *wszystkie = nullptr;
	trans *transtemp = nullptr;
	trans *nowa = nullptr;

	while (head)
	{
		transtemp = head->transhead;
		while (transtemp)
		{
			if (!wszystkie)
			{
				trans *nowa = new trans;
				nowa->konto = transtemp->konto;
				nowa->kwota = transtemp->kwota;
				nowa->termin = transtemp->termin;
				wszystkie = nowa;
				nowa->next = nullptr;
			}
			else
			{
				trans *nowa = new trans;
				nowa->konto = transtemp->konto;
				nowa->kwota = transtemp->kwota;
				nowa->termin = transtemp->termin;
				nowa->next = wszystkie;
				wszystkie = nowa;
			}
			transtemp = transtemp->next;
		}
		head = head->next;
	}

	if (!wszystkie)
	{
		std::cout << "Brak transakcji do utworzenia raportu" << std::endl;
		return;
	}


	if (arg == "n")
		wszystkie = sortujkonto(wszystkie);
	else if (arg == "k")
		wszystkie = sortujkwota(wszystkie);
	else if (arg == "d")
		wszystkie = sortujdate(wszystkie);
	else
	{
		std::cout << "Nieprawidolwy argument sortowania: raport/operacje - zobacz -help" << std::endl;
		usuntrans(wszystkie);
		return;
	}



	std::ofstream raport("raport.txt");

	transtemp = wszystkie;

	if (raport)
	{
		raport << "Raport transakcji wykonanych w banku  od " << a.dzien << "." << a.miesiac << "." << a.rok << " do " << b.dzien << "." << b.miesiac << " ." << b.rok << std::endl;
		while (wszystkie)
		{
			if ((wiekszadate(wszystkie->termin, a) && mniejszadate(wszystkie->termin, b)) || rownadate(wszystkie->termin, a) || rownadate(wszystkie->termin, b))
			{
				raport << wszystkie->termin.dzien << "." << wszystkie->termin.miesiac << "." << wszystkie->termin.rok << " " << wszystkie->kwota << " PLN " << wszystkie->konto << std::endl;
			}
			wszystkie = wszystkie->next;
		}
		raport.close();
	}
	std::cout << "Raport utworzony pomyslnie (raport.txt)" << std::endl;
	usuntrans(transtemp);
}

void wyciag(uzytkownik *head, date a, date b, int konto)
{
	head = szukajkonto(head, konto);

	if (head == nullptr)
	{
		std::cout << "Nie znaleziono uzytkownika!" << std::endl;
		return;
	}

	head->transhead = sortujdate(head->transhead);

	trans *transhead = head->transhead;

	if (mniejszadate(b, a))
	{
		date c = b;
		b = a;
		a = c;
	}

	std::ofstream raport("wyciag.txt");

	int wydatki = 0;
	int przychody = 0;
	int bilans = 0;

	if (raport)
	{
		raport << "Wyciag z konta " << head->konto << " za okres " << a.dzien << "." << a.miesiac << "." << a.rok << " - " << b.dzien << "." << b.miesiac << "." << b.rok << std::endl;
		while (transhead)
		{
			if ((mniejszadate(a, transhead->termin) || rownadate(transhead->termin, a)) && (wiekszadate(b, transhead->termin) || rownadate(transhead->termin, b)))
			{
				raport << transhead->termin.dzien << "." << transhead->termin.miesiac << "." << transhead->termin.rok << " " << transhead->kwota << " PLN " << std::endl;

				if (transhead->kwota > 0)
					przychody += transhead->kwota;
				else
					wydatki += transhead->kwota;

				bilans += transhead->kwota;
			}
			transhead = transhead->next;
		}

		raport << "Podsumowanie:" << std::endl;
		raport << "- wydatki: " << wydatki << " PLN" << std::endl;
		raport << "- przychody: " << przychody << " PLN" << std::endl;
		raport << "- bilans: " << bilans << " PLN" << std::endl;
		raport.close();

	}
	std::cout << "Wyciag utworzony pomyslnie (wyciag.txt)" << std::endl;
}

void raportdebet(uzytkownik *&head, std::string arg)
{
	if (arg == "n")
		head = sortujnazwiskouzyt(head);
	else if (arg == "k")
		head = sortujkontouzyt(head);
	else
	{
		std::cout << "Niepoprawny argument sortowania: raport/debet - zobacz -help" << std::endl;
		return;
	}

	uzytkownik *temp = head;

	std::ofstream raport("raport.txt");
	if (raport)
	{
		raport << "Raport uzytkownikow z debetem na konice" << std::endl;
		while (temp)
		{
			if (temp->limit < 0)
			{
				raport << temp->imie << " " << temp->nazwisko << " " << temp->limit << " " << temp->konto << std::endl;
			}
			temp = temp->next;
		}
		raport.close();
	}
	std::cout << "Raport utworzony pomyslnie (raport.txt)" << std::endl;
}

trans* sortujdate(trans *head)
{
	trans* temp = head;
	trans* max = nullptr;
	trans* poprz;
	trans* posortowana = nullptr;
	while (head)
	{
		poprz = nullptr;	//reset lub deklaracja poprz
		temp = head;		//reset temp
		max = temp;			//reset max
		while (temp)
		{
			if (mniejszadate(temp->termin, max->termin))
				max = temp;
			temp = temp->next;
		}

		temp = head;		//powrot temp

		while (temp)
		{
			if (temp->konto == max->konto && rownadate(temp->termin, max->termin) && temp->kwota == max->kwota)
			{
				if (!poprz)									//jezeli nie ma poprzedniego
				{
					if (!head->next)						//ani nastepnego
					{
						head = nullptr;
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
					head = head->next;
					if (!posortowana)						//lista nieutworzona
					{
						posortowana = temp;
						posortowana->next = nullptr;
						break;
					}
					else
					{
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
				}
				else										//normanie
				{
					poprz->next = temp->next;
					if (!posortowana)						//ale bez utworzonej listy
					{
						posortowana = temp;
						posortowana->next = nullptr;
						break;
					}
					else
					{
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
				}
			}
			else
			{
				poprz = temp;								//na koniec petli obecny element staje sie poprzednim
				temp = temp->next;							//a nastepny obecnym
			}
		}
	}
	return posortowana;
}

trans* sortujkwota(trans *head)
{
	trans* temp = head;
	trans* max = nullptr;
	trans* poprz;
	trans* posortowana = nullptr;
	while (head)
	{
		poprz = nullptr;	//reset lub deklaracja poprz
		temp = head;		//reset temp
		max = temp;			//reset max
		while (temp)
		{
			if (temp->kwota < max->kwota)
				max = temp;
			temp = temp->next;
		}

		temp = head;		//powrot temp

		while (temp)
		{
			if (temp->konto == max->konto && rownadate(temp->termin, max->termin) && temp->kwota == max->kwota)
			{
				if (!poprz)									//jezeli nie ma poprzedniego
				{
					if (!head->next)						//ani nastepnego
					{
						head = nullptr;
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
					head = head->next;
					if (!posortowana)						//lista nieutworzona
					{
						posortowana = temp;
						posortowana->next = nullptr;
						break;
					}
					else
					{
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
				}
				else										//normanie
				{
					poprz->next = temp->next;
					if (!posortowana)						//ale bez utworzonej listy
					{
						posortowana = temp;
						posortowana->next = nullptr;
						break;
					}
					else
					{
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
				}
			}
			else
			{
				poprz = temp;								//na koniec petli obecny element staje sie poprzednim
				temp = temp->next;							//a nastepny obecnym
			}
		}
	}
	return posortowana;
}

trans* sortujkonto(trans *head)
{
	trans* temp = head;
	trans* max = nullptr;
	trans* poprz;
	trans* posortowana = nullptr;
	while (head)
	{
		poprz = nullptr;	//reset lub deklaracja poprz
		temp = head;		//reset temp
		max = temp;			//reset max
		while (temp)
		{
			if (temp->konto > max->konto)
				max = temp;
			temp = temp->next;
		}

		temp = head;		//powrot temp

		while (temp)
		{
			if (temp->konto == max->konto && rownadate(temp->termin, max->termin) && temp->kwota == max->kwota)
			{
				if (!poprz)									//jezeli nie ma poprzedniego
				{
					if (!head->next)						//ani nastepnego
					{
						head = nullptr;
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
					head = head->next;
					if (!posortowana)						//lista nieutworzona
					{
						posortowana = temp;
						posortowana->next = nullptr;
						break;
					}
					else
					{
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
				}
				else										//normanie
				{
					poprz->next = temp->next;
					if (!posortowana)						//ale bez utworzonej listy
					{
						posortowana = temp;
						posortowana->next = nullptr;
						break;
					}
					else
					{
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
				}
			}
			else
			{
				poprz = temp;								//na koniec petli obecny element staje sie poprzednim
				temp = temp->next;							//a nastepny obecnym
			}
		}
	}
	return posortowana;
}

uzytkownik* sortujkontouzyt(uzytkownik *head)
{
	uzytkownik* temp = head;
	uzytkownik* max = nullptr;
	uzytkownik* poprz;
	uzytkownik* posortowana = nullptr;
	while (head)
	{
		poprz = nullptr;	//reset lub deklaracja poprz
		temp = head;		//reset temp
		max = temp;			//reset max
		while (temp)
		{
			if (temp->konto > max->konto)
				max = temp;
			temp = temp->next;
		}

		temp = head;		//powrot temp

		while (temp)
		{
			if (temp->konto == max->konto && temp->nazwisko == max->nazwisko && temp->imie == max->imie)
			{
				if (!poprz)									//jezeli nie ma poprzedniego
				{
					if (!head->next)						//ani nastepnego
					{
						head = nullptr;
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
					head = head->next;
					if (!posortowana)						//lista nieutworzona
					{
						posortowana = temp;
						posortowana->next = nullptr;
						break;
					}
					else
					{
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
				}
				else										//normanie
				{
					poprz->next = temp->next;
					if (!posortowana)						//ale bez utworzonej listy
					{
						posortowana = temp;
						posortowana->next = nullptr;
						break;
					}
					else
					{
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
				}
			}
			else
			{
				poprz = temp;								//na koniec petli obecny element staje sie poprzednim
				temp = temp->next;							//a nastepny obecnym
			}
		}
	}
	return posortowana;
}

uzytkownik* sortujnazwiskouzyt(uzytkownik *head)
{
	uzytkownik* temp = head;
	uzytkownik* max = nullptr;
	uzytkownik* poprz;
	uzytkownik* posortowana = nullptr;
	while (head)
	{
		poprz = nullptr;	//reset lub deklaracja poprz
		temp = head;		//reset temp
		max = temp;			//reset max
		while (temp)
		{
			if (temp->nazwisko > max->nazwisko)
				max = temp;
			temp = temp->next;
		}

		temp = head;		//powrot temp

		while (temp)
		{
			if (temp->konto == max->konto && temp->nazwisko == max->nazwisko && temp->imie == max->imie)
			{
				if (!poprz)									//jezeli nie ma poprzedniego
				{
					if (!head->next)						//ani nastepnego
					{
						head = nullptr;
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
					head = head->next;
					if (!posortowana)						//lista nieutworzona
					{
						posortowana = temp;
						posortowana->next = nullptr;
						break;
					}
					else
					{
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
				}
				else										//normanie
				{
					poprz->next = temp->next;
					if (!posortowana)						//ale bez utworzonej listy
					{
						posortowana = temp;
						posortowana->next = nullptr;
						break;
					}
					else
					{
						temp->next = posortowana;
						posortowana = temp;
						break;
					}
				}
			}
			else
			{
				poprz = temp;								//na koniec petli obecny element staje sie poprzednim
				temp = temp->next;							//a nastepny obecnym
			}
		}
	}
	return posortowana;
}

void zapis(uzytkownik *head, std::string plik)				//Bardzo wazna czesc tej funkcji stanowi odpowiednie formatowanie pliku bez ktorego, plik nie zaladuje sie ponownie
{
	std::ofstream plikzap(plik);
	if (plikzap) {
		while (head)
		{
			plikzap << head->imie << " " << head->nazwisko << " " << head->konto << " " << head->limit;
			if (head->transhead)
			{
				trans *transhead = head->transhead;
				while (transhead)
				{
					plikzap << " " << transhead->termin.rok << " " << transhead->termin.miesiac << " " << transhead->termin.dzien << " " << transhead->kwota;
					transhead = transhead->next;
				}
				if (head->next)
					plikzap << std::endl;
			}
			else
			{
				if (head->next)
					plikzap << std::endl;
				else
					break;
			}
			head = head->next;
		}
	}
}

bool mniejszadate(date a, date b)
{
	if (a.rok < b.rok)
		return true;
	if (a.rok > b.rok)
		return false;
	else {
		if (a.miesiac < b.miesiac)
			return true;
		if (a.miesiac > b.miesiac)
			return false;
		else {
			if (a.dzien < b.dzien)
				return true;
			if (a.dzien > b.dzien)
				return false;
			else
				return false;
		}
	}
}

bool wiekszadate(date a, date b)
{
	if (a.rok > b.rok)
		return true;
	if (a.rok < b.rok)
		return false;
	else {
		if (a.miesiac > b.miesiac)
			return true;
		if (a.miesiac < b.miesiac)
			return false;
		else {
			if (a.dzien > b.dzien)
				return true;
			if (a.dzien < b.dzien)
				return false;
			else
				return false;
		}
	}
}

bool rownadate(date a, date b)
{
	if (a.dzien == b.dzien && a.miesiac == b.miesiac && a.rok == b.rok)
		return true;
	else
		return false;
}

void wypisztrans(trans *transhead)
{
	while (transhead)
	{
		std::cout << transhead->konto << " " << transhead->kwota << " " << transhead->termin.rok << " " << transhead->termin.miesiac << " " << transhead->termin.dzien << std::endl;
		transhead = transhead->next;
	}
}

void usun(uzytkownik*head)
{
	uzytkownik* usuwany = nullptr;
	while (head)
	{
		trans* transhead = head->transhead;
		trans* usuwana = nullptr;
		while (transhead)
		{
			usuwana = transhead;
			transhead = transhead->next;
			delete(usuwana);
		}
		usuwany = head;
		head = head->next;
		delete(usuwany);
	}
}

void usuntrans(trans*transhead)
{
	trans* usuwana = nullptr;
	while (transhead)
	{
		usuwana = transhead;
		transhead = transhead->next;
		delete(usuwana);
	}
}

bool sprawdzdate(date a)
{
	if (a.dzien > 0 && a.dzien <= 31 && a.miesiac > 0 && a.miesiac <= 12 && a.rok > 0 && a.rok < 3000)
		return true;
	else
		return false;
}

bool sprawdzint(int a)
{
	if (a < -100000000 || a > 100000000)
		return false;
	else
		return true;
}

void wypiszhelp()
{
	std::cout << "-fin <nazwapliku.txt> - Przelacznik do ustawiania nazwy pliku odczytu/zapisu, musi byc wywolany na poczatku, tylko raz, wymagany do uruchomienia programu." << std::endl;
	std::cout << "-wy <numerkonta> <kwota> - wyplata podanej kwoty z konta o podanym numerze." << std::endl;
	std::cout << "-we <numerkonta> <kwota> - wplata podanej kwoty na konto o podanym numerze." << std::endl;
	std::cout << "-wyci¹g <numerkonta> <dd> <mm> <rrrr> <dd> <mm> <rrrr> - wyciag transakcji z konta o podanym numerze w podanym przedziale dat (kolejnosc nie ma znaczenia)." << std::endl;
	std::cout << "-undo <numerkonta> <dd> <mm> <rrrr> <kwota> - usuniecie transakcji (tylko jednej) wykonanej w danym dniu, na okreslona kwote z okreslonego konta." << std::endl;
	std::cout << "-wywe <numerkonta>(nadawca) <numerkonta>(odbiorca) <kwota> - wplata okreslonej kwoty z konta nadawcy na konto odbiorcy." << std::endl;
	std::cout << "-rT <argumentsortowanie>(n, k, d) <dd> <mm> <rrrr> <dd> <mm> <rrrr> - stworzenie raportu wszytkich wykonanych w banku transakcji w danym przedziale dat (kolejnosc nie ma znaczenia), posortowane wg. n - numeru konta, k - kwoty lub d - daty." << std::endl;
	std::cout << "-rD <argumentsortowanie>(n, k) - stworzenie raportu uzytkownikow, ktorzy maja debet na koncie posortowane wg. n - nazwiska, k - numeru konta." << std::endl;
	std::cout << "-help - opis przelacznikow i ich argumentow" << std::endl;
}