#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class User {
	int id;
	string name;
	string surname;
	string lastname;
	string phone;
	string email;
	string login;
	string passord;
	string role;
public:
	User() {}

	User(int id, string name, string surname, string lastname, string phone, string email, string login, string password, string role) {
		this->id = id;
		this->name = name;
		this->surname = surname;
		this->lastname = lastname;
		this->phone = phone;
		this->email = email;
		this->login = login;
		this->passord = passord;
		this->role = role;
	}

	void setId(int id) { this->id = id; }
	int getId() { return this->id; }
	void setName(string name) { this->name = name; }
	string getName() { return this->name; }
	void setSurname(string surname) { this->surname = surname; }
	string getSurname() { return this->surname; }
	void setLastname(string lastname) { this->lastname = lastname; }
	string getLastname() { return this->lastname; }
	void setPhone(string phone) { this->phone = phone; }
	string getPhone() { return this->phone; }
	void setEmail(string email) { this->email = email; }
	string getEmail() { return this->email; }
	void setLogin(string login) { this->login = login; }
	string getLogin() { return this->login; }
	void setPassord(string passord) { this->passord = passord; }
	string getPassord() { return this->passord; }
	void setRole(string role) { this->role = role; }
	string getRole() { return this->role; }

	friend ostream& operator<<(ostream &os, const User &user) {
		cout << "|" << setw(5) << user.id;
		cout << "|" << setw(15) << user.name;
		cout << "|" << setw(15) << user.surname;
		cout << "|" << setw(15) << user.lastname;
		cout << "|" << setw(15) << user.phone;
		cout << "|" << setw(15) << user.email << "|" << endl;
		return os;
	}

};

