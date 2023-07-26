#pragma once

#include <map>

#include "Engine/SmartNode.h"
#include "Events/CombatEvents.h"

namespace cocos2d
{
	class Sprite;
	class Value;

	typedef std::map<std::string, Value> ValueMap;
}

class Clippy;
class HackableCode;
class PlatformerEntity;

class Buff : public SmartNode
{
public:
	struct BuffData
	{
		float duration = 0.0f;
		std::string uniqueId; // If set to non-empty string, the buff will be unique against this key.
		float priority = 0.0f;

		BuffData() : duration(-1.0f), uniqueId(""), priority(0.5f) { }
		BuffData(float duration) : duration(duration), uniqueId(""), priority(0.5f) { }
		BuffData(std::string uniqueId) : duration(-1.0f), uniqueId(uniqueId), priority(0.5f) { }
		BuffData(float duration, std::string uniqueId) : duration(duration), uniqueId(uniqueId), priority(0.5f) { }
		BuffData(float duration, std::string uniqueId, float priority) : duration(duration), uniqueId(uniqueId), priority(priority) { }
	};

	void setBuffIndex(int index, int maxIndex);
	bool hasBuffIcon();
	float getRemainingDuration();
	BuffData getBuffData();
	void setRemoveBuffCallback(std::function<void()> removeBuffCallback);
	bool removeBuff();
	void registerClippyOnto(std::string identifier, std::function<Clippy*()> clippyFunc);

protected:
	Buff(PlatformerEntity* caster, PlatformerEntity* owner, std::string buffIconResource, AbilityType abilityType, BuffData buffData);
	virtual ~Buff();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	virtual void registerHackables();
	virtual void elapse(float dt);
	virtual void onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed);
	virtual void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onAfterDamageTaken(CombatEvents::DamageOrHealingArgs* damageOrHealing);
	virtual void onAfterDamageDealt(CombatEvents::DamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeHealingDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onAfterHealingTaken(CombatEvents::DamageOrHealingArgs* damageOrHealing);
	virtual void onAfterHealingDealt(CombatEvents::DamageOrHealingArgs* damageOrHealing);
	virtual void onTimelineReset(CombatEvents::TimelineResetArgs* timelineReset);
	void toggleCanRemoveBuff(bool canRemove);

	BuffData buffData;
	PlatformerEntity* caster = nullptr;
	PlatformerEntity* owner = nullptr;
	std::vector<HackableCode*> hackables;
	AbilityType abilityType = AbilityType::Physical;

	static cocos2d::ValueMap HackStateStorage;
	
	static const std::string StateKeyDamageOrHealingPtr;
	static const std::string StateKeyOriginalDamageOrHealing;
	static const std::string StateKeyHealth;
	static const std::string StateKeyDamageDealt;
	static const std::string StateKeyDamageTaken;
	static const std::string StateKeySpeed;

private:
	typedef SmartNode super;
	friend class TimelineEntry;

	cocos2d::Node* iconContainer = nullptr;
	cocos2d::Sprite* buffGlow = nullptr;
	cocos2d::Sprite* buffIcon = nullptr;
	
	bool isBuffIconPresent = false;
	bool wasRemoved = false;
	bool isBuffRemovalDisabled = false;
	float elapsedTime = 0.0f;
	float asyncElapsedTime = 0.0f;
	void unregisterHackables();
};
