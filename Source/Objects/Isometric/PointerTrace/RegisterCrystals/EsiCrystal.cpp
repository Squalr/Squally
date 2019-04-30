#include "EsiCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string EsiCrystal::MapKeyEsiCrystal = "esi-crystal";

EsiCrystal* EsiCrystal::create(ValueMap& initProperties)
{
	EsiCrystal* instance = new EsiCrystal(initProperties);

	instance->autorelease();

	return instance;
}

EsiCrystal::EsiCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EsiCrystal);

	this->crystalNode->addChild(this->crystal);
}

EsiCrystal::~EsiCrystal()
{
}

void EsiCrystal::onEnter()
{
	super::onEnter();
}

void EsiCrystal::initializePositions()
{
	super::initializePositions();
}
