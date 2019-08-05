#include "CagedChicken.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedChicken::MapKeyCagedChicken = "caged-chicken";

CagedChicken* CagedChicken::create(ValueMap& initProperties)
{
	CagedChicken* instance = new CagedChicken(initProperties);

	instance->autorelease();

	return instance;
}

CagedChicken::CagedChicken(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalChicken)
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
