/** @file */
#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <string>
//#include <vld.h>


/** Struktura pozwalaj�ca w �atwy spos�b opisa� dat�. */
struct date {
	int dzien;				///< dzie�
	int miesiac;			///< miesi�c
	int rok;				///< rok
};

/** Struktura przechowuj�ca informacje o transakcjach. */
struct trans {
	double kwota;			///< kwota transakcji
	date termin;			///< data wykonanej transakcji
	trans* next;			///< wska�nik na kolejny element listy
	int konto;				///< numer konta kt�rego transakcja dotyczy
};

/** Struktura przechowuj�ca informacje o u�ytkownikach banku. */
struct uzytkownik {
	int konto;				///< numer konta
	std::string imie;		///< imi� u�ytkownika
	std::string nazwisko;	///< nazwisko u�ytkownika
	double limit;			///< stan konta
	trans *transhead;		///< lista transakcji wykonanych na koncie
	uzytkownik *next;		///< wska�nik na kolejny element listy
};

#endif 
