// This is a common file used by the server and the client
#ifndef REQUEST_TYPES_H
#define REQUEST_TYPES_H

#include <string>
#include <stdexcept>

enum class RequestsTypes
{
	// 0 is reserved
	LOG_IN = 2 << 1,
	SIGN_UP = 2 << 2
};


inline std::string convertRequestTypeToString(RequestsTypes requestType)
{
	switch(requestType) {
		case RequestsTypes::LOG_IN: return "log_in";
		case RequestsTypes::SIGN_UP: return "sign_up";
		default: throw std::logic_error("There is no string for such requestType");
	}
}

#endif // REQUEST_TYPES_H
