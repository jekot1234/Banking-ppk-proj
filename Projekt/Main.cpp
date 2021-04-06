#include <iostream>
#include <string>
//#include <vld.h>
#include <iomanip>
#include <ctime>
#include <sstream>


#include "struktury.h"
#include "funkcje.h"

int main(int argc, char* argv[])
{

	date dzis = { 22, 1, 2019 };
	uzytkownik *head = nullptr;
	std::string komeda;


	if (argc >= 2)
	{
		komeda = argv[1];

		if (komeda == "-fin")
		{
			head = wczytaj(argv[2]);
		}
		else
		{
			std::cout << "Brak przelacznika -fin! Pomoc:" << std::endl;
			wypiszhelp();
		}
	}
	else
	{
		std::cout << "Brak przelacznikow! Pomoc:" << std::endl;
		wypiszhelp();
	}


	if (head)
	{
		int i = 3;
		std::string argument;

		while (i <= argc - 1)
		{
			argument = argv[i];
			if (argument == "-wy")
			{
				if (argc < i + 2)
				{
					std::cout << "Brak wystarczajacej liczby argumentow (-wy)" << std::endl;
					break;
				}
				int numer = std::stoi(argv[i + 1]);
				if (!sprawdzint(numer))
				{
					std::cout << "Blad" << std::endl;
					break;
				}
				int kwota = std::stoi(argv[i + 2]);
				if (!sprawdzint(kwota))
				{
					std::cout << "Blad" << std::endl;
					break;
				}
				wyplata(head, kwota, dzis, numer);
				i += 2;
			}
			if (argument == "-we")
			{
				if (argc < i + 2)
				{
					std::cout << "Brak wystarczajacej liczby argumentow (-we)" << std::endl;
					break;
				}
				int numer = std::stoi(argv[i + 1]);
				if (!sprawdzint(numer))
				{
					std::cout << "Blad" << std::endl;
					break;
				}
				int kwota = std::stoi(argv[i + 2]);
				if (!sprawdzint(kwota))
				{
					std::cout << "Blad" << std::endl;
					break;
				}

				wplata(head, kwota, dzis, numer);
				i += 2;
			}
			if (argument == "-wyci¹g")
			{
				if (argc < i + 7)
				{
					std::cout << "Brak wystarczajacej liczby argumentow (-wyci¹g)" << std::endl;
					break;
				}
				int numer = std::stoi(argv[i + 1]);
				if (!sprawdzint(numer))
				{
					std::cout << "Blad" << std::endl;
					break;
				}

				int d = std::stoi(argv[i + 2]);
				int m = std::stoi(argv[i + 3]);
				int r = std::stoi(argv[i + 4]);

				date a = { d, m, r };
				if (!sprawdzdate(a))
				{
					std::cout << "Bledna data" << std::endl;
					break;
				}

				d = std::stoi(argv[i + 5]);
				m = std::stoi(argv[i + 6]);
				r = std::stoi(argv[i + 7]);

				date b = { d, m, r };
				if (!sprawdzdate(b))
				{
					std::cout << "Bledna data" << std::endl;
					break;
				}

				wyciag(head, a, b, numer);

				i += 7;
			}
			if (argument == "-undo")
			{
				if (argc < i + 5)
				{
					std::cout << "Brak wystarczajacej liczby argumentow (-undo)" << std::endl;
					break;
				}
				int konto = std::stoi(argv[i + 1]);

				int d = std::stoi(argv[i + 2]);
				int m = std::stoi(argv[i + 3]);
				int r = std::stoi(argv[i + 4]);

				date termin = { d, m, r };

				if (!sprawdzdate(termin))
				{
					std::cout << "Bledna data" << std::endl;
					break;
				}

				int kwota = std::stoi(argv[i + 5]);

				undo(head, kwota, termin, konto);

				i += 5;
			}
			if (argument == "-wywe")
			{
				if (argc < i + 3)
				{
					std::cout << "Brak wystarczajacej liczby argumentow (-wywe)" << std::endl;
					break;
				}
				int kontoA = std::stoi(argv[i + 1]);
				if (!sprawdzint(kontoA))
				{
					std::cout << "Blad" << std::endl;
					break;
				}
				int kontoB = std::stoi(argv[i + 2]);
				if (!sprawdzint(kontoB))
				{
					std::cout << "Blad" << std::endl;
					break;
				}
				int kwota = std::stoi(argv[i + 3]);
				if (!sprawdzint(kwota))
				{
					std::cout << "Blad" << std::endl;
					break;
				}

				wywe(head, kwota, kontoA, kontoB, dzis);

				i += 3;
			}
			if (argument == "-rT")
			{
				if (argc < i + 7)
				{
					std::cout << "Brak wystarczajacej liczby argumentow (-rT)" << std::endl;
					break;
				}
				std::string arg = argv[i + 1];

				int d = std::stoi(argv[i + 2]);
				int m = std::stoi(argv[i + 3]);
				int r = std::stoi(argv[i + 4]);

				date a = { d, m, r };

				if (!sprawdzdate(a))
				{
					std::cout << "Bledna data" << std::endl;
					break;
				}

				d = std::stoi(argv[i + 5]);
				m = std::stoi(argv[i + 6]);
				r = std::stoi(argv[i + 7]);

				date b = { d, m, r };

				if (!sprawdzdate(b))
				{
					std::cout << "Bledna data" << std::endl;
					break;
				}

				raport(head, a, b, arg);

				i += 7;
			}
			if (argument == "-rD")
			{
				if (argc < i + 1)
				{
					std::cout << "Brak wystarczajacej liczby argumentow (-rD)" << std::endl;
					break;
				}
				std::string arg = argv[i + 1];

				raportdebet(head, arg);

				i++;
			}
			if (argument == "-help")
			{
				wypiszhelp();
			}
			i++;
		}

		zapis(head, argv[2]);
		usun(head);
	}
	return 0;
}