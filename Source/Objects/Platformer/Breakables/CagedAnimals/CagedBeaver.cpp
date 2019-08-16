#include "CagedBeaver.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedBeaver::MapKeyCagedBeaver = "caged-beaver";

CagedBeaver* CagedBeaver::create(ValueMap& properties)
{
	CagedBeaver* instance = new CagedBeaver(properties);

	instance->autorelease();

	return instance;
}

CagedBeaver::CagedBeaver(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalBeaver)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Beaver);

	this->animalNode->addChild(this->animalSprite);
}

CagedBeaver::~CagedBeaver()
{
}

void CagedBeaver::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedBeaver::getAnimalName()
{
	return nullptr;
}

std::string CagedBeaver::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Beaver;
}
