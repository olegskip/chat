#include "multiple_responses_types.h"

bool doesEnumHaveState(RequestsTypes mainEnum, RequestsTypes state) noexcept
{
	const int mainEnumInt = static_cast<int>(mainEnum), secondInt = static_cast<int>(state);
	return mainEnumInt == 0 || mainEnumInt == (mainEnumInt & secondInt);
}

void addStateToEnum(RequestsTypes &mainEnum, RequestsTypes stateToAdd) noexcept
{
	mainEnum = static_cast<RequestsTypes>(static_cast<int>(mainEnum) | static_cast<int>(stateToAdd));
}

void removeStateFromEnum(RequestsTypes &mainEnum, RequestsTypes stateToRemove) noexcept
{
	mainEnum = static_cast<RequestsTypes>(static_cast<int>(mainEnum) ^ static_cast<int>(stateToRemove));
}

void clearEnum(RequestsTypes &mainEnum) noexcept
{
	mainEnum = static_cast<RequestsTypes>(0);
}
