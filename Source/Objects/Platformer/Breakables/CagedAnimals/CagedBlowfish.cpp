#include "CagedBlowfish.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedBlowfish::MapKeyCagedBlowfish = "caged-blowfish";

CagedBlowfish* CagedBlowfish::create(ValueMap& initProperties)
{
	CagedBlowfish* instance = new CagedBlowfish(initProperties);

	instance->autorelease();

	return instance;
}

CagedBlowfish::CagedBlowfish(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalBlowfish)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Blowfish);

	this->animalNode->addChild(this->animalSprite);
}

CagedBlowfish::~CagedBlowfish()
{
}

void CagedBlowfish::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
