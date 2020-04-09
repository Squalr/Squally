#include "CagedDuck.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedDuck::MapKey = "caged-duck";

CagedDuck* CagedDuck::create(ValueMap& properties)
{
	CagedDuck* instance = new CagedDuck(properties);

	instance->autorelease();

	return instance;
}

CagedDuck::CagedDuck(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalDuck)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Duck);

	this->animalNode->addChild(this->animalSprite);
}

CagedDuck::~CagedDuck()
{
}

void CagedDuck::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedDuck::getAnimalName()
{
	return nullptr;
}

std::string CagedDuck::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Duck;
}
