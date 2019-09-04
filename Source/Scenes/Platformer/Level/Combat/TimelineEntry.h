#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerAttack;
class PlatformerEntity;

class TimelineEntry : public SmartNode
{
public:
	static TimelineEntry* create(PlatformerEntity* entity);

	PlatformerEntity* getEntity();
	void applyDamageOrHealing(PlatformerEntity* caster, int damageOrHealing);
	void stageTarget(PlatformerEntity* target);
	void stageCast(PlatformerAttack* attack);
	void defend();
	float getProgress();
	void setProgress(float progress);
	void addTimeWithoutActions(float dt);
	void addTime(float dt);

	static const float CastPercentage;

private:
	typedef SmartNode super;
	TimelineEntry(PlatformerEntity* entity);
	virtual ~TimelineEntry() = default;

	struct DamageArgs
	{
		int damageDelta;

		DamageArgs(int damageDelta) : damageDelta(damageDelta) { }
	};

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	bool isPlayerEntry();
	void performCast();
	void tryInterrupt();
	void resetTimeline();

	PlatformerAttack* currentCast;
	PlatformerEntity* entity;
	TimelineEntry* target;
	cocos2d::Sprite* line;
	cocos2d::Sprite* circle;
	cocos2d::Sprite* emblem;
	cocos2d::Node* orphanedAttackCache;

	float speed;
	float interruptBonus;
	float progress;
	bool isBlocking;
	bool isCasting;

	static const float BaseSpeedMultiplier;
};
