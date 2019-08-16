#include "CagedMountainLion.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedMountainLion::MapKeyCagedMountainLion = "caged-mountain-lion";

CagedMountainLion* CagedMountainLion::create(ValueMap& properties)
{
	CagedMountainLion* instance = new CagedMountainLion(properties);

	instance->autorelease();

	return instance;
}

CagedMountainLion::CagedMountainLion(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalMountainLion)
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

LocalizedString* CagedMountainLion::getAnimalName()
{
	return nullptr;
}

std::string CagedMountainLion::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_MountainLion;
}
