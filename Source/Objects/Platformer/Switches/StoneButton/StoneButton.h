#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class StoneButton : public HackableObject
{
public:
	static StoneButton* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyStoneButton;

protected:
	StoneButton(cocos2d::ValueMap& initProperties);
	virtual ~StoneButton();

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
