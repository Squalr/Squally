#pragma once

#include "Engine/SmartNode.h"
#include "Events/CombatEvents.h"

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

	void setBuffIndex(int index, int maxIndex);
	bool hasBuffIcon();
	void elapse(float dt);
	float getRemainingDuration();
	BuffData getBuffData();
	void setRemoveBuffCallback(std::function<void()> removeBuffCallback);
	void removeBuff();
	void registerClippyOnto(std::string identifier, std::function<Clippy*()> clippyFunc);

protected:

	Buff(PlatformerEntity* caster, PlatformerEntity* owner, std::string buffIconResource, AbilityType abilityType, BuffData buffData);
	virtual ~Buff();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	virtual void registerHackables();
	virtual void onTimelineReset(bool wasInterrupt);
	virtual void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback);
	virtual void onBeforeDamageTaken(CombatEvents::ModifyableDamageOrHealing damageOrHealing);
	virtual void onBeforeDamageDelt(CombatEvents::ModifyableDamageOrHealing damageOrHealing);
	virtual void onAfterDamageTaken(CombatEvents::DamageOrHealing damageOrHealing);
	virtual void onAfterDamageDelt(CombatEvents::DamageOrHealing damageOrHealing);
	virtual void onBeforeHealingTaken(CombatEvents::ModifyableDamageOrHealing damageOrHealing);
	virtual void onBeforeHealingDelt(CombatEvents::ModifyableDamageOrHealing damageOrHealing);

	BuffData buffData;
	PlatformerEntity* caster;
	PlatformerEntity* owner;
	std::vector<HackableCode*> hackables;
	AbilityType abilityType;

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
