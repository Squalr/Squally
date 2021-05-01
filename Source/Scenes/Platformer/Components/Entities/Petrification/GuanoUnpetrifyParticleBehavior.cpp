#include "GuanoUnpetrifyParticleBehavior.h"

#include "Engine/Particles/SmartParticles.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

GuanoUnpetrifyParticleBehavior* GuanoUnpetrifyParticleBehavior::create(GameObject* owner)
{
	GuanoUnpetrifyParticleBehavior* instance = new GuanoUnpetrifyParticleBehavior(owner);

	instance->autorelease();

	return instance;
}

GuanoUnpetrifyParticleBehavior::GuanoUnpetrifyParticleBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->unpetrifyParticles = SmartParticles::create(ParticleResources::Objects_StatueBreak, SmartParticles::CullInfo(Size(113.0f, 160.0f)));

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->unpetrifyParticles);
}

GuanoUnpetrifyParticleBehavior::~GuanoUnpetrifyParticleBehavior()
{
}

void GuanoUnpetrifyParticleBehavior::onLoad()
{
}

void GuanoUnpetrifyParticleBehavior::onDisable()
{
	super::onDisable();
}

void GuanoUnpetrifyParticleBehavior::unpetrify()
{
	this->unpetrifyParticles->start();
}
