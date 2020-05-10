#include "Scrappy.h"

#include "cocos/math/CCGeometry.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/EntityResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Scrappy::MapKey = "scrappy";

Scrappy* Scrappy::deserialize(ValueMap& properties)
{
	Scrappy* instance = new Scrappy(properties);

	instance->autorelease();

	return instance;
}

Scrappy::Scrappy(ValueMap& properties) : super(properties,
	Scrappy::MapKey,
	EntityResources::Helpers_EndianForest_Scrappy_Animations,
	EntityResources::Helpers_EndianForest_Scrappy_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->fireAnimation = SmartAnimationSequenceNode::create();

	this->fireAnimation->setFlippedY(true);
	this->fireAnimation->setScale(0.25f);

	this->belowAnimationNode->addChild(this->fireAnimation);
}

Scrappy::~Scrappy()
{
}

void Scrappy::onEnter()
{
	super::onEnter();

	this->fireAnimation->playAnimationRepeat(FXResources::FlameSmall_FlameSmall_0000, 0.045f);
}

void Scrappy::initializePositions()
{
	super::initializePositions();
	
	this->fireAnimation->setPosition(Vec2(0.0f, -16.0f));
}

void Scrappy::initializeListeners()
{
	super::initializeListeners();
}

Vec2 Scrappy::getDialogueOffset()
{
	return Vec2(0.0f, 48.0f);
}

LocalizedString* Scrappy::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_EndianForest_Scrappy::create();
}
