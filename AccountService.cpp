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
	cout << "�����������" << endl;
	ifstream usersFile("e://����/�����/users.txt");
	if (!usersFile.is_open()) {
		cout << "���� ������ �� ����������!" << endl;
		system("pause");
		return;
	}
	cout << "������� �����:" << endl;
	string login;
	enterValue(login);
	cout << "������� ������" << endl;
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
		cout << "������������ �� ����������!" << endl;
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
	cout << "�����������" << endl;
	User user;
	user.setRole("us");
	string buffer;
	while (true) {
		cout << "������� ����� (a-z, �����, ������ ��������������, �����, �� 3 �� 12 ��������)" << endl;
		enterValue(buffer);
		regex loginRe("[a-z\\d_.]{3,12}");
		if (checkLogin(buffer)) {
			if (regex_match(buffer.c_str(), loginRe)) {
				user.setLogin(buffer);
				break;
			}
			else cout << "�������� �����, ���������� ���" << endl;
		}
		else cout << "������������ � ����� ������� ����������, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� ������ (a-z, �����, ������ ��������������, �����, �� 3 �� 12 ��������)" << endl;
		enterValue(buffer);
		regex passRe("[a-z\\d_.]{3,12}");
			if (regex_match(buffer.c_str(), passRe)) {
				user.setPassord(this->service.encodePassword(buffer));
				break;
			}
			else cout << "�������� ������ ������, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� ��� (������ �����, �� ����� 25 ��������)" << endl;
		enterValue(buffer);
		regex namesRe("[a-z�-�A-Z�-�]{1,25}");
		if (regex_match(buffer.c_str(), namesRe)) {
			user.setName(buffer);
			break;
		}
		else cout << "�������� ������ �����, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� ������� (������ �����, �� ����� 25 ��������)" << endl;
		enterValue(buffer);
		regex namesRe("[a-z�-�A-Z�-�]{1,25}");
		if (regex_match(buffer.c_str(), namesRe)) {
			user.setSurname(buffer);
			break;
		}
		else cout << "�������� ������ �������, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� �������� (������ �����, �� ����� 25 ��������)" << endl;
		enterValue(buffer);
		regex namesRe("[a-z�-�A-Z�-�]{1,25}");
		if (regex_match(buffer.c_str(), namesRe)) {
			user.setLastname(buffer);
			break;
		}
		else cout << "�������� ������ ��������, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� ������� (� ������� 9 ����)" << endl;
		enterValue(buffer);
		regex phoneRe("[\\d]{9}");
		if (regex_match(buffer.c_str(), phoneRe)) {
			user.setPhone(buffer);
			break;
		}
		else cout << "�������� ������ ��������, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� �����" << endl;
		enterValue(buffer);
		regex phoneRe("[(a-z\\d_.]{6,15}@[a-z]{2,7}.[a-z]{2,3}");
		if (regex_match(buffer.c_str(), phoneRe)) {
			user.setEmail(buffer);
			break;
		}
		else cout << "�������� ������ �����, ���������� ���" << endl;
	}
	user.setId(getLastId() + 1);
	ofstream file("e://����/�����/users.txt", ios::app);
	if (!file.is_open()) {
		cout << "������ �������� �����!" << endl;
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