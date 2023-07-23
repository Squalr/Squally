#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class WorldSound;

class DistractVfx : public Buff
{
public:
	static DistractVfx* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string DistractVfxIdentifier;

protected:
	DistractVfx(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~DistractVfx();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef Buff super;

	void applyDistractVfx();
	
	cocos2d::Sprite* bell = nullptr;
	WorldSound* bellSfx = nullptr;
	
	static const float Duration;
};
