#include "CagedRaccoon.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedRaccoon::MapKeyCagedRaccoon = "caged-raccoon";

CagedRaccoon* CagedRaccoon::create(ValueMap& properties)
{
	CagedRaccoon* instance = new CagedRaccoon(properties);

	instance->autorelease();

	return instance;
}

CagedRaccoon::CagedRaccoon(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalRaccoon)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Raccoon);

	this->animalNode->addChild(this->animalSprite);
}

CagedRaccoon::~CagedRaccoon()
{
}

void CagedRaccoon::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedRaccoon::getAnimalName()
{
	return nullptr;
}

std::string CagedRaccoon::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Raccoon;
}
