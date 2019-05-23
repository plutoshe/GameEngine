#pragma once
#include "Delegate.h"
#include <string>
#include <map>
#include <functional>


template<void(*T)()>
void doOp2() {
	T();
}
template<void(*T)()>
void doOp1() {
	doOp2<T>();
}




template<class ... Params>
class MessageController {
public:
	typedef std::map<std::string, Engine::MultiCastDelegate<Params ...>> handlerType;

	handlerType handlers;
	void RegisterMessageHandler(std::string i_Message, Engine::Delegate<Params ...> i_pHandler) {
		if (!handlers.count(i_Message)) {
			handlers.insert(
				handlerType::value_type(i_Message, Engine::MultiCastDelegate<Params ... >())
			);
		}
		handlers[i_Message].AddDelegate(i_pHandler);
	}
	void DeregisterMessageHandler(std::string i_Message, void* i_pHandler ) {
		if (handlers.count(i_Message)) 
			handlers[i_Message].RemoveDelegate(i_pHandler);
	}
	void SendMessage(std::string i_Message, Params ... i_Parameters) {
		if (handlers.count(i_Message)) 
			handlers[i_Message].ExecuteOnBound(i_Parameters ...);
	}
};
