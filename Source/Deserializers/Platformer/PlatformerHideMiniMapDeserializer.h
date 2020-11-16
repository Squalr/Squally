#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class PlatformerHideMiniMapDeserializer : public PropertyDeserializer
{
public:
	static PlatformerHideMiniMapDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

protected:
	PlatformerHideMiniMapDeserializer();
	virtual ~PlatformerHideMiniMapDeserializer();

private:
	typedef PropertyDeserializer super;

	static const std::string PropertyHideMiniMap;
};
