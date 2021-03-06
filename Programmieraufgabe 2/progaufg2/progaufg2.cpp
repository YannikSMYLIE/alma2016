// progaufg2.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include "largeint.h"
#include <iostream>
#include <vector>

const std::string LargeInt::digits = "0123456789";

int get_input()
{
	int n;
	std::cout << "Bitte eine Zahl eingeben.\n";
	std::cin >> n;
	return n;
}


LargeInt::LargeInt(inputtype i)   // constructor, calls constructor of vector
{
	do {
		_v.push_back(i % 10);
		i /= 10;
	} while (i > 0);
}


std::string LargeInt::decimal() const   // returns decimal representation
{
	std::string s("");
	for (auto i : _v) {       // range for statement: i runs over all
		s = digits[i] + s;    // elements of _v
	}
	return s;
}


bool LargeInt::operator<(const LargeInt & arg) const   // checks if < arg
{
	if (_v.size() == arg._v.size()) {
		auto it2 = arg._v.rbegin();
		for (auto it1 = _v.rbegin(); it1 != _v.rend(); ++it1, ++it2) {
			if (*it1 < *it2) return true;
			if (*it1 > *it2) return false;
		}
		return false;
	}
	return _v.size() < arg._v.size();
}

/* Pr�fen ob LargeInt gleich sind, muss auch in largeInt.h erg�nzt werden! */
bool LargeInt::operator==(const LargeInt & arg) const
{
	/* Wenn die Zahlen unterschiedlich lang sind offensichtlich nicht */
	if (_v.size() != arg._v.size())
		return false;
	/* An jeder Stelle muss die gleiche Zahl stehen.
	Hei�t Einerstelle == Einerstelle
	Zehnerstelle = Zehnerstelle usw. */
	for (auto i = 0; i < _v.size(); i++)
	{
		if (_v[i] != arg._v[i])
			return false;
	}
	return true;
}

/* Pr�fen ob LargeInt ungleich sind, muss auch in largeInt.h erg�nzt werden! */
bool LargeInt::operator!=(const LargeInt & arg) const
{
	/* Die Zahlen sind dann unterschiedlich wenn sie nicht gleich sind. (logisch) */
	return !(*this == arg);
}


LargeInt LargeInt::operator+(const LargeInt & arg) const  // addition
{
	LargeInt result(*this);
	result += arg;
	return result;
}
const LargeInt & LargeInt::operator+=(const LargeInt & arg)   // addition
{
	if (arg._v.size() > _v.size()) {
		_v.resize(arg._v.size(), 0);
	}
	auto it1 = _v.begin();
	for (auto it2 = arg._v.begin(); it2 != arg._v.end(); ++it2, ++it1) {
		*it1 += *it2;
	}
	short carry = 0;
	for (auto & i : _v) {
		i += carry;
		carry = i / 10;
		i %= 10;
	}
	if (carry != 0) _v.push_back(carry);
	return *this;
}

// Shift Funktionen
void LargeInt::shiftRight()
{
	_v.push_back(0);
	for (int i = _v.size() - 2; i >= 0; i--)
	{
		_v[i + 1] = _v[i];
	}
	_v[0] = 0;
}

/* Der Operator wird eingef�hrt */
LargeInt LargeInt::operator*(const LargeInt & arg) const {
	LargeInt result(0);
	std::vector<LargeInt> summanden(_v.size() + arg._v.size() - 1, 0);
	
	int fL, fR, sL, sR;
	for (int i = 0; i < _v.size() + arg._v.size() - 1; i++)
	{
		// Grenzen fuer erste Zahl ermitteln
		fL = (_v.size() - 1) - i;
		fR = fL + arg._v.size() - 1;
		if (fL < 0)
			fL = 0;
		if (fR >= _v.size())
			fR = _v.size() - 1;

		// Grenzen fuer zweite Zahl ermitteln
		sL = (arg._v.size() - 1) - i;
		sR = sL + _v.size() - 1;
		if (sL < 0)
			sL = 0;
		if (sR >= arg._v.size())
			sR = arg._v.size() - 1;

		// Zahlen addieren
		for (int j = 0; fL + j <= fR; j++)
		{
			summanden[i] += LargeInt(_v[fL + j] * arg._v[sR - j]);
		}
	}
	// Summanden zur Summe addieren
	for (int i = 0; i < summanden.size() - 1; i++)
	{
		result += summanden[i];
		result.shiftRight();
	}
	result += summanden[summanden.size() - 1];
	// Wir geben die Zahl zur�ck
	return result;
}


/* Mit dieser Funktion berechnen wir C rekursiv.
Bei Berechnungen, bei denen wir immer wieder die gleichen Werte ben�tigen ist das mega Kacke, da jeder Wert mehrfach berechnet wird.
(Dazu einfach mal nen Baum malen, dann sieht man dass C(0) f�r jeden Aufruf von C berechent werden muss!
Daher dauert die Berechnung von C(10) bereits (f�r eine solche Aufgabe) sehr lange. */
LargeInt calcCRek(int n)
{
	if (n == 0) // Einfachster Fall
		return LargeInt(1);

	// Ansonsten rekursion anweden, da wir eine Summe haben brauchen wir eine Variable um die Summe zu speichern.
	LargeInt summe(0);
	for (int k = 0; k < n; k++) // < da wir bis n-1 summieren!
	{
		summe += calcCRek(k) * calcCRek(n - k - 1);
	}
	return summe;
}

/* Mit dieser Funktion berechnen wir C iterativ.
Das ist viel besser, denn am Anfang legen wir ein Array der L�nge n an in das wir einmal berechnete Werte speichern.
Dadurch m�ssen wir jedes C nur einmal berechnen und sparen eine menge Zeit. */
LargeInt clacCIt(int n)
{
	// Unser Vektor in dem wir alle C(k) speichern 0 <= k <= n
	std::vector<LargeInt> cs(n+1, 0);
	cs[0] = 1; // C(0) = 1 nach Definition
	for (int i = 1; i <= n; i++) // Berechne alle C(1) bis C(n)
	{
		LargeInt summe(0);
		for (int k = 0; k < i; k++) // wenn C(i) berechnet wird geht die Summe von 0 bis i. (wichtig: wieder weil die Formel eigentlich f�r i+1 gilt).
		{
			/* Hier wird es jetzt effizienter. Anstatt die Werte neu zu berechnen
			greifen wir einfach die gespeicherten Werte zur�ck. */
			summe += cs[k] * cs[i - k - 1];
		}
		cs[i] = summe;
	}
	return cs[n];
}





int main()
{
	// LargeInt hat eine zus�tzliche Funktion print() bekommen um die Zahlen auszugeben. Wie geht das besser?


	
	std::cout << "Bitte verschiedene Zahlen eingeben um Programm zu testen, eine negative Zahl beendet das Programm" << std::endl;
	int n = get_input();

	while (n >= 0)
	{
		LargeInt ergebnisIt = clacCIt(n);
		std::cout << "Zahl berechnet iterativ: ";
		ergebnisIt.print();
		std::cout << std::endl;

		LargeInt ergebnisRec = calcCRek(n);
		std::cout << "Zahl berechnet rekusriv: ";
		ergebnisRec.print();
		std::cout << std::endl;

		n = get_input();
	}
	std::cout << "Programm wird beendet...";
	return 0;
}