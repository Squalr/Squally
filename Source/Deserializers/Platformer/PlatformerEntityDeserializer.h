#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"

class GameObject;

class PlatformerEntityDeserializer : public ObjectDeserializer
{
public:
	static PlatformerEntityDeserializer* create();
	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;

	static const std::string MapKeyTypeEntity;

private:
	typedef ObjectDeserializer super;

	PlatformerEntityDeserializer();
	~PlatformerEntityDeserializer();

	std::map<std::string, std::function<GameObject*(cocos2d::ValueMap)>> deserializers;
};
