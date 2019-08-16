#include "CagedPig.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedPig::MapKeyCagedPig = "caged-pig";

CagedPig* CagedPig::create(ValueMap& properties)
{
	CagedPig* instance = new CagedPig(properties);

	instance->autorelease();

	return instance;
}

CagedPig::CagedPig(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalPig)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Pig);

	this->animalNode->addChild(this->animalSprite);
}

CagedPig::~CagedPig()
{
}

void CagedPig::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedPig::getAnimalName()
{
	return nullptr;
}

std::string CagedPig::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Pig;
}
