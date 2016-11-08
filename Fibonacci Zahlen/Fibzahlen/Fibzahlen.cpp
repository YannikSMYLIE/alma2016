// Fibzahlen.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <vector>


int get_input()
{
	int n;
	std::cout << "Zahl eingeben, Hure!" << std::endl << "Hier! ->  ";

	std::cin >> n;
	std::cout << " <- ";
	return n;
}

int fib_rekursion(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return fib_rekursion(n - 1) + fib_rekursion(n - 2);
}

int fib_iteration(int n)
{
	std::vector<int> fib_vector(n, 1);
	for (int i = 2; i < n; i++)
	{
		fib_vector[i] = fib_vector[i - 1] + fib_vector[i - 2];
	}
	return fib_vector[n-1];
}



int main()
{
	
	std::cout << std::endl << "Alter Was nennst du mich Hure?! Die Fibonacci Zahl lautet:" << std::endl << fib_iteration(get_input());
    return 0;
}

