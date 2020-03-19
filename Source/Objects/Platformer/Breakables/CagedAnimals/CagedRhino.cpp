#include "CagedRhino.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedRhino::MapKey = "caged-rhino";

CagedRhino* CagedRhino::create(ValueMap& properties)
{
	CagedRhino* instance = new CagedRhino(properties);

	instance->autorelease();

	return instance;
}

CagedRhino::CagedRhino(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalRhino)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Rhino);

	this->animalNode->addChild(this->animalSprite);
}

CagedRhino::~CagedRhino()
{
}

void CagedRhino::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedRhino::getAnimalName()
{
	return nullptr;
}

std::string CagedRhino::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Rhino;
}
