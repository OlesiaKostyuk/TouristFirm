#include "pch.h"
#include "Service.h"
#include <strstream>
#include <fstream>

using namespace std;

User Service::createUserFromString(char* userString) {
	User user;
	char buffer[50];
	strstream stream;
	strcat(userString, "\n");
	stream << userString;
	if (stream.good()) {
		stream >> buffer;
		int id = atoi(buffer);
		user.setId(id);
	}
	if (stream.good()) {
		stream >> buffer;
		user.setName(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		user.setSurname(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		user.setLastname(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		user.setPhone(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		user.setEmail(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		user.setLogin(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		user.setPassord(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		user.setRole(convert(buffer));
	}
	return user;
}

Tour Service::createTourFromString(char* tourString) {
	Tour tour;
	char buffer[50];
	strstream stream;
	strcat(tourString, "\n");
	stream << tourString;
	if (stream.good()) {
		stream >> buffer;
		int id = atoi(buffer);
		tour.setId(id);
	}
	if (stream.good()) {
		stream >> buffer;
		tour.setCountry(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		tour.setBeginDate(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		tour.setEndDate(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		int cost = atoi(buffer);
		tour.setCost(cost);
	}
	if (stream.good()) {
		stream >> buffer;
		int id = atoi(buffer);
		tour.setHotelId(id);
	}
	if (stream.good()) {
		stream >> buffer;
		tour.setAviaCompanyName(convert(buffer));
	}
	return tour;
}

Hotel Service::createHotelFromString(char* hotelString) {
	Hotel hotel;
	char buffer[50];
	strstream stream;
	strcat(hotelString, "\n");
	stream << hotelString;
	if (stream.good()) {
		stream >> buffer;
		int id = atoi(buffer);
		hotel.setId(id);
	}
	if (stream.good()) {
		stream >> buffer;
		hotel.setHotelName(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		int id = atoi(buffer);
		hotel.setStars(id);
	}
	if (stream.good()) {
		stream >> buffer;
		hotel.setCountry(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		hotel.setTown(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		hotel.setDescription(convert(buffer));
	}
	return hotel;
}

Booking Service::createBookingFromString(char* bookingString) {
	Booking booking;
	char buffer[50];
	strstream stream;
	strcat(bookingString, "\n");
	stream << bookingString;
	if (stream.good()) {
		stream >> buffer;
		int id = atoi(buffer);
		booking.setBookId(id);
	}
	if (stream.good()) {
		stream >> buffer;
		int id = atoi(buffer);
		booking.setTourId(id);
	}
	if (stream.good()) {
		stream >> buffer;
		int id = atoi(buffer);
		booking.setUserId(id);
	}
	if (stream.good()) {
		stream >> buffer;
		booking.setPassportNumber(convert(buffer));
	}
	if (stream.good()) {
		stream >> buffer;
		booking.setPaymentStatus(convert(buffer));
	}
	return booking;
}

string Service::convert(char* mas) {
	strstream wordStream;
	wordStream << mas << ends;
	string str = wordStream.str();
	return str;
}

void Service::printTourTableString() {
	cout << "+-----+------------+------------+------------+------------+------------+------------+" << endl;
}

void Service::printTourTableTitle() {
	cout << "|" << setw(5) << "id";
	cout << "|" << setw(12) << "Страна";
	cout << "|" << setw(12) << "Начало";
	cout << "|" << setw(12) << "Конец";
	cout << "|" << setw(12) << "Стоимость";
	cout << "|" << setw(12) << "id отеля";
	cout << "|" << setw(12) << "Авиакомпания" << "|" << endl;
}

void Service::printHotelTableString() {
	cout << "+-----+---------------+----------+---------------+---------------+------------------------------+" << endl;
}

void Service::printHotelTableTitle() {
	cout << "|" << setw(5) << "id";
	cout << "|" << setw(15) << "Название";
	cout << "|" << setw(10) << "Звезды";
	cout << "|" << setw(15) << "Страна";
	cout << "|" << setw(15) << "Город";
	cout << "|" << setw(30) << "Описание" << "|" << endl;
}

void Service::printBookingTableString() {
	cout << "+----------+----------+---------------+--------------------+---------------+" << endl;
}

void Service::printBookingTableTitle() {
	cout << "|" << setw(10) << "id брони";
	cout << "|" << setw(10) << "id тура";
	cout << "|" << setw(15) << "id пользователя";
	cout << "|" << setw(20) << "номер паспорта";
	cout << "|" << setw(15) << "статус оплаты" << "|" << endl;
}

void Service::enterValue(string &result) {
	strstream ss;
	char buffer[100];
	cin >> buffer;
	ss << buffer << ends;
	result = ss.str();
}

void Service::deleteStringFromFile(int stringNumber, string fileName) {
	string line;
	string line_file_text;
	int currentLineNumber = 0;
	ifstream fileIn(fileName);
	if (!fileIn)
	{
		cerr << "Ошибка, невозможно открыть файл" << endl;
		return;
	}
	while (getline(fileIn, line))
	{
		currentLineNumber++;

		if (currentLineNumber != stringNumber)
		{
			line_file_text.insert(line_file_text.size(), line);
			line_file_text.insert(line_file_text.size(), "\r\n");
		}
	}
	fileIn.close();
	ofstream fileOut(fileName, ios::trunc | ios::binary);
	fileOut.write(line_file_text.c_str(), line_file_text.size());
	fileOut.clear();
	fileOut.close();
}

void Service::sortTourVectorByCost(Vector<Tour> &tour) {
	for (int i = 0; i < tour.getSize() - 1; i++) {
		for (int j = i + 1; j < tour.getSize(); j++) {
			if (tour.getArray()[i].getCost() > tour.getArray()[j].getCost()) {
				Tour temp = tour.getArray()[i];
				tour.getArray()[i] = tour.getArray()[j];
				tour.getArray()[j] = temp;
			}
		}
	}
}

void Service::sortTourVectorByBeginDate(Vector<Tour> &tour) {
	for (int i = 0; i < tour.getSize() - 1; i++) {
		for (int j = i + 1; j < tour.getSize(); j++) {
			if (tour.getArray()[i].getBeginDate() > tour.getArray()[j].getBeginDate()) {
				Tour temp = tour.getArray()[i];
				tour.getArray()[i] = tour.getArray()[j];
				tour.getArray()[j] = temp;
			}
		}
	}
}

void Service::sortTourVectorByEndDate(Vector<Tour> &tour) {
	for (int i = 0; i < tour.getSize() - 1; i++) {
		for (int j = i + 1; j < tour.getSize(); j++) {
			if (tour.getArray()[i].getEndDate() > tour.getArray()[j].getEndDate()) {
				Tour temp = tour.getArray()[i];
				tour.getArray()[i] = tour.getArray()[j];
				tour.getArray()[j] = temp;
			}
		}
	}
}

void Service::printHotelVector(Vector<Hotel> &hotels) {
	this->printHotelTableString();
	this->printHotelTableTitle();
	for (int i = 0; i < hotels.getSize(); i++)
	{
		this->printHotelTableString();
		cout << hotels.getArray()[i];
	}
	this->printHotelTableString();
}

void Service::printTourVector(Vector<Tour> &tours) {
	this->printTourTableString();
	this->printTourTableTitle();
	for (int i = 0; i < tours.getSize(); i++)
	{
		this->printTourTableString();
		cout << tours.getArray()[i];
	}
	this->printTourTableString();
}

void Service::createHotelVector(Vector<Hotel> &hotels) {
	ifstream hotelsFile("e://ЛАБЫ/Олесе/hotels.txt");
	if (!hotelsFile.is_open()) {
		cout << "Базы данных не существует!" << endl;
		system("pause");
		exit(0);
	}
	char hotelBuffer[300];
	while (!hotelsFile.eof()) {
		hotelsFile.getline(hotelBuffer, 200);
		if (strcmp(hotelBuffer, "") == 0) break;
		Hotel hotel = createHotelFromString(hotelBuffer);
		hotels.add(hotel);
	}
	hotelsFile.close();
}

void Service::createTourVector(Vector<Tour> &tours) {
	ifstream toursFile("e://ЛАБЫ/Олесе/tours.txt");
	if (!toursFile.is_open()) {
		cout << "Базы данных не существует!" << endl;
		system("pause");
		exit(0);
	}
	char tourBuffer[300];
	while (!toursFile.eof()) {
		toursFile.getline(tourBuffer, 200);
		if (strcmp(tourBuffer, "") == 0) break;
		Tour tour = createTourFromString(tourBuffer);
		tours.add(tour);
	}
	toursFile.close();
}

void Service::createUserVector(Vector<User> &users) {
	ifstream usersFile("e://ЛАБЫ/Олесе/users.txt");
	if (!usersFile.is_open()) {
		cout << "Базы данных не существует!" << endl;
		system("pause");
		exit(0);
	}
	char userBuffer[300];
	while (!usersFile.eof()) {
		usersFile.getline(userBuffer, 200);
		if (strcmp(userBuffer, "") == 0) break;
		User user = createUserFromString(userBuffer);
		users.add(user);
	}
	usersFile.close();
}

void Service::createBookingVector(Vector<Booking> &books, int id = 0) {
	ifstream bookFile("e://ЛАБЫ/Олесе/bookings.txt");
	if (!bookFile.is_open()) {
		cout << "Базы данных не существует!" << endl;
		system("pause");
		exit(0);
	}
	char bookBuffer[300];
	while (!bookFile.eof()) {
		bookFile.getline(bookBuffer, 200);
		if (strcmp(bookBuffer, "") == 0) break;
		Booking book = createBookingFromString(bookBuffer);
		if (id == 0) books.add(book);
		else if (book.getUserId() == id) books.add(book);
	}
	sortBookingVectorById(books);
	bookFile.close();
}

void Service::removeUserBooking(int bookId, int userId) {
	int counter = 0;
	Vector<Booking> book;
	createBookingVector(book);
	for (int i = 0; i < book.getSize(); i++)
	{
		counter++;
		if (book.getArray()[i].getBookId() == bookId) {
			if (book.getArray()[i].getUserId() == userId) {
				deleteStringFromFile(counter, "e://ЛАБЫ/Олесе/bookings.txt");
				cout << "Бронь удалена" << endl;
			}
			else {
				cout << "Ошибка доступа" << endl;
			}
			return;
		}
	}
	cout << "Запись не найдена" << endl;
}

int Service::getLastBookingId() {
	Vector<Booking> book;
	createBookingVector(book);
	int maxId = -1;

	for (int i = 0; i < book.getSize(); i++)
	{
		if (book.getArray()[i].getBookId() > maxId) maxId = book.getArray()[i].getBookId();
	}
	return maxId;
}

void Service::sortBookingVectorById(Vector<Booking> &book) {
	for (int i = 0; i < book.getSize() - 1; i++) {
		for (int j = i + 1; j < book.getSize(); j++) {
			if (book.getArray()[i].getBookId() > book.getArray()[j].getBookId()) {
				Booking temp = book.getArray()[i];
				book.getArray()[i] = book.getArray()[j];
				book.getArray()[j] = temp;
			}
		}
	}
}

User Service::getUserById(int id) {
	Vector<User> users;
	createUserVector(users);
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users.getArray()[i].getId() == id) return users.getArray()[i];
	}
	cout << "Пользователь не найден" << endl;
	User user;
	return user;
}