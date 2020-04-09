#include "CagedChicken.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedChicken::MapKey = "caged-chicken";

CagedChicken* CagedChicken::create(ValueMap& properties)
{
	CagedChicken* instance = new CagedChicken(properties);

	instance->autorelease();

	return instance;
}

CagedChicken::CagedChicken(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalChicken)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Chicken);

	this->animalNode->addChild(this->animalSprite);
}

CagedChicken::~CagedChicken()
{
}

void CagedChicken::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedChicken::getAnimalName()
{
	return nullptr;
}

std::string CagedChicken::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Chicken;
}
