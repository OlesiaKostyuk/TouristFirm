#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Review
{
	int hotelId;
	int id;
	int userId;
	string text;
	int rate;
public:
	Review() {};

	int getId() { return this->id; }
	void setId(int id) { this->id = id; }
	int getHotelId() { return this->hotelId; }
	void setHotelId(int id) { this->hotelId = id; }
	int getUserId() { return this->userId; }
	void setUserlId(int id) { this->userId = id; }
	int getRate() { return this->rate; }
	void setRate(int rate) { this->rate = rate; }
	string getText() { return this->text; }
	void setText(string text) { this->text = text; }

	friend ostream& operator<<(ostream &os, const Review &review) {
		cout << "|" << setw(5) << review.id;
		cout << "|" << setw(8) << review.userId;
		cout << "|" << setw(5) << review.rate;
		cout << "|" << setw(5) << review.text << endl;
		return os;
	}

	~Review() {};
};

