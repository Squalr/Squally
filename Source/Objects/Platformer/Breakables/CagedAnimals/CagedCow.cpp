#include "CagedCow.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedCow::MapKey = "caged-cow";

CagedCow* CagedCow::create(ValueMap& properties)
{
	CagedCow* instance = new CagedCow(properties);

	instance->autorelease();

	return instance;
}

CagedCow::CagedCow(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalCow)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Cow);

	this->animalNode->addChild(this->animalSprite);
}

CagedCow::~CagedCow()
{
}

void CagedCow::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedCow::getAnimalName()
{
	return nullptr;
}

std::string CagedCow::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Cow;
}
