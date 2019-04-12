#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Hotel
{
	int id;
	string hotelName;
	int stars;
	string country;
	string town;
	string description;
public:
	Hotel() {};

	int getId() { return this->id; }
	void setId(int id) { this->id = id; }
	string getHotelName() { return this->hotelName; }
	void setHotelName(string name) { this->hotelName = name; }
	int getStars() { return this->stars; }
	void setStars(int stars) { this->stars = stars; }
	string getCountry() { return this->country; }
	void setCountry(string country) { this->country = country; }
	string getTown() { return this->town; }
	void setTown(string town) { this->town = town; }
	string getDescription() { return this->description; }
	void setDescription(string desc) { this->description = desc; }

	friend ostream& operator<<(ostream &os, const Hotel &hotel) {
		cout << "|" << setw(5) << hotel.id;
		cout << "|" << setw(15) << hotel.hotelName;
		cout << "|" << setw(10) << hotel.stars;
		cout << "|" << setw(15) << hotel.country;
		cout << "|" << setw(15) << hotel.town;
		cout << "|" << setw(30) << hotel.description << "|" << endl;
		return os;
	}

	~Hotel() {};
};

