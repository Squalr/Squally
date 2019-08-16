#include "CagedPanda.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedPanda::MapKeyCagedPanda = "caged-panda";

CagedPanda* CagedPanda::create(ValueMap& properties)
{
	CagedPanda* instance = new CagedPanda(properties);

	instance->autorelease();

	return instance;
}

CagedPanda::CagedPanda(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalPanda)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Panda);

	this->animalNode->addChild(this->animalSprite);
}

CagedPanda::~CagedPanda()
{
}

void CagedPanda::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedPanda::getAnimalName()
{
	return nullptr;
}

std::string CagedPanda::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Panda;
}
