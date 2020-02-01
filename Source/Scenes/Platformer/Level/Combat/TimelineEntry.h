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
	PlatformerEntity* getStagedTarget();
	PlatformerAttack* getStagedCast();
	void defend();
	float getProgress();
	void setProgress(float progress);
	void tryPerformActions();
	void addTimeWithoutActions(float dt);
	void addTime(float dt);
	bool isPlayerEntry();

	static const float CastPercentage;

private:
	typedef SmartNode super;
	TimelineEntry(PlatformerEntity* entity);
	virtual ~TimelineEntry();

	struct DamageArgs
	{
		int damageDelta;

		DamageArgs(int damageDelta) : damageDelta(damageDelta) { }
	};

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void performCast();
	void tryInterrupt(bool blocked);
	void resetTimeline();
	void cameraFocusEntity(PlatformerEntity* entity);

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
	bool isCasting;

	static const float BaseSpeedMultiplier;
};
