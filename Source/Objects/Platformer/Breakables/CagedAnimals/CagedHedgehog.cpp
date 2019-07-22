#include "CagedHedgehog.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedHedgehog::MapKeyCagedHedgehog = "caged-hedgehog";

CagedHedgehog* CagedHedgehog::create(ValueMap& initProperties)
{
	CagedHedgehog* instance = new CagedHedgehog(initProperties);

	instance->autorelease();

	return instance;
}

CagedHedgehog::CagedHedgehog(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalHedgehog)
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
