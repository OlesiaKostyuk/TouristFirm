#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Tour
{
	int id;
	string beginDate;
	string endDate;
	int cost;
	int hotelId;
	string aviaCompanyName;
	string country;
public:
	Tour() {};

	Tour(int id, string bd, string ed, int cost, int hId, string comp, string cntr) {
		this->id = id;
		this->beginDate = bd;
		this->endDate = ed;
		this->cost = cost;
		this->hotelId = hId;
		this->aviaCompanyName = comp;
		this->country = cntr;
	};

	~Tour() {};

	int getId() { return this->id; }
	void setId(int id) { this->id = id; }
	int getHotelId() { return this->hotelId; }
	void setHotelId(int id) { this->hotelId = id; }
	string getBeginDate() { return this->beginDate; }
	void setBeginDate(string date) { this->beginDate = date; }
	string getEndDate() { return this->endDate; }
	void setEndDate(string date) { this->endDate = date; }
	int getCost() { return this->cost; }
	void setCost(int cost) { this->cost = cost; }
	string getAviaCompanyName() { return this->aviaCompanyName; }
	void setAviaCompanyName(string name) { this->aviaCompanyName = name; }
	string getCountry() { return this->country; }
	void setCountry(string country) { this->country = country; }

	friend ostream& operator<<(ostream &os, const Tour &tour) {
		cout << "|" << setw(5) << tour.id;
		cout << "|" << setw(19) << tour.country;
		cout << "|" << setw(12) << tour.beginDate;
		cout << "|" << setw(12) << tour.endDate;
		cout << "|" << setw(12) << tour.cost;
		cout << "|" << setw(12) << tour.hotelId;
		cout << "|" << setw(19) << tour.aviaCompanyName << "|" << endl;
		return os;
	}
};

