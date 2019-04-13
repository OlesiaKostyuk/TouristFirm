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
	cout << "Добро пожаловать, пользователь!" << endl;
	cout << "1) Показать все туры" << endl;
	cout << "2) Показать все отели" << endl;
	cout << "3) Показать мои брони" << endl;
	cout << "4) Мой профиль" << endl;
	cout << "5) Выйти" << endl;
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
	int sort = 0;
	while (true) {
		system("cls");
		cout << "Все отели:" << endl;
		Vector<Hotel> hotels;
		this->service.createHotelVector(hotels);
		this->sortHotels(sort, hotels);
		this->service.printHotelVector(hotels);
		switch (hotelsMenu())
		{
		case 1: {
			int id;
			cout << "Введите id отеля: ";
			cin >> id;
			this->addReview(id);
			this->service.printEnterMessage();
			break;
		}
		case 2: {
			Vector<Review> reviews;
			int id;
			cout << "Введите id отеля: ";
			cin >> id;
			this->service.createReviewVector(reviews, id);
			if (reviews.getSize() == 0) cout << "Отзывов нет" << endl;
			else {
				this->service.printReviewString();
				this->service.printReviewTitle();
				for (int i = 0; i < reviews.getSize(); i++) {
					this->service.printReviewString();
					cout << reviews.getArray()[i];
				}
				this->service.printReviewString();
			}
			this->service.printEnterMessage();
			break;
		}
		case 3: {
			cout << "1) Сортировать отели по названию" << endl;
			cout << "2) Сортировать отели по звездам" << endl;
			cout << "3) Не сортировать" << endl;
			cin >> sort; break;
		}
		case 4:
			int id;
			cout << "Введите id отеля: ";
			cin >> id;
			showTourListByHotel(id);
			break;

		default:
			return;
		}
	}
}

void UserMenu::sortHotels(int i, Vector<Hotel> &hotel) {
	switch (i)
	{
	case 1: this->service.sortHotelsVectorByName(hotel); break;
	case 2: this->service.sortHotelsVectorByRate(hotel); break;
	}
}

int UserMenu::hotelsMenu() {
	int i;
	cout << "1) Оставить отзыв на отель" << endl;
	cout << "2) Показать отзывы на отель" << endl;
	cout << "3) Сортировать отели" << endl;
	cout << "4) Показать туры по отелю" << endl;
	cout << "5) Назад" << endl;
	cin >> i;
	return i;
}

void UserMenu::showAllTours() {
	bool isShown = true;
	int sort = 0;
	while (isShown) {
		system("cls");
		cout << "Все туры:" << endl;
		Vector<Tour> tours;
		this->service.createTourVector(tours);
		this->sortTours(sort, tours);
		this->service.printTourVector(tours);
		switch (toursMenu()) {
		case 1: {
			int i;
			cout << "Введите id тура:" << endl;
			cin >> i;
			showHotelById(getHotelIdByTourId(i));
			break;
		}
		case 2: {
			int i;
			cout << "Введите id тура:" << endl;
			cin >> i;
			bookTour(i);
			break;
		}
		case 3: {
			cout << "1) Сотировать по стоимости" << endl;
			cout << "2) Сотировать по дате начала" << endl;
			cout << "3) Сотировать по дате конца" << endl;
			cout << "4) Не сортировать" << endl;
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
		cout << "Id тура отсутствует" << endl;
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
				this->service.printHotelTableString();
				cout << endl << "Отзывы: "<<endl;
				Vector<Review> reviews;
				this->service.createReviewVector(reviews, id);
				if (reviews.getSize() == 0) cout << "Отзывов нет" << endl;
				else {
					this->service.printReviewString();
					this->service.printReviewTitle();
					for (int i = 0; i < reviews.getSize(); i++) {
						this->service.printReviewString();
						cout << reviews.getArray()[i];
					}
					this->service.printReviewString();
				}
			}
		}
	}
	this->service.printEnterMessage();
}

int UserMenu::toursMenu() {
	int i;
	cout << "1) Показать отель из тура" << endl;
	cout << "2) Забронировать тур" << endl;
	cout << "3) Сортировать туры" << endl;
	cout << "4) Назад" << endl;
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
		cout << "Мои брони:" << endl;
		Vector<Booking> books;
		this->service.createBookingVector(books, this->userId);
		this->service.printBookingTableString();
		this->service.printBookingTableTitle();
		for (int i = 0; i < books.getSize(); i++) {
			this->service.printBookingTableString();
			cout << books.getArray()[i];
		}
		this->service.printBookingTableString();
		cout << "1) Удалить бронь" << endl;
		cout << "2) Назад" << endl;
		int i;
		cin >> i;
		if (i == 1) {
			int id;
			cout << "Введите id брони, которую хотите удалить" << endl;
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
			cout << "Введите номер пасспорта" << endl;
			this->service.enterValue(passport);
			regex passReg("[A-Z]{2}[\\d]{7}");
			if (regex_match(passport.c_str(), passReg)) {
				break;
			}
			else cout << "Неверный формат номера паспорта, попробуйте еще" << endl;
		}
		ofstream file("e://ЛАБЫ/Олесе/bookings.txt", ios::app);
		if (!file.is_open()) {
			cout << "Ошибка открытия файла!" << endl;
			return;
		}
		else {
			file << "\n" << id << " " << tourId << " " << this->userId << " " << passport << " unpaid";
			cout << "Тур забронирован" << endl;
			this->service.printEnterMessage();
		}
		file.close();
	}
	else {
		cout << "id не найден" << endl;
		this->service.printEnterMessage();
	}

}

void UserMenu::addReview(int hotelId) {
	Vector<Review> reviews;
	this->service.createReviewVector(reviews, 0);
	bool exist = false;
	for (int i = 0; i < reviews.getSize(); i++)
	{
		if (reviews.getArray()[i].getId() == hotelId) {
			exist = true;
			break;
		}
	}
	int id = this->service.getLastReviewId() + 1;
	if (exist) {
		char text[500];
		cout << "Введите текст отзыва: " << endl;
		cin.get();
		cin.getline(text, 500, '\n');
		ofstream file("e://ЛАБЫ/Олесе/review.txt", ios::app);
		int rate = 0;
		cout << "Введите оценку отелю от 1 до 5 (другие значения принимаются как 2) ";
		cin >> rate;
		rate = rate < 5 && rate > 0 ? rate : 2;
		if (!file.is_open()) {
			cout << "Ошибка открытия файла!" << endl;
			return;
		}
		else {
			for (int i = 0; i < strlen(text); i++) {
				if (text[i] == ' ') text[i] = '_';
			}
			file << "\n" << id << " " << hotelId << " " << this->userId << " " << rate << " " << text;
			cout << "Отзыв добавлен" << endl;
		}
		file.close();
	}
	else {
		cout << "id не найден" << endl;
		this->service.printEnterMessage();
	}
}

void UserMenu::showMyProfile() {
	system("cls");
	User user = this->service.getUserById(this->userId);
	this->service.printUserString();
	this->service.printUserTitle();
	this->service.printUserString();
	cout << user;
	this->service.printUserString();
	this->service.printEnterMessage();
}

void UserMenu::showTourListByHotel(int id) {
	Vector<Tour> tours;
	this->service.createTourVector(tours);
	this->service.printTourTableString();
	this->service.printTourTableTitle();
	for (int i = 0; i < tours.getSize(); i++) {
		if (tours.getArray()[i].getHotelId() == id) {
			this->service.printTourTableString();
			cout << tours.getArray()[i];			
		}
	}
	this->service.printTourTableString();
	this->service.printEnterMessage();
}