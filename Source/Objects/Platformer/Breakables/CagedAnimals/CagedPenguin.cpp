#include "CagedPenguin.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedPenguin::MapKeyCagedPenguin = "caged-penguin";

CagedPenguin* CagedPenguin::create(ValueMap& properties)
{
	CagedPenguin* instance = new CagedPenguin(properties);

	instance->autorelease();

	return instance;
}

CagedPenguin::CagedPenguin(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalPenguin)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Penguin);

	this->animalNode->addChild(this->animalSprite);
}

CagedPenguin::~CagedPenguin()
{
}

void CagedPenguin::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedPenguin::getAnimalName()
{
	return nullptr;
}

std::string CagedPenguin::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Penguin;
}
