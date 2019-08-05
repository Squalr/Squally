#include "CagedSheep.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedSheep::MapKeyCagedSheep = "caged-sheep";

CagedSheep* CagedSheep::create(ValueMap& initProperties)
{
	CagedSheep* instance = new CagedSheep(initProperties);

	instance->autorelease();

	return instance;
}

CagedSheep::CagedSheep(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalSheep)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Sheep);

	this->animalNode->addChild(this->animalSprite);
}

CagedSheep::~CagedSheep()
{
}

void CagedSheep::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedSheep::getAnimalName()
{
	return nullptr;
}

std::string CagedSheep::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Sheep;
}
