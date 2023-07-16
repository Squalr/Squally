#include "DistractVfx.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DistractVfx::DistractVfxIdentifier = "distract";
const float DistractVfx::Duration = 5.0f;

DistractVfx* DistractVfx::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	DistractVfx* instance = new DistractVfx(caster, target);

	instance->autorelease();

	return instance;
}

DistractVfx::DistractVfx(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Physical, BuffData(DistractVfx::Duration))
{
	this->bell = Sprite::create(FXResources::Bell_Bell);
	this->bellSfx = WorldSound::create(SoundResources::Hand_Bell1);

	this->bell->setScale(0.75f);

	this->addChild(this->bell);
	this->addChild(this->bellSfx);
}

DistractVfx::~DistractVfx()
{
}

void DistractVfx::onEnter()
{
	super::onEnter();

	this->applyDistractVfx();
}

void DistractVfx::initializePositions()
{
	super::initializePositions();

	this->bell->setPositionY(this->owner->getEntityTopPointRelative().y + 64.0f);
}

void DistractVfx::applyDistractVfx()
{
	const float RotationSpeed = 0.15f;
	const float RotationDelta = 30.0f;

	this->bellSfx->play();

	this->bell->runAction(Sequence::create(
		RotateTo::create(RotationSpeed / 2.0f, RotationDelta / 2.0f),
		EaseSineInOut::create(RotateTo::create(RotationSpeed, -RotationDelta)),
		EaseSineInOut::create(RotateTo::create(RotationSpeed, RotationDelta)),
		EaseSineInOut::create(RotateTo::create(RotationSpeed, -RotationDelta)),
		EaseSineInOut::create(RotateTo::create(RotationSpeed, RotationDelta)),
		CallFunc::create([=]()
		{
			this->bell->runAction(FadeTo::create(0.25f, 0));
		}),
		nullptr
	));
}
