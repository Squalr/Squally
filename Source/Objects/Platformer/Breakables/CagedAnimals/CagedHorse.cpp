#include "CagedHorse.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedHorse::MapKeyCagedHorse = "caged-horse";

CagedHorse* CagedHorse::create(ValueMap& initProperties)
{
	CagedHorse* instance = new CagedHorse(initProperties);

	instance->autorelease();

	return instance;
}

CagedHorse::CagedHorse(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalHorse)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Horse);

	this->animalNode->addChild(this->animalSprite);
}

CagedHorse::~CagedHorse()
{
}

void CagedHorse::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
