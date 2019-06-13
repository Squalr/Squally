#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"

class PlatformerObjectDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	typedef GlobalNode super;
	PlatformerObjectDeserializer();
	~PlatformerObjectDeserializer();
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	std::map<std::string, std::function<SerializableObject*(cocos2d::ValueMap)>> deserializers;

	static PlatformerObjectDeserializer* instance;
	static const std::string KeyTypeObject;
};
