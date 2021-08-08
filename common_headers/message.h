#ifndef MESSAGE_H
#define MESSAGE_H

#ifdef IS_QT
	#define PlatformString QString
	#include <QString>
#else
	#define PlatformString std::string
	#include <string>
#endif

#include "queue"

class Message
{
public:
	Message(PlatformString senderUsername_, PlatformString messageText_): senderUsername(senderUsername_), messageText(messageText_) {};
	const PlatformString senderUsername, messageText;

	inline bool isValid() const noexcept
	{
		// QString and std::string have different functions to check if it's empty, so i used size()
		return senderUsername.size() > 0 && messageText.size() > 0;
	}

};

/*
 * When a user scrolls up, there can be some messages located on the server,
 * which a user doesn't have. So this variable means how many messages will be send
 * every time when a user scrolls up
 *
 */
const unsigned int newMessagesQuantity = 15;

typedef std::queue<std::shared_ptr<const Message>> MessagesPtrQueue;

#endif // MESSAGE_H
