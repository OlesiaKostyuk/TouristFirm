#pragma once
#include "User.h"
#include "Tour.h"
#include "Booking.h"
#include "Hotel.h"
#include "Vector.h"
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

	string convert(char* mas);
	void deleteStringFromFile(int number, string fileName);
	void printEnterMessage() {
		cout << "������ ���� ����� ����������" << endl;
		cin.get();
		cin.get();
	}
	void sortTourVectorByCost(Vector<Tour> &vector);
	void sortTourVectorByBeginDate(Vector<Tour> &vector);
	void sortTourVectorByEndDate(Vector<Tour> &vector);
	void sortBookingVectorById(Vector<Booking> &vector);
	void enterValue(string &str);

	void removeUserBooking(int bookId, int userId);
	int getLastBookingId();

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

	Service() {}
	~Service() {}
};

