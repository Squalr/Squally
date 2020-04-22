#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class BackgroundDeserializer : public PropertyDeserializer
{
public:
	static BackgroundDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

protected:
	BackgroundDeserializer();
	virtual ~BackgroundDeserializer();

private:
	typedef PropertyDeserializer super;

	static const std::string MapKey;
};
