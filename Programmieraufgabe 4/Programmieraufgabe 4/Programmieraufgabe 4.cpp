// Programmieraufgabe 4.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include "graph.h"


int main()
{
	Graph graph("C:\\Users\\Yannik\\graph.txt", Graph::undirected);
	graph.print();

    return 0;
}

