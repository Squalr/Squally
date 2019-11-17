#pragma once

#include "Engine/Maps/GameObject.h"

class PhysicsInitializer : public GameObject
{
public:
	static PhysicsInitializer* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyPhysicsInitializer;

protected:
	void onEnter() override;

private:
	typedef GameObject super;
	PhysicsInitializer(cocos2d::ValueMap& properties);
	~PhysicsInitializer();

	float gravity;

	static const std::string MapKeyGravity;
	static const float DefaultGravity;
	static const float MinimumGravity;
	static const float MaximumGravity;
};
