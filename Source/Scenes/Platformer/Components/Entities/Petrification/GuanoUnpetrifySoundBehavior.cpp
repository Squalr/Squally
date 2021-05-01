#include "GuanoUnpetrifySoundBehavior.h"

#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

GuanoUnpetrifySoundBehavior* GuanoUnpetrifySoundBehavior::create(GameObject* owner)
{
	GuanoUnpetrifySoundBehavior* instance = new GuanoUnpetrifySoundBehavior(owner);

	instance->autorelease();

	return instance;
}

GuanoUnpetrifySoundBehavior::GuanoUnpetrifySoundBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->statueBreakSound = WorldSound::create(SoundResources::Platformer_Objects_Statue_RumbleAndBreak1);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->statueBreakSound);
}

GuanoUnpetrifySoundBehavior::~GuanoUnpetrifySoundBehavior()
{
}

void GuanoUnpetrifySoundBehavior::onLoad()
{
}

void GuanoUnpetrifySoundBehavior::onDisable()
{
	super::onDisable();
}

void GuanoUnpetrifySoundBehavior::unpetrify()
{
	this->statueBreakSound->play();
}
