#include "CagedTiger.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedTiger::MapKeyCagedTiger = "caged-tiger";

CagedTiger* CagedTiger::create(ValueMap& initProperties)
{
	CagedTiger* instance = new CagedTiger(initProperties);

	instance->autorelease();

	return instance;
}

CagedTiger::CagedTiger(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalTiger)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Tiger);

	this->animalNode->addChild(this->animalSprite);
}

CagedTiger::~CagedTiger()
{
}

void CagedTiger::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedTiger::getAnimalName()
{
	return nullptr;
}

std::string CagedTiger::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Tiger;
}
