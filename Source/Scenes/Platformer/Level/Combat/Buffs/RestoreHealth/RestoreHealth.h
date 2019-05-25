#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;

class RestoreHealth : public Buff
{
public:
	static RestoreHealth* create(PlatformerEntity* target, int healAmount);

protected:
	RestoreHealth(PlatformerEntity* target, int healAmount);
	~RestoreHealth();

	void registerHackables() override;
	void tick() override;
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();

	float duration;
	cocos2d::Sprite* iconFrame;
	cocos2d::Sprite* icon;

	static const std::string RestoreHealthIdentifier;
};
