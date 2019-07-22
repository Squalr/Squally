#include "CagedHippo.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedHippo::MapKeyCagedHippo = "caged-hippo";

CagedHippo* CagedHippo::create(ValueMap& initProperties)
{
	CagedHippo* instance = new CagedHippo(initProperties);

	instance->autorelease();

	return instance;
}

CagedHippo::CagedHippo(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalHippo)
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
