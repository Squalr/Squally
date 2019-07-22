#include "CagedPenguin.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedPenguin::MapKeyCagedPenguin = "caged-penguin";

CagedPenguin* CagedPenguin::create(ValueMap& initProperties)
{
	CagedPenguin* instance = new CagedPenguin(initProperties);

	instance->autorelease();

	return instance;
}

CagedPenguin::CagedPenguin(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalPenguin)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Penguin);

	this->animalNode->addChild(this->animalSprite);
}

CagedPenguin::~CagedPenguin()
{
}

void CagedPenguin::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
