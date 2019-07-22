#include "CagedParrot.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedParrot::MapKeyCagedParrot = "caged-parrot";

CagedParrot* CagedParrot::create(ValueMap& initProperties)
{
	CagedParrot* instance = new CagedParrot(initProperties);

	instance->autorelease();

	return instance;
}

CagedParrot::CagedParrot(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalParrot)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Parrot);

	this->animalNode->addChild(this->animalSprite);
}

CagedParrot::~CagedParrot()
{
}

void CagedParrot::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
