#pragma once
#include "Engine/GlobalNode.h"
#include "Engine/Events/DeserializationEvents.h"

class SerializableObject;

class PlatformerEntityDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();
	static PlatformerEntityDeserializer* getInstance();

	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static const std::string KeyTypeEntity;

private:
	typedef GlobalNode super;
	PlatformerEntityDeserializer();
	virtual ~PlatformerEntityDeserializer();

	void initializeListeners() override;

	static PlatformerEntityDeserializer* instance;

	std::map<std::string, std::function<SerializableObject*(cocos2d::ValueMap)>> deserializers;
};
