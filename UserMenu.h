#pragma once
#include "Service.h"
class UserMenu
{
	int userId;
	Service *service;
public:

	void menu();
	int showMenu();

	int toursMenu();
	int hotelsMenu();
	int getHotelIdByTourId(int id);

	void showHotelById(int id);

	void showAllTours();
	void showAllHotels();

	void bookTour(int tourId);
	void showUserBookings();
	void showMyProfile();

	void showTourListByHotel(int id);

	void addReview(int hotelId);

	void sortTours(int i, Vector<Tour> &tours);
	void sortHotels(int i, Vector<Hotel> &tours);
	UserMenu(int id) { 
		service = Service::getInstance();
		this->userId = id; };
	~UserMenu() {};
};

