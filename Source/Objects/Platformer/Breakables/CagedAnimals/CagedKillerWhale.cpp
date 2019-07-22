#include "CagedKillerWhale.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedKillerWhale::MapKeyCagedKillerWhale = "caged-killer-whale";

CagedKillerWhale* CagedKillerWhale::create(ValueMap& initProperties)
{
	CagedKillerWhale* instance = new CagedKillerWhale(initProperties);

	instance->autorelease();

	return instance;
}

CagedKillerWhale::CagedKillerWhale(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalKillerWhale)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_KillerWhale);

	this->animalNode->addChild(this->animalSprite);
}

CagedKillerWhale::~CagedKillerWhale()
{
}

void CagedKillerWhale::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
