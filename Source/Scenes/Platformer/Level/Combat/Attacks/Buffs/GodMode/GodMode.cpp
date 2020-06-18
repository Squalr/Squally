#include "GodMode.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNDYING 1

const std::string GodMode::GodModeIdentifier = "god-mode";

GodMode* GodMode::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	GodMode* instance = new GodMode(caster, target);

	instance->autorelease();

	return instance;
}

GodMode::GodMode(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Physical, BuffData(-1.0f, GodMode::GodModeIdentifier))
{
}

GodMode::~GodMode()
{
}

void GodMode::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	(*damageOrHealing->damageOrHealing) = 0;
}
