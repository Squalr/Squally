#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class WoodenCrate : public HackableObject
{
public:
	static WoodenCrate* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WoodenCrate(cocos2d::ValueMap& properties);
	virtual ~WoodenCrate();

	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	cocos2d::Sprite* box;
	CollisionObject* boxCollision;
};
