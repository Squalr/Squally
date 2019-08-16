#include "CagedBear.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedBear::MapKeyCagedBear = "caged-bear";

CagedBear* CagedBear::create(ValueMap& properties)
{
	CagedBear* instance = new CagedBear(properties);

	instance->autorelease();

	return instance;
}

CagedBear::CagedBear(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalBear)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Bear);

	this->animalNode->addChild(this->animalSprite);
}

CagedBear::~CagedBear()
{
}

void CagedBear::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedBear::getAnimalName()
{
	return nullptr;
}

std::string CagedBear::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Bear;
}
