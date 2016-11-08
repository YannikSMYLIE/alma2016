// 1Programmieraufgabe.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <iostream>
#include <vector>




int get_input()
{
	int n;
	std::cout << "Enter an integer: " << std::endl << "penis" << std::endl << std::endl << "Hart";
	std::cin >> n;
	return n;
}

bool is_prime(int n)
{
	// numbers less than 2 are not prime:
	if (n < 2) 
		return false;

	// check all possible divisors up to the square root of n:
	for (int i = 2; i * i <= n; i++ ) 
	{
		if (n % i == 0) 
			return false;
	}
	return true;
}


std::vector<int> sieve(int n)
{
	int anzahlPrim = 0;
	std::vector<bool> is_prime(n + 1, true);  // Initializes variables

	for (int i = 2; i <= n; ++i) {
		if (is_prime[i]) {
			anzahlPrim++;
			for (int j = i; j <= n / i; ++j) {
				is_prime[i * j] = false;
			}
		}
	}

	std::vector<int> primzahlen(anzahlPrim, 0);
	int position = 0;
	for (int i = 2; i < n+1; i++)
	{
		if (is_prime[i])
		{
			primzahlen[position] = i;
			position++;
		}
	}

	return primzahlen;
}





int main()
{
	// Zahlen einlesen
	int a = get_input();
	if (a % 2 == 1) // wenn ungerade um 1 erhöhen
		a++;
	int b = get_input();
	if (b % 2 == 1) // wenn ungerade um 1 verringern
		b--;
	// Anzahl grader Zahlen ermitteln
	int gradeZahlen = (b - a) / 2 + 1;
	// Array definieren
	std::vector<int> anzahlKombinationen(gradeZahlen, 0);

	// Für jede grade Zahl Kombinationen suchen
	for (int i = 0; i < gradeZahlen; i++)
	{
		int zahl = a + i * 2;
		std::vector<int> primzahlen = sieve(zahl / 2);

		for (int j = 0; j < primzahlen.size(); j++)
		{
			int p2 = zahl - primzahlen[j];
			if (is_prime(p2))
			{
				anzahlKombinationen[i]++;
			}
		}
	}

	/* Welche Zahl hat die wenigsten Kombinationen? */
	int index = 0;
	for (int i = 1; i < anzahlKombinationen.size(); i++)
	{
		if (anzahlKombinationen[i] < anzahlKombinationen[index])
			index = i;
	}

	// Ausgabe der Zahl
	int zahl = a + index * 2;
	std::cout << zahl << " hat die wenigsten Kombinationsmöglichkeiten" << std::endl;
	std::cout << "Und zwar folgende:" << std::endl;
	// Kombinationen ausgeben, aus Speicherplatzgründen werden diese noch mal berechnet
	std::vector<int> primzahlen = sieve(zahl / 2);

	for (int j = 0; j < primzahlen.size(); j++)
	{
		int p2 = zahl - primzahlen[j];
		if (is_prime(p2))
		{
			std::cout << "c = {" << primzahlen[j] << ", " << p2 << "}" << std::endl;
		}
	}

    return 0;
}

