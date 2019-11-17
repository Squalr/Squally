#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class MusicDeserializer : public PropertyDeserializer
{
public:
	static MusicDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

private:
	typedef PropertyDeserializer super;
	MusicDeserializer();
	~MusicDeserializer();

	static const std::string MapKeyMusicProperty;
	static const std::string MapKeyDelayProperty;
};
