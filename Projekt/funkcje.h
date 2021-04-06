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
@param nazwa nazwa pliku wej�ciowego.
@return wskanikna pocz�tek utworzonej listy.
*/
uzytkownik* wczytaj(std::string nazwa);

/** Funkcja tworzy transakcje wyp�acenia pieni�dzy z konta.
@param head lista u�ytkownik�w.
@param kwota kwota do wyp�acenia.
@param termin dzien w ktorym zosta�a wykonana transakcja.
@param konto numer konta u�ytkownika
@return funkcja nie zwraca niczego.
*/
void wyplata(uzytkownik * &head, int kwota, date termin, int konto);

/** Funkcja tworzy transakcje wp�acenia pieni�dzy z konta.
@param head lista u�ytkownik�w.
@param kwota kwota do wp�acenia.
@param termin dzien w ktorym zosta�a wykonana transakcja.
@param konto numer konta u�ytkownika.
@return funkcja nie zwraca niczego.
*/
void wplata(uzytkownik * &head, int kwota, date termin, int konto);

/** Funkcja usuwa transakcj� z konta u�ytkownika.
@param head lista u�ytkownik�w.
@param kwota kwota transakjci do usuni�cia.
@param termin data transakcji do usuni�cia.
@param konto numer konta, z kt�rego ma zosta� usuni�ta transakcja.
@return funkcja nie zwraca niczego.
*/
void undo(uzytkownik *head, int kwota, date termin, int konto);

/** Funkcja tworzy transakcje pomi�dzy u�ytkownikami banku.
@param head lista u�ytkownik�w.
@param kwota kwota transakcji.
@param kontoA numer konta nadawcy
@param kontoB numer konta odbiorcy
@param termin dzien w ktorym zosta�a wykonana transakcja.
@return funkcja nie zwraca niczego.
*/
void wywe(uzytkownik *head, int kwota, int kontoA, int kontoB, date termin);

/** Funkcja wypisuje u�ytkownik�w banku na konsol�.
@param head lista u�ytkownik�w.
@param nastepne prawda gdy ma wypisac takze kolejnych u�ytkownik�w, fa�sz gdy tylko wskazanego przez wska�nik.
@return funkcja nie zwraca niczego.
*/
void wypisz(uzytkownik *head, bool nastepne);

/** Funkcja wyszukuje u�ytkownika po numerze konta.
@param head lista u�ytkownik�w.
@param szukane numer konta szukanego u�ytkownika.
@return funkcja zwraca wskaznik na znalezionego u�ytkownika.
*/
uzytkownik* szukajkonto(uzytkownik *head, int szukane);

/** Funkcja tworzy raport operacji wykonanych w banku w danym okresie.
@param head lista u�ytkownik�w.
@param a pocz�tek przedzia�u dat.
@param b koniec przedzia�u dat.
@param arg okre�la wg. czego operacje maj� by� posortowane: k - kwota, n - numer konta, d - data.
@return funkcja nie zwraca niczego.
*/
void raport(uzytkownik *head, date a, date b, std::string arg);

/** Funkcja tworzy raport operacji wykonanych na koncie.
@param head lista u�ytkownik�w.
@param a pocz�tek przedzia�u dat.
@param b koniec przedzia�u dat.
@param konto numer konta u�ytkownika dla kt�rego raport ma zosta� stworzony.
@return funkcja nie zwraca niczego.
*/
void wyciag(uzytkownik *head, date a, date b, int konto);

/** Funkcja tworzy raport u�ytkownik�w z debetem na konice.
@param head lista u�ytkownik�w.
@param arg okre�la wg. czego u�ytkownicy maj� by� posortowani: k - numer konta, n - nazwisko.
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
@return funkcja zwraca wska�nik na posortowan� list�.
*/
trans* sortujdate(trans *transhead);

/** Funkcja sortuje transakcje wg. kwoty.
@param transhead lista transakcji.
@return funkcja zwraca wska�nik na posortowan� list�.
*/
trans* sortujkwota(trans *transhead);

/** Funkcja sortuje transakcje wg. numeru konta.
@param transhead lista transakcji.
@return funkcja zwraca wska�nik na posortowan� list�.
*/
trans* sortujkonto(trans *transhead);

/** Funkcja sortuje u�ytkownik�w wg. numeru konta.
@param head lista u�ytkownik�w.
@return funkcja zwraca wska�nik na posortowan� list�.
*/
uzytkownik* sortujkontouzyt(uzytkownik *head);

/** Funkcja sortuje u�ytkownik�w wg. nazwiska.
@param head lista u�ytkownik�w.
@return funkcja zwraca wska�nik na posortowan� list�.
*/
uzytkownik* sortujnazwiskouzyt(uzytkownik *head);

/** Funkcja zapisuje ca�� struktur� do pliku
@param head lista u�ytkownik�w.
@param plik nazwa pliku
@return funkcja nie zwraca niczego.
*/
void zapis(uzytkownik *head, std::string plik);

/** Funkcja sprawdza czy data A jest wcze�niejsza od daty B
@param a data A
@param b data B
@return funkcja zwraca prawd� lub fa�sz
*/
bool mniejszadate(date a, date b);

/** Funkcja sprawdza czy data A jest p�niejsza od daty B
@param a data A
@param b data B
@return funkcja zwraca prawd� lub fa�sz
*/
bool wiekszadate(date a, date b);

/** Funkcja sprawdza czy data A jest r�wna dacie B
@param a data A
@param b data B
@return funkcja zwraca prawd� lub fa�sz
*/
bool rownadate(date a, date b);

/** Funkcja usuwa u�ytkownik�w z listy
@param head lista u�ytkownik�w.
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
@return funkcja zwraca prawd� lub fa�sz
*/
bool sprawdzdate(date a);
/** Funkcja wypisuje pomoc
@return funkcja nie zwraca niczego.
*/
void wypiszhelp();

/** Funkcja sprawdza czy liczba jest w zakresie -10^8 - 10^8
@param a liczba
@return funkcja zwraca prawd� lub fa�sz
*/
bool sprawdzint(int a);





#endif

