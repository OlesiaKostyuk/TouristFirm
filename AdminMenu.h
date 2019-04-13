#include "Service.h"
class AdminMenu
{
	Service service;
public:
	void menu();
	int showMenu();

	void showAllHotels();
	void showAllTours();
	void showAllBookings();
	void showAllUsers();

	int toursMenu();
	int hotelsMenu();
	int bookingsMenu();

	void addTour();
	void deleteTour();

	AdminMenu() {};
	~AdminMenu() {};
};

