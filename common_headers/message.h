#ifndef MESSAGE_H
#define MESSAGE_H

#ifdef IS_QT
	#define PlatformString QString
	#include <QString>
#else
	#define PlatformString std::string
	#include <string>
#endif

class Message
{
public:
	Message(PlatformString senderUsername_, PlatformString messageText_): senderUsername(senderUsername_), messageText(messageText_) {};
	const PlatformString senderUsername, messageText;
};

#endif // MESSAGE_H
