#include "CagedMonkey.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedMonkey::MapKeyCagedMonkey = "caged-monkey";

CagedMonkey* CagedMonkey::create(ValueMap& initProperties)
{
	CagedMonkey* instance = new CagedMonkey(initProperties);

	instance->autorelease();

	return instance;
}

CagedMonkey::CagedMonkey(ValueMap& initProperties) : super(initProperties)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_MONKEY);

	this->animalNode->addChild(this->animalSprite);
}

CagedMonkey::~CagedMonkey()
{
}

void CagedMonkey::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
