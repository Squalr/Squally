#include "SuperHeat.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/FXResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNDYING 1

const std::string SuperHeat::SuperHeatIdentifier = "super-heat";
const float SuperHeat::Duration = 5.0f;

SuperHeat* SuperHeat::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	SuperHeat* instance = new SuperHeat(caster, target);

	instance->autorelease();

	return instance;
}

SuperHeat::SuperHeat(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Fire, BuffData(SuperHeat::Duration))
{
	this->spellEffect = SmartAnimationSequenceNode::create();

	this->spellEffect->setAnimationAnchor(Vec2(0.5f, 0.0f));

	this->addChild(this->spellEffect);
}

SuperHeat::~SuperHeat()
{
}

void SuperHeat::onEnter()
{
	super::onEnter();

	this->spellEffect->playAnimation(FXResources::FireOrb_ready_attack_00, 0.05f, true);
}

void SuperHeat::initializePositions()
{
	super::initializePositions();

	this->spellEffect->setPositionY(this->owner->getEntityCenterPoint().y);
}
