#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class PhysicsDeserializer : public PropertyDeserializer
{
public:
	static PhysicsDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

private:
	typedef PropertyDeserializer super;
	PhysicsDeserializer();
	~PhysicsDeserializer();

	static const std::string MapKeyPhysics;
};
