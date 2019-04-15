#pragma once
#include "User.h"
#include "Tour.h"
#include "Booking.h"
#include "Hotel.h"
#include "Vector.h"
#include "Review.h"
#include <iostream>
#include <string>
#include <strstream>
using namespace std;
class Service
{
public:

	User createUserFromString(char* userString);
	Tour createTourFromString(char* tourString);
	Hotel createHotelFromString(char* hotelString);
	Booking createBookingFromString(char* bookingString);
	Review createReviewFromString(char* reviewString);
	void printTourTableString();
	void printHotelTableString();
	void printBookingTableString();
	void printTourTableTitle();
	void printHotelTableTitle();
	void printBookingTableTitle();
	void printTourVector(Vector<Tour> &vector);
	void printHotelVector(Vector<Hotel> &vector);

	void createHotelVector(Vector<Hotel> &hotels);
	void createTourVector(Vector<Tour> &tours);
	void createUserVector(Vector<User> &users);
	void createBookingVector(Vector<Booking> &books, int id);
	void createReviewVector(Vector<Review> &review, int id);

	string convert(char* mas);
	void deleteStringFromFile(int number, string fileName);
	void printEnterMessage() {
		cout << "Нажите ввод чтобы продолжить" << endl;
		cin.get();
		cin.get();
	}

	void sortHotelsVectorByRate(Vector<Hotel> &vector);
	void sortHotelsVectorByName(Vector<Hotel> &vector);

	void sortTourVectorByCost(Vector<Tour> &vector);
	void sortTourVectorByBeginDate(Vector<Tour> &vector);
	void sortTourVectorByEndDate(Vector<Tour> &vector);
	void sortBookingVectorById(Vector<Booking> &vector);
	void enterValue(string &str);

	void removeUserBooking(int bookId, int userId);
	int getLastBookingId();
	int getLastReviewId();
	int getLastTourId();
	int getLastHotelId();

	User getUserById(int id);
	string encodePassword(string str) {
		string salt = "salt_for_password";
		int diff = 0;
		for (int i = 0; i < str.length(); i++) {
			diff += (int)str[i];
		}
		for (int i = 0; i < salt.length(); i++) {
			salt[i] = salt[i] ^ (str.length() + diff % 23);
		}
		for (int i = 0; i < str.length(); i++) {
			str[i] = str[i] ^ diff % 16;
		}
		return str + salt;
	}

	void printReviewString() {
		cout << "+-----+--------+-----+----------------------------------------------------------------------------------------" << endl;
	}

	void printReviewTitle() {
		cout << "|" << setw(5) << "id";
		cout << "|" << setw(8) << "userId";
		cout << "|" << setw(5) << "rate";
		cout << "|" << setw(5) << "text" << endl;
	}

	void printUserString() {
		cout << "+-----+---------------+---------------+---------------+---------------+----------------------+" << endl;
	}

	void printUserTitle() {
		cout << "|" << setw(5) << "id";
		cout << "|" << setw(15) << "Name";
		cout << "|" << setw(15) << "Surname";
		cout << "|" << setw(15) << "Last name";
		cout << "|" << setw(15) << "Phone";
		cout << "|" << setw(22) << "Email" << "|" << endl;
	}

	string replace(string str, char old, char newChar) {
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == old) str[i] = newChar;
		}
		return str;
	}

	void replace(char str[], char old, char newChar) {
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] == old) str[i] = newChar;
		}
	}

	Service() {}
	~Service() {}
};



