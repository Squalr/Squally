#include "CagedLizard.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedLizard::MapKeyCagedLizard = "caged-lizard";

CagedLizard* CagedLizard::create(ValueMap& initProperties)
{
	CagedLizard* instance = new CagedLizard(initProperties);

	instance->autorelease();

	return instance;
}

CagedLizard::CagedLizard(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalLizard)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Lizard);

	this->animalNode->addChild(this->animalSprite);
}

CagedLizard::~CagedLizard()
{
}

void CagedLizard::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedLizard::getAnimalName()
{
	return nullptr;
}

std::string CagedLizard::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Lizard;
}
