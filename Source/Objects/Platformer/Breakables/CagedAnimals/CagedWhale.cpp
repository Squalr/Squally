#include "CagedWhale.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedWhale::MapKeyCagedWhale = "caged-whale";

CagedWhale* CagedWhale::create(ValueMap& initProperties)
{
	CagedWhale* instance = new CagedWhale(initProperties);

	instance->autorelease();

	return instance;
}

CagedWhale::CagedWhale(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalWhale)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Whale);

	this->animalNode->addChild(this->animalSprite);
}

CagedWhale::~CagedWhale()
{
}

void CagedWhale::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedWhale::getAnimalName()
{
	return nullptr;
}

std::string CagedWhale::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Whale;
}
