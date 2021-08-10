#pragma once

#include "Engine/Deserializers/Properties/GameComponentDeserializer.h"

class PlatformerComponentDeserializer : public GameComponentDeserializer
{
public:
	static PlatformerComponentDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;
	std::string getPropertyDeserializerKey() override;

protected:
	PlatformerComponentDeserializer();
	virtual ~PlatformerComponentDeserializer();

private:
	typedef GameComponentDeserializer super;
};
