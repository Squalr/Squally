#include "CagedRaccoon.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedRaccoon::MapKeyCagedRaccoon = "caged-raccoon";

CagedRaccoon* CagedRaccoon::create(ValueMap& initProperties)
{
	CagedRaccoon* instance = new CagedRaccoon(initProperties);

	instance->autorelease();

	return instance;
}

CagedRaccoon::CagedRaccoon(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalRaccoon)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Raccoon);

	this->animalNode->addChild(this->animalSprite);
}

CagedRaccoon::~CagedRaccoon()
{
}

void CagedRaccoon::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
