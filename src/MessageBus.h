#ifndef _MESSAGEBUS_H_
#define _MESSAGEBUS_H_

class Message;
class MessageType;
class MessageListener;

class MessageBus
{
	MessageBus(void);
	MessageBus(const MessageBus &other);
	MessageBus& operator=(const MessageBus &rhs);
	~MessageBus(void);

public:
	static void sendMessage(const Message &message);
	static void registerMessageType(const MessageType type);
	static bool subscribeMessage(MessageListener *subscriber, const MessageType type);
	
private:
	static const MessageBus m_instance;
};

#endif // _MESSAGEBUS_H_