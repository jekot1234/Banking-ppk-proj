/** @file */
#ifndef FUNKCJE_H 
#define FUNKCJE_H

#include <vector> 
#include <string>
#include <fstream>    
#include <sstream>
//#include <vld.h>

#include "struktury.h"
/** Funkcja wczytuje dane z pliku do listy.
@param nazwa nazwa pliku wejœciowego.
@return wskanikna pocz¹tek utworzonej listy.
*/
uzytkownik* wczytaj(std::string nazwa);

/** Funkcja tworzy transakcje wyp³acenia pieniêdzy z konta.
@param head lista u¿ytkowników.
@param kwota kwota do wyp³acenia.
@param termin dzien w ktorym zosta³a wykonana transakcja.
@param konto numer konta u¿ytkownika
@return funkcja nie zwraca niczego.
*/
void wyplata(uzytkownik * &head, int kwota, date termin, int konto);

/** Funkcja tworzy transakcje wp³acenia pieniêdzy z konta.
@param head lista u¿ytkowników.
@param kwota kwota do wp³acenia.
@param termin dzien w ktorym zosta³a wykonana transakcja.
@param konto numer konta u¿ytkownika.
@return funkcja nie zwraca niczego.
*/
void wplata(uzytkownik * &head, int kwota, date termin, int konto);

/** Funkcja usuwa transakcjê z konta u¿ytkownika.
@param head lista u¿ytkowników.
@param kwota kwota transakjci do usuniêcia.
@param termin data transakcji do usuniêcia.
@param konto numer konta, z którego ma zostaæ usuniêta transakcja.
@return funkcja nie zwraca niczego.
*/
void undo(uzytkownik *head, int kwota, date termin, int konto);

/** Funkcja tworzy transakcje pomiêdzy u¿ytkownikami banku.
@param head lista u¿ytkowników.
@param kwota kwota transakcji.
@param kontoA numer konta nadawcy
@param kontoB numer konta odbiorcy
@param termin dzien w ktorym zosta³a wykonana transakcja.
@return funkcja nie zwraca niczego.
*/
void wywe(uzytkownik *head, int kwota, int kontoA, int kontoB, date termin);

/** Funkcja wypisuje u¿ytkowników banku na konsolê.
@param head lista u¿ytkowników.
@param nastepne prawda gdy ma wypisac takze kolejnych u¿ytkowników, fa³sz gdy tylko wskazanego przez wskaŸnik.
@return funkcja nie zwraca niczego.
*/
void wypisz(uzytkownik *head, bool nastepne);

/** Funkcja wyszukuje u¿ytkownika po numerze konta.
@param head lista u¿ytkowników.
@param szukane numer konta szukanego u¿ytkownika.
@return funkcja zwraca wskaznik na znalezionego u¿ytkownika.
*/
uzytkownik* szukajkonto(uzytkownik *head, int szukane);

/** Funkcja tworzy raport operacji wykonanych w banku w danym okresie.
@param head lista u¿ytkowników.
@param a pocz¹tek przedzia³u dat.
@param b koniec przedzia³u dat.
@param arg okreœla wg. czego operacje maj¹ byæ posortowane: k - kwota, n - numer konta, d - data.
@return funkcja nie zwraca niczego.
*/
void raport(uzytkownik *head, date a, date b, std::string arg);

/** Funkcja tworzy raport operacji wykonanych na koncie.
@param head lista u¿ytkowników.
@param a pocz¹tek przedzia³u dat.
@param b koniec przedzia³u dat.
@param konto numer konta u¿ytkownika dla którego raport ma zostaæ stworzony.
@return funkcja nie zwraca niczego.
*/
void wyciag(uzytkownik *head, date a, date b, int konto);

/** Funkcja tworzy raport u¿ytkowników z debetem na konice.
@param head lista u¿ytkowników.
@param arg okreœla wg. czego u¿ytkownicy maj¹ byæ posortowani: k - numer konta, n - nazwisko.
@return funkcja nie zwraca niczego.
*/
void raportdebet(uzytkownik *&head, std::string arg);

/** Funkcja wypisuje transakcje
@param transhead lista transakcji.
@return funkcja nie zwraca niczego.
*/
void wypisztrans(trans *transhead);

/** Funkcja sortuje transakcje wg. daty.
@param transhead lista transakcji.
@return funkcja zwraca wskaŸnik na posortowan¹ listê.
*/
trans* sortujdate(trans *transhead);

/** Funkcja sortuje transakcje wg. kwoty.
@param transhead lista transakcji.
@return funkcja zwraca wskaŸnik na posortowan¹ listê.
*/
trans* sortujkwota(trans *transhead);

/** Funkcja sortuje transakcje wg. numeru konta.
@param transhead lista transakcji.
@return funkcja zwraca wskaŸnik na posortowan¹ listê.
*/
trans* sortujkonto(trans *transhead);

/** Funkcja sortuje u¿ytkowników wg. numeru konta.
@param head lista u¿ytkowników.
@return funkcja zwraca wskaŸnik na posortowan¹ listê.
*/
uzytkownik* sortujkontouzyt(uzytkownik *head);

/** Funkcja sortuje u¿ytkowników wg. nazwiska.
@param head lista u¿ytkowników.
@return funkcja zwraca wskaŸnik na posortowan¹ listê.
*/
uzytkownik* sortujnazwiskouzyt(uzytkownik *head);

/** Funkcja zapisuje ca³¹ strukturê do pliku
@param head lista u¿ytkowników.
@param plik nazwa pliku
@return funkcja nie zwraca niczego.
*/
void zapis(uzytkownik *head, std::string plik);

/** Funkcja sprawdza czy data A jest wczeœniejsza od daty B
@param a data A
@param b data B
@return funkcja zwraca prawdê lub fa³sz
*/
bool mniejszadate(date a, date b);

/** Funkcja sprawdza czy data A jest póŸniejsza od daty B
@param a data A
@param b data B
@return funkcja zwraca prawdê lub fa³sz
*/
bool wiekszadate(date a, date b);

/** Funkcja sprawdza czy data A jest równa dacie B
@param a data A
@param b data B
@return funkcja zwraca prawdê lub fa³sz
*/
bool rownadate(date a, date b);

/** Funkcja usuwa u¿ytkowników z listy
@param head lista u¿ytkowników.
@return funkcja nie zwraca niczego.
*/
void usun(uzytkownik*head);

/** Funkcja usuwa transakcje z listy
@param transhead lista transakcji.
@return funkcja nie zwraca niczego.
*/
void usuntrans(trans*transhead);

/** Funkcja sprawdza czy data A jest poprawna
@param a data A
@return funkcja zwraca prawdê lub fa³sz
*/
bool sprawdzdate(date a);
/** Funkcja wypisuje pomoc
@return funkcja nie zwraca niczego.
*/
void wypiszhelp();

/** Funkcja sprawdza czy liczba jest w zakresie -10^8 - 10^8
@param a liczba
@return funkcja zwraca prawdê lub fa³sz
*/
bool sprawdzint(int a);





#endif

