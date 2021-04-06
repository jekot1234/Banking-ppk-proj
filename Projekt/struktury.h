/** @file */
#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <string>
//#include <vld.h>


/** Struktura pozwalaj¹ca w ³atwy sposób opisaæ datê. */
struct date {
	int dzien;				///< dzieñ
	int miesiac;			///< miesi¹c
	int rok;				///< rok
};

/** Struktura przechowuj¹ca informacje o transakcjach. */
struct trans {
	double kwota;			///< kwota transakcji
	date termin;			///< data wykonanej transakcji
	trans* next;			///< wskaŸnik na kolejny element listy
	int konto;				///< numer konta którego transakcja dotyczy
};

/** Struktura przechowuj¹ca informacje o u¿ytkownikach banku. */
struct uzytkownik {
	int konto;				///< numer konta
	std::string imie;		///< imiê u¿ytkownika
	std::string nazwisko;	///< nazwisko u¿ytkownika
	double limit;			///< stan konta
	trans *transhead;		///< lista transakcji wykonanych na koncie
	uzytkownik *next;		///< wskaŸnik na kolejny element listy
};

#endif 
