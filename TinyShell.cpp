// TinyShell.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "command.h"
#include <iostream>


int main()
{
	string s;
	while (1)
	{
		cout << ">>";
		getline(cin, s);
		getCommandID(s);
		cout << setfill('.') << setw(120) << "." << endl << setfill(' ');
	}
}
