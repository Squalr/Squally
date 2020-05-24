#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class PlatformerCrackDeserializer : public PropertyDeserializer
{
public:
	static PlatformerCrackDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

protected:
	PlatformerCrackDeserializer();
	virtual ~PlatformerCrackDeserializer();

private:
	typedef PropertyDeserializer super;

	static const std::string MapKey;
};
