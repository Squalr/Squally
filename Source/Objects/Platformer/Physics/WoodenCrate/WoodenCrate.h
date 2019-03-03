#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class WoodenCrate : public HackableObject
{
public:
	static WoodenCrate* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyWoodenCrate;

protected:
	WoodenCrate(cocos2d::ValueMap& initProperties);
	virtual ~WoodenCrate();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	cocos2d::Sprite* box;
	CollisionObject* boxCollision;
};
