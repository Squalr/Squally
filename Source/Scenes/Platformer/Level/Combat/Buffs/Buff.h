#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class HackableCode;
class PlatformerEntity;

class Buff : public SmartNode
{
protected:
	Buff(PlatformerEntity* caster, PlatformerEntity* target);
	~Buff();

	void onEnter() override;
	void initializeListeners() override;
	virtual void registerHackables();
	virtual void onTimelineReset(bool wasInterrupt);
	virtual void onBeforeDamageTaken(int* damageOrHealing, bool* blocked, std::function<void()> handleCallback);
	virtual void onBeforeDamageDelt(int* damageOrHealing, std::function<void()> handleCallback);
	void removeBuff();

	void enableClippy();
	void disableClippy();

	bool showClippy;

	PlatformerEntity* caster;
	PlatformerEntity* target;
	std::vector<HackableCode*> hackables;

private:
	typedef SmartNode super;
	
	void unregisterHackables();
};
