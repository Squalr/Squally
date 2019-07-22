#include "CagedYeti.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedYeti::MapKeyCagedYeti = "caged-yeti";

CagedYeti* CagedYeti::create(ValueMap& initProperties)
{
	CagedYeti* instance = new CagedYeti(initProperties);

	instance->autorelease();

	return instance;
}

CagedYeti::CagedYeti(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalYeti)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Yeti);

	this->animalNode->addChild(this->animalSprite);
}

CagedYeti::~CagedYeti()
{
}

void CagedYeti::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
