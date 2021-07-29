/*
 * This is a common file used for the server and the client
 * These codes are used for server-client to send responses. 
 * I don't use HTTP codes because there's no need to use so many codes.
 * List of the codes:
 * 1) Get requests:
 *	0 - bad request, the get request can't be executed
 *	1 - OK, the get request was successfully executed
 * 2) Creating an account
 *	2 - the account was created
 *	3 - the username or the password contain forbidden characters. The client and the server seem to have different requirements to the username or to the password
 *	4 - a diffent user with same username already exists
 */

#ifndef RESPONSE_CODES_H
#define RESPONSE_CODES_H

enum class ResponsesCodes
{
    UNEXPECTED_ERROR = -1,
    
	// logging in
	SUCCESSFULLY_LOGGED_IN = 0,
	NO_SUCH_USERNAME_CANNOT_LOG_IN = 1,
	INCORRECT_PASSWORD_CANNOT_LOG_IN = 2,

	// signing up
	SUCCESSFULLY_SIGNED_UP = 3,
	INVALID_USERNAME_OR_PASSWORD_TO_SIGN_UP = 4,
	USERNAME_IS_TAKEN_CANNOT_SIGN_UP = 5
};

#endif // RESPONSE_CODES_H
