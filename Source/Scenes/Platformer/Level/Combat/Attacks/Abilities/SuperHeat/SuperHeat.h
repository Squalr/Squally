#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;

class SuperHeat : public Buff
{
public:
	static SuperHeat* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string SuperHeatIdentifier;

protected:
	SuperHeat(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~SuperHeat();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef Buff super;

	void applySuperHeat();
	
	SmartAnimationSequenceNode* spellEffect = nullptr;
	
	static const float Duration;
};
