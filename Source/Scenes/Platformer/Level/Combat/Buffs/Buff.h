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
	Buff(PlatformerEntity* target, std::string iconResource, int stacks = 1, float tickDuration = Buff::TICK_NONE, float duration = Buff::DURATION_INFINITE);
	~Buff();

	void onEnter() override;
	virtual void registerHackables();
	virtual void unregisterHackables();
	virtual void tick();

	PlatformerEntity* target;
	std::vector<HackableCode*> hackables;

	static const float TICK_NONE;
	static const float DURATION_INFINITE;

private:
	typedef SmartNode super;

	int stacks;
	float tickDuration;
	float duration;
	cocos2d::Sprite* iconFrame;
	cocos2d::Sprite* icon;
};
