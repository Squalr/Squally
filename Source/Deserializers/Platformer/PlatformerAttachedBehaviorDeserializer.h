#pragma once

#include "Engine/Deserializers/Properties/AttachedBehaviorDeserializer.h"

class PlatformerAttachedBehaviorDeserializer : public AttachedBehaviorDeserializer
{
public:
	static PlatformerAttachedBehaviorDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;
	std::string getPropertyDeserializerKey() override;

protected:
	PlatformerAttachedBehaviorDeserializer();
	virtual ~PlatformerAttachedBehaviorDeserializer();

private:
	typedef AttachedBehaviorDeserializer super;
};
