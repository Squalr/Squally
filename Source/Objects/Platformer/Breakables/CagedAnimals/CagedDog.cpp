#include "CagedDog.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedDog::MapKey = "caged-dog";

CagedDog* CagedDog::create(ValueMap& properties)
{
	CagedDog* instance = new CagedDog(properties);

	instance->autorelease();

	return instance;
}

CagedDog::CagedDog(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalDog)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Dog);

	this->animalNode->addChild(this->animalSprite);
}

CagedDog::~CagedDog()
{
}

void CagedDog::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedDog::getAnimalName()
{
	return nullptr;
}

std::string CagedDog::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Dog;
}
