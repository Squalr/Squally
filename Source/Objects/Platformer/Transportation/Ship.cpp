#include "Ship.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsBody.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Ship::MapKeyShip = "ship";

Ship* Ship::create(ValueMap& initProperties)
{
	Ship* instance = new Ship(initProperties);

	instance->autorelease();

	return instance;
}

Ship::Ship(ValueMap& initProperties) : super(initProperties)
{
	this->hull = Sprite::create(ObjectResources::Transportation_Ship_Hull);
	
	this->addChild(this->hull);
}

Ship::~Ship()
{
}

void Ship::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Ship::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
}

void Ship::initializePositions()
{
	super::initializePositions();
}

void Ship::initializeListeners()
{
	super::initializeListeners();
}
