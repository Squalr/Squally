#include "CagedDog.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedDog::MapKeyCagedDog = "caged-dog";

CagedDog* CagedDog::create(ValueMap& initProperties)
{
	CagedDog* instance = new CagedDog(initProperties);

	instance->autorelease();

	return instance;
}

CagedDog::CagedDog(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalDog)
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
