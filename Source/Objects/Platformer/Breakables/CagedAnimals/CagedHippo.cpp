#include "CagedHippo.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedHippo::MapKeyCagedHippo = "caged-hippo";

CagedHippo* CagedHippo::create(ValueMap& properties)
{
	CagedHippo* instance = new CagedHippo(properties);

	instance->autorelease();

	return instance;
}

CagedHippo::CagedHippo(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalHippo)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Hippo);

	this->animalNode->addChild(this->animalSprite);
}

CagedHippo::~CagedHippo()
{
}

void CagedHippo::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedHippo::getAnimalName()
{
	return nullptr;
}

std::string CagedHippo::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Hippo;
}
