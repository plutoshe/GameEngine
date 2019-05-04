#include <iostream>

#include "Message.h"
#include "Delegate.h"

class messageHandler1 {
public:
	int callBackCount = 0;
	void callback() {
		callBackCount++;
	}
};
int callback = 0;
void test1() {
	callback = 1;
}


bool MessageControllerUnitTest() {
	MessageController<> message1;
	MessageController<bool> message2;
	messageHandler1 handler1;
	Engine::Delegate<> ab = Engine::Delegate<>::Create<test1>();
	Engine::Delegate<> abc = Engine::Delegate<>::Create < messageHandler1, &messageHandler1::callback >(&handler1);
	message1.RegisterMessageHandler("aaa", ab);
	message1.RegisterMessageHandler("aaa", abc);
	message1.SendMessage("aaa");

	if (callback != 1 || handler1.callBackCount != 1) {
		std::cout << "Test message controller failed!" << std::endl;
		return false;
	}
	return true;
}