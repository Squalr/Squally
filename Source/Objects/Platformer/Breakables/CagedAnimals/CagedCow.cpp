#include "CagedCow.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedCow::MapKeyCagedCow = "caged-cow";

CagedCow* CagedCow::create(ValueMap& initProperties)
{
	CagedCow* instance = new CagedCow(initProperties);

	instance->autorelease();

	return instance;
}

CagedCow::CagedCow(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalCow)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Cow);

	this->animalNode->addChild(this->animalSprite);
}

CagedCow::~CagedCow()
{
}

void CagedCow::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
