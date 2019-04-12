#include "pch.h"
#include "AdminMenu.h"
#include <iostream>
using namespace std;

int AdminMenu::showMenu() {
	system("cls");
	int i;
	cout << "Добро пожаловать, администратор!" << endl;
	cout << "5) Выйти" << endl;
	cin >> i;
	return i;
}

void AdminMenu::menu() {
	while (true) {
		switch (showMenu()) {
		default: return;
		}
	}
}
