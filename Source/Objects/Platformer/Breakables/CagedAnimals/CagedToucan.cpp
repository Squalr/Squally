#include "CagedToucan.h"

#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CagedToucan::MapKey = "caged-Toucan";

CagedToucan* CagedToucan::create(ValueMap& properties)
{
	CagedToucan* instance = new CagedToucan(properties);

	instance->autorelease();

	return instance;
}

CagedToucan::CagedToucan(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalToucan)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Toucan);

	this->animalNode->addChild(this->animalSprite);
}

CagedToucan::~CagedToucan()
{
}

void CagedToucan::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedToucan::getAnimalName()
{
	return Strings::Menus_Collectables_Animals_Toucan::create();
}

std::string CagedToucan::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Toucan;
}
