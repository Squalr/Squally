#include "Condensation.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNDYING 1

const std::string Condensation::CondensationIdentifier = "condensation";
const float Condensation::Duration = 5.0f;

Condensation* Condensation::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Condensation* instance = new Condensation(caster, target);

	instance->autorelease();

	return instance;
}

Condensation::Condensation(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Water, BuffData(Condensation::Duration, Condensation::CondensationIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Bubbles);

	this->addChild(this->spellEffect);
}

Condensation::~Condensation()
{
}

void Condensation::onEnter()
{
	super::onEnter();

	this->spellEffect->start();
}

void Condensation::initializePositions()
{
	super::initializePositions();
}
