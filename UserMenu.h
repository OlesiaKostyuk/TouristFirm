#pragma once
#include "Service.h"
class UserMenu
{
	int userId;
	Service service;
public:

	void menu();
	int showMenu();

	int toursMenu();
	int getHotelIdByTourId(int id);

	void showHotelById(int id);

	void showAllTours();
	void showAllHotels();

	void bookTour(int tourId);
	void showUserBookings();
	void showMyProfile();

	void sortTours(int i, Vector<Tour> &tours);
	UserMenu(int id) { this->userId = id; };
	~UserMenu() {};
};

