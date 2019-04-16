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
	cout << "Добро пожаловать, администратор!" << endl;
	cout << "1) Просмотреть туры" << endl;
	cout << "2) Просмотреть отели" << endl;
	cout << "3) Просмотреть заявки" << endl;
	cout << "4) Просмотреть пользователей" << endl;
	cout << "5) Выйти" << endl;
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
		service->createTourVector(tours);
		service->printTourVector(tours);
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
	while (true) {
		system("cls");
		Vector<Hotel> hotels;
		service->createHotelVector(hotels);
		service->printHotelVector(hotels);
		switch (hotelsMenu())
		{
		case 1: this->addHotel(); break;
		case 2: this->deleteHotel(); break;
		default:
			return;
		}
	}
}

void AdminMenu::showAllBookings() {
	bool filter = false;
	while (true) {
		system("cls");
		Vector<Booking> bookings;
		service->createBookingVector(bookings, 0);
		service->sortBookingVectorById(bookings);
		service->printBookingTableString();
		service->printBookingTableTitle();
		for (int i = 0; i < bookings.getSize(); i++)
		{
			if (filter) {
				if (bookings.getArray()[i].getPaymentStatus() == "unpaid")
				{
					service->printBookingTableString();
					cout << bookings.getArray()[i];
				}
			}
			else {
				service->printBookingTableString();
				cout << bookings.getArray()[i];
			}
		}
		service->printBookingTableString();
		switch (bookingsMenu())
		{
		case 1: {
			cout << "1) Показать только неоплаченные 2) Показать все" << endl;
			int i;
			cin >> i;
			if (i == 1) filter = true;
			else filter = false;
			break; 
		}
		case 2: {
			int id, counter = 0;
			cout << "Введите id брони которую хотите изменить на оплаченную" << endl;
			cin >> id;
			bool existAndUnpaid = false;
			Booking temp;
			for (int i = 0; i < bookings.getSize(); i++)
			{
				if (bookings.getArray()[i].getBookId() == id) {
					if (bookings.getArray()[i].getPaymentStatus() == "unpaid") existAndUnpaid = true;
					break;
				}
			}
			if (existAndUnpaid) {
				Vector<Booking> booking;
				service->createBookingVector(booking, 0);
				for (int i = 0; i < booking.getSize(); i++)
				{
					counter++;
					if (booking.getArray()[i].getBookId() == id) {
						temp = booking.getArray()[i];
						service->deleteStringFromFile(counter, "e://ЛАБЫ/4 сем/bookings.txt");
						ofstream file("e://ЛАБЫ/4 сем/bookings.txt", ios::app);
						if (!file.is_open()) {
							cout << "Ошибка открытия файла!" << endl;
							break;
						}
						else {
							file << temp.getBookId() << " " << temp.getTourId() << " " << temp.getUserId() << " " << temp.getPassportNumber() << " paid";
							cout << "Бронь изменена" << endl;
						}
						file.close();
						break;
					}
				}
			}
			else {
				cout << "Бронь с таким id не найдена или она уже оплачена" << endl;
			}
			service->printEnterMessage();
			break;
		}
		default:
			return;
		}
	}
}

void AdminMenu::showAllUsers() {
	system("cls");
	Vector<User> users;
	service->createUserVector(users);
	service->printUserString();
	service->printUserTitle();
	for (int i = 0; i < users.getSize(); i++) {
		if (users.getArray()[i].getRole() == "us") {
			service->printUserString();
			cout << users.getArray()[i];
		}
	}
	service->printUserString();
	service->printEnterMessage();
}

int AdminMenu::toursMenu() {
	int i;
	cout << "1) Добавить тур" << endl;
	cout << "2) Удалить тур" << endl;
	cout << "3) Назад" << endl;
	cin >> i;
	return i;
}

int AdminMenu::hotelsMenu() {
	int i;
	cout << "1) Добавить отель" << endl;
	cout << "2) Удалить отель" << endl;
	cout << "3) Назад" << endl;
	cin >> i;
	return i;
}

int AdminMenu::bookingsMenu() {
	int i;
	cout << "1) Фильтровать брони" << endl;
	cout << "2) Обновить статус брони на оплачено" << endl;
	cout << "3) Назад" << endl;
	cin >> i;
	return i;
}

void AdminMenu::addTour() {
	Tour tour;
	string buffer;
	while (true) {
		cout << "Введите страну: " << endl;;
		service->enterValue(buffer);
		regex tourRe("[a-zA-Zа-яА-Я]{2,30}");
		if (regex_match(buffer.c_str(), tourRe)) {
			tour.setCountry(buffer);
			break;
		}
		else cout << "Неверный формат страны, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите название авиакомпании: " << endl;;
		service->enterValue(buffer);
		regex tourRe("[a-zA-Zа-яА-Я\\d]{2,40}");
		if (regex_match(buffer.c_str(), tourRe)) {
			tour.setAviaCompanyName(buffer);
			break;
		}
		else cout << "Неверный формат авиакомпании, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите дату начала в формате yyyy/mm/dd: " << endl;;
		service->enterValue(buffer);
		regex dateRe("[\\d]{4}\\/[\\d]{2}\\/[\\d]{2}");
		if (regex_match(buffer.c_str(), dateRe)) {
			tour.setBeginDate(buffer);
			break;
		}
		else cout << "Неверный формат даты, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите дату окончания в формате yyyy/mm/dd: " << endl;;
		service->enterValue(buffer);
		regex dateRe("[\\d]{4}\\/[\\d]{2}\\/[\\d]{2}");
		if (regex_match(buffer.c_str(), dateRe)) {
			if (tour.getBeginDate() < buffer) {
				tour.setEndDate(buffer);
				break;
			}
			else {
				cout << "Дана окончания не может быть больше или равна дате начала, попробуйте еще" << endl;
			}
		}
		else cout << "Неверный формат даты, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите стоимоть: " << endl;;
		service->enterValue(buffer);
		regex costRe("[\\d]+");
		if (regex_match(buffer.c_str(), costRe)) {
			tour.setCost(atoi(buffer.data()));
			break;
		}
		else cout << "Неверный формат цены, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите id отеля: " << endl;;
		service->enterValue(buffer);
		regex costRe("[\\d]+");
		if (regex_match(buffer.c_str(), costRe)) {
			int id = atoi(buffer.data());
			bool exist = false;
			Vector<Hotel> hotels;
			service->createHotelVector(hotels);
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
				cout << "Отель не найден" << endl;
			}
		}
		else cout << "Неверный формат цены, попробуйте еще" << endl;
	}
	ofstream file("e://ЛАБЫ/4 сем/tours.txt", ios::app);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}
	else {
		file << "\n" << service->getLastTourId() + 1 << " " << tour.getCountry() << " " << tour.getBeginDate() << " " << tour.getEndDate() << " " << tour.getCost();
		file << " " << tour.getHotelId() << " " << tour.getAviaCompanyName();
		cout << "Тур добавлен" << endl;
	}
	file.close();
	service->printEnterMessage();
}

void AdminMenu::deleteTour() {
	cout << "Введите id тура, который вы хотите удалить" << endl;
	int id;
	cin >> id;
	Vector<Tour> tours;
	service->createTourVector(tours);
	Vector<Booking> bookings;
	service->createBookingVector(bookings, 0);
	bool error = false;
	for (int j = 0; j < bookings.getSize(); j++) {
		if (id == bookings.getArray()[j].getTourId()) {
			error = true;
			break;
		}
	}
	if (error) {
		cout << "Вы не можете удалить данный тур, так как он уже забронирован" << endl;
		service->printEnterMessage();
		return;
	}
	else {
		int counter = 0;
		for (int i = 0; i < tours.getSize(); i++)
		{
			counter++;
			if (tours.getArray()[i].getId() == id) {
				cout << "Тур удален" << endl;
				service->deleteStringFromFile(counter, "e://ЛАБЫ/4 сем/tours.txt");
				return;
			}
		}
	}
	cout << "Тур в таким id не найден" << endl;
	service->printEnterMessage();
}

void AdminMenu::addHotel() {
	Hotel hotel;
	string buffer;
	while (true) {
		cout << "Введите название отеля: " << endl;;
		service->enterValue(buffer);
		regex hotelRe("[a-zA-Zа-яА-Я]{2,30}");
		if (regex_match(buffer.c_str(), hotelRe)) {
			hotel.setHotelName(buffer);
			break;
		}
		else cout << "Неверный формат названия отеля, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите количество звезд: " << endl;;
		service->enterValue(buffer);
		regex starRe("[12345]");
		if (regex_match(buffer.c_str(), starRe)) {
			hotel.setStars(atoi(buffer.data()));
			break;
		}
		else cout << "Неверный формат звезд отеля, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите страну: " << endl;;
		service->enterValue(buffer);
		regex hotelRe("[a-zA-Zа-яА-Я]{2,30}");
		if (regex_match(buffer.c_str(), hotelRe)) {
			hotel.setCountry(buffer);
			break;
		}
		else cout << "Неверный формат страны, попробуйте еще" << endl;
	}
	while (true) {
		cout << "Введите город: " << endl;;
		service->enterValue(buffer);
		regex hotelRe("[a-zA-Zа-яА-Я]{2,30}");
		if (regex_match(buffer.c_str(), hotelRe)) {
			hotel.setTown(buffer);
			break;
		}
		else cout << "Неверный формат города, попробуйте еще" << endl;
	}

	char text[500];
	cout << "Введите описание: " << endl;
	cin.get();
	cin.getline(text, 500, '\n');
	for (int i = 0; i < strlen(text); i++) {
		if (text[i] == ' ') text[i] = '_';
	}
	strstream stream;
	stream << text << ends;
	hotel.setDescription(stream.str());
	ofstream file("e://ЛАБЫ/4 сем/hotels.txt", ios::app);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}
	else {
		file << "\n" << service->getLastHotelId() + 1 << " " << hotel.getHotelName() << " " << hotel.getStars() << " " << hotel.getCountry();
		file << " " << hotel.getTown() << " " << hotel.getDescription();
		cout << "Отель добавлен" << endl;
	}
	file.close();
	service->printEnterMessage();
}

void AdminMenu::deleteHotel() {
	cout << "Введите id отеля, который вы хотите удалить" << endl;
	int id;
	cin >> id;
	Vector<Hotel> hotels;
	service->createHotelVector(hotels);
	Vector<Tour> tours;
	service->createTourVector(tours);
	bool error = false;
	for (int j = 0; j < tours.getSize(); j++) {
		if (id == tours.getArray()[j].getHotelId()) {
			error = true;
			break;
		}
	}
	if (error) {
		cout << "Вы не можете удалить данный отель, так как он он уже веключен в тур" << endl;
		service->printEnterMessage();
		return;
	}
	else {
		int counter = 0;
		for (int i = 0; i < hotels.getSize(); i++)
		{
			counter++;
			if (hotels.getArray()[i].getId() == id) {
				cout << "Отель удален" << endl;
				service->deleteStringFromFile(counter, "e://ЛАБЫ/4 сем/hotels.txt");
				return;
			}
		}
	}
	cout << "Отель в таким id не найден" << endl;
	service->printEnterMessage();

}