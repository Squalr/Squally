#include "CagedKoala.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedKoala::MapKey = "caged-koala";

CagedKoala* CagedKoala::create(ValueMap& properties)
{
	CagedKoala* instance = new CagedKoala(properties);

	instance->autorelease();

	return instance;
}

CagedKoala::CagedKoala(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalKoala)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Koala);

	this->animalNode->addChild(this->animalSprite);
}

CagedKoala::~CagedKoala()
{
}

void CagedKoala::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedKoala::getAnimalName()
{
	return nullptr;
}

std::string CagedKoala::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Koala;
}
