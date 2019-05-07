#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"

class GenericObjectDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	typedef GlobalNode super;
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static GenericObjectDeserializer* instance;
	static const std::string KeyTypeObject;
};
