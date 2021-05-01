#pragma once

#include "Engine/Deserializers/Properties/ComponentDeserializer.h"

class PlatformerComponentDeserializer : public ComponentDeserializer
{
public:
	static PlatformerComponentDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;
	std::string getPropertyDeserializerKey() override;

protected:
	PlatformerComponentDeserializer();
	virtual ~PlatformerComponentDeserializer();

private:
	typedef ComponentDeserializer super;
};
