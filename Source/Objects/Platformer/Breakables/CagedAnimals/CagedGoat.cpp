#include "CagedGoat.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedGoat::MapKeyCagedGoat = "caged-goat";

CagedGoat* CagedGoat::create(ValueMap& initProperties)
{
	CagedGoat* instance = new CagedGoat(initProperties);

	instance->autorelease();

	return instance;
}

CagedGoat::CagedGoat(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalGoat)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Goat);

	this->animalNode->addChild(this->animalSprite);
}

CagedGoat::~CagedGoat()
{
}

void CagedGoat::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedGoat::getAnimalName()
{
	return nullptr;
}

std::string CagedGoat::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Goat;
}
