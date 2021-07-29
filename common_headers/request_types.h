// This is a common file used by the server and the client
#ifndef REQUESTS_TYPES_H
#define REQUESTS_TYPES_H

#include <string>
#include <stdexcept>


enum class RequestType
{
	LOG_IN,
	SIGN_UP
};

inline std::string convertRequestTypeToString(RequestType requestType)
{
	switch(requestType) {
		case RequestType::LOG_IN: return "log_in";
		case RequestType::SIGN_UP: return "sign_up";
		default: throw std::logic_error("There is no string for such requestType");
	}
}

#endif // REQUEST_TYPES_H
