#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;

class Vanish : public Buff
{
public:
	static Vanish* create(PlatformerEntity* caster);

protected:
	Vanish(PlatformerEntity* caster);
	virtual ~Vanish();

	void onEnter() override;

private:
	typedef Buff super;

	cocos2d::Sprite* aura = nullptr;
};
