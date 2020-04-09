#include "CagedSquid.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedSquid::MapKey = "caged-squid";

CagedSquid* CagedSquid::create(ValueMap& properties)
{
	CagedSquid* instance = new CagedSquid(properties);

	instance->autorelease();

	return instance;
}

CagedSquid::CagedSquid(ValueMap& properties) : super(properties, SaveKeys::SaveKeyCollectableAnimalSquid)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Squid);

	this->animalNode->addChild(this->animalSprite);
}

CagedSquid::~CagedSquid()
{
}

void CagedSquid::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}

LocalizedString* CagedSquid::getAnimalName()
{
	return nullptr;
}

std::string CagedSquid::getSpriteResource()
{
	return ObjectResources::Collectables_Animals_Squid;
}
