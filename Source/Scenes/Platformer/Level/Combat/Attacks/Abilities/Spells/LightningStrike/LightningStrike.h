#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;

class LightningStrike : public Buff
{
public:
	static LightningStrike* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string LightningStrikeIdentifier;

protected:
	LightningStrike(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~LightningStrike();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef Buff super;

	void applyLightningStrike();
	
	SmartAnimationSequenceNode* spellEffect;
	
	static const float Duration;
};
