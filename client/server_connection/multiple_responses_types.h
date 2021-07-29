#ifndef NEEDED_RESPONSE_TYPES_H
#define NEEDED_RESPONSE_TYPES_H

#include "requests_types.h"

/*
 * The client can send several identical requests to the server(e.g. the server didn't answer the previous ones)
 * But the user doesn't want to wait so he decided to do something else(e.g. he doesn't want anymore to log in, he wants to sign)
 * So the client doesn't need these packets anymore, therefore there is no need to process them
 * In other words, the client process only needed requests and these functions help to contain multiple request's types
 */

bool doesEnumHaveState(RequestsTypes mainEnum, RequestsTypes state) noexcept;
void addStateToEnum(RequestsTypes &mainEnum, RequestsTypes stateToAdd) noexcept;
void removeStateFromEnum(RequestsTypes &mainEnum, RequestsTypes stateToRemove) noexcept;
void clearEnum(RequestsTypes &mainEnum) noexcept;

#endif // NEEDED_RESPONSE_TYPES_H
