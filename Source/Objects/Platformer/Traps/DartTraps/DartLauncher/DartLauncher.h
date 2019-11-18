#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class DartPool;
class HackableData;
class SmartAnimationNode;

class DartLauncher : public HackableObject
{
public:
	static DartLauncher* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyDartLauncher;

protected:
	DartLauncher(cocos2d::ValueMap& properties);
	~DartLauncher();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;
	void shoot(float dt);

	float launchTimer;
	float launchSpeed;
	float rotation;
	cocos2d::Node* launcherContainer;
	cocos2d::Sprite* launcherSprite;
	DartPool* dartPool;

	static const std::string PropertyLaunchSpeed;
	static const float DefaultLaunchSpeed;
	static const float LaunchCooldownMin;
	static const float LaunchCooldownMax;
};
