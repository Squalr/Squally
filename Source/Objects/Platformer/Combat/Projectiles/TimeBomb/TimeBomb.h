#pragma once

#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"

class ConstantString;
class LocalizedLabel;
class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class ThrownObject;
class WorldSound;

class TimeBomb : public ThrownObject
{
public:
	static TimeBomb* create(PlatformerEntity* owner, PlatformerEntity* target, std::function<void()> onExplode);
	
	void runSpawnFX() override;
	void runImpactFX() override;

protected:
	TimeBomb(PlatformerEntity* owner, PlatformerEntity* target, std::function<void()> onExplode);
	virtual ~TimeBomb();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef ThrownObject super;

	void updateTimerText();
	void explode();
	void tickTimeBomb();

	bool hasExploded = false;
	int bombTick = 0;
	float elapsed = 0.0f;

	SmartAnimationSequenceNode* explosionAnim = nullptr;
	WorldSound* spawnSound = nullptr;
	WorldSound* tickSound = nullptr;
	WorldSound* tickSoundPositive = nullptr;
	WorldSound* explodeSound = nullptr;
	std::function<void()> onExplode = nullptr;

	cocos2d::Sprite* bomb = nullptr;
	cocos2d::Sprite* timerPlate = nullptr;
	LocalizedLabel* timerLabel = nullptr;
	ConstantString* minutesString = nullptr;
	ConstantString* secondsString = nullptr;

	static const float HackDuration;
	static const int TimerInitial;
	static const int TimerMax;
};
