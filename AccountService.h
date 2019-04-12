#pragma once
#include "Service.h"
class AccountService
{
public:

	Service service;

	AccountService() {};
	void registration();
	void authorization();
	~AccountService() {};
};

