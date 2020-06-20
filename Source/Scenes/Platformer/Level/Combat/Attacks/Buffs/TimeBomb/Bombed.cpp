#include "Bombed.h"

using namespace cocos2d;

const std::string Bombed::BombedIdentifier = "strength";

Bombed* Bombed::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Bombed* instance = new Bombed(caster, target);

	instance->autorelease();

	return instance;
}

Bombed::Bombed(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Fire, BuffData(-1.0f, Bombed::BombedIdentifier))
{
}

Bombed::~Bombed()
{
}
