#include "pch.h"
#include "UserMenu.h"
#include "Service.h"
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

int UserMenu::showMenu() {
	system("cls");
	int i;
	cout << "����� ����������, ������������!" << endl;
	cout << "1) �������� ��� ����" << endl;
	cout << "2) �������� ��� �����" << endl;
	cout << "3) �������� ��� �����" << endl;
	cout << "4) ��� �������" << endl;
	cout << "5) �����" << endl;
	cin >> i;
	return i;
}

void UserMenu::menu() {
	while (true) {
		switch (showMenu()) {
		case 1: {
			this->showAllTours(); break;
		}
		case 2: {
			this->showAllHotels(); break;
		}
		case 3: {
			this->showUserBookings(); break;
		}
		case 4: {
			this->showMyProfile(); break;
		}
		default: return;
		}
	}
}

void UserMenu::showAllHotels() {
	system("cls");
	cout << "��� �����:" << endl;
	Vector<Hotel> hotels;
	this->service.createHotelVector(hotels);
	this->service.printHotelVector(hotels);
	this->service.printEnterMessage();
}

void UserMenu::showAllTours() {
	bool isShown = true;
	int sort = 0;
	while (isShown) {
		system("cls");
		cout << "��� ����:" << endl;
		Vector<Tour> tours;
		this->service.createTourVector(tours);
		this->sortTours(sort, tours);
		this->service.printTourVector(tours);
		switch (toursMenu()) {
		case 1: {
			int i;
			cout << "������� id ����:" << endl;
			cin >> i;
			showHotelById(getHotelIdByTourId(i));
			break;
		}
		case 2: {
			int i;
			cout << "������� id ����:" << endl;
			cin >> i;
			bookTour(i);
			break;
		}
		case 3: {
			cout << "1) ���������� �� ���������" << endl;
			cout << "2) ���������� �� ���� ������" << endl;
			cout << "3) ���������� �� ���� �����" << endl;
			cout << "4) �� �����������" << endl;
			cin >> sort;
			break;
		}
		default: isShown = false; break;
		}
	}
}

int UserMenu::getHotelIdByTourId(int id) {
	Vector<Tour> tours;
	this->service.createTourVector(tours);
	for (int i = 0; i < tours.getSize(); i++)
	{
		if (tours.getArray()[i].getId() == id) return tours.getArray()[i].getHotelId();
	}
	return -1;
}

void UserMenu::showHotelById(int id) {
	if (id == -1) {
		cout << "Id ���� �����������" << endl;
	}
	else {
		Vector<Hotel> hotels;
		this->service.createHotelVector(hotels);
		this->service.printHotelTableString();
		this->service.printHotelTableTitle();
		for (int i = 0; i < hotels.getSize(); i++)
		{
			if (hotels.getArray()[i].getId() == id) {
				this->service.printHotelTableString();
				cout << hotels.getArray()[i];
			}
		}
		this->service.printHotelTableString();
	}
	this->service.printEnterMessage();
}

int UserMenu::toursMenu() {
	int i;
	cout << "1) �������� ����� �� ����" << endl;
	cout << "2) ������������� ���" << endl;
	cout << "3) ����������� ����" << endl;
	cout << "4) �����" << endl;
	cin >> i;
	return i;
}

void UserMenu::sortTours(int i, Vector<Tour> &tours) {
	switch (i) {
	case 1: this->service.sortTourVectorByCost(tours); break;
	case 2: this->service.sortTourVectorByBeginDate(tours); break;
	case 3: this->service.sortTourVectorByEndDate(tours); break;
	}
}

void UserMenu::showUserBookings() {
	while (true)
	{
		system("cls");
		cout << "��� �����:" << endl;
		Vector<Booking> books;
		this->service.createBookingVector(books, this->userId);
		this->service.printBookingTableString();
		this->service.printBookingTableTitle();
		for (int i = 0; i < books.getSize(); i++) {
			this->service.printBookingTableString();
			cout << books.getArray()[i];
		}
		this->service.printBookingTableString();
		cout << "1) ������� �����" << endl;
		cout << "2) �����" << endl;
		int i;
		cin >> i;
		if (i == 1) {
			int id;
			cout << "������� id �����, ������� ������ �������" << endl;
			cin >> id;
			this->service.removeUserBooking(id, this->userId);
		}
		else {
			return;
		}
		this->service.printEnterMessage();
	}
}

void UserMenu::bookTour(int tourId) {
	Vector<Tour> tours;
	this->service.createTourVector(tours);
	bool exist = false;
	for (int i = 0; i < tours.getSize(); i++)
	{
		if (tours.getArray()[i].getId() == tourId) {
			exist = true;
			break;
		}
	}
	int id = this->service.getLastBookingId() + 1;
	if (exist) {
		string passport;
		while (true) {
			cout << "������� ����� ���������" << endl;
			this->service.enterValue(passport);
			regex passReg("[A-Z]{2}[\\d]{7}");
			if (regex_match(passport.c_str(), passReg)) {
				break;
			}
			else cout << "�������� ������ ������ ��������, ���������� ���" << endl;
		}
		ofstream file("e://����/�����/bookings.txt", ios::app);
		if (!file.is_open()) {
			cout << "������ �������� �����!" << endl;
			return;
		}
		else {
			file << "\n" << id << " " << tourId << " " << this->userId << " " << passport << " unpaid";
			cout << "��� ������������" << endl;
			this->service.printEnterMessage();
		}
		file.close();
	}
	else {
		cout << "id �� ������" << endl;
		this->service.printEnterMessage();
	}

}

void UserMenu::showMyProfile() {
	User user = this->service.getUserById(this->userId);

}