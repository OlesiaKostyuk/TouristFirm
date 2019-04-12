#include "pch.h"
#include "AccountService.h"
#include "Service.h"
#include "Vector.h"
#include "UserMenu.h"
#include "AdminMenu.h"
#include <iostream>
#include <strstream>
#include <string>
#include <fstream>
#include <regex>
using namespace std;

void enterValue(string &);
bool checkLogin(string);
int getLastId();

void AccountService::authorization() {
	system("cls");
	cout << "Авторизация" << endl;
	ifstream usersFile("e://ЛАБЫ/Олесе/users.txt");
	if (!usersFile.is_open()) {
		cout << "Базы данных не существует!" << endl;
		system("pause");
		return;
	}
	cout << "Введите логин:" << endl;
	string login;
	enterValue(login);
	cout << "Введите пароль" << endl;
	string password;
	enterValue(password);
	char userBuffer[300];
	while (!usersFile.eof()) {
		usersFile.getline(userBuffer, 200);
		User user = this->service.createUserFromString(userBuffer);
		if (user.getLogin() == login && user.getPassord() == this->service.encodePassword(password)) {
			if (user.getRole() == "us") {
				UserMenu userMenu(user.getId());
				userMenu.menu();
			}
			if (user.getRole() == "ad") {
				AdminMenu adminMenu;
				adminMenu.menu();
			}
			return;
		}
	}
	if (usersFile.eof() || userBuffer == "") {
		cout << "Пользователя не существует!" << endl;
		system("pause");
		return;
	}
	usersFile.close();
	system("pause");
}

void enterValue(string &result) {
	strstream ss;
	char buffer[100];
	cin >> buffer;
	ss << buffer << ends;
	result = ss.str();
}

void AccountService::registration() {
	cout << "Регистрация" << endl;
	User user;
	user.setRole("us");
	string buffer;
	while (true) {
		cout << "Введите логин (a-z, цифры, нижнее подчеркиваение, точки, от 3 до 12 символов)" << endl;
		enterValue(buffer);
		regex loginRe("[a-z\\d_.]{3,12}");
		if (checkLogin(buffer)) {
			if (regex_match(buffer.c_str(), loginRe)) {
				user.setLogin(buffer);
				break;
			}
			else cout << "Неверный логин, попробуйте еще" << endl;
		}
		else cout << "Пользователь с таким логином существует, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите пароль (a-z, цифры, нижнее подчеркиваение, точки, от 3 до 12 символов)" << endl;
		enterValue(buffer);
		regex passRe("[a-z\\d_.]{3,12}");
			if (regex_match(buffer.c_str(), passRe)) {
				user.setPassord(this->service.encodePassword(buffer));
				break;
			}
			else cout << "Неверный формат пароля, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите имя (только буквы, не более 25 символов)" << endl;
		enterValue(buffer);
		regex namesRe("[a-zа-яA-ZА-Я]{1,25}");
		if (regex_match(buffer.c_str(), namesRe)) {
			user.setName(buffer);
			break;
		}
		else cout << "Неверный формат имени, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите фамилию (только буквы, не более 25 символов)" << endl;
		enterValue(buffer);
		regex namesRe("[a-zа-яA-ZА-Я]{1,25}");
		if (regex_match(buffer.c_str(), namesRe)) {
			user.setSurname(buffer);
			break;
		}
		else cout << "Неверный формат фамилии, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите отчество (только буквы, не более 25 символов)" << endl;
		enterValue(buffer);
		regex namesRe("[a-zа-яA-ZА-Я]{1,25}");
		if (regex_match(buffer.c_str(), namesRe)) {
			user.setLastname(buffer);
			break;
		}
		else cout << "Неверный формат отчества, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите телефон (в формате 9 цифр)" << endl;
		enterValue(buffer);
		regex phoneRe("[\\d]{9}");
		if (regex_match(buffer.c_str(), phoneRe)) {
			user.setPhone(buffer);
			break;
		}
		else cout << "Неверный формат телефона, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите почту" << endl;
		enterValue(buffer);
		regex phoneRe("[(a-z\\d_.]{6,15}@[a-z]{2,7}.[a-z]{2,3}");
		if (regex_match(buffer.c_str(), phoneRe)) {
			user.setEmail(buffer);
			break;
		}
		else cout << "Неверный формат почты, попробуйте еще" << endl;
	}
	user.setId(getLastId() + 1);
	ofstream file("e://ЛАБЫ/Олесе/users.txt", ios::app);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}
	else {
		file <<"\n"<< user.getId() << " " << user.getName() << " " << user.getSurname() << " " << user.getLastname() << " " << user.getPhone() << " ";
		file << user.getEmail() << " " << user.getLogin() << " " << user.getPassord() << " " << user.getRole();
	}
	file.close();
	system("pause");

}

bool checkLogin(string login) {
	Service service;
	Vector<User> users;
	service.createUserVector(users);
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users.getArray()[i].getLogin() == login) return false;
	}
	return true;
}

int getLastId() {
	Service service;
	Vector<User> users;
	service.createUserVector(users);
	int maxId = -1;
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users.getArray()[i].getId() > maxId) maxId = users.getArray()[i].getId();
	}
	return maxId;
}