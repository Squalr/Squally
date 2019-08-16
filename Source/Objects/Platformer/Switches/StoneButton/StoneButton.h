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
	static StoneButton* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyStoneButton;

protected:
	StoneButton(cocos2d::ValueMap& properties);
	virtual ~StoneButton();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	std::string stoneButtonEventName;
	float maxDefaultButtonPosition;
	cocos2d::Sprite* buttonBase;
	cocos2d::Sprite* button;
	CollisionObject* buttonCollision;

	static const float ButtonPressureSpeed;
	static const float ButtonPressureOffsetMin;
};
