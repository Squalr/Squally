#include "CagedBird.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedBird::MapKeyCagedBird = "caged-bird";

CagedBird* CagedBird::create(ValueMap& initProperties)
{
	CagedBird* instance = new CagedBird(initProperties);

	instance->autorelease();

	return instance;
}

CagedBird::CagedBird(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalBird)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Bird);

	this->animalNode->addChild(this->animalSprite);
}

CagedBird::~CagedBird()
{
}

void CagedBird::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
