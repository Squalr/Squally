#pragma once

#include "cocos/base/CCValue.h"

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class PlatformerRubberbandingDeserializer : public PropertyDeserializer
{
public:
	static PlatformerRubberbandingDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

protected:
	PlatformerRubberbandingDeserializer();
	virtual ~PlatformerRubberbandingDeserializer();

private:
	typedef PropertyDeserializer super;

	static const std::string PropertyRubberBand;
};
