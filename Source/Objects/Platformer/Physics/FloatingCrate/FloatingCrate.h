#pragma once

#include "Objects/Platformer/Physics/DensityObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class FloatingCrate : public DensityObject
{
public:
	static FloatingCrate* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyFloatingCrate;

protected:
	FloatingCrate(cocos2d::ValueMap& initProperties);
	virtual ~FloatingCrate();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;
	float getObjectHeight() override;

private:
	typedef DensityObject super;

	float getDensity() override;
	float getDensityNonVirtual();

	cocos2d::Sprite* sprite;
	CollisionObject* collision;
};
