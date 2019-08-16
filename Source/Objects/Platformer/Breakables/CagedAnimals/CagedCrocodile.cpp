#include "CagedCrocodile.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedCrocodile::MapKeyCagedCrocodile = "caged-crocodile";

CagedCrocodile* CagedCrocodile::create(ValueMap& properties)
{
	CagedCrocodile* instance = new CagedCrocodile(properties);

	instance->autorelease();

	return instance;
}

CagedCrocodile::CagedCrocodile(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalCrocodile)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Crocodile);

	this->animalNode->addChild(this->animalSprite);
}

CagedCrocodile::~CagedCrocodile()
{
}

void CagedCrocodile::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedCrocodile::getAnimalName()
{
	return nullptr;
}

std::string CagedCrocodile::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Crocodile;
}
