#include "MayanRuneBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

MayanRuneBase::MayanRuneBase(std::string emblemResource, std::string emblemResourceDisabled) : super()
{
	this->emblemFrame = Sprite::create(ObjectResources::Doors_Mayan_GemFrame);
	this->emblemDisabled = Sprite::create(emblemResourceDisabled);
	this->emblem = Sprite::create(emblemResource);

	this->disableGem();

	this->addChild(this->emblemFrame);
	this->addChild(this->emblemDisabled);
	this->addChild(this->emblem);
}

MayanRuneBase::~MayanRuneBase()
{
}

void MayanRuneBase::runFX()
{
}

void MayanRuneBase::enableGem()
{
	this->emblemDisabled->setVisible(false);
	this->emblem->setVisible(true);
}

void MayanRuneBase::disableGem()
{
	this->emblemDisabled->setVisible(true);
	this->emblem->setVisible(false);
}
