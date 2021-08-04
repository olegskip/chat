// This is a common file used by the server and the client
#ifndef REQUEST_TYPES_H
#define REQUEST_TYPES_H

#include <string>
#include <stdexcept>

enum class RequestsTypes
{
	NOTHING = 0,
	LOG_IN = 1,
	SIGN_UP = 2,

	/*
	 * If this a request is sent from the server to the client then there are new messages,
	 * If from the client to server then the client asks the server to post new messages
	 */
	NEW_MESSAGES = 4
};


#endif // REQUEST_TYPES_H
