#include "CagedFox.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedFox::MapKeyCagedFox = "caged-fox";

CagedFox* CagedFox::create(ValueMap& properties)
{
	CagedFox* instance = new CagedFox(properties);

	instance->autorelease();

	return instance;
}

CagedFox::CagedFox(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalFox)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Fox);

	this->animalNode->addChild(this->animalSprite);
}

CagedFox::~CagedFox()
{
}

void CagedFox::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedFox::getAnimalName()
{
	return nullptr;
}

std::string CagedFox::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Fox;
}
