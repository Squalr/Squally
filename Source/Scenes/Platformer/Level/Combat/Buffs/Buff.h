#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class Clippy;
class HackableCode;
class PlatformerEntity;

class Buff : public SmartNode
{
public:
	struct BuffData
	{
		float duration;
		
		// If set to non-empty string, the buff will be unique against this key.
		std::string uniqueId;

		BuffData() : duration(-1.0f), uniqueId("") { }
		BuffData(float duration) : duration(duration), uniqueId("") { }
		BuffData(std::string uniqueId) : duration(-1.0f), uniqueId(uniqueId) { }
		BuffData(float duration, std::string uniqueId) : duration(duration), uniqueId(uniqueId) { }
	};

	enum class AbilityType
	{
		Physical,
		Holy,
		Fire,
		Frost,
		Water,
		Arcane,
		Nature,
		Shadow,
		Lightning,
	};

	struct ModifyableDamageOrHealing
	{
		int* damageOrHealing;
		int originalDamageOrHealing;
		int originalDamageOrHealingBeforeBuffs;
		int originalDamageOrHealingBeforeBuffsAndStats;
		AbilityType abilityType;
		PlatformerEntity* caster;
		PlatformerEntity* target;
		std::function<void()> handleCallback;

		ModifyableDamageOrHealing(
			int* damageOrHealing,
			int originalDamageOrHealing,
			int originalDamageOrHealingBeforeBuffs,
			int originalDamageOrHealingBeforeBuffsAndStats,
			AbilityType abilityType, 
			PlatformerEntity* caster,
			PlatformerEntity* target,
			std::function<void()> handleCallback
		)
			: damageOrHealing(damageOrHealing),
				originalDamageOrHealing(originalDamageOrHealing),
				originalDamageOrHealingBeforeBuffs(originalDamageOrHealingBeforeBuffs),
				originalDamageOrHealingBeforeBuffsAndStats(originalDamageOrHealingBeforeBuffsAndStats),
				abilityType(abilityType),
				caster(caster),
				target(target),
				handleCallback(handleCallback)
		{
		}
	};

	struct DamageOrHealing
	{
		int damageOrHealing;
		int originalDamageOrHealingBeforeBuffs;
		int originalDamageOrHealingBeforeBuffsAndStats;
		AbilityType abilityType;
		PlatformerEntity* caster;
		PlatformerEntity* target;

		DamageOrHealing(
			int damageOrHealing,
			int originalDamageOrHealingBeforeBuffs,
			int originalDamageOrHealingBeforeBuffsAndStats,
			AbilityType abilityType, 
			PlatformerEntity* caster,
			PlatformerEntity* target
		)
			: damageOrHealing(damageOrHealing),
				originalDamageOrHealingBeforeBuffs(originalDamageOrHealingBeforeBuffs),
				originalDamageOrHealingBeforeBuffsAndStats(originalDamageOrHealingBeforeBuffsAndStats),
				abilityType(abilityType),
				caster(caster),
				target(target)
		{
		}
	};

	void setBuffIndex(int index, int maxIndex);
	bool hasBuffIcon();
	void elapse(float dt);
	float getRemainingDuration();
	BuffData getBuffData();
	void setRemoveBuffCallback(std::function<void()> removeBuffCallback);
	void removeBuff();
	void registerClippyOnto(std::string identifier, std::function<Clippy*()> clippyFunc);

protected:

	Buff(PlatformerEntity* caster, PlatformerEntity* owner, std::string buffIconResource, BuffData buffData);
	virtual ~Buff();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	virtual void registerHackables();
	virtual void onTimelineReset(bool wasInterrupt);
	virtual void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback);
	virtual void onBeforeDamageTaken(ModifyableDamageOrHealing damageOrHealing);
	virtual void onBeforeDamageDelt(ModifyableDamageOrHealing damageOrHealing);
	virtual void onAfterDamageTaken(DamageOrHealing damageOrHealing);
	virtual void onAfterDamageDelt(DamageOrHealing damageOrHealing);
	virtual void onBeforeHealingTaken(ModifyableDamageOrHealing damageOrHealing);
	virtual void onBeforeHealingDelt(ModifyableDamageOrHealing damageOrHealing);

	BuffData buffData;
	PlatformerEntity* caster;
	PlatformerEntity* owner;
	std::vector<HackableCode*> hackables;

private:
	typedef SmartNode super;

	std::function<void()> removeBuffCallback;
	cocos2d::Node* iconContainer;
	cocos2d::Sprite* buffGlow;
	cocos2d::Sprite* buffIcon;
	
	bool isBuffIconPresent;
	bool wasRemoved;
	float elapsedTime;
	void unregisterHackables();
};
