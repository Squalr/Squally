#pragma once

#include "Objects/Platformer/Projectiles/Combat/ThrownObject/ThrownObject.h"

class Clippy;
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
	static TimeBomb* create(PlatformerEntity* owner, PlatformerEntity* target);
	
	void enableClippy();
	void runSpawnFX() override;
	void runImpactFX();

protected:
	TimeBomb(PlatformerEntity* owner, PlatformerEntity* target);
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

	bool hasExploded;
	int bombTick;
	float elapsed;

	Clippy* clippy;
	SmartAnimationSequenceNode* explosionAnim;
	WorldSound* spawnSound;
	WorldSound* tickSound;
	WorldSound* explodeSound;

	cocos2d::Sprite* bomb;
	cocos2d::Sprite* timerPlate;
	LocalizedLabel* timerLabel;
	ConstantString* minutesString;
	ConstantString* secondsString;

	static const float HackDuration;
	static const int TimerInitial;
	static const int TimerMax;
};
