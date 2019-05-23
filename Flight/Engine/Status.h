#pragma once
#include <string>

class Status
{
public:
	Status();
	Status(int statusCode, std::string msg) {
		StatusCode = statusCode;
		Message = msg;
	}
	~Status();

	void operator=(const Status &e) {
		StatusCode = e.StatusCode;
	}

	int StatusCode;
	std::string Message;
};
static Status NoError(200, "Success!");
static Status BadError(400, "Bad Happened!");
static Status NullPointerError(401, "Null Pointer Reference!");



