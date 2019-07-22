#include "CagedWorm.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedWorm::MapKeyCagedWorm = "caged-worm";

CagedWorm* CagedWorm::create(ValueMap& initProperties)
{
	CagedWorm* instance = new CagedWorm(initProperties);

	instance->autorelease();

	return instance;
}

CagedWorm::CagedWorm(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalWorm)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Worm);

	this->animalNode->addChild(this->animalSprite);
}

CagedWorm::~CagedWorm()
{
}

void CagedWorm::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
