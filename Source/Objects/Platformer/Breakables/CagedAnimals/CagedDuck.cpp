#include "CagedDuck.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedDuck::MapKeyCagedDuck = "caged-duck";

CagedDuck* CagedDuck::create(ValueMap& initProperties)
{
	CagedDuck* instance = new CagedDuck(initProperties);

	instance->autorelease();

	return instance;
}

CagedDuck::CagedDuck(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalDuck)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Duck);

	this->animalNode->addChild(this->animalSprite);
}

CagedDuck::~CagedDuck()
{
}

void CagedDuck::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
