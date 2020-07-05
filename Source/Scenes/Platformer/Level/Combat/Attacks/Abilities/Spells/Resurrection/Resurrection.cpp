#include "Resurrection.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Particles/SmartParticles.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Resurrection::ResurrectionIdentifier = "resurrection";
const float Resurrection::Duration = 2.0f;

Resurrection* Resurrection::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Resurrection* instance = new Resurrection(caster, target);

	instance->autorelease();

	return instance;
}

Resurrection::Resurrection(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Holy, BuffData(Resurrection::Duration))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Resurrect);
	this->spellAura = Sprite::create(FXResources::Auras_HexagonAura);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Resurrection::~Resurrection()
{
}

void Resurrection::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));
}
