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

	void elapse(float dt);
	float getRemainingDuration();
	BuffData getBuffData();
	void setRemoveBuffCallback(std::function<void()> removeBuffCallback);
	void removeBuff();

protected:

	Buff(PlatformerEntity* caster, PlatformerEntity* target, BuffData buffData);
	virtual ~Buff();

	void onEnter() override;
	void onExit() override;
	void initializeListeners() override;
	virtual void registerHackables();
	void registerClippy(Clippy* clippy);
	virtual void onTimelineReset(bool wasInterrupt);
	virtual void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback);
	virtual void onBeforeDamageTaken(int* damageOrHealing, std::function<void()> handleCallback);
	virtual void onBeforeDamageDelt(int* damageOrHealing, std::function<void()> handleCallback);
	virtual void onBeforeHealingTaken(int* damageOrHealing, std::function<void()> handleCallback);
	virtual void onBeforeHealingDelt(int* damageOrHealing, std::function<void()> handleCallback);

	BuffData buffData;
	PlatformerEntity* caster;
	PlatformerEntity* target;
	std::vector<HackableCode*> hackables;

private:
	typedef SmartNode super;

	std::function<void()> removeBuffCallback;
	
	bool wasRemoved;
	float elapsedTime;
	void unregisterHackables();
};
