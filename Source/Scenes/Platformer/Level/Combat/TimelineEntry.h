#pragma once

#include "Engine/SmartNode.h"

#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/AbilityType.h"

namespace cocos2d
{
	class Sprite;
}

class EntityCombatBehaviorBase;
class PlatformerAttack;
class PlatformerEntity;

class TimelineEntry : public SmartNode
{
public:
	static TimelineEntry* create(PlatformerEntity* entity, int spawnIndex);

	PlatformerEntity* getEntity();
	void applyDamage(CombatEvents::DamageOrHealingArgs* args);
	void applyHealing(CombatEvents::DamageOrHealingArgs* args);
	void applyManaRestore(CombatEvents::ManaRestoreOrDrainArgs* args);
	void applyManaDrain(CombatEvents::ManaRestoreOrDrainArgs* args);
	void stageTargets(std::vector<PlatformerEntity*> targets);
	void stageCast(PlatformerAttack* attack);
	std::vector<PlatformerEntity*> getStagedTargets();
	PlatformerAttack* getStagedCast();
	void defend();
	float getProgress();
	void setProgress(float progress);
	void tryPerformActions();
	void addInitSpeed(float bonus);
	void addTimeWithoutActions(float dt);
	void addTime(float dt);
	bool isPlayerEntry();
	void setSelected(bool isSelected);
	void clearBuffTargets();
	void addBuffTarget(std::string iconResource = "");
	const std::string getEmblemResource();

	static const float CastPercentage;
	static const float BaseSpeedMultiplier;
	static const int DefaultMinDamage;
	static const int DefaultMaxDamage;
	static const int DefaultMinHealing;
	static const int DefaultMaxHealing;

protected:
	TimelineEntry(PlatformerEntity* entity, int spawnIndex);
	virtual ~TimelineEntry();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef SmartNode super;

	bool isPacifist();

	void performCast();
	void tryInterrupt();
	void resetTimeline();
	void cameraFocusEntry();

	PlatformerAttack* currentCast = nullptr;
	PlatformerEntity* entity = nullptr;
	EntityCombatBehaviorBase* combatBehavior = nullptr;
	std::vector<PlatformerEntity*> targets;
	std::vector<TimelineEntry*> targetsAsEntries;
	cocos2d::Sprite* line = nullptr;
	cocos2d::Sprite* circle = nullptr;
	cocos2d::Sprite* circleSelected = nullptr;
	cocos2d::Sprite* emblem = nullptr;
	cocos2d::Sprite* overlayCircle = nullptr;
	std::vector<cocos2d::Sprite*> targetIcons;
	cocos2d::Sprite* skull = nullptr;
	cocos2d::Node* orphanedAttackCache = nullptr;

	int spawnIndex = 0;
	float interruptBonus = 0.0f;
	float progress = 0.0f;
	bool isCasting = false;
	bool isBlocking = false;
};
