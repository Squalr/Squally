#include "CagedGiraffe.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedGiraffe::MapKeyCagedGiraffe = "caged-giraffe";

CagedGiraffe* CagedGiraffe::create(ValueMap& initProperties)
{
	CagedGiraffe* instance = new CagedGiraffe(initProperties);

	instance->autorelease();

	return instance;
}

CagedGiraffe::CagedGiraffe(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalGiraffe)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Giraffe);

	this->animalNode->addChild(this->animalSprite);
}

CagedGiraffe::~CagedGiraffe()
{
}

void CagedGiraffe::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedGiraffe::getAnimalName()
{
	return nullptr;
}

std::string CagedGiraffe::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Giraffe;
}
