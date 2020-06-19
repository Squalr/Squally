#pragma once

#include "Engine/SmartNode.h"

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
	void applyDamage(PlatformerEntity* caster, int damage, bool disableBuffProcessing, AbilityType abilityType);
	void applyHealing(PlatformerEntity* caster, int healing, bool disableBuffProcessing, AbilityType abilityType);
	void applyManaRestore(PlatformerEntity* caster, int manaGain, bool disableBuffProcessing, AbilityType abilityType);
	void applyManaDrain(PlatformerEntity* caster, int manaGain, bool disableBuffProcessing, AbilityType abilityType);
	void stageTargets(std::vector<PlatformerEntity*> targets);
	void stageCast(PlatformerAttack* attack);
	std::vector<PlatformerEntity*> getStagedTargets();
	PlatformerAttack* getStagedCast();
	void defend();
	float getProgress();
	void setProgress(float progress);
	void tryPerformActions();
	void addTimeWithoutActions(float dt);
	void addTime(float dt);
	bool isPlayerEntry();
	void setSelected(bool isSelected);
	void clearBuffTargets();
	void addBuffTarget(std::string iconResource = "");

	static const float CastPercentage;
	static const float BaseSpeedMultiplier;

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

	struct DamageArgs
	{
		int damageDealta;

		DamageArgs(int damageDealta) : damageDealta(damageDealta) { }
	};

	void performCast();
	void tryInterrupt();
	void resetTimeline();
	void cameraFocusEntry();

	PlatformerAttack* currentCast;
	PlatformerEntity* entity;
	EntityCombatBehaviorBase* combatBehavior;
	std::vector<PlatformerEntity*> targets;
	std::vector<TimelineEntry*> targetsAsEntries;
	cocos2d::Sprite* line;
	cocos2d::Sprite* circle;
	cocos2d::Sprite* circleSelected;
	cocos2d::Sprite* emblem;
	cocos2d::Sprite* overlayCircle;
	std::vector<cocos2d::Sprite*> targetIcons;
	cocos2d::Sprite* skull;
	cocos2d::Node* orphanedAttackCache;

	int spawnIndex;
	float interruptBonus;
	float progress;
	bool isCasting;
	bool isBlocking;
};
