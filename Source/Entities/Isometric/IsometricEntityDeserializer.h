#pragma once

#include "Engine/GlobalNode.h"
#include "Engine/Events/DeserializationEvents.h"

class IsometricEntityDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	IsometricEntityDeserializer();
	~IsometricEntityDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static IsometricEntityDeserializer* instance;
	static const std::string KeyTypeIsometricEntity;
};
