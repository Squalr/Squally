#pragma once

#include "cocos/base/CCValue.h"

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class PlatformerMiniMapRequiredItemDeserializer : public PropertyDeserializer
{
public:
	static PlatformerMiniMapRequiredItemDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

protected:
	PlatformerMiniMapRequiredItemDeserializer();
	virtual ~PlatformerMiniMapRequiredItemDeserializer();

private:
	typedef PropertyDeserializer super;

	static const std::string PropertyMiniMapRequiredItem;
};
