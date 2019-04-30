#include "EbxCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string EbxCrystal::MapKeyEbxCrystal = "ebx-crystal";

EbxCrystal* EbxCrystal::create(ValueMap& initProperties)
{
	EbxCrystal* instance = new EbxCrystal(initProperties);

	instance->autorelease();

	return instance;
}

EbxCrystal::EbxCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbxCrystal);

	this->crystalNode->addChild(this->crystal);
}

EbxCrystal::~EbxCrystal()
{
}

void EbxCrystal::onEnter()
{
	super::onEnter();
}

void EbxCrystal::initializePositions()
{
	super::initializePositions();
}
