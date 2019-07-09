#pragma once

#include "Engine/Maps/ObjectDeserializer.h"

class PlatformerObjectDeserializer : public ObjectDeserializer
{
public:
	static PlatformerObjectDeserializer* create();

private:
	typedef ObjectDeserializer super;

	PlatformerObjectDeserializer();
	~PlatformerObjectDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args);

	std::map<std::string, std::function<GameObject*(cocos2d::ValueMap)>> deserializers;

	static const std::string KeyTypeObject;
};
