#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class PhysicsDeserializer : public PropertyDeserializer
{
public:
	static PhysicsDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

protected:
	PhysicsDeserializer();
	~PhysicsDeserializer();

private:
	typedef PropertyDeserializer super;

	static const std::string MapKeyPhysics;
};
