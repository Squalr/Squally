#include "CagedTurtle.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedTurtle::MapKeyCagedTurtle = "caged-turtle";

CagedTurtle* CagedTurtle::create(ValueMap& properties)
{
	CagedTurtle* instance = new CagedTurtle(properties);

	instance->autorelease();

	return instance;
}

CagedTurtle::CagedTurtle(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalTurtle)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Turtle);

	this->animalNode->addChild(this->animalSprite);
}

CagedTurtle::~CagedTurtle()
{
}

void CagedTurtle::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedTurtle::getAnimalName()
{
	return nullptr;
}

std::string CagedTurtle::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Turtle;
}
