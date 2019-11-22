#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class PlatformerTextureDeserializer : public ObjectDeserializer
{
public:
	static PlatformerTextureDeserializer* create();

	static const std::string MapKeyTypeTexture;

private:
	typedef ObjectDeserializer super;

	PlatformerTextureDeserializer();
	~PlatformerTextureDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args);

	std::map<std::string, std::function<GameObject*(cocos2d::ValueMap)>> deserializers;
};
