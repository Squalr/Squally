#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class BackgroundDeserializer : public PropertyDeserializer
{
public:
	static BackgroundDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;
	std::string getPropertyDeserializerKey() override;

private:
	typedef PropertyDeserializer super;
	BackgroundDeserializer();
	~BackgroundDeserializer();

	static const std::string MapKeyBackground;
};
