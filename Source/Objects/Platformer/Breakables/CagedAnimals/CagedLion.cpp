#include "CagedLion.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedLion::MapKeyCagedLion = "caged-lion";

CagedLion* CagedLion::create(ValueMap& properties)
{
	CagedLion* instance = new CagedLion(properties);

	instance->autorelease();

	return instance;
}

CagedLion::CagedLion(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalLion)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Lion);

	this->animalNode->addChild(this->animalSprite);
}

CagedLion::~CagedLion()
{
}

void CagedLion::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedLion::getAnimalName()
{
	return nullptr;
}

std::string CagedLion::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Lion;
}
