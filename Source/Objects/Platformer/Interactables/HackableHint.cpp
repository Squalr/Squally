#include "HackableHint.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HackableHint::MapKeyHackableHint = "hackable-hint";

HackableHint* HackableHint::create(ValueMap& initProperties)
{
	HackableHint* instance = new HackableHint(initProperties);

	instance->autorelease();

	return instance;
}

HackableHint::HackableHint(ValueMap& initProperties) : super(initProperties)
{
	Size collisionSize = Size(this->properties.at(SerializableObject::MapKeyWidth).asFloat(), this->properties.at(SerializableObject::MapKeyHeight).asFloat());
	
	this->hintCollision = CollisionObject::create(PhysicsBody::createBox(collisionSize), (CollisionType)PlatformerCollisionType::Trigger, false, false);
	this->interactMenu = InteractMenu::create(ConstantString::create("[TAB]"));

	this->addChild(this->hintCollision);
	this->addChild(this->interactMenu);
}

HackableHint::~HackableHint()
{
}

void HackableHint::onEnter()
{
	super::onEnter();
}

void HackableHint::initializePositions()
{
	super::initializePositions();
}

void HackableHint::initializeListeners()
{
	super::initializeListeners();

	this->hintCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->interactMenu->show();
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->hintCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->interactMenu->hide();
		return CollisionObject::CollisionResult::DoNothing;
	});
}
