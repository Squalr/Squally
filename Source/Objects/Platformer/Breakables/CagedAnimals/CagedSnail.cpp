#include "CagedSnail.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedSnail::MapKey = "caged-snail";

CagedSnail* CagedSnail::create(ValueMap& properties)
{
	CagedSnail* instance = new CagedSnail(properties);

	instance->autorelease();

	return instance;
}

CagedSnail::CagedSnail(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalSnail)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Snail);

	this->animalNode->addChild(this->animalSprite);
}

CagedSnail::~CagedSnail()
{
}

void CagedSnail::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedSnail::getAnimalName()
{
	return nullptr;
}

std::string CagedSnail::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Snail;
}
