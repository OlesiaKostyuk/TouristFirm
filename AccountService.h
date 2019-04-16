#pragma once
#include "Service.h"
class AccountService
{
public:

	Service *service;

	AccountService() {
		this->service = Service::getInstance();
	};
	void registration();
	void authorization();
	~AccountService() {};
};

