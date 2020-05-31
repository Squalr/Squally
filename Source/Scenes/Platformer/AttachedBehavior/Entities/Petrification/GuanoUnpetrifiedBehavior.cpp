#include "GuanoUnpetrifiedBehavior.h"

#include "Engine/Particles/SmartParticles.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

GuanoUnpetrifiedBehavior* GuanoUnpetrifiedBehavior::create(GameObject* owner)
{
	GuanoUnpetrifiedBehavior* instance = new GuanoUnpetrifiedBehavior(owner);

	instance->autorelease();

	return instance;
}

GuanoUnpetrifiedBehavior::GuanoUnpetrifiedBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->unpetrifyParticles = SmartParticles::create(ParticleResources::Objects_StatueBreak, SmartParticles::CullInfo(Size(113.0f, 160.0f)));
	this->statueBreakSound = WorldSound::create(SoundResources::Platformer_Objects_Statue_RumbleAndBreak);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->unpetrifyParticles);
	this->addChild(this->statueBreakSound);
}

GuanoUnpetrifiedBehavior::~GuanoUnpetrifiedBehavior()
{
}

void GuanoUnpetrifiedBehavior::onLoad()
{
}

void GuanoUnpetrifiedBehavior::onDisable()
{
	super::onDisable();
}

void GuanoUnpetrifiedBehavior::unpetrify()
{
	this->unpetrifyParticles->start();
	this->statueBreakSound->play();
}
