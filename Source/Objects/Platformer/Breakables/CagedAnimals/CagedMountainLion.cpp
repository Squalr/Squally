#include "CagedMountainLion.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedMountainLion::MapKeyCagedMountainLion = "caged-mountain-lion";

CagedMountainLion* CagedMountainLion::create(ValueMap& initProperties)
{
	CagedMountainLion* instance = new CagedMountainLion(initProperties);

	instance->autorelease();

	return instance;
}

CagedMountainLion::CagedMountainLion(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalMountainLion)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_MountainLion);

	this->animalNode->addChild(this->animalSprite);
}

CagedMountainLion::~CagedMountainLion()
{
}

void CagedMountainLion::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
