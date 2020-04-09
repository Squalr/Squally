#include "CagedSkunk.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedSkunk::MapKey = "caged-skunk";

CagedSkunk* CagedSkunk::create(ValueMap& properties)
{
	CagedSkunk* instance = new CagedSkunk(properties);

	instance->autorelease();

	return instance;
}

CagedSkunk::CagedSkunk(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalSkunk)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Skunk);

	this->animalNode->addChild(this->animalSprite);
}

CagedSkunk::~CagedSkunk()
{
}

void CagedSkunk::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedSkunk::getAnimalName()
{
	return nullptr;
}

std::string CagedSkunk::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Skunk;
}
