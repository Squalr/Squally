#include "CagedReindeer.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedReindeer::MapKeyCagedReindeer = "caged-reindeer";

CagedReindeer* CagedReindeer::create(ValueMap& initProperties)
{
	CagedReindeer* instance = new CagedReindeer(initProperties);

	instance->autorelease();

	return instance;
}

CagedReindeer::CagedReindeer(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalReindeer)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Reindeer);

	this->animalNode->addChild(this->animalSprite);
}

CagedReindeer::~CagedReindeer()
{
}

void CagedReindeer::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
