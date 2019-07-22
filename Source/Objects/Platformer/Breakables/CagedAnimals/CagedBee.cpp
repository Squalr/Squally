#include "CagedBee.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedBee::MapKeyCagedBee = "caged-bee";

CagedBee* CagedBee::create(ValueMap& initProperties)
{
	CagedBee* instance = new CagedBee(initProperties);

	instance->autorelease();

	return instance;
}

CagedBee::CagedBee(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalBee)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Bee);

	this->animalNode->addChild(this->animalSprite);
}

CagedBee::~CagedBee()
{
}

void CagedBee::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
