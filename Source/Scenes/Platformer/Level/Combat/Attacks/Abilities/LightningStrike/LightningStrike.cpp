#include "LightningStrike.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/FXResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNDYING 1

const std::string LightningStrike::LightningStrikeIdentifier = "lightning-strike";
const float LightningStrike::Duration = 5.0f;

LightningStrike* LightningStrike::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	LightningStrike* instance = new LightningStrike(caster, target);

	instance->autorelease();

	return instance;
}

LightningStrike::LightningStrike(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Water, BuffData(LightningStrike::Duration))
{
	this->spellEffect = SmartAnimationSequenceNode::create();

	this->spellEffect->setAnimationAnchor(Vec2(0.5f, 0.0f));

	// This is a bit of hack, but this prevents the buff from being removed if the target dies
	// This allows the lightning strike animation to play out
	this->toggleCanRemoveBuff(false);

	this->addChild(this->spellEffect);
}

LightningStrike::~LightningStrike()
{
}

void LightningStrike::onEnter()
{
	super::onEnter();

	this->spellEffect->playAnimation(FXResources::Lightning_Lightning_0000, 0.05f, true, [=]()
	{
		this->toggleCanRemoveBuff(true);
		this->removeBuff();
	});
}

void LightningStrike::initializePositions()
{
	super::initializePositions();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y - 56.0f);
}
