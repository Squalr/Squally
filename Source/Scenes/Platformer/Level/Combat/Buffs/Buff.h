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

	void setBuffIndex(int index, int maxIndex);
	bool hasBuffIcon();
	void elapse(float dt);
	float getRemainingDuration();
	BuffData getBuffData();
	void setRemoveBuffCallback(std::function<void()> removeBuffCallback);
	void removeBuff();
	void registerClippyOnto(std::string identifier, std::function<Clippy*()> clippyFunc);

protected:

	Buff(PlatformerEntity* caster, PlatformerEntity* target, std::string buffIconResource, BuffData buffData);
	virtual ~Buff();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	virtual void registerHackables();
	virtual void onTimelineReset(bool wasInterrupt);
	virtual void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback);
	virtual void onBeforeDamageTaken(volatile int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target);
	virtual void onBeforeDamageDelt(volatile int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target);
	virtual void onBeforeHealingTaken(volatile int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target);
	virtual void onBeforeHealingDelt(volatile int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target);

	BuffData buffData;
	PlatformerEntity* caster;
	PlatformerEntity* target;
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
