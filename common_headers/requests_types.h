// This is a common file used by the server and the client
#ifndef REQUEST_TYPES_H
#define REQUEST_TYPES_H

#include <string>

enum class RequestsTypes
{
	NOTHING = 0,
	LOG_IN,
	SIGN_UP,
	NEW_MESSAGES, // when somebody sends new messages to the server
	LOAD_MORE_MESSAGES // when a user scrolls up and wants more messages to load from the server
};


#endif // REQUEST_TYPES_H
