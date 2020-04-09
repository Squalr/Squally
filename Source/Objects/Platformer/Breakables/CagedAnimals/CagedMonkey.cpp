#include "CagedMonkey.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedMonkey::MapKey = "caged-monkey";

CagedMonkey* CagedMonkey::create(ValueMap& properties)
{
	CagedMonkey* instance = new CagedMonkey(properties);

	instance->autorelease();

	return instance;
}

CagedMonkey::CagedMonkey(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalMonkey)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Monkey);

	this->animalNode->addChild(this->animalSprite);
}

CagedMonkey::~CagedMonkey()
{
}

void CagedMonkey::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedMonkey::getAnimalName()
{
	return nullptr;
}

std::string CagedMonkey::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Monkey;
}
