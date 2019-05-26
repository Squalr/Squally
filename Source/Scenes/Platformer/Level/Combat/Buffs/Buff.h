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
	Buff(PlatformerEntity* target);
	~Buff();

	void onEnter() override;
	virtual void registerHackables();
	void removeBuff();

	PlatformerEntity* target;
	std::vector<HackableCode*> hackables;

private:
	typedef SmartNode super;
	
	void unregisterHackables();
};
