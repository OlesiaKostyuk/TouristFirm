#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Booking
{
	int bookId;
	int tourId;
	int userId;
	string passportNumber;
	string paymentStatus;
public:
	Booking() {};

	int getBookId() { return this->bookId; }
	void setBookId(int id) { this->bookId = id; }
	int getTourId() { return this->tourId; }
	void setTourId(int id) { this->tourId = id; }
	int getUserId() { return this->userId; }
	void setUserId(int id) { this->userId = id; }
	string getPassportNumber() { return this->passportNumber; }
	void setPassportNumber(string number) { this->passportNumber = number; }
	string getPaymentStatus() { return this->paymentStatus; }
	void setPaymentStatus(string status) { this->paymentStatus = status; }

	friend ostream& operator<<(ostream &os, const Booking &book) {
		cout << "|" << setw(10) << book.bookId;
		cout << "|" << setw(10) << book.tourId;
		cout << "|" << setw(15) << book.userId;
		cout << "|" << setw(20) << book.passportNumber;
		cout << "|" << setw(15) << book.paymentStatus << "|" << endl;
		return os;
	}

	~Booking() {};
};

