#include "CagedSquirrel.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedSquirrel::MapKey = "caged-squirrel";

CagedSquirrel* CagedSquirrel::create(ValueMap& properties)
{
	CagedSquirrel* instance = new CagedSquirrel(properties);

	instance->autorelease();

	return instance;
}

CagedSquirrel::CagedSquirrel(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalSquirrel)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Squirrel);

	this->animalNode->addChild(this->animalSprite);
}

CagedSquirrel::~CagedSquirrel()
{
}

void CagedSquirrel::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedSquirrel::getAnimalName()
{
	return nullptr;
}

std::string CagedSquirrel::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Squirrel;
}
