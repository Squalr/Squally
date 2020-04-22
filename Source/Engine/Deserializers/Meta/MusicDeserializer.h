#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class MusicDeserializer : public PropertyDeserializer
{
public:
	static MusicDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

protected:
	MusicDeserializer();
	virtual ~MusicDeserializer();

private:
	typedef PropertyDeserializer super;

	static const std::string MapKey;
	static const std::string MapKeyDelayProperty;
};
