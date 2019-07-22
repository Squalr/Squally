#include "CagedPig.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedPig::MapKeyCagedPig = "caged-pig";

CagedPig* CagedPig::create(ValueMap& initProperties)
{
	CagedPig* instance = new CagedPig(initProperties);

	instance->autorelease();

	return instance;
}

CagedPig::CagedPig(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalPig)
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
