#include "CagedHedgehog.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedHedgehog::MapKeyCagedHedgehog = "caged-hedgehog";

CagedHedgehog* CagedHedgehog::create(ValueMap& properties)
{
	CagedHedgehog* instance = new CagedHedgehog(properties);

	instance->autorelease();

	return instance;
}

CagedHedgehog::CagedHedgehog(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalHedgehog)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Hedgehog);

	this->animalNode->addChild(this->animalSprite);
}

CagedHedgehog::~CagedHedgehog()
{
}

void CagedHedgehog::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedHedgehog::getAnimalName()
{
	return nullptr;
}

std::string CagedHedgehog::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Hedgehog;
}
