#include "CagedBunny.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedBunny::MapKeyCagedBunny = "caged-bunny";

CagedBunny* CagedBunny::create(ValueMap& initProperties)
{
	CagedBunny* instance = new CagedBunny(initProperties);

	instance->autorelease();

	return instance;
}

CagedBunny::CagedBunny(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalBunny)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Bunny);

	this->animalNode->addChild(this->animalSprite);
}

CagedBunny::~CagedBunny()
{
}

void CagedBunny::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedBunny::getAnimalName()
{
	return nullptr;
}

std::string CagedBunny::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Bunny;
}
