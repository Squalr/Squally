#include "CagedMouse.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedMouse::MapKeyCagedMouse = "caged-mouse";

CagedMouse* CagedMouse::create(ValueMap& initProperties)
{
	CagedMouse* instance = new CagedMouse(initProperties);

	instance->autorelease();

	return instance;
}

CagedMouse::CagedMouse(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalMouse)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Mouse);

	this->animalNode->addChild(this->animalSprite);
}

CagedMouse::~CagedMouse()
{
}

void CagedMouse::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedMouse::getAnimalName()
{
	return nullptr;
}

std::string CagedMouse::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Mouse;
}
