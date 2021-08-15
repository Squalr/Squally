#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class WorldSound;

class StoneButton : public HackableObject
{
public:
	static StoneButton* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PropertySwitch;

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

	float maxDefaultButtonPosition = 0.0f;
	cocos2d::Sprite* buttonBase = nullptr;
	cocos2d::Sprite* button = nullptr;
	CollisionObject* buttonCollision = nullptr;
	WorldSound* buttonSound = nullptr;

	bool isSwitch = false;
	bool hasCollided = false;

	static const float ButtonPressureSpeed;
	static const float ButtonPressureOffsetMin;
};
