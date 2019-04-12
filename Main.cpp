#include "pch.h"
#include <iostream>
#include <fstream>
#include "Windows.h"
#include "AccountService.h"
using namespace std;

int menu();

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	AccountService accountService;
	while (true)
	{
		switch (menu())
		{
		case 1:
		{
			accountService.authorization();
		}break;
		case 2:
		{
			accountService.registration();
		}break;
		case 0:
		{
			return 0;
		}
		default: return 0;
		}
	}

}

int menu()
{
	system("cls");
	int ch = 0;
	cout << "1-Авторизоваться\n2-Зарегистрироваться\n0-Выход" << endl;
	cin >> ch;
	return ch;
}
