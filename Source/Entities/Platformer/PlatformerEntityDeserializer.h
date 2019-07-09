#pragma once

#include "Engine/Maps/ObjectDeserializer.h"

class GameObject;

class PlatformerEntityDeserializer : public ObjectDeserializer
{
public:
	static PlatformerEntityDeserializer* create();
	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;

	static const std::string KeyTypeEntity;

private:
	typedef ObjectDeserializer super;
	PlatformerEntityDeserializer();
	virtual ~PlatformerEntityDeserializer();

	std::map<std::string, std::function<GameObject*(cocos2d::ValueMap)>> deserializers;
};
