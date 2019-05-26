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
	virtual void onBeforeDamageTaken(int* damageOrHealing, bool* handled);
	virtual void onBeforeDamageDelt(int* damageOrHealing, bool* handled);
	void removeBuff();

	PlatformerEntity* caster;
	PlatformerEntity* target;
	std::vector<HackableCode*> hackables;

private:
	typedef SmartNode super;
	
	void unregisterHackables();
};
