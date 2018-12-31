#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"

class IsometricObjectDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	typedef GlobalNode super;
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static IsometricObjectDeserializer* instance;
	static const std::string KeyTypeIsometricObject;
};
