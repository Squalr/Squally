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
		std::string uniqueId;

		BuffData() : uniqueId("") { }
		BuffData(std::string uniqueId) : uniqueId(uniqueId) { }
	};

	BuffData getBuffData();
	void setRemoveBuffCallback(std::function<void()> removeBuffCallback);
	void removeBuff();

protected:

	Buff(PlatformerEntity* caster, PlatformerEntity* target, BuffData buffData);
	~Buff();

	void onEnter() override;
	void initializeListeners() override;
	virtual void registerHackables();
	void registerClippy(Clippy* clippy);
	virtual void onTimelineReset(bool wasInterrupt);
	virtual void onBeforeDamageTaken(int* damageOrHealing, bool* blocked, std::function<void()> handleCallback);
	virtual void onBeforeDamageDelt(int* damageOrHealing, std::function<void()> handleCallback);

	BuffData buffData;
	PlatformerEntity* caster;
	PlatformerEntity* target;
	std::vector<HackableCode*> hackables;

private:
	typedef SmartNode super;

	std::function<void()> removeBuffCallback;
	
	void unregisterHackables();
};
