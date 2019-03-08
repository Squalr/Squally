#pragma once

#include "Objects/Platformer/Physics/DensityObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class FloatingAsteroid : public DensityObject
{
public:
	static FloatingAsteroid* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyFloatingAsteroid;

protected:
	FloatingAsteroid(cocos2d::ValueMap& initProperties);
	virtual ~FloatingAsteroid();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	float getObjectHeight() override;

private:
	typedef DensityObject super;

	float getDensity() override;
	float getDensityNonVirtual();

	cocos2d::Sprite* sprite;
	CollisionObject* collision;
};
