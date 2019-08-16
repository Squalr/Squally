#include "CagedTucan.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedTucan::MapKeyCagedTucan = "caged-tucan";

CagedTucan* CagedTucan::create(ValueMap& properties)
{
	CagedTucan* instance = new CagedTucan(properties);

	instance->autorelease();

	return instance;
}

CagedTucan::CagedTucan(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalTucan)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Tucan);

	this->animalNode->addChild(this->animalSprite);
}

CagedTucan::~CagedTucan()
{
}

void CagedTucan::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedTucan::getAnimalName()
{
	return nullptr;
}

std::string CagedTucan::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Tucan;
}
