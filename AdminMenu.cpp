#include "pch.h"
#include "AdminMenu.h"
#include "Service.h"
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

int AdminMenu::showMenu() {
	system("cls");
	int i;
	cout << "����� ����������, �������������!" << endl;
	cout << "1) ����������� ����" << endl;
	cout << "2) ����������� �����" << endl;
	cout << "3) ����������� �����" << endl;
	cout << "3) ����������� �������������" << endl;
	cout << "5) �����" << endl;
	cin >> i;
	return i;
}

void AdminMenu::menu() {
	while (true) {
		switch (showMenu()) {
		case 1: {
			this->showAllTours(); break;
		}
		case 2: {
			this->showAllHotels(); break;
		}
		case 3: {
			this->showAllBookings(); break;
		}
		case 4: {
			this->showAllUsers(); break;
		}
		default: return;
		}
	}
}

void AdminMenu::showAllTours() {
	while (true) {
		system("cls");
		Vector<Tour> tours;
		this->service.createTourVector(tours);
		this->service.printTourVector(tours);
		switch (toursMenu())
		{
		case 1: this->addTour(); break;
		case 2: this->deleteTour(); break;
		default:
			return;
		}
	}

}

void AdminMenu::showAllHotels() {

}

void AdminMenu::showAllBookings() {

}

void AdminMenu::showAllUsers() {
	system("cls");
	Vector<User> users;
	this->service.createUserVector(users);
	this->service.printUserString();
	this->service.printUserTitle();
	for (int i = 0; i < users.getSize(); i++) {
		if (users.getArray()[i].getRole() == "us") {
			this->service.printUserString();
			cout << users.getArray()[i];
		}
	}
	this->service.printUserString();
	this->service.printEnterMessage();
}

int AdminMenu::toursMenu() {
	int i;
	cout << "1) �������� ���" << endl;
	cout << "2) ������� ���" << endl;
	cout << "3) �����" << endl;
	cin >> i;
	return i;
}

int AdminMenu::hotelsMenu() {
	int i;
	cout << "1) �������� �����" << endl;
	cout << "2) ������� �����" << endl;
	cout << "3) �����" << endl;
	cin >> i;
	return i;
}

int AdminMenu::bookingsMenu() {
	int i;
	cout << "1) ����������� �����" << endl;
	cout << "2) �������� ������ ����� �� ��������" << endl;
	cout << "3) �����" << endl;
	cin >> i;
	return i;
}

void AdminMenu::addTour() {
	Tour tour;
	string buffer;
	while (true) {
		cout << "������� ������: " << endl;;
		this->service.enterValue(buffer);
		regex tourRe("[a-zA-Z�-��-�]{2,30}");
		if (regex_match(buffer.c_str(), tourRe)) {
			tour.setCountry(buffer);
			break;
		}
		else cout << "�������� ������ ������, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� �������� ������������: " << endl;;
		this->service.enterValue(buffer);
		regex tourRe("[a-zA-Z�-��-�\\d]{2,40}");
		if (regex_match(buffer.c_str(), tourRe)) {
			tour.setAviaCompanyName(buffer);
			break;
		}
		else cout << "�������� ������ ������������, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� ���� ������ � ������� dd-mm-yyyy: " << endl;;
		this->service.enterValue(buffer);
		regex dateRe("[\\d]{2}\\/[\\d]{2}\\/[\\d]{4}");
		if (regex_match(buffer.c_str(), dateRe)) {
			tour.setBeginDate(buffer);
			break;
		}
		else cout << "�������� ������ ����, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� ���� ��������� � ������� dd-mm-yyyy: " << endl;;
		this->service.enterValue(buffer);
		regex dateRe("[\\d]{2}\\/[\\d]{2}\\/[\\d]{4}");
		if (regex_match(buffer.c_str(), dateRe)) {
			if (tour.getBeginDate() < buffer) {
				tour.setEndDate(buffer);
				break;
			}
			else {
				cout << "���� ��������� �� ����� ���� ������ ��� ����� ���� ������, ���������� ���" << endl;
			}
		}
		else cout << "�������� ������ ����, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� ��������: " << endl;;
		this->service.enterValue(buffer);
		regex costRe("[\\d]+");
		if (regex_match(buffer.c_str(), costRe)) {
			tour.setCost(atoi(buffer.data()));
			break;
		}
		else cout << "�������� ������ ����, ���������� ���" << endl;
	}
	while (true) {
		cout << "������� id �����: " << endl;;
		this->service.enterValue(buffer);
		regex costRe("[\\d]+");
		if (regex_match(buffer.c_str(), costRe)) {
			int id = atoi(buffer.data());
			bool exist = false;
			Vector<Hotel> hotels;
			this->service.createHotelVector(hotels);
			for (int i = 0; i < hotels.getSize(); i++) {
				if (hotels.getArray()[i].getId() == id) {
					exist = true;
					break;
				}
			}
			if (exist) {
				tour.setHotelId(id);
				break;
			}
			else {
				cout << "����� �� ������" << endl;
			}
		}
		else cout << "�������� ������ ����, ���������� ���" << endl;
	}
	ofstream file("e://����/�����/tours.txt", ios::app);
	if (!file.is_open()) {
		cout << "������ �������� �����!" << endl;
		return;
	}
	else {
		file << "\n" << this->service.getLastTourId() +1 << " " << tour.getCountry() << " " << tour.getBeginDate() << " " << tour.getEndDate() << " " << tour.getCost();
		file << " " << tour.getHotelId() << " " << tour.getAviaCompanyName();
		cout << "��� ��������" << endl;
	}
	file.close();
	this->service.printEnterMessage();
}

void AdminMenu::deleteTour() {
	cout << "������� id ����, ������� �� ������ �������" << endl;
	int id;
	cin >> id;
	Vector<Tour> tours;
	this->service.createTourVector(tours);
	Vector<Booking> bookings;
	this->service.createBookingVector(bookings, 0);
	bool error = false;
	for (int j = 0; j < bookings.getSize(); j++) {
		if (id == bookings.getArray()[j].getTourId()) {
			error = true;
			break;
		}
	}
	if (error) {
		cout << "�� �� ������ ������� ������ ���, ��� ��� �� ��� ������������" << endl;
		this->service.printEnterMessage();
		return;
	}
	else {
		int counter = 0;
		for (int i = 0; i < tours.getSize(); i++)
		{
			counter++;
			if (tours.getArray()[i].getId() == id) {
				this->service.deleteStringFromFile(counter, "e://����/�����/tours.txt");
				return;
			}
		}
	}
	cout << "��� � ����� id �� ������" << endl;
	this->service.printEnterMessage();
}