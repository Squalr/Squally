#include "CagedCat.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedCat::MapKeyCagedCat = "caged-cat";

CagedCat* CagedCat::create(ValueMap& properties)
{
	CagedCat* instance = new CagedCat(properties);

	instance->autorelease();

	return instance;
}

CagedCat::CagedCat(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalCat)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Cat);

	this->animalNode->addChild(this->animalSprite);
}

CagedCat::~CagedCat()
{
}

void CagedCat::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedCat::getAnimalName()
{
	return nullptr;
}

std::string CagedCat::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Cat;
}
