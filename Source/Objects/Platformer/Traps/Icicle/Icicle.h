#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class Icicle : public HackableObject
{
public:
	static Icicle* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Icicle(cocos2d::ValueMap& properties);
	virtual ~Icicle();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void applyGravity();

	cocos2d::Sprite* sprite;
	CollisionObject* collision;
};
