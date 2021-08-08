/*
 * This is a common file used for the server and the client
 * These codes are used for server-client to send responses. 
 * I don't use HTTP codes because there's no need to use so many codes.
 */

#ifndef RESPONSE_CODES_H
#define RESPONSE_CODES_H

enum class ResponsesCodes
{
    UNEXPECTED_ERROR = -1,
    
	// logging in
	SUCCESSFULLY_LOGGED_IN,
	NO_SUCH_USERNAME_CANNOT_LOG_IN,
	INCORRECT_PASSWORD_CANNOT_LOG_IN,

	// signing up
	SUCCESSFULLY_SIGNED_UP,
	INVALID_USERNAME_OR_PASSWORD_TO_SIGN_UP,
	USERNAME_IS_TAKEN_CANNOT_SIGN_UP,

	// messages
	SUCCESSFULLY_LOADED_MORE_MESSAGES,
	// when a user scrolls up and want more messages, but there are none
	THERE_ARE_NO_MORE_MESSAGES_CANT_LOAD_MORE
};

#endif // RESPONSE_CODES_H
