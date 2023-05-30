#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartAnimationSequenceNode;
class WorldSound;

class ElectricityBeam : public HackableObject
{
public:
	static ElectricityBeam* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ElectricityBeam(cocos2d::ValueMap& properties);
	virtual ~ElectricityBeam();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void toggleDisabled();
	void updateElectricityBeam();

	SmartAnimationSequenceNode* electricityAnimation = nullptr;
	CollisionObject* electricityCollision = nullptr;
	cocos2d::Sprite* ballLeft = nullptr;
	cocos2d::Sprite* ballRight = nullptr;
	WorldSound* electricitySfx = nullptr;

	volatile float currentElectricityBeamCountDown = 0.0f;
	volatile float maxElectricityBeamCountDown = 1.0f;
	volatile float storedDt = 0.0f;
	volatile bool compareResult = false;
	volatile bool isRunningAnimation = false;
	volatile bool isVertical = false;
	volatile bool isDisabled = false;
	volatile bool disableSave = false;

	static const std::string PropertyVertical;
	static const std::string PropertyDisabled;
	static const std::string PropertyDisableSave;
	static const std::string SaveKeyDisabled;
};
