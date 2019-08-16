#include "CagedBat.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedBat::MapKeyCagedBat = "caged-bat";

CagedBat* CagedBat::create(ValueMap& properties)
{
	CagedBat* instance = new CagedBat(properties);

	instance->autorelease();

	return instance;
}

CagedBat::CagedBat(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalBat)
{
	this->animalSprite = Sprite::create(this->getSpriteResource());

	this->animalNode->addChild(this->animalSprite);
}

CagedBat::~CagedBat()
{
}

void CagedBat::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedBat::getAnimalName()
{
	return nullptr;
}

std::string CagedBat::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Bat;
}
