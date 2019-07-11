#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"

class GameObject;

class IsometricEntityDeserializer : public ObjectDeserializer
{
public:
	static IsometricEntityDeserializer* create();
	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;

	static const std::string MapKeyTypeEntity;

private:
	typedef ObjectDeserializer super;

	IsometricEntityDeserializer();
	~IsometricEntityDeserializer();

	std::map<std::string, std::function<GameObject*(cocos2d::ValueMap)>> deserializers;
};
